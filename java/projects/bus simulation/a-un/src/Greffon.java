package tec;

import java.util.ArrayList;

public class Greffon {
    Vehicule vehicule;
    Collecte collection;

    public Greffon(Vehicule vehicule, Collecte collection){
        this.vehicule = vehicule;
        this.collection = collection;
    }

    public void allerArretSuivant() {
        vehicule.allerArretSuivant();
        collection.changerArret();
    }

    void monteeDemanderAssis(Passager p) throws IllegalStateException {
        vehicule.monteeDemanderAssis(p);
        collection.uneEntree();
    }

    void monteeDemanderDebout(Passager p) throws IllegalStateException {
        vehicule.monteeDemanderDebout(p);
        collection.uneEntree();
    }

    void arretDemanderSortie(Passager p) {
        vehicule.arretDemanderSortie(p);
        collection.uneSortie();
    }

    public String toString() {
        return vehicule.toString();
    }
}
