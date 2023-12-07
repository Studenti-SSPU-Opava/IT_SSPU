from random import choice
from random import randint


n = 0
d = 1
w = ""
weatherTypes = ["Je krásný den", "Je nehezký den", "Leje jako z konve", "Svítí slunce", "Svítí měsíc", "Vybuchují supernovy", "Hoří Vám dům", "Smrdí vám koule", "Padají trakaře"]
selectAction = 0
dollars = 20
val = 0



while True:
    if selectAction == 3:
        break
    w = choice(weatherTypes) #náhodná volba počasí
    print("(den", str(d) + ")\n" + str(w), "a Vy máte", dollars, "dolarů\nCo dnes hodláte dělat?\n")


    if selectAction == 0:
        try:
            selectAction = int(input("Napište číslo:\n\n1 - koupit negry\n2 - Pracovat\n3 - Konec hry\n"))
        except:
            print("Otrokář je hloupý, neumí psát čísla")
    else:
        print("Error 0x01: špatné proměnná selectAction")


    if selectAction >= 4:
        print("Zadal jsi číslo mimo rozsah")
    else:
        match selectAction:

            case 1:
                print("\nMáte", n, "negrů\n\nStiskněte 1 pro koupení negra\nStiskněte 2 pro ubičování a následnou smrt negra\n")
                try: 
                    val = int(input())
                    if (val == 1):
                        n += 1
                        print("koupili jste si negra.")
                    elif (val == 2):
                        n -= 1
                        print("Ubičovali a zabili jste negra (zemřel).")
                except:
                    print("Vypadá to že mistr otrokář neumí psát čísla, negři ho ubičovali a zabili (umřel jste)")
                    break


            case 2:
                vydelano = randint(10,30)
                dollars += vydelano
                print("Vydělali jste", vydelano, "dolarů")
            case 3:
                break
        selectAction = 0
        d += 1


print("------------------KONEC HRY------------------")