teza_tovora = int(input("vpisi stevilo goriva "))
kolicina_goriva_za_tovor = 0
vsa_kolicina_goriva = 0

while teza_tovora > 0:
    teza_tovora = teza_tovora // 3
    if teza_tovora > 1:
        teza_tovora -= 2
    vsa_kolicina_goriva += teza_tovora
    kolicina_goriva_za_tovor += 1

print(kolicina_goriva_za_tovor, vsa_kolicina_goriva)