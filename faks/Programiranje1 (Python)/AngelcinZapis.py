
def koordinate(zapis):
    return ((int(zapis.strip("-")), int(zapis.strip("-")) + int(zapis.count("-")) - 1))

def vrstica(zapis):
    splitted_string = zapis.split()
    stevilka_vrstice = int(splitted_string[0].strip("( )"))
    seznam_ovir = []

    for i in splitted_string[1:]:
        seznam_ovir.append(((int(i.strip("-")), int(i.strip("-")) + int(i.count("-")) - 1, stevilka_vrstice)))

    return seznam_ovir

def preberi(zapis):
    novi_zapis = zapis.splitlines()
    seznam_ovir = []

    for i in novi_zapis:
        splitted_string = i.split()
        stevilka_vrstice = int(splitted_string[0].strip("( )"))

        for i in splitted_string[1:]:
            seznam_ovir.append(((int(i.strip("-")), int(i.strip("-")) + int(i.count("-")) - 1, stevilka_vrstice)))

    return seznam_ovir

def intervali(zapis):
    seznam_ovir = []
    for zacetek, konec in zapis:
        seznam_ovir.append(str(zacetek) + "-" * (konec - zacetek + 1))

    return seznam_ovir


def zapisi_vrstico(vrstica, zapis):
    ovire = "(" + str(vrstica) + ")"

    for zacetek, konec in zapis:
        ovire += " " + str(zacetek) + "-" * (konec - zacetek + 1)

    return ovire


def zapisi(ovire):
    sorted_ovire = sorted(ovire, key = lambda x: (x[2], x[0]))
    trenutna_vrstica = sorted_ovire[0][2]
    niz = "(" + str(trenutna_vrstica) + ")"

    for zacetek, konec, vrstica in sorted_ovire:
        if vrstica == trenutna_vrstica:
            niz += " " + str(zacetek) + "-" * (konec - zacetek + 1)
        else:
            trenutna_vrstica = vrstica
            niz += "\n"
            niz += "(" + str(trenutna_vrstica) + ")"
            niz += " " + str(zacetek) + "-" * (konec - zacetek + 1)

    return niz



import unittest

class Obvezna(unittest.TestCase):
    def test_koordinate(self):
        self.assertEqual((3, 4), koordinate("3--"))
        self.assertEqual((5, 10), koordinate("5------"))
        self.assertEqual((123, 123), koordinate("123-"))
        self.assertEqual((123, 125), koordinate("123---"))

    def test_vrstica(self):
        self.assertEqual([(1, 3, 4), (5, 11, 4), (15, 15, 4)], vrstica("  (4) 1---  5------- 15-"))
        self.assertEqual([(989, 991, 1234)], vrstica("(1234) 989---"))

    def test_preberi(self):
        self.assertEqual([(5, 6, 4),
                          (90, 100, 13), (5, 8, 13), (19, 21, 13),
                          (9, 11, 5), (19, 20, 5), (30, 34, 5),
                          (9, 11, 4),
                          (22, 25, 13), (17, 19, 13)], preberi(
""" (4) 5--
(13) 90-----------   5---- 19---
 (5) 9---           19--   30-----
(4)           9---
(13)         22---- 17---
"""))

    def test_intervali(self):
        self.assertEqual(["6-----", "12-", "20---", "98-----"], intervali([(6, 10), (12, 12), (20, 22), (98, 102)]))

    def test_zapisi_vrstico(self):
        self.assertEqual("(5) 6----- 12-", zapisi_vrstico(5, [(6, 10), (12, 12)]).rstrip("\n"))
        self.assertEqual("(8) 6----- 12- 20--- 98-----", zapisi_vrstico(8, [(6, 10), (12, 12), (20, 22), (98, 102)]).rstrip("\n"))
        self.assertEqual("(8) 6----- 12- 20--- 98-----", zapisi_vrstico(8, [(6, 10), (12, 12), (20, 22), (98, 102)]).rstrip("\n"))

class Dodatna(unittest.TestCase):
    def test_zapisi(self):
        ovire = [(5, 6, 4),
          (90, 100, 13), (5, 8, 13), (9, 11, 13),
          (9, 11, 5), (19, 20, 5), (30, 34, 5),
          (9, 11, 4),
          (22, 25, 13), (17, 19, 13)]
        kopija_ovir = ovire.copy()
        self.assertEqual("""(4) 5-- 9---
(5) 9--- 19-- 30-----
(13) 5---- 9--- 17--- 22---- 90-----------""", zapisi(ovire).rstrip("\n"))
        self.assertEqual(ovire, kopija_ovir, "Pusti seznam `ovire` pri miru")

if __name__ == "__main__":
    unittest.main()