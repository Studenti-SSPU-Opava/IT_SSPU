from random import seed
from random import choice

n = 1
d = 1
w = ""
weatherTypes = ["Je krásný den", "Je nehezký den"]
selectAction = 1
dollars = 20
val = 0



while True:
    w = choice(weatherTypes)
    print("(den", str(d) + ")\n" + str(w), "a Vy máte", dollars, "dolarů\nCo dnes hodláte dělat?")
    try:
        selectAction = int(input("Napište číslo:\n\n1 - koupit negry\n2 - Pracovat\n"))
    except:
        break
    match selectAction:
        case 1:
            if (n == 0):
                print("Došli ti negři, tvé naděje na život jsou nulové (umřel jste)")
                break
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

print("------------------KONEC HRY------------------")