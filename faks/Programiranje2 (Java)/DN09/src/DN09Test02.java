import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;

public class DN09Test02 {

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
    public void testOsnovniKriterij() {
        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");

        OsnovniKriterij k = new OsnovniKriterij();
        Assert.assertEquals(k.steviloTock(tekmovanje, "Slovenija"), 78);
        Assert.assertEquals(k.steviloTock(tekmovanje, "Švedska"), 583);
        Assert.assertEquals(k.steviloTock(tekmovanje, "Irska"), 0);

        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Armenija"), 0);
        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Islandija"), 12);
        Assert.assertEquals(k.steviloTock(miniTekmovanje, "Češka"), 4);
    }

    @Test
    public void testStTock(){
        Tekmovanje tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");

        Assert.assertEquals(tekmovanje.steviloTock("Slovenija"), 78);
        Assert.assertEquals(tekmovanje.steviloTock("Švedska"), 583);
        Assert.assertEquals(tekmovanje.steviloTock("Irska"), 0);

        Assert.assertEquals(miniTekmovanje.steviloTock("Armenija"), 0);
        Assert.assertEquals(miniTekmovanje.steviloTock("Islandija"), 12);
        Assert.assertEquals(miniTekmovanje.steviloTock("Češka"), 4);

        // Testni kriterij, ki vraca toliko tock, kot je crk v imenu drzave
        Kriterij mojKriterij = new Kriterij() {
            @Override
            public int steviloTock(Tekmovanje tekmovanje, String drzava) {
                return drzava.length();
            }
        };

        // Testiranje nastavljanja kriterija
        tekmovanje.setKriterij(mojKriterij);
        Assert.assertEquals(tekmovanje.steviloTock("Slovenija"), 9);
        Assert.assertEquals(tekmovanje.steviloTock("Švedska"), 7);
        Assert.assertEquals(tekmovanje.steviloTock("Irska"), 5);
    }

    @Test
    public void testIzpis(){
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        miniTekmovanje.izpisiTocke();

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Seznam tekmovalcev in njihovih tock:\n" +
                "(Češka) Vesna - My Sister's Crown: 4t\n" +
                "(Armenija) Brunette - Future Lover: 0t\n" +
                "(Islandija) Diljá - Power: 12t\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));
        System.out.println(expected);
    }

    @Test
    public void testIzpisPrazna(){
        // Testira `izpisiTekmovalce()` in `izpisiGlasove()` v primeru prazenga tekmovanja
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        praznoTekmovanje.izpisiTocke();

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Seznam tekmovalcev je prazen.\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));

        System.out.println(expected);
    }

}