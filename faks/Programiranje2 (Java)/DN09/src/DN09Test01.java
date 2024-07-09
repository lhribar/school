import org.junit.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;

public class DN09Test01 {

    Tekmovanje tekmovanje;
    Tekmovanje miniTekmovanje;
    Tekmovanje praznoTekmovanje;

    @Before
    public void init(){
        tekmovanje = Tekmovanje.izDatotek("viri/tekmovalci_2023.csv", "viri/glasovi_2023.csv");

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

        // Tekmovanje mora imeti ustrezen konstruktor
        miniTekmovanje = new Tekmovanje(seznamTekmovalcev, seznamGlasov);

        // Prazno tekmovanje
        praznoTekmovanje = new Tekmovanje(new ArrayList<>(), new ArrayList<>());
    }

    @Test
    public void testBranje(){
        // Manjkajoca datoteka mora vracati null
        Assert.assertNull(Tekmovanje.izDatotek("manjkajocaDatoteka.csv", "manjkajocaDatoteka.csv"));
        // Preveri stevilo prebranih tekmovalcev in glasov
        Assert.assertNotNull(tekmovanje);
        Assert.assertEquals(tekmovanje.getSeznamTekmovalcev().size(), 37);
        Assert.assertEquals(tekmovanje.getSeznamGlasov().size(), 554);

        Tekmovalec t = tekmovanje.getSeznamTekmovalcev().get(0);
        Assert.assertEquals(t.getDrzava(), "Albanija");
    }

    @Test
    public void testToString(){
        Tekmovalec t = new Tekmovalec("Izrael", "Noa Kirel", "Unicorn");
        Assert.assertEquals(t.toString(), "(Izrael) Noa Kirel - Unicorn");

        Glas g = new Glas("Slovenija", "Hrvaška", 10);
        Assert.assertEquals(g.toString(), "Slovenija --10t-> Hrvaška");
    }

    @Test
    public void testIzpis(){
        // Testira `izpisiTekmovalce()` in `izpisiGlasove()`
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        miniTekmovanje.izpisiTekmovalce();
        miniTekmovanje.izpisiGlasove();

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Seznam tekmovalcev:\n" +
                "(Češka) Vesna - My Sister's Crown\n" +
                "(Armenija) Brunette - Future Lover\n" +
                "(Islandija) Diljá - Power\n" +
                "Seznam glasov:\n" +
                "Češka --6t-> Islandija\n" +
                "Armenija --6t-> Islandija\n" +
                "Armenija --4t-> Češka\n" +
                "Islandija --0t-> Češka\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));

        System.out.println(expected);
    }

    @Test
    public void testIzpisPrazna(){
        // Testira `izpisiTekmovalce()` in `izpisiGlasove()` v primeru prazenga tekmovanja
        PrintStream orig = System.out;
        final ByteArrayOutputStream myOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(myOut));

        praznoTekmovanje.izpisiTekmovalce();
        praznoTekmovanje.izpisiGlasove();

        final String stdOut = myOut.toString();
        System.setOut(orig);

        String expected = "Seznam tekmovalcev je prazen.\n" +
                "Seznam glasov je prazen.\n";

        Assert.assertEquals(stdOut.trim().replace("\r", ""), expected.trim().replace("\r", ""));

        System.out.println(expected);
    }

}