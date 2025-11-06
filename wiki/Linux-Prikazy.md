# Linux Příkazy

Kompletní přehled užitečných příkazů pro práci s Linuxem.

## 📝 Legenda
- `""` - Vyplnit hodnotu (uvozovky nejsou součástí příkazu)
- `<>` - Volitelný parametr
- `[]` - Povinný parametr

---

## 📁 Správa souborů a složek

### Změnit aktuální složku (Change Directory)
```bash
cd cesta/k/slozce
```

### Vytvořit novou složku (Make Directory)
```bash
mkdir nazev-složky
```

### Vytvořit soubor
```bash
touch adresář/nazev-souboru.txt
```

### Zobrazit obsah složky
```bash
ls
ls -la  # Podrobný výpis včetně skrytých souborů
```

### Kopírovat soubor
```bash
cp zdroj cil
```

### Přesunout/přejmenovat soubor
```bash
mv zdroj cil
```

### Smazat soubor
```bash
rm nazev-souboru
```

### Smazat složku
```bash
rm -r nazev-složky
```

---

## 👤 Správa uživatelů a oprávnění

### Přepnout se na účet root (superuživatel)
```bash
sudo prikaz
```

### Přidat uživatele (jako root)
```bash
adduser název-uživatele
```

### Odebrat uživatele (jako root)
```bash
deluser název-uživatele
```

### Přidat skupinu (jako root)
```bash
addgroup název-skupiny
```

### Odebrat skupinu (jako root)
```bash
delgroup název-skupiny
```

### Přidat uživatele do skupiny (jako root)
```bash
usermod -a -G název-skupiny název-uživatele
```

### Změnit vlastnictví souboru
```bash
chown uzivatel:skupina cesta/k/souboru
```

### Změnit oprávnění souboru
```bash
chmod 755 cesta/k/souboru
# Číselné hodnoty: 7=rwx, 6=rw-, 5=r-x, 4=r--
```

---

## 📦 Správa balíčků (APT)

### Instalovat balíček pomocí APT
```bash
sudo apt install název-balíčku
```

### Aktualizovat seznam dostupných balíčků
```bash
sudo apt update
```

### Upgradovat nainstalované balíčky
```bash
sudo apt upgrade
```

### Hledat instalační balíček
```bash
apt-cache search název-balíčku
```

### Odinstalovat balíček
```bash
sudo apt remove název-balíčku
```

---

## 🌐 Síťové příkazy

### Zobrazit IP adresu v terminálu
```bash
ip addr show
# Nebo kratší verze
ip a
```

### Přihlásit se přes SSH na vzdálený server
```bash
ssh uzivatelske-jmeno@ip-adresa-serveru
```

### Odhlásit se ze SSH serveru
```bash
exit
```

### Kopírovat soubor na/z vzdáleného serveru
```bash
# Kopírování na server
scp cesta/k/souboru uzivatel@server:/cilova/cesta/

# Kopírování ze serveru
scp uzivatel@server:/cesta/k/souboru /lokalni/cesta/
```

### Test připojení k serveru
```bash
ping ip-adresa
```

---

## 📄 Práce s textovými soubory

### Zobrazit obsah souboru
```bash
cat nazev-souboru.txt
```

### Editovat soubor v Midnight Commander
```bash
mcedit nazev-souboru.txt
```

### Zobrazit začátek souboru
```bash
head nazev-souboru.txt
head -n 20 soubor.txt  # Prvních 20 řádků
```

### Zobrazit konec souboru
```bash
tail nazev-souboru.txt
tail -n 20 soubor.txt  # Posledních 20 řádků
```

### Sledovat obsah souboru v reálném čase
Užitečné pro sledování log souborů.
```bash
tail -f cesta/k/souboru.log
```

### Hledat text v souborech
```bash
grep "hledany-text" soubor.txt
grep -r "hledany-text" slozka/  # Rekurzivní hledání
```

---

## 🖥️ Správa procesů

### Zobrazit procesy
```bash
ps aux          # Všechny procesy
ps              # Pouze vaše procesy
ps ax           # Všechny aktuální procesy
```

### Interaktivní zobrazení procesů
```bash
top             # Základní monitoring
htop            # Vylepšená verze (může vyžadovat instalaci)
```

### Ukončit proces
```bash
kill PID                # Normální ukončení
kill -9 PID             # Vynucené ukončení
killall nazev-procesu   # Ukončit všechny procesy daného jména
```

### Změnit prioritu procesu
```bash
# nice: nastavit prioritu při spuštění (-20 až +19)
nice -n 10 prikaz

# renice: změnit prioritu běžícího procesu
renice -n 19 -p PID
```

### Sledovat I/O operace
```bash
iotop  # Zobrazí procesy podle využití disku
```

---

## 💾 Správa disků

### Zobrazit informace o blokových zařízeních
```bash
lsblk
```

### Zobrazit UUID disků
```bash
blkid
```

### Vytvořit souborový systém
```bash
mkfs.ext4 /dev/sdXY      # ext4
mkfs.vfat /dev/sdXY      # FAT32
mkfs.ntfs /dev/sdXY      # NTFS
```

### Připojit disk
```bash
mount /dev/sdXY /mnt/pripojny-bod
```

### Odpojit disk
```bash
umount /mnt/pripojny-bod
```

### Zobrazit využití disku
```bash
df -h               # Místo na discích
du -sh slozka/      # Velikost složky
```

---

## 📊 Systémové informace

### Zobrazit systémové zprávy
```bash
dmesg | more
dmesg | less
```

### Zobrazit logy přihlášení
```bash
last
```

### Zobrazit informace o systému
```bash
uname -a            # Všechny informace
lsb_release -a      # Informace o distribuci
```

### Zobrazit využití RAM
```bash
free -h
```

---

## 🔧 Pokročilé nástroje

### Screen - virtuální terminály
Vytváří virtuální terminály, které můžete odpojit a znovu připojit.
```bash
screen              # Spustit novou session
screen -d           # Odpojit session
screen -r           # Znovu připojit session
screen -ls          # Seznam sessions
```

### Spustit příkaz na pozadí
```bash
nohup prikaz &      # Příkaz poběží i po odhlášení
```

### Opakovat příkaz v intervalech
```bash
watch -n 2 prikaz   # Spustí příkaz každé 2 sekundy
```

### Vytvořit symbolický link
```bash
ln -s /cesta/k/zdroji /cesta/k/linku
```

### Spustit VS Code z terminálu
```bash
code .              # Otevře aktuální složku
code soubor.txt     # Otevře konkrétní soubor
```

---

## 💡 Užitečné tipy

- Použijte `man prikaz` pro zobrazení manuálové stránky k příkazu
- Použijte `prikaz --help` pro rychlou nápovědu
- Šipka nahoru/dolů v terminálu zobrazí historii příkazů
- Tab klávesa doplní názvy souborů a příkazů
- Ctrl+C ukončí běžící příkaz
- Ctrl+Z pozastaví běžící příkaz
