def vsota_kvadratov(n):
    return sum(i**2 for i in range(1, n+1))

def vsota_kvadratov_pal(n):
    print([i**2 for i in range (1, n+1) if str(i) == str(i)[::-1]])





def subs(niz, polozaj):
    return ''.join(niz[int(i)] for i in polozaj)

xs = [183, 168, 175, 176, 192, 180]

def mean(xs):
    return sum(i for i in xs) / len(xs)

def std(xs):
    return

morse = {
    'A': '.-',
    'B': '-...',
    'C': '-.-.',
    'D': '-..',
    'E': '.',
    'F': '..-.',
    'G': '--.',
    'H': '....',
    'I': '..',
    'J': '.---',
    'K': '-.-',
    'L': '.-..',
    'M': '--',
    'N': '-.',
    'O': '---',
    'P': '.--.',
    'Q': '--.-',
    'R': '.-.',
    'S': '...',
    'T': '-',
    'U': '..-',
    'V': '...-',
    'W': '.--',
    'X': '-..-',
    'Y': '-.--',
    'Z': '--..',
    '1': '.----',
    '2': '..---',
    '3': '...--',
    '4': '....-',
    '5': '.....',
    '6': '-....',
    '7': '--...',
    '8': '---..',
    '9': '----.',
    '0': '-----',
    ' ': ''
}

def txt2morse(s):
    return ' '.join(morse[i] for i in s)


t = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
def obrni(t):
    return [[t[i][j] for i in range(0, len(t))] for j in range(len(t[0]))]


