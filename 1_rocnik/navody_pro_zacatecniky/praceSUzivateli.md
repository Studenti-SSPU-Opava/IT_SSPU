# Prace s uživateli

## Jak se přihlásit jako root(sudo)

```
sudo su -
```

- **sudo su -** (ne jenom sudo su) znamená, že se přihlásíme jako root v home adresáři roota namísto home adresáři stávajícího uživatele

## Jak vytvořit nového uživatele

```
useradd
```
- používáno s pomocí scriptů pro vytváření velkého množství jazyků
```
adduser
```
- používáno jednoduše s terminálem pro vytvoření malého množství uživatelů

## Jak se přihlásit jako uživatel
```
su - "uživatelské jméno"

// případně (pokud uživatel nemá práva roota)
sudo su - "uživatelské jméno"
```

# Práce se skupinami (groups)

## Jak zjistit které součástí kterých skupin uživatel je

```
groups
```

## Jak vytvořit novou skupinu
praceSUzivately
```
addgroup "jmeno skupiny"
```

## Jak přidat uživatele do skupiny

```
usermod -a -G "jmeno skupiny" "uživatelské jméno"

//případně (pokud uživatel nemá práva roota)
sudo usermod -a -G "jmeno skupiny" "uživatelské jméno"
```

# Práce s právy uživatelů a skupin v adresářích

## Jak změnit vlastníka složky

```
chown "jméno uživatele"."jméno skupiny" "složka"

//případně (pokud uživatel nemá práva roota)
sudo chown "jméno uživatele"."jméno skupiny" "složka"
```

## Jak změnit práva vlastníka, skupiny a všech ostatních ve složce

```
chmod "prava vlastníka (0-7)""práva skupiny (0-7)""práva všech ostatních (0-7)" "složka"

//případně (pokud uživatel nemá práva roota)
sudo chmod "prava vlastníka (0-7)""práva skupiny (0-7)""práva všech ostatních (0-7)" "složka"
```
- příklad
```
chmod 770 /test
```
- práva se zapisují jako číslo od 0 do 7, 0 jsou žádné permise, 7 jsou všechny permise
- abychom zjistili jaká prává mají musíme číslo 0-7 převést do binárního
  - první číslice určuje, jestli můžeme číst soubory složky
  - druhá určuje, jestli můžeme vytvářet a upravovat soubory ve složce
  - třetí určuje, jestli můžeme vidět soubory ve složce
  - příklad: 5(dec) = 101(bin) = r-x = uživatel může vidět a číst soubory ve složce, nemůže je vytvářet ani upravovat   










poznámka:
díky moc za napsání návodu (bez Davida by tu nebyl! :D )