# Definice funkce 'funkce' s jedním parametrem 'a'.
def funkce(a):
    # Výpis hodnoty parametru 'a' na standardní výstup.
    print(a)
    # Návratová hodnota funkce je hodnota parametru 'a'.
    return a

# Definice funkce 'mocnina' s jedním parametrem 'a'.
def mocnina(a):
    # Návratová hodnota funkce je druhá mocnina hodnoty parametru 'a'.
    return a * a

# Definice funkce 'soucin' s dvěma parametry 'a' a 'b'.
def soucin(a, b):
    # Návratová hodnota funkce je součet hodnot parametrů 'a' a 'b'.
    return a + b

# Volání funkce 'soucin' s argumenty 2 a 3 a přiřazení výsledku do proměnné 'promena'.
promena = soucin(2, 3)

# Výpis hodnoty proměnné 'promena' na standardní výstup.
print(promena)
