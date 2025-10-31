# Jak na home assistant
## VBOX
### Co je potřeba na začátek
- nainstalujte si vbox
- stáhněte si iso image pro debian 12.5
### Jak nakonfigurovat vbox
- jako iso si vyberete stáhlý debian 12.5
- zaškrtnete skip unattended install
- zvolíte dostatek místa (např. 50GB)
- po vytvoření přejděte do nastavení
### Instalace debianu
- zvolte install **NE GRAPHICAL INSTALL**
- vyberte jazyk (ideálně angličtinu)
- vyberte Česko jako zemi
- vyberte klavesnici na kterou jste zvykli
- zvolte "hostname" jako home-assistant
- nechte domain name volné
- vyberte si nějaké heslo pro root(a)
- zvolte si "Full name" jako vaše celé jméno např. David Pustka
- zvolte si "username" jako vaše jméno malým např. david
- zvolte si "password" jako nějaké heslo
- zvolte "partitioning method" hned tu první ("Guided - use entire disk")
- vyberte jedinou partition, kterou vám to nabízí
- zvolte "partitioning scheme" hned tu první ("All files in one partition...")
- dokončete partitioning
- zvolte "yes" u "write changes to disk"
- zvolte "no" u "Scan extra installation media?"
- zvolete "Czechia" (mělo by vám to nabídnout hnedka jako první u) "Debian archive mirror country:"
- zvolte hned to první "deb.debian.org"
- nemáme http proxy, takže dáme jenom continue
- zvolte "no" u "Participate in the package usage survey?"
- zvolte **jenom** "ssh server" a "standard system utilities" **a neinstalujte** "Debian desktop enviroment" a "Gnome"
- zvolte "yes" u "Install the GRUB boot loader to your primary drive"
- u "Device for boot loader installation" vyberte /dev/sda/... (to by mělo být jediné co je k dispozici kromě "Enter device manually"
- zvolte "Continue" u "Please choose \<Continue\> to reboot"
- přihlaste se pomocí "username" co jste zadávali (např. david) a hesla pro tohoto uživatele
### Instalace home assistanta
- nejdříve musíme zjistit ip adresu: `ip add`
	- pokud jste vše udělali správně, ta druhá by měla být enp0s3 nebo něco podobného
- otevřete terminál a přihlašte se do serveru: `ssh username@ipaddress`, např. `ssh david@192.168.1.110`
- přihlaste se jako root: `su -`
- `apt update`
- postupujeme podle https://github.com/home-assistant/supervised-installer
- nainstalujeme potřebné balíčky
- `apt install \
apparmor \
cifs-utils \
curl \
dbus \
jq \
libglib2.0-bin \
lsb-release \
network-manager \
nfs-common \
systemd-journal-remote \
systemd-resolved \
udisks2 \
wget -y`
- to nám vytvoří *symlinky* a my musíme upravit DNS: `nano /etc/systemd/resolved.conf`, tam změníme komentář `#DNS` na `DNS=1.1.1.1` a uložíme (Ctrl+X, y, Enter)
- potom musíme tyto změny aplikovat pomocí `systemctl restart systemd-resolved.service`
- pokračujeme dále podle instrukcí z githubu: `curl -fsSL get.docker.com | sh`
- pak podle instrukcí nainstalujeme os-agent https://github.com/home-assistant/os-agent/tree/main#using-home-assistant-supervised-on-debian
	- stáhneme si [poslední verzi os=agent](https://github.com/home-assistant/os-agent/releases/tag/1.6.0) pomocí wget: `wget https://github.com/home-assistant/os-agent/releases/download/1.6.0/os-agent_1.6.0_linux_x86_64.deb` (tu adresu jsem získal tak, že jsem kliknul pravým na os-agent..._x86_64.deb (3 odspodu) v Assets a zvolil "Copy link address")
	- nakonec nainstalujeme pomocí dpkg: `dpkg -i os-agent_1.6.0_linux_x86_64.deb`
	- můžeme si ověřit, že vše funguje pomocí: `gdbus introspect --system --dest 				io.hass.os --object-path /io/hass/os`, pokud to nevrátí error, vše funguje
- poslední krok je nainstalovat home-assistant supervised debian package: `wget -O homeassistant-supervised.deb https://github.com/home-assistant/supervised-installer/releases/latest/download/homeassistant-supervised.deb
apt install ./homeassistant-supervised.deb`
	- **pokud to nejde, nebo se to nikam neposouá, restartujte server a zkuste to znovu**
- v browseru jděte na "ip adresa serveru":8123
## Konfigurace home assistanta
### Vytvoření uživatele
- jméno: celé jméno (např. David Pustka)
- zvolíme si nějaké heslo
- home location: Opava
- nechceme poskytovat informace, takže next
- finish
### Řešení problému s system is unhealthy
- restartujte server, dokud se to nevyřeší samo
### Mqtt broker
- jděte do settings -> add-ons -> add-on store
- vyhledejte mosquitto broker
- nainstalujte
- spusťte
### VS code
- podobně jako mqqt nainstalujte a spusťte
