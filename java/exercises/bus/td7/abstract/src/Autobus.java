package tec;

import java.util.ArrayList;
import java.util.Iterator;

public class Autobus extends Vehicule implements Transport {
    private ArrayList<Passager> passagers;
    private Jauge nbPlaceAssise;
    private Jauge nbPlaceDebout;
    private int numeroArret;

    public Autobus(int maxAssis, int maxDebout) throws IllegalArgumentException {
	if (maxAssis < 0 || maxDebout < 0)
	    throw new IllegalArgumentException();
	else {
	    nbPlaceAssise = new Jauge(maxAssis, maxAssis - 1);
	    nbPlaceDebout = new Jauge(maxDebout, maxDebout - 1);
	    passagers = new ArrayList<Passager>();
	    numeroArret = 0;
	}
    }

    private int chercherEmplacementVide() {
	for (int i = 0; i < passagers.size(); i++) {
	    if (passagers.get(i) == null)
		return i;
	}
	return -1;
    }

    private int chercherPassager(Passager p) {
	for (int i = 0; i < passagers.size(); i++) {
	    if (passagers.get(i) == p)
		return i;
	}
	return -1;
    }

    public void allerArretSuivant() {
	numeroArret++;
	for (Passager p : passagers) {
	    if (p != null)
		p.nouvelArret(this, numeroArret);

	    /*
	     * numeroArret++; ArrayList<Passager> passagers2 = new
	     * ArrayList<Passager>(passagers); Iterator it = passagers2.iterator();
	     * while(it.hasNext()) { Passager p = (Passager) it.next(); if (p != null)
	     * p.nouvelArret(this, numeroArret); }
	     */
	}
    }

    boolean aPlaceAssise() {
	return (nbPlaceAssise.estVert());
    }

    boolean aPlaceDebout() {
	return (nbPlaceDebout.estVert());
    }

    void monteeDemanderAssis(Passager p) throws IllegalStateException {
	if (chercherPassager(p) != -1)
	    throw new IllegalStateException();
	else {
	    passagers.add(p);
	    if (nbPlaceAssise.estVert()) {
		p.changerEnAssis();
		nbPlaceAssise.decrementer();
	    } else if (nbPlaceDebout.estVert()) {
		p.changerEnDebout();
		nbPlaceDebout.decrementer();
	    }
	}
    }

    void monteeDemanderDebout(Passager p) throws IllegalStateException {
	if (chercherPassager(p) != -1)
	    throw new IllegalStateException();
	else {
	    passagers.add(p);
	    if (nbPlaceDebout.estVert()) {
		p.changerEnDebout();
		nbPlaceDebout.decrementer();
	    } else if (nbPlaceAssise.estVert()) {
		p.changerEnAssis();
		nbPlaceAssise.decrementer();
	    }
	}
    }

    void arretDemanderDebout(Passager p) {
	p.changerEnDebout();
	nbPlaceAssise.incrementer();
	nbPlaceDebout.decrementer();
    }

    void arretDemanderAssis(Passager p) {
	p.changerEnAssis();
	nbPlaceAssise.decrementer();
	nbPlaceDebout.incrementer();
    }

    void arretDemanderSortie(Passager p) {
	if (p.estDehors() == false) {
	    if (p.estAssis() == true)
		nbPlaceAssise.incrementer();
	    else
		nbPlaceDebout.incrementer();
	}
	p.changerEnDehors();
	passagers.set(chercherPassager(p), null);
    }

    public String toString() {
	return ("Arret en cours: " + numeroArret + ", reste des places debout: " + nbPlaceDebout.estVert()
		+ ", reste des places assises:" + nbPlaceAssise.estVert());
    }
}
