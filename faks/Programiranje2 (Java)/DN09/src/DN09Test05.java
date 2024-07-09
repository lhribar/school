import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;

public class DN09Test05 {

    Tekmovanje miniTekmovanje;
    Tekmovanje praznoTekmovanje;

    ZgodovinaTekmovanj miniZgodovinaTekmovanj;



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
    public void testConstructor(){
        //Testira razred zgodovinaTekmovanj
        // Konstruktor mora ustrezno nastaviti zgodovino tekmovanj
        miniZgodovinaTekmovanj = new ZgodovinaTekmovanj(new ArrayList<>(Arrays.asList(miniTekmovanje, miniTekmovanje)));
        Assert.assertNotNull(miniZgodovinaTekmovanj);
    }
    /*
    @Test
    public void testBranjePodatkov(){
        // Testira branje podatkov
        // Metoda izDatotek mora ustrezno delovati
        ZgodovinaTekmovanj zgodovinaTekmovanj = ZgodovinaTekmovanj.izDatotek("viri/tekmovalci_sample.csv", "viri/glasovi_sample.csv");
        Assert.assertEquals(zgodovinaTekmovanj.seznamTekmovanj.get(0).getSeznamTekmovalcev().get(0).getDrzava(), "Švedska");
        Assert.assertEquals(zgodovinaTekmovanj.seznamTekmovanj.get(2).getSeznamTekmovalcev().get(5).getDrzava(), "Ukrajina");
    }

    @Test
    public void testSkupnoSteviloTock(){
        // Testira skupno število točk
        miniZgodovinaTekmovanj = new ZgodovinaTekmovanj(new ArrayList<>(Arrays.asList(miniTekmovanje, miniTekmovanje)));
        Assert.assertEquals(miniZgodovinaTekmovanj.getSkupnoSteviloTock("Islandija"), 24);
        Assert.assertEquals(miniZgodovinaTekmovanj.getSkupnoSteviloTock("Armenija"), 0);

        ZgodovinaTekmovanj zgodovinaTekmovanj = ZgodovinaTekmovanj.izDatotek("viri/tekmovalci_sample.csv", "viri/glasovi_sample.csv");
        Assert.assertEquals(zgodovinaTekmovanj.getSkupnoSteviloTock("Islandija"), 146);
        Assert.assertEquals(zgodovinaTekmovanj.getSkupnoSteviloTock("Armenija"), 156);
    }
    @Test
    public void testPovprecnaUvrstitev(){
        // Testira povprečno uvrstitev
        miniZgodovinaTekmovanj = new ZgodovinaTekmovanj(new ArrayList<>(Arrays.asList(miniTekmovanje, miniTekmovanje)));
        Assert.assertEquals(miniZgodovinaTekmovanj.povprecnaUvrstitev("Islandija"), 1, 0.01);
        Assert.assertEquals(miniZgodovinaTekmovanj.povprecnaUvrstitev("Armenija"), 3, 0.01);
        Assert.assertEquals(miniZgodovinaTekmovanj.povprecnaUvrstitev("Češka"), 2, 0.01);

        ZgodovinaTekmovanj zgodovinaTekmovanj = ZgodovinaTekmovanj.izDatotek("viri/tekmovalci_sample.csv", "viri/glasovi_sample.csv");
        Assert.assertEquals(zgodovinaTekmovanj.povprecnaUvrstitev("Islandija"), 22, 0.01);
        Assert.assertEquals(zgodovinaTekmovanj.povprecnaUvrstitev("Armenija"), 15, 0.01);
        Assert.assertEquals(zgodovinaTekmovanj.povprecnaUvrstitev("Češka"), 22, 0.01);
    }

    @Test
    public void testNajboljsaUvrstitev(){
        // Testira najboljšo uvrstitev
        miniZgodovinaTekmovanj = new ZgodovinaTekmovanj(new ArrayList<>(Arrays.asList(miniTekmovanje, miniTekmovanje)));
        Assert.assertEquals(miniZgodovinaTekmovanj.najboljsaUvrstitev("Islandija"), 1);
        Assert.assertEquals(miniZgodovinaTekmovanj.najboljsaUvrstitev("Armenija"), 3);
        Assert.assertEquals(miniZgodovinaTekmovanj.najboljsaUvrstitev("Češka"), 2);

        ZgodovinaTekmovanj zgodovinaTekmovanj = ZgodovinaTekmovanj.izDatotek("viri/tekmovalci_sample.csv", "viri/glasovi_sample.csv");
        Assert.assertEquals(zgodovinaTekmovanj.najboljsaUvrstitev("Islandija"), 2);
        Assert.assertEquals(zgodovinaTekmovanj.najboljsaUvrstitev("Armenija"), 14);
        Assert.assertEquals(zgodovinaTekmovanj.najboljsaUvrstitev("Češka"), 10);
    }


    @Test
    public void testPobrateneDrzave(){
        // Testira pobratene države
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        ZgodovinaTekmovanj zgodovinaTekmovanj = ZgodovinaTekmovanj.izDatotek("viri/tekmovalci_sample.csv", "viri/glasovi_sample.csv");

        zgodovinaTekmovanj.izpisiPobrateneDrzave(5);

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Drzave z najvec medsebojnih glasov:\n"+
                "1. Norveška <-(74t)-> Švedska\n"+
                "2. Estonija <-(59t)-> Švedska\n"+
                "3. Belgija <-(54t)-> Švedska\n"+
                "4. Hrvaška <-(53t)-> Slovenija\n"+
                "5. Islandija <-(51t)-> Švedska\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));
    }*/

}