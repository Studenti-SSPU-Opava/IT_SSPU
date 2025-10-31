# ***Plánuje se předělání souboru***





# Návod na Příkazy

## Vyplnit hodnotu: ""
## Volitelný parametr: <>
## Povinný parametr: []

---

##### Klonovat repozitář z GitHubu

```bash
git clone https://github.com/"jmeno"/"nazev-repozitare"git // git@github.com:"jmeno"/"nazev-repozitare"git
```

##### Odeslat změny na GitHub

```bash
git push ![branch]
```

##### Nastavit globální e-mail pro Git

```bash
git config --global "user.email"
```

##### Nastavit globální jméno pro Git

```bash
git config --global "user.name"
```

##### Přidat všechny změny do přípravy na commit

```bash
git add .
```

##### Provést commit s komentářem k změnám

```bash
git commit
```

##### Stáhnout změny ze vzdáleného repozitáře

```bash
git pull
```

##### Kopírovat ID

```bash
ssh-copy-id "uzivatelskeJmeno"@"ipAdresaServeru"
```

# Příkazy pro Linux

##### Změnit aktuální složku (Change Directory)

```bash
cd
```

##### Vytvořit novou složku (Make Directory)

```bash
mkdir
```

##### Přepnout se na účet root (superuživatel)

```bash
sudo
```

##### Instalovat balíček pomocí APT

```bash
sudo apt install
```

##### Aktualizovat seznam dostupných balíčků

```bash
sudo apt-get update
```

##### Editovat soubor v Midnight Commander (mc)

```bash
mcedit
```

##### Zobrazit IP adresu v terminálu

```bash
ip add show
```

##### Přihlásit se přes SSH na vzdálený server

```bash
ssh "uzivatelskeJmeno"@"ipAdresaServeru"
```

##### Odhlásit se ze SSH serveru

```bash
exit
```

##### Hledat instalační balíček

```bash
apt-cache search "nazev balicku"
```

##### Kopírovat soubor na/vzdálený server nebo z/vzdáleného serveru

```bash
scp "zdrojova cesta serveru/PC" "cilova slozka serveru/PC"
```

##### Přidat uživatele (jako root)

```bash
adduser "nazevUzivatele"
```

##### Odebrat uživatele (jako root)

```bash
deluser "nazevUzivatele"
```

##### Přidat skupinu pro uživatele (jako root)

```bash
usermod -a -G "nazevUzivatele"
```

##### Odebrat skupinu pro uživatele (jako root)

```bash
usermod -G "nazevUzivatele" "nazevUzivatele"
```

##### Přidat skupinu (jako root)

```bash
addgroup "nazevSkupiny"
```

##### Odebrat skupinu (jako root)

```bash
delgroup "nazevSkupiny"
```

##### Vytvořit soubor

```bash
touch "adresar"/"nazevSouboru"
```

##### Změnit uživatelská oprávnění

```bash
chown [cislo opravneni] /[uzivatel]
```

##### Změnit vlastnictví uživatele

```bash
chown [uzivatel].[skupina] /[uzivatel]
```

##### Zobrazit systémové zprávy s nástrojem "more"

```bash
dmesg | more
```

##### Sledovat obsah posledních řádků souboru v reálném čase

```bash
tail <-f> 
```

##### Zobrazit začátek textového souboru

```bash
head
```

##### Zobrazit logy

```bash
last
```

##### Ukončit proces

```bash
kill <-9 - vyhodit z operační paměti> <cislo procesu>
```

##### Zobrazit procesy

```bash
ps aux
```

##### Zobrazit informace o blokových zařízeních

```bash
lsblk
```

##### Zobrazit jedinečné číslo harddisku

```bash
blkid
```

##### Připravit úložiště pro vytvoření oddílu

```bash
gparted
```

##### Vytvořit souborový systém

```bash
mkfs <vfat, ext, ntfs...> <zarizeni>
```
##### Vytvořit link
```bash
ln
```

# Příkazy pro Windows

##### Otevřít příkazový řádek (Command Prompt)

```bash
cmd
```




ps ax   - vypíše všechny aktuální procesy
ps   - vypíše všechny uživatelovy aktuální procesy
kill -9 PID   - "zabije" proces
kill -1   - znovunačtení konfigurace
kill -l  - vypíše všechny parametry kill
kill all -9 - zabije všechno
top - vypíše co v procesech běží (hodnota "wa" je nejdůležitější, je v třetím řádku)
    - můžete najít co nejvíce žere
sudo apt install   - instaluje něco
sudo apt update   - update 
iotop  - můžete najít co nejvíce zpomaluje pc
grep - příkaz používaný k vyhledávání a porovnávání textových vzorů v souborech obsažených v regulárních výrazech
nice, renice - (-20...+19) - nice - umožňuje nakonfigurovat hodnotu nice procesu před jeho spuštěním
                           - renice - mění hodnotu nice jednoho nebo více běžících procesů
renice -n 19 4844(
-n  - změna hodnoty
19  - hodnota na kterou to změníme 
4844  - PID procesu
)
code .  - spustí vscode
chmod  -  umožňuje správci nastavit nebo upravit oprávnění souboru
screen - vytváří virtuální terminál, dá se pak přepínat
-d  -detach
-r  -reconect
nehup  - spuštění příkazu nebo skriptu na pozadí, i když se odhlásíte z aktuální relace
watch  - může se použít k provádění příkazu v pravidelných intervalech
sudo   - oprávnění
