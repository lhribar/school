
import edu.princeton.cs.algs4.StdDraw;

public class DN06 {
    public static void main(String[] args) {
        String niz = args[0];

        StdDraw.setXscale(0, 100);
        StdDraw.setYscale(0, 100);

        for (int i = 0; i < 10; i++){
            if (i%3 == 0){
                StdDraw.setPenRadius(0.008);
            }
            else{
                StdDraw.setPenRadius(0.002);
            }
            StdDraw.line(5, i*10 + 5, 95, i*10+5); //navpicna
            StdDraw.line(i*10 + 5, 5, i*10 + 5, 95); //vodoravna
        }
        int visina = 90;
        int sirina = 10;
        for (int i = 0; i < niz.length(); i++){
            if (niz.charAt(i) != '0') {
                StdDraw.text(sirina, visina, Character.toString(niz.charAt(i)));
            }
            sirina += 10;
            if (sirina > 90) {
                sirina = 10;
                visina -= 10;
            }
        }
    }
}