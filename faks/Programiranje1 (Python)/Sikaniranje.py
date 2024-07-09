ovire = [(1, 3, 6), (2, 4, 3), (4, 6, 7),
         (3, 4, 9), (6, 9, 5), (9, 10, 2), (9, 10, 8)]

#obvezna naloga
index_stolpca = 6
najkrajsa_ovira = 10

for x1, x2, y in ovire:
    if x1 <= index_stolpca <= x2:
        if y < najkrajsa_ovira:
            najkrajsa_ovira = y
print(najkrajsa_ovira)


#dodatni del
sirina_kolesarske_steze = 0
for _, x2, _ in ovire:
    if x2 > sirina_kolesarske_steze:
        sirina_kolesarske_steze = x2


index_trenutnega_stolpca = 0
najdalsa_pot = 0
index_stolpca_najdaljse_poti = 1

st_vseh_ovir = 0
for i in ovire:
    st_vseh_ovir += 1

nasel_najdalso_pot = False; #ce v 3. stolpcu ne najdemo poti, je to avtomatsko najdalsa pot in ne rabimo gledati za ostale poti

for i in range(sirina_kolesarske_steze):
    index_trenutnega_stolpca += 1
    stevilo_ovir = 0
    temp_najdalsa_pot = sirina_kolesarske_steze #ce imamo eno oviro v 1. in 3. vrstici, rabimo vzeti tisto, ki ima manjsi index
    nasel_oviro = False
    for x1, x2, y in ovire:
        stevilo_ovir += 1
        if x1 <= index_trenutnega_stolpca <= x2 and y <= temp_najdalsa_pot:
            nasel_oviro = True
            temp_najdalsa_pot = y
        elif stevilo_ovir == st_vseh_ovir and not nasel_oviro:
            najdalsa_pot = sirina_kolesarske_steze
            index_stolpca_najdaljse_poti = index_trenutnega_stolpca
            nasel_najdalso_pot = True
            break

    if nasel_najdalso_pot:
        break
    if nasel_oviro and temp_najdalsa_pot > najdalsa_pot:
        najdalsa_pot = temp_najdalsa_pot
        index_stolpca_najdaljse_poti = index_trenutnega_stolpca


print(index_stolpca_najdaljse_poti , najdalsa_pot)
if najdalsa_pot == sirina_kolesarske_steze:
    print("zmaga")







