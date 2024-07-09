zemljevid = [
    "......",
    "..##..",
    ".##.#.",
    "...###",
    "###.##",
]

def dolzina_ovir(vrstica):
    skupna_dolzina_ovir = 0

    for i in range(len(vrstica)):
        if vrstica[i] == "#":
            skupna_dolzina_ovir += 1

    return skupna_dolzina_ovir

#print(dolzina_ovir(zemljevid[1]))

def stevilo_ovir(vrstica):
    nasel_oviro = False
    skupno_stevilo_ovir = 0
    for i in range(len(vrstica)):
        if vrstica[i] == "#" and not nasel_oviro:
            nasel_oviro = True
            skupno_stevilo_ovir += 1
        elif vrstica[i] == "." and nasel_oviro:
            nasel_oviro = False

    return skupno_stevilo_ovir


def najsirsa_ovira(vrstica):
    nasel_oviro = False
    dolzina_najdalse_ovire = 0
    dolzina_trenutne_ovire = 0
    for i in range(len(vrstica)):
        if vrstica[i] == "#":
            dolzina_trenutne_ovire += 1
            if not nasel_oviro:
                nasel_oviro = True

        if (i == len(vrstica)-1) or (vrstica[i] == "." and nasel_oviro):
            nasel_oviro = False
            if dolzina_trenutne_ovire > dolzina_najdalse_ovire:
                dolzina_najdalse_ovire = dolzina_trenutne_ovire
            dolzina_trenutne_ovire = 0

    return dolzina_najdalse_ovire



def pretvori_vrstico(vrstica):
    x1 = 0
    x2 = 0
    nasel_oviro = False
    seznam_ovir =[]
    for i in range(len(vrstica)):
        x2 += 1
        if vrstica[i] == "#" and not nasel_oviro:
            x1 = x2
            nasel_oviro = True
        if vrstica[i] == "." and nasel_oviro:
            nasel_oviro = False
            seznam_ovir.append((x1, x2-1))

    if nasel_oviro:
        seznam_ovir.append((x1, x2))

    return seznam_ovir


def pretvori_zemljevid(vrstice):
    x1 = 0
    x2 = 0
    trenutna_vrstica = 0
    seznam_vseh_ovir=[]
    for i in range(len(vrstice)):
        trenutna_vrstica += 1
        x2 = 0
        nasel_oviro = False
        for j in range(len(vrstice[i])):
            x2 += 1
            if vrstice[i][j] == "#" and not nasel_oviro:
                x1 = x2
                nasel_oviro = True
            if vrstice[i][j] == "." and nasel_oviro:
                nasel_oviro = False
                seznam_vseh_ovir.append((x1, x2 - 1, trenutna_vrstica))

        if nasel_oviro:
            seznam_vseh_ovir.append((x1, x2, trenutna_vrstica))

    return seznam_vseh_ovir

def izboljsave(prej, potem):
    seznam_vseh_ovir_prej = pretvori_zemljevid(prej)
    seznam_vseh_ovir_potem = pretvori_zemljevid(potem)
    seznam_vseh_novih_ovir = []

    nasel_oviro = False

    for x1,x2,y in seznam_vseh_ovir_potem:
        nasel_oviro = False
        for x3,x4,y2 in seznam_vseh_ovir_prej:
            if x1 == x3 and x2 == x4 and y == y2:
                nasel_oviro = True
        if (not nasel_oviro):
            seznam_vseh_novih_ovir.append((x1, x2, y))

    return seznam_vseh_novih_ovir


def huligani(prej, potem):
    seznam_dodanih = izboljsave(prej, potem)
    seznam_odstranjenih = izboljsave(potem, prej)

    return seznam_dodanih, seznam_odstranjenih

import unittest


class Test(unittest.TestCase):
    def test_dolzina_ovir(self):
        self.assertEqual(3, dolzina_ovir("...###..."))
        self.assertEqual(1, dolzina_ovir("...#..."))
        self.assertEqual(2, dolzina_ovir("...#..#."))
        self.assertEqual(7, dolzina_ovir("#...#####..#."))
        self.assertEqual(8, dolzina_ovir("...#####.##...#"))
        self.assertEqual(9, dolzina_ovir("#...#####.##...#"))
        self.assertEqual(6, dolzina_ovir("##...#.#...##"))
        self.assertEqual(0, dolzina_ovir("..."))
        self.assertEqual(0, dolzina_ovir("."))

    def test_stevilo_ovir(self):
        self.assertEqual(1, stevilo_ovir("...###..."))
        self.assertEqual(1, stevilo_ovir("...#..."))
        self.assertEqual(2, stevilo_ovir("...#..#."))
        self.assertEqual(3, stevilo_ovir("#...#####..#."))
        self.assertEqual(3, stevilo_ovir("...#####.##...#"))
        self.assertEqual(4, stevilo_ovir("#...#####.##...#"))
        self.assertEqual(4, stevilo_ovir("##...#.#...##"))
        self.assertEqual(0, stevilo_ovir("..."))
        self.assertEqual(0, stevilo_ovir("."))

    def test_najsirsa_ovira(self):
        self.assertEqual(3, najsirsa_ovira("...###..."))
        self.assertEqual(1, najsirsa_ovira("...#..."))
        self.assertEqual(1, najsirsa_ovira("...#..#."))
        self.assertEqual(5, najsirsa_ovira("#...#####..#."))
        self.assertEqual(5, najsirsa_ovira("...#####.##...#"))
        self.assertEqual(5, najsirsa_ovira("#...#####.##...#"))
        self.assertEqual(6, najsirsa_ovira("######...#####.##...#"))
        self.assertEqual(6, najsirsa_ovira("...#####.##...######"))

    def test_pretvori_vrstico(self):
        self.assertEqual([(3, 5)], pretvori_vrstico("..###."))
        self.assertEqual([(3, 5), (7, 7)], pretvori_vrstico("..###.#."))
        self.assertEqual([(1, 2), (5, 7), (9, 9)], pretvori_vrstico("##..###.#."))
        self.assertEqual([(1, 1), (4, 6), (8, 8)], pretvori_vrstico("#..###.#."))
        self.assertEqual([(1, 1), (4, 6), (8, 8)], pretvori_vrstico("#..###.#"))
        self.assertEqual([], pretvori_vrstico("..."))
        self.assertEqual([], pretvori_vrstico(".."))
        self.assertEqual([], pretvori_vrstico("."))

    def test_pretvori_zemljevid(self):
        zemljevid = [
            "......",
            "..##..",
            ".##.#.",
            "...###",
            "###.##",
        ]
        self.assertEqual([(3, 4, 2), (2, 3, 3), (5, 5, 3), (4, 6, 4), (1, 3, 5), (5, 6, 5)], pretvori_zemljevid(zemljevid))

        zemljevid = [
            "..............##...",
            "..###.....###....##",
            "...###...###...#...",
            "...........#.....##",
            "...................",
            "###.....#####...###"
        ]
        self.assertEqual([(15, 16, 1),
                          (3, 5, 2), (11, 13, 2), (18, 19, 2),
                          (4, 6, 3), (10, 12, 3), (16, 16, 3),
                          (12, 12, 4), (18, 19, 4),
                          (1, 3, 6), (9, 13, 6), (17, 19, 6)], pretvori_zemljevid(zemljevid))

    def test_izboljsave(self):
        prej = [
            "..............##...",
            "..###.....###....##",
            "...###...###...#...",
            "...........#.....##",
            "...................",
            "###.....#####...###"
        ]

        potem = [
            "...##.........##...",
            "..###.....###....##",
            "#..###...###...#...",
            "...###.....#.....##",
            "................###",
            "###.....#####...###"
        ]

        self.assertEqual([(4, 5, 1), (1, 1, 3), (4, 6, 4), (17, 19, 5)], izboljsave(prej, potem))

        self.assertEqual([], izboljsave(prej, prej))

    def test_huligani(self):
        prej = [
            "..............##...",
            "..###.....###....##",
            "...###...###...#...",
            "...........#.....##",
            "...................",
            "###.....#####...###"
        ]

        potem = [
            "...##..............",
            "..........###....##",
            "#..###...###...#...",
            "...###.....#.....##",
            "................###",
            "###.....##.##...###"
        ]

        dodane, odstranjene = huligani(prej, potem)
        self.assertEqual([(4, 5, 1), (1, 1, 3), (4, 6, 4), (17, 19, 5), (9, 10, 6), (12, 13, 6)], dodane, "Napaka v seznamu dodanih")
        self.assertEqual([(15, 16, 1), (3, 5, 2), (9, 13, 6)], odstranjene, "Napaka v seznamu odstranjenih")

        dodane, odstranjene = huligani(potem, prej)  # Pazi, obrnjeno!
        self.assertEqual([(15, 16, 1), (3, 5, 2), (9, 13, 6)], dodane, "Napaka v seznamu dodanih")
        self.assertEqual([(4, 5, 1), (1, 1, 3), (4, 6, 4), (17, 19, 5), (9, 10, 6), (12, 13, 6)], odstranjene, "Napaka v seznamu odstranjenih")

        self.assertEqual(([], []), huligani(prej, prej))


if __name__ == "__main__":
    unittest.main()

