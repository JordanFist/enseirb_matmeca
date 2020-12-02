package tec;

import java.util.ArrayList;

public class GreffonAutobus extends Autobus {
    Collecte collection;
    
    public GreffonAutobus (int maxAssis, int maxDebout, Collecte collection) throws IllegalArgumentException {
        super(maxAssis, maxDebout);
        this.collection = collection;
    }

    @Override
    public void allerArretSuivant() {
        super.allerArretSuivant();
        collection.changerArret();
    }

    @Override
    void monteeDemanderAssis(Passager p) throws IllegalStateException {
        super.monteeDemanderAssis(p);
        if (p.estDehors() == false)
            collection.uneEntree();
    }

    @Override
    void monteeDemanderDebout(Passager p) throws IllegalStateException {
        super.monteeDemanderDebout(p);
        if (p.estDehors() == false)
            collection.uneEntree();
    }
    
    @Override
    void arretDemanderSortie(Passager p) {
        if (p.estDehors() == false) {
            super.arretDemanderSortie(p);
            collection.uneSortie();
        }
    }
}