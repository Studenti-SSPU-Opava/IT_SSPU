# Jak zabezpečit ssh server


###### Změníme oprávnění pro soubor id_rsa
```
chmod 600  ~/.ssh/id_rsa
```


###### Pošleme na server náš public klíč ze složky .ssh na našem PC
```
ssh-copy-id "uzivatelskeJmeno"@"ipAdresaServeru"
```

###### Připojíme se na server pomocí ssh
```
ssh "uzivatelskeJmeno"@"ipAdresaServeru"
```

###### Otevřeme soubor sshd_config v editoru vi (pokud neumíme s VIMem, nahraďíme slovíčko "vi" slovíčkem "nano" pro otevření v editoru nano)

```
sudo vi /etc/ssh/sshd_config
```

###### Najdeme řádek "#PasswordAutentication yes" a přepíšeme ho na "PasswordAutentication no" (nezapomene oddělat #)

###### Uložíme soubor a zavřeme

###### Otevřeme soubor 50-cloud-init.conf
```
sudo vi /etc/ssh/sshd_config.d/50-cloud-init.conf
```

###### Přepíšeme "yes" na "no"

###### Zavřeme a uložíme soubor
