# Windows Příkazy

Přehled užitečných příkazů pro práci s Windows.

---

## 🖥️ Základní příkazy

### Otevřít příkazový řádek (Command Prompt)
Stiskněte `Win + R` a napište:
```bash
cmd
```

### Otevřít PowerShell
Stiskněte `Win + R` a napište:
```bash
powershell
```

### Otevřít PowerShell jako správce
Stiskněte `Win + X` a vyberte "Windows PowerShell (správce)"

---

## 📁 Správa souborů

### Zobrazit obsah složky
```bash
dir
```

### Změnit složku
```bash
cd cesta\ke\slozce
```

### Vytvořit složku
```bash
mkdir nazev-slozky
```

### Smazat soubor
```bash
del nazev-souboru.txt
```

### Smazat složku
```bash
rmdir /s nazev-slozky
```

### Kopírovat soubor
```bash
copy zdroj cil
```

### Přesunout soubor
```bash
move zdroj cil
```

---

## 🌐 Síťové příkazy

### Zobrazit IP konfiguraci
```bash
ipconfig
ipconfig /all  # Podrobné informace
```

### Test připojení
```bash
ping adresa
```

### Zobrazit síťová připojení
```bash
netstat
netstat -an  # Všechna připojení a porty
```

### Obnovit IP adresu
```bash
ipconfig /release
ipconfig /renew
```

### Vyčistit DNS cache
```bash
ipconfig /flushdns
```

---

## 💡 Užitečné tipy

- Použijte `prikaz /?` pro zobrazení nápovědy k příkazu
- Tab klávesa doplní názvy souborů a složek
- Šipka nahoru/dolů zobrazí historii příkazů
- Pro spuštění příkazu jako správce, klikněte pravým tlačítkem na CMD/PowerShell a vyberte "Spustit jako správce"
