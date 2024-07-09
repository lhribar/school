import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;

public class DN09Test03 {

    Tekmovanje miniTekmovanje;
    Tekmovanje praznoTekmovanje;



    @Before
    public void init(){
        ArrayList<Tekmovalec> seznamTekmovalcev = new ArrayList<>(Arrays.asList(
                new Tekmovalec("Češka", "Vesna", "My Sister's Crown"),
                new Tekmovalec("Armenija", "Brunette", "Future Lover"),
                new Tekmovalec("Islandija", "Diljá", "Power")
        ));

        ArrayList<Glas> seznamGlasov = new ArrayList<>(Arrays.asList(
                new Glas("Češka", "Islandija", 6),
                new Glas("Armenija", "Islandija", 6),
                new Glas("Armenija", "Češka", 4),
                new Glas("Islandija", "Češka", 0)
        ));

        miniTekmovanje = new Tekmovanje(seznamTekmovalcev, seznamGlasov);

        // Prazno tekmovanje
        praznoTekmovanje = new Tekmovanje(new ArrayList<>(), new ArrayList<>());
    }

    @Test
    public void testIzpisZmagovalca(){
        // Testira izpis zmagovalca
        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");
        OsnovniKriterij k = new OsnovniKriterij();

        tekmovanje.setKriterij(k);

        Tekmovalec zmagovalec = tekmovanje.getZmagovalec();
        Assert.assertEquals(zmagovalec.getDrzava(), "Švedska");

        Assert.assertEquals(miniTekmovanje.getZmagovalec().getDrzava(), "Islandija");
    }

    @Test
    public void testMestoDrzave(){
        // Testira mesto države
        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");
        OsnovniKriterij k = new OsnovniKriterij();

        tekmovanje.setKriterij(k);

        int mesto = tekmovanje.getMesto("Nizozemska");

        Assert.assertEquals(mesto, 32);

        // Za manjkajoce drzave metoda vrne -1
        int mesto2 = tekmovanje.getMesto("Slovenijaaaa");

        Assert.assertEquals(mesto2, -1);

        int mesto3 = tekmovanje.getMesto("Slovenija");

        Assert.assertEquals(mesto3, 21);
    }

    @Test
    public void testIzpisNajboljsihDrzav(){
        // Testira izpis najboljših držav
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");
        OsnovniKriterij k = new OsnovniKriterij();

        tekmovanje.setKriterij(k);

        tekmovanje.izpisiRezultateUrejeno(5);

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Najboljse uvrsceni tekmovalci:\n"+
                "1. (Švedska) Loreen - Tattoo: 583t\n"+
                "2. (Finska) Käärijä - Cha Cha Cha: 526t\n"+
                "3. (Izrael) Noa Kirel - Unicorn: 362t\n"+
                "4. (Italija) Marco Mengoni - Due vite: 350t\n"+
                "5. (Norveška) Alessandra - Queen of Kings: 268t\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));



    }

    @Test
    public void testIzpisNajboljsihDrzav2(){
        // Testira izpis, ce je držav vec kot argument funkcije
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));


        OsnovniKriterij k = new OsnovniKriterij();

        miniTekmovanje.setKriterij(k);

        miniTekmovanje.izpisiRezultateUrejeno(5);

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Najboljse uvrsceni tekmovalci:\n"+
                "1. (Islandija) Diljá - Power: 12t\n"+
                "2. (Češka) Vesna - My Sister's Crown: 4t\n"+
                "3. (Armenija) Brunette - Future Lover: 0t\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));



    }


}