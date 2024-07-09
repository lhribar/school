import java.lang.reflect.Array;
import java.util.ArrayList;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DN09 {
    public static void main(String[] args) {
        Tekmovanje tekmovanje = Tekmovanje.izDatotek(args[1], args[2]);
        if (args[0].equals("izpisiTekmovanje")) {
            tekmovanje.izpisiTekmovalce();

            System.out.println();
            tekmovanje.izpisiGlasove();
        }
        else if (args[0].equals("izpisiTocke")){
            tekmovanje.izpisiTocke();
        }
        else if (args[0].equals("najboljse")){
            tekmovanje.izpisiRezultateUrejeno(Integer.parseInt(args[3]));
        }
        else if (args[0].equals("utezeno")){
            UtezeniKriterij utezeni = new UtezeniKriterij(Float.parseFloat(args[4]), Float.parseFloat(args[5]));
            tekmovanje.setKriterij(utezeni);
            tekmovanje.izpisiRezultateUrejeno(Integer.parseInt(args[3]));
        }

    }

}

class Tekmovalec {
    String drzava, izvajalec, naslov_pesmi;
    Tekmovalec(String drzava, String izvajalec, String naslov_pesmi) {
        this.drzava = drzava;
        this.izvajalec = izvajalec;
        this.naslov_pesmi = naslov_pesmi;
    }

    public String getDrzava() {
        return drzava;
    }

    public String getIzvajalec() {
        return izvajalec;
    }

    public String getNaslov_pesmi() {
        return naslov_pesmi;
    }

    public String toString() {
        return "(" + drzava + ") " + izvajalec + " - " + naslov_pesmi;
    }
}


class Glas {
    String odDrzave, zaDrzavo;
    int stTock;

    Glas(String odDrzave, String zaDrzavo, int stTock){
        this.odDrzave = odDrzave;
        this.zaDrzavo = zaDrzavo;
        this.stTock = stTock;
    }

    public String getOdDrzave() {
        return odDrzave;
    }

    public String getZaDrzavo() {
        return zaDrzavo;
    }

    public String toString() {
        return odDrzave + " --" +stTock + "t-> " + zaDrzavo;
    }
}


class Tekmovanje {
    ArrayList<Tekmovalec> seznamTekmovalcev;
    ArrayList<Glas> seznamGlasov;
    Kriterij kriterij;
    public boolean urejeno = false;

    Tekmovanje(ArrayList<Tekmovalec> seznamTekmovalcev, ArrayList<Glas> seznamGlasov) {
        this.seznamTekmovalcev = seznamTekmovalcev;
        this.seznamGlasov = seznamGlasov;
        this.kriterij = new OsnovniKriterij();
    }

    public ArrayList<Tekmovalec> getSeznamTekmovalcev(){
        return seznamTekmovalcev;
    }

    public ArrayList<Glas> getSeznamGlasov(){
        return seznamGlasov;
    }

    public void setKriterij(Kriterij kriterij){
        urejeno = false;
        this.kriterij = kriterij;
    }



    static Tekmovanje izDatotek(String datotekaTekmovalci, String datotekaGlasovi){
        ArrayList<Tekmovalec> tempSeznamTekmovalcev = new ArrayList<Tekmovalec>();
        ArrayList<Glas> tempSeznamGlas = new ArrayList<Glas>();

        try {
            File myObj = new File(datotekaTekmovalci);
            Scanner myReader = new Scanner(myObj);
            String data = myReader.nextLine();
            while (myReader.hasNextLine()) {
                data = myReader.nextLine();
                String[] sdata = data.split(";");
                Tekmovalec tempTekmovalec = new Tekmovalec(sdata[1], sdata[2], sdata[3]);
                tempSeznamTekmovalcev.add(tempTekmovalec);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            return null;
        }

        try {
            File myObj = new File(datotekaGlasovi);
            Scanner myReader = new Scanner(myObj);
            String data = myReader.nextLine();
            while (myReader.hasNextLine()) {
                data = myReader.nextLine();
                String[] sdata = data.split(";");
                if (Integer.parseInt(sdata[0]) < 2016){
                    Glas tempGlas = new Glas(sdata[2], sdata[3], Integer.parseInt(sdata[4]));
                }

                else{
                    int stTock = 0;
                    if (sdata.length != 6)
                        stTock = Integer.valueOf(sdata[6]);
                    LocenGlas tempLocenGlas = new LocenGlas(sdata[2], sdata[3], Integer.valueOf(sdata[4]), Integer.valueOf(sdata[5]), stTock);
                    tempSeznamGlas.add(tempLocenGlas);
                }

            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            return null;
        }

        Tekmovanje tempTekmovanje = new Tekmovanje(tempSeznamTekmovalcev, tempSeznamGlas);

        return tempTekmovanje;
    }



    public void izpisiTekmovalce() {
        if (seznamTekmovalcev.isEmpty()) {
            System.out.println("Seznam tekmovalcev je prazen.");
            return;
        }

        System.out.println("Seznam tekmovalcev:");
        for (Tekmovalec tekmovalec : seznamTekmovalcev) {
           System.out.println(tekmovalec.toString());
        }
    }

    public void izpisiGlasove() {
        if (seznamGlasov.isEmpty()) {
            System.out.println("Seznam glasov je prazen.");
            return;
        }

        System.out.println("Seznam glasov:");
        for (Glas glas : seznamGlasov) {
            System.out.println(glas.toString());
        }
    }

    public int steviloTock(String drzava){

        int tocke = 0;
        for (int i = 0; i < seznamGlasov.size(); i++){
            if (seznamGlasov.get(i).odDrzave.equals(drzava)){
                tocke = kriterij.steviloTock(this, drzava);
                break;
            }
        }
        return tocke;
    }

    public void izpisiTocke() {
        if (seznamTekmovalcev.size() == 0){
            System.out.println("Seznam tekmovalcev je prazen.");
            return;
        }
        System.out.println("Seznam tekmovalcev in njihovih tock:");
        for (Tekmovalec tekmovalec: seznamTekmovalcev){
            int tocke = kriterij.steviloTock(this, tekmovalec.getDrzava());
            System.out.println(tekmovalec.toString() + ": " + tocke + "t");
        }
    }

    Tekmovalec getZmagovalec() {
        Tekmovalec zmagovalec = null;
        int najTocke = 0;
        for (Tekmovalec tekmovalec: seznamTekmovalcev){
            int tocke = kriterij.steviloTock(this, tekmovalec.getDrzava());
            if (tocke > najTocke) {
                zmagovalec = tekmovalec;
                najTocke = tocke;
            }
        }
        return zmagovalec;
    }

    public void urediPoTockah() {
        for (int i = 0; i < this.seznamTekmovalcev.size(); i++){
            for (int j = this.seznamTekmovalcev.size() - 1; j > i; j--){
                if (kriterij.steviloTock(this, seznamTekmovalcev.get(j).getDrzava()) > kriterij.steviloTock(this, seznamTekmovalcev.get(j-1).getDrzava())){
                    Tekmovalec temp = seznamTekmovalcev.get(j);
                    seznamTekmovalcev.set(j, seznamTekmovalcev.get(j-1));
                    seznamTekmovalcev.set(j-1, temp);
                }
            }
        }
        urejeno = true;
    }

    int getMesto(String drzava){
        urediPoTockah();
        int mesto = 1;
        for (Tekmovalec tekmovalec: seznamTekmovalcev){
            if (tekmovalec.getDrzava().equals(drzava))
                return mesto;
            mesto ++;
        }
        return -1;
    }

    void izpisiRezultateUrejeno(int topK){
        urediPoTockah();
        System.out.println("Najboljse uvrsceni tekmovalci:");
        int stevec = 0;
        for (int i = 0; i < seznamTekmovalcev.size() && i < topK; i++){
            System.out.println(i+1 + ". " + seznamTekmovalcev.get(i).toString() + ": " + steviloTock(seznamTekmovalcev.get(i).getDrzava()) + "t");
        }
    }

}

interface Kriterij {
    int steviloTock(Tekmovanje tekmovanje, String drzava);
}

class OsnovniKriterij implements Kriterij {
    public int steviloTock(Tekmovanje tekmovanje, String drzava){
        int tocke = 0;
        for (int i = 0; i < tekmovanje.seznamGlasov.size(); i++){
            if (tekmovanje.seznamGlasov.get(i).zaDrzavo.equals(drzava)){
                tocke += tekmovanje.seznamGlasov.get(i).stTock;
            }
        }
        return tocke;
    }
}

class LocenGlas extends Glas {
    private int stTockGlasovi;
    private int stTockZirija;
    public LocenGlas(String odDrzave, String zaDrzavo, int stTock, int stTockGlasovi, int stTockZirije) {
        super(odDrzave, zaDrzavo, stTock);
        this.stTockGlasovi = stTockGlasovi;
        this.stTockZirija = stTockZirije;
    }

    public int getStTockGlasovi() {
        return stTockGlasovi;
    }

    public int getStTockZirija() {
        return stTockZirija;
    }
}

class UtezeniKriterij implements Kriterij {
    float utezGlasovanja;
    float utezZirija;

    public UtezeniKriterij(float utezGlasovanja, float utezZirija){
        this.utezGlasovanja = utezGlasovanja;
        this.utezZirija = utezZirija;
    }

    public int steviloTock(Tekmovanje tekmovanje, String drzava) {
        float tocke = 0;
        for (int i = 0; i < tekmovanje.seznamGlasov.size(); i++){
            if (tekmovanje.seznamGlasov.get(i).zaDrzavo.equals(drzava)){
                if (tekmovanje.seznamGlasov.get(i) instanceof LocenGlas){
                    tocke += ((LocenGlas) tekmovanje.seznamGlasov.get(i)).getStTockGlasovi() * utezGlasovanja;
                    tocke += ((LocenGlas) tekmovanje.seznamGlasov.get(i)).getStTockZirija() * utezZirija;
                }
                else {
                    tocke += tekmovanje.seznamGlasov.get(i).stTock * utezZirija;
                }
            }
        }
        return Math.round(tocke);
    }
}

class ZgodovinaTekmovanj {
    ArrayList<Tekmovanje> seznamTekmovanj;
    ZgodovinaTekmovanj(ArrayList<Tekmovanje> seznamTekmovanj){
        this.seznamTekmovanj = seznamTekmovanj;
    }

}
