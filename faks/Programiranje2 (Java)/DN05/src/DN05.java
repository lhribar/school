import java.io.File;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;
import java.util.Scanner;

import java.util.HashMap;
import java.util.Map;
import java.util.*;

public class DN05 {
    private static int width = -1;
    private static int height = -1;
    public static void main(String[] args) {

        //naloga 1
        if (args[0].equals("izpisi"))
            izpisiSliko(preberiSliko(args[1]));
        else if (args[0].equals("histogram"))
            izpisiHistogram(preberiSliko(args[1]));
        else if (args[0].equals("svetlost"))
            System.out.println("Srednja vrednost sivine na sliki " + args[1] + " je: " + svetlostSlike(preberiSliko(args[1])));

        //naloga 2
        else if (args[0].equals("zmanjsaj"))
            izpisiSliko(zmanjsajSliko(preberiSliko(args[1])));
        else if (args[0].equals("rotiraj"))
            izpisiSliko(rotirajSliko(preberiSliko(args[1])));
        else if (args[0].equals("zrcali"))
            izpisiSliko(zrcaliSliko(preberiSliko(args[1])));
        else if (args[0].equals("vrstica"))
            System.out.println("Max razlika svetlo - temno je v " + poisciMaxVrstico(preberiSliko(args[1])) + ". vrstici.");

        //naloga 3
        else if (args[0].equals("barvna"))
            izpisiBarvnoSliko(preberiBarvnoSliko(args[1]));
        else if (args[0].equals("sivinska"))
            izpisiSliko(pretvoriVSivinsko(preberiBarvnoSliko(args[1])));

        //naloga 4
        else if (args[0].equals("uredi")) {
            preberiVseInIzpisi(args);
        }

        //naloga 5
        else if (args[0].equals("jedro"))
            konvolucijaJedro(preberiSliko(args[1]));
        else if (args[0].equals("glajenje"))
            konvolucijaGlajenje(preberiSliko(args[1]));
        else if (args[0].equals("robovi"))
            konvolucijaRobovi(preberiSliko(args[1]));


    }

    public static int[][] preberiSliko(String ime) {
        int[][] tabela = null;

        try {
            File myObj = new File(ime);
            Scanner myReader = new Scanner(myObj);
            int counter = 0;
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                if (counter == 0) {
                    String[] prvaVrstica = data.split(" ");
                    if (prvaVrstica == null) {
                        System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov");
                        System.exit(1);
                    }
                    if (prvaVrstica.length < 4){
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }
                    try {
                        Integer.parseInt(prvaVrstica[1]);
                        Integer.parseInt(prvaVrstica[3]);

                    } catch (NumberFormatException e) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2 (velikost slike ni pravilna).");
                        System.exit(1);
                    }
                    if (!(prvaVrstica[0].equals("P2:"))) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }

                    else if ((prvaVrstica[1].matches("[a-zA-z]+")  || Integer.parseInt(prvaVrstica[1]) <= 0)) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }
                    else if (!(prvaVrstica[2].equals("x"))) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }

                    else if ( Integer.parseInt(prvaVrstica[3]) <= 0 ) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2 (velikost slike je 0 ali negativna).");
                        System.exit(1);
                    }
                    else{
                        width = Integer.parseInt(prvaVrstica[1]);
                        height = Integer.parseInt(prvaVrstica[3]);

                    }
                }
                else if (counter == 1){
                    int vsota = 0;
                    String[] drugaVrstica = data.split(" ");

                    if (drugaVrstica.length < width * height){
                        System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov.");
                        System.exit(1);
                    }

                    for (int i = 0; i < drugaVrstica.length; i++){
                        if (Integer.parseInt(drugaVrstica[i]) < 0 || Integer.parseInt(drugaVrstica[i]) > 255){
                            System.out.println("Napaka: datoteka " + ime + " vsebuje podatke izven obsega 0 do 255.");
                            System.exit(1);
                        }
                    }

                    int stevec = 0;
                    tabela = new int[height][width];
                    for (int i = 0; i < height; i++){
                        for (int j = 0; j < width; j++){
                            tabela[i][j] = Integer.parseInt(drugaVrstica[stevec]);
                            stevec++;
                        }
                    }
                }
                counter++;
            }
            if (counter == 0){
                System.out.println("Napaka: Datoteka " + ime + " je prazna.");
                System.exit(1);

            }
            else if (counter == 1){
                System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov.");
                System.exit(1);
            }


            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Napaka: datoteka " + ime + " ne obstaja.");
            System.exit(1);
        }


        return tabela;
    }
    static public void izpisiSliko(int[][] tabela){
        System.out.println("velikost slike: " + width + " x " + height);
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++)
                System.out.print(tabela[i][j] + " ");
            System.out.println();
        }
    }

    static public void izpisiHistogram(int[][] slika){
        Map<Integer, Integer> mapSlika = new TreeMap<>();

        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                mapSlika.put(slika[i][j], mapSlika.getOrDefault(slika[i][j], 0) + 1);
            }
        }

        System.out.println("sivina : # pojavitev");
        for (Map.Entry<Integer, Integer> entry : mapSlika.entrySet()) {
            System.out.printf("%6d : %4d%n", entry.getKey(), entry.getValue());
        }
    }

    public static double svetlostSlike(int[][] slika){
        int vsota = 0;
        for(int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                vsota += slika[i][j];
            }
        }
        double average = vsota / (double)(height * width);
        return Math.round(average * 100.0) / 100.0;
    }


    public static int poisciMaxVrstico(int[][] slika){
        int najvecjaRazlika = 0;
        int index = 0;

        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                for (int k = j; k < width; k++){
                    if (Math.abs(slika[i][j] - slika[i][k]) > najvecjaRazlika){
                        najvecjaRazlika = Math.abs(slika[i][j] - slika[i][k]);
                        index = i + 1;
                    }
                }
            }
        }

        return index;
    }

    public static int[][] zmanjsajSliko(int[][] slika){
        if (height < 3 || width < 3)
            return slika;
        if (height %2 == 1) {
            height -= 1;
        }
        if (width %2 == 1){
            width -= 1;
        }

        int[][] zmanjsanaSlika = new int[height][width];

        for (int i = 0, iCounter = 0; i < height; i += 2){
            for (int j = 0, jCounter = 0; j < width; j += 2){
                int vsota = 0;
                vsota += slika[i][j];
                vsota += slika[i][j+1];
                vsota += slika[i+1][j];
                vsota += slika[i+1][j+1];
                zmanjsanaSlika[iCounter][jCounter] = vsota / 4;
                jCounter++;
            }
            iCounter++;
        }
        width /= 2;
        height /= 2;

        return zmanjsanaSlika;
    }
    public static int[][] rotirajSliko(int[][] slika) {


        int[][] rotatedSlika = new int[width][height];


        for (int i = 0; i < slika.length; i++) {
            for (int j = 0; j < slika[i].length; j++) {
                rotatedSlika[j][slika.length - 1 - i] = slika[i][j];
            }
        }

        int t= width;
        width = height;
        height = t;
        return rotatedSlika;
    }

    public static int[][] zrcaliSliko(int[][] slika){
        int[][] zrcaljena = new int[height][width];

        for (int i = 0; i < slika.length; i++) {
            for (int j = 0; j < slika[i].length; j++) {
                zrcaljena[i][j] = slika[i][width-j-1];
            }
        }

        return zrcaljena;
    }

    //NALOGA 3

    public static int[][][] preberiBarvnoSliko(String ime){
        int[][][] tabela = null;

        try {
            File myObj = new File(ime);
            Scanner myReader = new Scanner(myObj);
            int counter = 0;
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                if (counter == 0) {
                    String[] prvaVrstica = data.split(" ");
                    if (prvaVrstica == null) {
                        System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov");
                        System.exit(1);
                    }
                    else if (!(prvaVrstica[0].equals("P2B:") || prvaVrstica[0].equals("PB2:"))) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }
                    else if ((prvaVrstica[1].matches("[a-zA-z]+")  || Integer.parseInt(prvaVrstica[1]) <= 0)) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }
                    else if (!(prvaVrstica[2].equals("x"))) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2.");
                        System.exit(1);
                    }
                    else if ( Integer.parseInt(prvaVrstica[3]) <= 0 ) {
                        System.out.println("Napaka: datoteka " + ime + " ni v formatu P2 (velikost slike je 0 ali negativna).");
                        System.exit(1);
                    }
                    else{
                        width = Integer.parseInt(prvaVrstica[1]);
                        height = Integer.parseInt(prvaVrstica[3]);


                    }
                }
                else if (counter == 1){
                    int vsota = 0;
                    String[] drugaVrstica = data.split(" ");

                    if (drugaVrstica.length < width * height){
                        System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov.");
                        System.exit(1);
                    }



                    tabela = new int[height][width][3];


                    int stevec = 0;
                    for (int i = 0; i < height; i++) {
                        for (int j = 0; j < width; j++) {
                            int vrednost = Integer.parseInt(drugaVrstica[stevec]);
                            String stevilka = "";

                            for (int k = 29; k >= 20; k--){
                                if ((vrednost / Math.pow(2, k)) >= 1) {
                                    stevilka += "1";
                                    vrednost -= Math.pow(2, k);
                                }
                                else
                                    stevilka += "0";
                            }

                            tabela[i][j][0] = Integer.parseInt(stevilka, 2); //rdeca
                            stevilka = "";
                            for (int k = 19; k >= 10; k--){
                                if ((vrednost / Math.pow(2, k)) >= 1) {
                                    stevilka += "1";
                                    vrednost -= Math.pow(2, k);
                                }
                                else
                                    stevilka += "0";
                            }

                            tabela[i][j][1] = Integer.parseInt(stevilka, 2); //zelena

                            stevilka = "";
                            for (int k = 9; k >= 0; k--){
                                if ((vrednost / Math.pow(2, k)) >= 1) {
                                    stevilka += "1";
                                    vrednost -= Math.pow(2, k);
                                }
                                else
                                    stevilka += "0";
                            }

                            tabela[i][j][2] = Integer.parseInt(stevilka, 2); //modra
                            stevec++;
                        }
                    }






                }
                counter++;
            }
            if (counter == 0){
                System.out.println("Napaka: Datoteka " + ime + " je prazna.");
                System.exit(1);

            }
            else if (counter == 1){
                System.out.println("Napaka: datoteka " + ime + " vsebuje premalo podatkov.");
                System.exit(1);
            }


            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Napaka: datoteka" + ime + " ne obstaja.");
        }


        return tabela;

    }

    public static void izpisiBarvnoSliko(int[][][] slika){
        System.out.println("velikost slike: " + width + " x " + height);
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                System.out.print("(");
                for (int k = 0; k < 3; k++) {
                    System.out.print(slika[i][j][k]);
                    if (k != 2)
                        System.out.print(",");
                }
                System.out.print(") ");

            }
            System.out.println();
        }
    }

    public static int[][] pretvoriVSivinsko(int[][][] slika){
        int[][] tabela = new int[height][width];
        int vsotaBarv = 0;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                vsotaBarv = 0;
                for (int k = 0; k < 3; k++){
                    vsotaBarv += slika[i][j][k];
                }
                tabela[i][j] = (vsotaBarv/3 * 255) / 1023;
            }
        }
        return tabela;
    }


    public static void preberiVseInIzpisi(String[] imenaSlik){

        for (int i = 0; i < imenaSlik.length - 1; i++){
            for (int j = imenaSlik.length - 1; j > i; j-- ) {
                if (((imenaSlik[i+1].compareToIgnoreCase(imenaSlik[j]) > 0) && (Math.round(svetlostSlike(preberiSliko(imenaSlik[i+1]))) == Math.round(svetlostSlike(preberiSliko(imenaSlik[j]))))
                        || (Math.round(svetlostSlike(preberiSliko(imenaSlik[i+1]))) < Math.round(svetlostSlike(preberiSliko(imenaSlik[j])))))){
                    String temp = imenaSlik[i+1];
                    imenaSlik[i+1] = imenaSlik[j];
                    imenaSlik[j] = temp;
                }
            }
        }

        for (int i = 0; i < imenaSlik.length - 1; i++) {
            System.out.println(imenaSlik[i+1] + " (" + Math.round(svetlostSlike(preberiSliko(imenaSlik[i+1]))) + ")");
        }
    }

    public static void konvolucijaJedro(int[][] slika){
        int[][] tabela = new int[height-2][width-2];
        for (int i = 0, iCounter = 0; i < height-2; i++){
            for (int j = 0, jCounter = 0; j < width-2; j++){
                int vsota = 0;

                vsota += slika[i][j];
                vsota += slika[i][j+1];
                vsota += slika[i][j+2];
                vsota += slika[i+1][j];
                vsota += slika[i+1][j+1];
                vsota += slika[i+1][j+2];
                vsota += slika[i+2][j];
                vsota += slika[i+2][j+1];
                vsota += slika[i+2][j+2];

                tabela[iCounter][jCounter] = vsota;
                jCounter++;

            }
            iCounter++;
        }
        height -= 2;
        width -= 2;
        izpisiSliko(tabela);
    }

    public static void konvolucijaGlajenje(int[][] slika){

        int[][] tabela = new int[height+2][width+2];
        for (int i = 0; i < height; i++){ //copy pasta tabela
            for (int j = 0; j < width; j++){
                tabela[i+1][j+1] = slika[i][j];
            }
        }

        for (int i = 0; i < height; i++){
            tabela[i+1][0] = slika[i][0]; //leva
            tabela[i+1][width+1] = slika[i][width-1]; //desna
        }

        for (int j = 0; j < width; j++){
            tabela[0][j+1] = slika[0][j]; //zgorna
            tabela[height+1][j+1] = slika[height-1][j]; //spodna
        }

        tabela[0][0] = slika[0][0]; //levo zgori
        tabela[height+1][0] = slika[height-1][1]; //levo spodi
        tabela[0][width+1] = slika[0][width-1]; //desno zgori
        tabela[height+1][width+1] = slika[height-1][width-1]; //desno spodi


        for (int i = 0, iCounter = 0; i < height; i++){
            for (int j = 0, jCounter = 0; j < width; j++){
                int vsota = 0;

                vsota += Math.round(tabela[i][j] * 1/16.0);
                vsota += Math.round(tabela[i][j+1] * 1/8.0);
                vsota += Math.round(tabela[i][j+2] * 1/16.0);
                vsota += Math.round(tabela[i+1][j] * 1/8.0);
                vsota += Math.round(tabela[i+1][j+1] * 1/4.0);
                vsota += Math.round(tabela[i+1][j+2] * 1/8.0);
                vsota += Math.round(tabela[i+2][j] * 1/16.0);
                vsota += Math.round(tabela[i+2][j+1] * 1/8.0);
                vsota += Math.round(tabela[i+2][j+2] * 1/16.0);
                slika[iCounter][jCounter] = vsota;
                jCounter++;

            }
            iCounter++;
        }

        izpisiSliko(slika);
    }

    public static void konvolucijaRobovi(int[][] slika){
        int[][] robovi = new int[height+2][width+2];

        for (int i = 0; i < height; i++){ //copy pasta tabela
            for (int j = 0; j < width; j++){
                robovi[i+1][j+1] = slika[i][j];
            }
        }

        for (int i = 0; i < height; i++){
            robovi[i+1][0] = slika[i][0]; //leva
            robovi[i+1][width+1] = slika[i][width-1]; //desna
        }

        for (int j = 0; j < width; j++){
            robovi[0][j+1] = slika[0][j]; //zgorna
            robovi[height+1][j+1] = slika[height-1][j]; //spodna
        }

        robovi[0][0] = slika[0][0]; //levo zgori
        robovi[height+1][0] = slika[height-1][1]; //levo spodi
        robovi[0][width+1] = slika[0][width-1]; //desno zgori
        robovi[height+1][width+1] = slika[height-1][width-1]; //desno spodi

        int maxStevilo = 0;
        for (int i = 0, iCounter = 0; i < height; i++) {
            for (int j = 0, jCounter = 0; j < width; j++) {
                int vsotaNavpicno = 0;

                vsotaNavpicno += Math.round(robovi[i][j] * 1);
                vsotaNavpicno += Math.round(robovi[i][j + 2] * -1);
                vsotaNavpicno += Math.round(robovi[i + 1][j] * 2);
                vsotaNavpicno += Math.round(robovi[i + 1][j + 2] * -2);
                vsotaNavpicno += Math.round(robovi[i + 2][j] * 1);
                vsotaNavpicno += Math.round(robovi[i + 2][j + 2] * -1);

                int vsotaVodoravno = 0;
                vsotaVodoravno += Math.round(robovi[i][j] * 1);
                vsotaVodoravno += Math.round(robovi[i][j+1] * 2);
                vsotaVodoravno += Math.round(robovi[i][j+2] * 1);

                vsotaVodoravno += Math.round(robovi[i+2][j] * -1);
                vsotaVodoravno += Math.round(robovi[i+2][j+1] * -2);
                vsotaVodoravno += Math.round(robovi[i+2][j+2] * -1);

                int trenutnoStevilo = (int)Math.round(Math.sqrt((Math.pow(vsotaVodoravno, 2) + Math.pow(vsotaNavpicno, 2))));

                if (trenutnoStevilo > maxStevilo)
                    maxStevilo = trenutnoStevilo;

                slika[iCounter][jCounter] = trenutnoStevilo;
                jCounter++;

            }
            iCounter++;
        }

        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++)
                slika[i][j] = (int)Math.round((slika[i][j] * 255.0 / maxStevilo));
        }
        izpisiSliko(slika);
    }
}

