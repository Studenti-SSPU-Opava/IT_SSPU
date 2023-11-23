# Náhled do Příkazů

##### Clone repozitáře z GitHubu

```
git clone https://github.com/"jmeno"/"nazev-repozitare".git // git@github.com:"jmeno"/"nazev-repozitare".git 
```

##### Nahrát změny na GitHub

```
git push ![branch]
```

##### Nastavit globální email pro Git

```
git config --global "user.email"
```

##### Nastavit globální jméno pro Git

```
git config --global "user.name"
```

##### Přidat všechny změny do stage pro commit

```
git add .
```

##### Provést commit s komentářem ke změnám

```
git commit
```

##### Stáhnout změny ze vzdáleného repozitáře

```
git pull
```

##### Copy ID
```
ssh-copy-id "uzivatelskeJmeno"@"ipAdresaServeru"
```

# Příkazy pro Linux

##### Změnit aktuální složku (Change Directory)

```
cd
```

##### Vytvořit novou složku (Make Directory)

```
mkdir
```

##### Přepnout se na účet root (superuživatel)

```
sudo
```

##### Instalovat balíček pomocí APT

```
sudo apt install
```

##### Aktualizovat seznam dostupných balíčků

```
sudo apt-get update
```

##### Editovat soubor v Midnight Commander (mc)

```
mcedit
```

##### Zobrazit IP adresu v terminálu

```
ip add show
```

##### Login pomocí ssh do vzdáleného serveru

```
ssh "uzivatelskeJmeno"@"ipAdresaServeru"
```

##### Odpojení od ssh serveru

```
exit
```

##### Odpojení od ssh serveru

```
logout
```

##### Vyhledání instalačního balíčku

```
apt-cache search "název balíčku"
```

##### Zkopírování klíče (souboru) na ssh server

```
ssh-copy-id "uzivatelskeJmeno"@"ipAdresaServeru"
```

##### Změna uživatelského oprávnění k souboru id_rsa pouze vlastník RW

```
chmod 600  ~/.ssh/id_rsa
```

##### Otevření souboru sshd_config v editoru vi

```
sudo vi /etc/ssh/sshd_config
```

##### Otevření souboru sshd_config v editoru nano

```
sudo nano /etc/ssh/sshd_config
```
##### Otevření souboru 50-cloud-init.conf v editoru vi

```
sudo vi /etc/ssh/sshd_config.d/50-cloud-init.conf
```

##### Kopírování z PC na vzdálený server nebo ze vzdáleného serveru do PC

```
scp "zdrojová cesta serveru/PC" "cílová složka serveru/PC"
```

##### Přidání uživatele (jako root)

```
adduser "nazevUzivatele"
```

##### Odebrání uživatele (jako root)

```
deluser "nazevUzivatele"
```

##### Přidání skupiny pro uživatele (jako root)

```
usermod -a -G "nazevUzivatele"
```

##### Odebrání skupiny pro uživatele (jako root)

```
usermod -G "nazevUzivatele" "nazevUzivatele"
```

##### Přidání skupiny (jako root)

```
addgroup "nazevSkupiny"
```

##### Odebrání skupiny (jako root)

```
delgroup "nazevSkupiny"
```

##### Vytváření souboru

```
touch "adresar"/"nazevSouboru"

```
##### změna uživatelského  módu

chown [číslo oprávnění] /[uzivatel]

##### Změna vlastnictví uživatele

chown [uzivatel].[skupina] /[uzivatel]


# Příkazy pro Windows

##### Otevřít příkazový řádek (Command Prompt) - napsat do okénka, které se otevře po zadání Win + R

```
cmd
```
