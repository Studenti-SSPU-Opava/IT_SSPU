# Jak nainstalovat nginx a wordpress
## Nainstalujeme potřebné
```
sudo apt update 
sudo apt install nginx php-fpm php-mysql mysql-server php-bz2 php-zip
```
## Nakonfigurujeme nginx
```
sudo mcedit /etc/nginx/sites-enabled/default
```
1. do řádku začínajícího na index přidáme index.php
2. odkomentujeme 'location ~ \.php$ {'
3. odkomentujeme 'fastcgi_pass'
4. odkomentujeme '}', ktera ukoncuje location

## Přidáme nového uživatele do databáze
```
sudo mysql
-- vytvoříme nového uživatele
-- můžete změnit první 'student' za vaše uživatelské jméno a druhé 'student' za vaše heslo
CREATE USER 'student'@'localhost' IDENTIFIED BY 'student';
-- dáme mu všechna práva
-- **TOHLE NEDĚLEJTE POKUD NEMUSÍTE, kdokoliv kdo má přístup k tomuto uživateli může kontrolovat každou databázi na serveru
GRANT ALL PRIVILEGES ON *.* TO 'sammy'@'localhost' WITH GRANT OPTION;
-- pro jistotu znovu načteme práva uživatelů
FLUSH PRIVILEGES;
exit
```
## Instalace a konfigurace wordpressu
```
cd /tmp
# stáhneme wordpress
wget https://wordpress.org/latest.zip
# unzipneme ho
sudo unzip latest.zip
# přesuneme wordpres do /var/www/html
sudo mv wordpress/ /var/www/html/
cd /var/www/html
# změníme vlastníka
sudo chown www-data.www-data -R wordpress/
# restartujeme nginx
sudo systemctl restart nginx
```
## Stránka by měla běžet na ip adrese vašeho server
