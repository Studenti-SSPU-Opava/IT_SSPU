from random import choice
from random import randint


n = 0
d = 1
p = 0
w = ""
doma = 0
weatherTypes = ["Je krásný den", "Je nehezký den", "Leje jako z konve", "Svítí slunce", "Svítí měsíc", "Vybuchují supernovy", "Hoří Vám dům", "Smrdí vám koule", "Padají trakaře"]
selectAction = 0
dollars = 20



while True:
    if doma == 0:
        w = choice(weatherTypes) #náhodná volba počasí

        print("(den", str(d) + ")\n" + str(w))
            #přivítání


    if selectAction == 0:
        try:
            selectAction = int(input("\nJste doma\nNapište číslo:\n\n1 - Jít na tržiště\n2 - Pracovat\n3 - Jít na bavlnová pole\n4 - Konec hry\n")) #vybrání akce
            doma = 1
        except:
            print("Otrokář je hloupý, neumí psát čísla")
            continue
    if selectAction > 4:
        print("Zadal jsi číslo mimo rozsah")
    
    
    #vykonání příkazů z nabídky:
    else:
        while True:
            match selectAction:


                case 1:
                    while True:
                        try:
                            val = int(input("\nJste na tržišti\nNapište číslo:\n\n1 - Jít do stánku s negry\n2 - Jít do stánku se zeleninou\n3 - Jít do stánku s masem\n4 - Jít do banky\n5 - Jít domů\n"))
                            
                            # Ověření zadané hodnoty
                            if 1 <= val <= 5:
                                break  # Platná hodnota, ukončení smyčky
                            else:
                                print("Neplatná volba. Zadejte prosím číslo od 1 do 5.")
                        except ValueError:
                            print("Chyba: Zadána neplatná hodnota. Zadejte prosím platné číslo.")


                            
                    match val:
                        case 1:
                            while True:
                                try:
                                    print("\nJste ve stánku s negry\nNapište číslo:\n\n1 - Koupit negra (50 dollarů, máte",dollars, "dolarů)\n2 - Prodat negry\n3 - Zpět na tržiště")
                                    sel = int(input())
                                    if 1 <= sel <= 3:# Ověření zadané hodnoty
                                        break  # Platná hodnota, ukončení smyčky
                                    else:
                                        print("Neplatná volba. Zadejte prosím číslo od 1 do 3.")
                                except ValueError:
                                    print("Chyba: Zadána neplatná hodnota. Zadejte prosím platné číslo.")
                            match sel:
                                case 1:
                                        if dollars >= 50:
                                            dollars -= 50
                                            n += 1
                                            print("Koupili jste si negra")
                                            break
                                        else:
                                            print("Nemáte dostatek dolarů")
                                case 2:
                                    print()
                                case 3:
                                    print()
                        case 2:
                            print("Jste ve stánku se zeleninou")
                        case 3:
                            print("Jste ve stánku s masem")
                        case 4:
                            print("Jste v bance")
                        case 5:
                            break
                        case _:
                            print("")



                case 2:
                    vydelano = randint(10,30)
                    dollars += vydelano
                    print("Vydělali jste", vydelano, "dolarů")
                    doma = 0
                case 3:
                    if p == 0:
                        print("jste u bavlnových polí")
                        break
                case 4:
                    print("------------------KONEC HRY------------------")
                    exit()
    selectAction = 0
    d += 1