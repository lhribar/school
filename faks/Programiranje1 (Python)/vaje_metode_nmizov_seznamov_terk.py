tviti = ["sandra: Spet ta dež. #dougcajt",
 "berta: @sandra Delaj domačo za #programiranje1",
 "sandra: @berta Ne maram #programiranje1 #krneki",
 "ana: kdo so te @berta, @cilka, @dani? #krneki",
 "cilka: jst sm pa #luft",
 "benjamin: pogrešam ano #zalosten",
 "ema: @benjamin @ana #split? po dvopičju, za začetek?"]

def vsi_avtorji(tviti):
    avtorji = []

    for oseba_in_tvit in tviti:
        oseba =  oseba_in_tvit.split(":")[0]
        if oseba not in avtorji:
            avtorji.append(oseba)
    return avtorji


def izloci_besedo(beseda):
    while beseda and not beseda[0].isalnum():
        beseda = beseda[1:]
    while beseda and not beseda[-1].isalnum():
        beseda = beseda[:-1]
    return beseda

def se_zacne_z(tvit, c):
    tvit = tvit.split(c)
    return [beseda for beseda in tvit[1:]]


def zberi_se_zacne_z(tvit, c):
    avtoji = []
    for poved in tvit:
        poved = poved.split()
        for beseda in poved:
            if beseda[0] == c:
                if poved[0][:-1] not in avtoji:
                    avtoji.append(poved[0][:-1])

    return avtoji


def vsi_hashtagi(tviti):
    vse_besede = []
    for poved in tviti:
        poved = poved.split("#")
        for beseda in poved[1:]:
            beseda = beseda.strip()
            if beseda not in vse_besede:
                vse_besede.append(beseda)

    return vse_besede

print(vsi_hashtagi(tviti))