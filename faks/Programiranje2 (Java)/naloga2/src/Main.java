String prepleti(String niz1, String niz2){
    String a = "";

    for (int i = 0; i < niz1.length() || i < niz2.length(); i++){
        if (i < niz1.length())
            a += niz1.charAt(i);
        else
            a += " ";
        if (i < niz2.length())
            a += niz2.charAt(i);
        else
            a += " ";

        }
    return a;
}

void odpleti(String niz){
    String niz1 = "";
    String niz2 = "";
    for (int i = 0; i < niz.length(); i += 2){

        niz1 += niz.charAt(i);
    }

    for (int i = 1; i < niz.length(); i += 2){

        niz2 += niz.charAt(i);
    }

    System.out.println(niz1);
    System.out.println(niz2);
}