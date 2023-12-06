n = 1
val = 0
while True:
    if (n == 0):
        print("Došli ti negři, tvé naděje na život jsou nulové (umřel jsi)")
        break
    print("Máte", n, "negrů")
    print("Stiskněte 1 pro koupení negra")
    print("Stiskněte 2 pro ubičování a následnou smrt negra")
    val = int(input())
    if (val == 1):
        n += 1
        print("koupili jste si negra. Váš aktuální počet negrů je", n)
    elif (val == 2):
        n -= 1
        print("Ubičovali a zabili jste negra (zemřel). Váš aktuální počet negrů je", n)
    else:
        print("Vypadá to že mistr otrokář neumí psát čísla, negři ho ubičovali a zabili (umřel jsi)")
        break
print("konec hry")