#!/usr/bin/env python3
import os
import sys
import unicodedata
import re
from urllib.parse import quote

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
TEXT_EXTENSIONS = {'.md', '.html', '.htm', '.css', '.js', '.py', '.txt', '.json'}

def normalize_name(name):
    # remove diacritics
    nfkd = unicodedata.normalize('NFKD', name)
    only_ascii = nfkd.encode('ASCII', 'ignore').decode('ASCII')
    # replace spaces and non alnum with underscore
    replaced = re.sub(r"[^A-Za-z0-9._-]+", '_', only_ascii)
    # collapse multiple underscores
    replaced = re.sub(r'_+', '_', replaced)
    # remove leading/trailing underscores or dots
    replaced = replaced.strip('_.')
    # keep extension case for files
    return replaced or name


def is_text_file(path):
    _, ext = os.path.splitext(path)
    return ext.lower() in TEXT_EXTENSIONS


def build_rename_map(root):
    mapping = {}
    # walk bottom-up so we rename files before dirs
    for dirpath, dirnames, filenames in os.walk(root, topdown=False):
        # files
        for f in filenames:
            old = f
            new = normalize_name(old)
            if new != old:
                oldp = os.path.join(dirpath, old)
                newp = os.path.join(dirpath, new)
                mapping[oldp] = newp
        # dirs
        for d in dirnames:
            old = d
            new = normalize_name(old)
            if new != old:
                oldp = os.path.join(dirpath, old)
                newp = os.path.join(dirpath, new)
                mapping[oldp] = newp
    return mapping


def apply_renames(mapping):
    # ensure no conflicts: if target exists, append suffix
    applied = []
    for oldp, newp in mapping.items():
        if not os.path.exists(oldp):
            print(f"SKIP (missing): {oldp}")
            continue
        target = newp
        if os.path.exists(target):
            base, ext = os.path.splitext(target)
            i = 1
            while os.path.exists(f"{base}_{i}{ext}"):
                i += 1
            target = f"{base}_{i}{ext}"
        os.rename(oldp, target)
        applied.append((oldp, target))
        print(f"RENAMED: {oldp} -> {target}")
    return applied


def replace_in_files(mapping, root):
    # prepare simple basename mapping and urlencoded forms
    basename_map = {}
    for oldp, newp in mapping.items():
        oldb = os.path.basename(oldp)
        newb = os.path.basename(newp)
        if oldb != newb:
            basename_map[oldb] = newb
            # also add URL-encoded variant
            basename_map[quote(oldb)] = newb
            basename_map[quote(oldb).replace('%20', ' ')] = newb

    if not basename_map:
        return 0

    changed_files = 0
    for dirpath, dirnames, filenames in os.walk(root):
        for f in filenames:
            path = os.path.join(dirpath, f)
            if is_text_file(path):
                try:
                    with open(path, 'r', encoding='utf-8') as fh:
                        data = fh.read()
                except Exception:
                    continue
                newdata = data
                for oldb, newb in basename_map.items():
                    newdata = newdata.replace(oldb, newb)
                if newdata != data:
                    with open(path, 'w', encoding='utf-8') as fh:
                        fh.write(newdata)
                    changed_files += 1
                    print(f"UPDATED LINKS IN: {path}")
    return changed_files


def main():
    print(f"ROOT={ROOT}")
    mapping = build_rename_map(ROOT)
    if not mapping:
        print("No names to normalize.")
        return
    print(f"Planned renames: {len(mapping)} items")
    for oldp, newp in mapping.items():
        print(f"  {oldp} -> {newp}")

    confirm = input('Proceed with renaming? [y/N]: ').strip().lower()
    if confirm != 'y':
        print('Aborting.')
        return

    applied = apply_renames(mapping)
    print(f"Applied {len(applied)} renames.")
    changed = replace_in_files(mapping, ROOT)
    print(f"Replaced links in {changed} files.")

if __name__ == '__main__':
    main()
