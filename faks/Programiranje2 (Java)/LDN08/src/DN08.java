public class DN08 {
    public static void main(String[] args) {
        Lik[] liki = new Lik[args.length];

        for (int i = 0; i < args.length; i++){
            String[] podatki = args[i].split(":");
            if (podatki[0].equals("pravokotnik")){
                liki[i] = new Pravokotnik(Integer.parseInt(podatki[1]), Integer.parseInt(podatki[2]));
            }
            else if (podatki[0].equals("kvadrat")){
                liki[i] = new Kvadrat(Integer.parseInt(podatki[1]));
            }
            else if (podatki[0].equals("nkotnik")){
                liki[i] = new NKotnik(Integer.parseInt(podatki[1]), Integer.parseInt(podatki[2]));
            }
        }

        System.out.println((int)skupniObseg(liki));
    }


    static double skupniObseg(Lik[] liki){
        int skupnaVsota = 0;
        for (int i = 0; i < liki.length; i++)
            skupnaVsota += liki[i].obseg();

        return skupnaVsota;
    }
}

abstract class Lik {
    abstract public int obseg();
}

class Pravokotnik extends Lik {
    int a, b;

    public Pravokotnik(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public int obseg(){
        return 2*a + 2*b;
    }
}

class Kvadrat extends Lik {
    int a;

    public Kvadrat(int a) {
        this.a = a;
    }

    public int obseg(){
        return 4*a;
    }
}

class NKotnik extends Lik {
    int n, a;

    public NKotnik(int n, int a){
        this.n = n;
        this.a = a;
    }

    public int obseg(){
        return n*a;
    }
}

