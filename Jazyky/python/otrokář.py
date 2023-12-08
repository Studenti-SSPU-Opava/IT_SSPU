from random import choice
from random import randint


n = 0
d = 1
p = 0
w = ""
weatherTypes = ["Je krásný den", "Je nehezký den", "Leje jako z konve", "Svítí slunce", "Svítí měsíc", "Vybuchují supernovy", "Hoří Vám dům", "Smrdí vám koule", "Padají trakaře"]
selectAction = 0
dollars = 20



while True:
    if selectAction == 4: #ukončí hru
        exit()


    w = choice(weatherTypes) #náhodná volba počasí

    print("(den", str(d) + ")\n" + str(w))
        #přivítání


    if selectAction == 0:
        try:
            selectAction = int(input("Jste doma\nNapište číslo:\n\n1 - Jít na tržiště\n2 - Pracovat\n3 - Jít na bavlnová pole\n4 - Konec hry\n")) #vybrání akce
        except:
            print("Otrokář je hloupý, neumí psát čísla")
    if selectAction > 4:
        print("Zadal jsi číslo mimo rozsah")
    
    
    #vykonání příkazů z nabídky:
    else:
        match selectAction:


            case 1:
                while True:
                    try:
                        val = int(input("\nJste na tržišti\nNapište číslo:\n\n1 - Jít do stánku s negry\n2 - Jít do stánku se zeleninou\n3 - Jít do stánku s masem\n4 - Jít do banky\n5 - Jít domů"))
                        
                        # Ověření zadané hodnoty
                        if 1 <= val <= 5:
                            break  # Platná hodnota, ukončení smyčky
                        else:
                            print("Neplatná volba. Zadejte prosím číslo od 1 do 5.")
                    except ValueError:
                        print("Chyba: Zadána neplatná hodnota. Zadejte prosím platné číslo.")


                        
                match val:
                    case 1:
                        print("Jste ve stánku s negry")
                    case 2:
                        print("Jste ve stánku se zeleninou")
                    case 3:
                        print("Jste ve stánku s masem")
                    case 4:
                        print("Jste v bance")
                    case 5:
                        print("")
                    case _:
                        print("")



            case 2:
                vydelano = randint(10,30)
                dollars += vydelano
                print("Vydělali jste", vydelano, "dolarů")
            case 3:
                if p == 0:
                    print()
    selectAction = 0
    d += 1


print("------------------KONEC HRY------------------")