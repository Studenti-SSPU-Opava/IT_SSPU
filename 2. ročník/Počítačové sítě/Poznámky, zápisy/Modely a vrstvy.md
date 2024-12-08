# Nejnovější verze zápisu vždy na: https://github.com/Shadow1088/SchoolNotes/blob/main/sitarina/jednoduse/ISO-OSI.md
<br><br>
--------------------------------------------------------------
<br><br>

-> Lukas Jarnot IT2

Kdyz na instagram posilame nove storycko, jak to funguje? 

OSI model (ou es aj)        - je model co nam ma dat nejakou predstavu kdy se co deje.
* ma SEDM vrstev, neboli cely proces odesilani storycka instagramu by se podle nej rozdelil do SEDM casti


vrstvy (casti): 

7․ Aplikacni (Application layer)- tady tuknes na tlacitko “Post” na tvem mobilu, tvuj mobil pouzije urcite protokoly ( protokol je soubor pravidel pro nejaky urcity ucel [!!] ) pro komunikaci na internetu a preda tve data - obrazek co posilas, tvuj username, cookies a nejake info o tvem mobilu. V tuhle chvili data vypadaji takhle -> { data } { HTTP header }


6․ Prezentacni (Presentation layer) - tady se tvoje data - ten obrazek co posilas, zkompresuji ( zmensi svou velikost) a zasifruji. V tuhle chvili data vypadaji takhle -> { zasifrovane data } { zasifrovany HTTP header }


5․ Relacni (Session layer) - jakmile se tvoje data zacnou odesilat, otevre se mezi tebou a Instagramem relace (“konverzace”).
Tato vrstva se stará o to, aby byla celá komunikace udržena v chodu, dokud není vše doručeno.
V tuhle chvili data vypadaji takhle -> { zasifrovane data } { zasifrovany HTTP header } { informace o relaci }






4․ Transportni (Transport layer) - tady se tvoje data rozdeli na mensi casti a vybere se protokol k jejich odeslani ( znova pripominam ze protokol jsou nejaka pravidla podle kterych se vykona urcita vec, tomhle pripade muzeme pouzit TCP - zkratku vysvetlovat nebudu, jenom to mate, TCP zajistuje JISTOTU ze se data doruci tak jak maji - bez chyb a v spravnem poradi
 V tuhle chvili data vypadaji takhle -> { TCP Header } { zasifrovane data }  { informace o relaci }


> vsimni si ze od tehle vrstvy data dostavaji nazev - segmenty


3․ Sitova (Network layer) - tahle vrstva ma za ukol vybrat logickou cestu jakou se data poslou, pouziva IP adresy k smerovani dat k cili - jako priklad bych uvedl navigaci, jsi ve Vidni a chces se autem dostat do Prahy, v tomhle prikladu si to predstav jako by navigace vybrala mesta kterymi musis projet aby ses tam dostal

> v tehle vrstve je nase cast dat nazvana packet (uz vic dulezitejsi - packet si predstav jako balik, do tehle chvile jsme data vytvorili - obalovali - rozdelili a ted urcujeme kudma bude nas balik (packet) putovat


V tuhle chvili nas packet vypada takhle: { IP Header } { TCP Header } { zasifrovany HTTP header }  { informace o relaci }




2․ Linkova (Data-link layer) - v minule vrstve jsme resili kudma pojede logicky, tady resime kudma pujde fyzicky - jakym kablem, jakym zarizenim (routery, switche - switch je jako prodluzovacka, ve zdi mame jednu/dve zasuvky.. to proste nestaci, stejne tak v routeru mame treba max ctyri, to nestaci, switch ma der vic - ma i dalsi vyhody ale to zatim staci) - resi se to pomoc MAC adres, kazde zarizeni ma svoji MAC adresu ve tvaru - AA:BB:CC:DD:EE:FF

MAC adresa je proste identifikator zarizeni, ja jsem IT2313 - moje ID je 2313
pouziva se jen ve tve siti, ne pres Internet

IP adresa je taky identifikator, ale pouziva se na Internetu a meni se


V tuhle chvili nas packet vypada takhle: { MAC header } { IP Header } { TCP Header } { zasifrovany HTTP header }  { informace o relaci }


>>> VSIMNI SI, ze se v kazde vrstve prida k nasi PDU (te casti dat) nejaky header - kazda vrstva OBALI nas PDU (cast dat) svymi informacema - tenhle proces se nazyva enkapsulace


> tady je nas packet rozclenen na “frejmy” (frame -y) (Mikes tomu rad rika cesky - ramecky




1․ Fyzicka (Physical layer) - nas frame je converted na bity (jednicky a nuly) a kabely se posle - bud elektricky, svetlem, radiovym signalem - zavisi na nasem mediu pres ktery ho prenasime, bud fiber-optic (svetelny kabel), normalni ethernetovy kabel RJ-45 a tak, anebo pres Wi-Fi (radiovym signalem)


>> PAMATUJ, ze jak mame enkapsulaci (proces kde kazda vrstva nejak data obali) ma taky svuj opak - dekapsulace. Kdyz posilame, jdeme od vrstvy k vrstve smerem dolu, kdyz nase storycko Instagram prijima, jde od vrstvy k vrstve smerem nahoru. Ve fyzicke to prijima, a dal to ROZBALUJE (dekapsulace) s kazdou dalsi vrstvou. Sitova vrstva si rozbali svoje, transportni si rozbali svoje..






TCP/IP - (tyy cii pii aj pii) - OSI model je pomyslny a rika nam JAK ASI BY TO MELO FUNGOVAT, TCP/IP je uz skutecny system jak to funguje a je zalozeny prave na OSI, ma CTYRI vrstvy 
- Aplikacni (obsahuje Aplikacni, Prezentacni a Relacni z OSI, ty tri shrnul do jedne)


- Transportni - stejne jako z OSI


- Sitova - Stejne jako z OSI


- Vrstva sitoveho rozhrani - dlouhy nazev ale jsou to vlastne Linkova a Fyzicka z OSI dohromady



<br><br>

 ### Poznámka maintainera: soubor bude pravděpodobně mírně předělán, pro lepší čitelnost, text zůstane stejný. Potřeba zeptat se autora textu zda to bude možné.
