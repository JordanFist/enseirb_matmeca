package tec;

import java.io.Writer;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class Fichier extends Collecte {

    private void ecrireDuTexte(Writer w) {
        PrintWriter p = new PrintWriter(w);
        p.println("numeroArret = " + numeroArret);
        p.println("nbPassagersEntres = " + nbPassagersEntres);
        p.println("nbPassagersSortis = " + nbPassagersSortis);
        p.flush();
    }

    void changerArret() {
        FileWriter file = null;
        try {
            file = new FileWriter("Data" + numeroArret +".txt");
        } catch (IOException e) {
            System.out.println("Le fichier ne peut pas etre crée");
            System.exit(1);
        }

        ecrireDuTexte(file);

        try {
            file.close();
        } catch(IOException e) {
            System.out.println("Le fichier ne peut pas etre fermé");
            System.exit(1);
        }
        super.changerArret();
    }
}