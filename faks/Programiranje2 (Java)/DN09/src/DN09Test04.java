import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;

public class DN09Test04 {

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
    public void testLocenGlas(){
        // Testira locenGlas
        // Konstruktor mora slediti navodilom
        LocenGlas locenGlas = new LocenGlas("Islandija", "Češka", 10, 8, 2);
        Assert.assertNotNull(locenGlas);
    }

    @Test
    public void testUtezeniKriterij(){
        // Testira delovanje uteženega kriterija
        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");

        UtezeniKriterij k = new UtezeniKriterij(0.1f, 5.3f);
        Assert.assertEquals(k.steviloTock(tekmovanje, "Slovenija"), 179);
        Assert.assertEquals(k.steviloTock(tekmovanje, "Švedska"), 1826);
        Assert.assertEquals(k.steviloTock(tekmovanje, "Irska"), 0);

        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Armenija"), 0);
        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Islandija"), 64);
        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Češka"), 21);

    }

    @Test
    public void preveriIzpisDrzav(){
        // Testira izpis držav z uteženim kriterijem
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");
        UtezeniKriterij k = new UtezeniKriterij(0.2f, 12f);

        tekmovanje.setKriterij(k);

        tekmovanje.izpisiRezultateUrejeno(5);

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Najboljse uvrsceni tekmovalci:\n"+
                "1. (Švedska) Loreen - Tattoo: 4129t\n"+
                "2. (Izrael) Noa Kirel - Unicorn: 2161t\n"+
                "3. (Italija) Marco Mengoni - Due vite: 2147t\n"+
                "4. (Finska) Käärijä - Cha Cha Cha: 1875t\n"+
                "5. (Estonija) Alika - Bridges: 1756t\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));


    }


}