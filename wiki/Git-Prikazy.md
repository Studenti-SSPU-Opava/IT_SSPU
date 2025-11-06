# Git Příkazy

Kompletní přehled příkazů pro práci s Git verzovacím systémem.

## 📝 Legenda
- `""` - Vyplnit hodnotu (uvozovky nejsou součástí příkazu)
- `<>` - Volitelný parametr
- `[]` - Povinný parametr

---

## 🔧 Základní konfigurace

### Nastavit globální e-mail pro Git
Nastavení vašeho e-mailu, který bude přiřazen k vašim commitům.

```bash
git config --global user.email "vas@email.com"
```

### Nastavit globální jméno pro Git
Nastavení vašeho jména, které bude zobrazeno u vašich commitů.

```bash
git config --global user.name "Vaše Jméno"
```

---

## 📥 Klonování a stahování

### Klonovat repozitář z GitHubu
Vytvoří lokální kopii vzdáleného repozitáře.

```bash
# HTTPS metoda
git clone https://github.com/jmeno/nazev-repozitaru.git

# SSH metoda
git clone git@github.com:jmeno/nazev-repozitaru.git
```

### Stáhnout změny ze vzdáleného repozitáře
Stáhne a automaticky sloučí změny z remote repozitáře.

```bash
git pull
```

---

## 💾 Commitování změn

### Přidat všechny změny do přípravy na commit
Připraví všechny změněné soubory k commitu.

```bash
git add .
```

### Přidat konkrétní soubor
```bash
git add nazev-souboru.txt
```

### Provést commit s komentářem
Uloží změny s popisnou zprávou.

```bash
git commit -m "Popis provedených změn"
```

### Provést commit (otevře editor pro zprávu)
```bash
git commit
```

---

## 📤 Odesílání změn

### Odeslat změny na GitHub
Nahraje vaše lokální commity na remote repozitář.

```bash
# Odeslat do aktuální branch
git push

# Odeslat do konkrétní branch
git push origin nazev-branch
```

---

## 🔍 Zobrazení informací

### Zobrazit status repozitáře
```bash
git status
```

### Zobrazit historii commitů
```bash
git log
```

### Zobrazit změny v souborech
```bash
git diff
```

---

## 🌿 Práce s větvemi (branches)

### Vytvořit novou větev
```bash
git branch nazev-vetve
```

### Přepnout se na větev
```bash
git checkout nazev-vetve
```

### Vytvořit a přepnout se na novou větev
```bash
git checkout -b nazev-vetve
```

### Seznam všech větví
```bash
git branch -a
```

---

## 🔐 SSH klíče

### Kopírovat SSH klíč na server
Zkopíruje váš veřejný SSH klíč na vzdálený server pro bezpečné připojení.

```bash
ssh-copy-id uzivatelske-jmeno@ip-adresa-serveru
```

---

## 💡 Užitečné tipy

- Před každým `git push` je dobré udělat `git pull` pro stažení aktuálních změn
- Commitujte často a s popisnými zprávami
- Používejte `.gitignore` soubor pro ignorování nepotřebných souborů
