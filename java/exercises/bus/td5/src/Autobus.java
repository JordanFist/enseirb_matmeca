package tec;

public class Autobus implements Vehicule, Transport{
    private Passager passagers[];
    public Jauge nbPlaceAssise;
    public Jauge nbPlaceDebout;
    private int numeroArret;


    public Autobus(int maxAssis, int maxDebout) {
	nbPlaceAssise = new Jauge(maxAssis, maxAssis - 1);
	nbPlaceDebout = new Jauge(maxDebout, maxDebout - 1);
	passagers = new Passager[maxAssis + maxDebout];
	numeroArret = 0;
    }


    private int chercherEmplacementVide() {
	for (int i = 0; i < passagers.length; i++) {
	    if (passagers[i] == null)
		return i;
	}
	return -1;
    }

    private int chercherPassager(Passager p) {
	for (int i = 0; i < passagers.length; i++) {
	    if (passagers[i] == p)
		return i;
	}
	return -1;
    }


    public void allerArretSuivant() {
	numeroArret++;
	for (Passager p : passagers) {
	    if (p != null)
		p.nouvelArret(this, numeroArret);
	}
    }

    public boolean aPlaceAssise() {
		return (nbPlaceAssise.estVert());
    }

    public boolean aPlaceDebout() {
		return (nbPlaceDebout.estVert());
    }

    public void arretDemanderAssis(Passager p) {
	p.changerEnAssis();
	nbPlaceAssise.decrementer();
	nbPlaceDebout.incrementer();

    }

    public void arretDemanderDebout(Passager p) {
	p.changerEnDebout();
	nbPlaceAssise.incrementer();
	nbPlaceDebout.decrementer();
    }

    public void arretDemanderSortie(Passager p) {
	if (p.estDehors() == false) {
	    if (p.estAssis() == true)
		nbPlaceAssise.incrementer();
	    else
		nbPlaceDebout.incrementer();
	}
	p.changerEnDehors();
	passagers[chercherPassager(p)] = null;
    }

    public void monteeDemanderAssis(Passager p) {
	int emplacement = chercherEmplacementVide();
	if (emplacement != -1) {
	    passagers[emplacement] = p;
	    if (nbPlaceAssise.estVert()) {
		p.changerEnAssis();
		nbPlaceAssise.decrementer();
	    }
	    else if (nbPlaceDebout.estVert()) {
		p.changerEnDebout();
		nbPlaceDebout.decrementer();
	    }
	}
    }

    public void monteeDemanderDebout(Passager p) {
	int emplacement = chercherEmplacementVide();
	if (emplacement != -1) {
	    passagers[emplacement] = p;
	    if (nbPlaceDebout.estVert()) {
		p.changerEnDebout();
		nbPlaceDebout.decrementer();
	    }
	    else if (nbPlaceAssise.estVert())  {
		p.changerEnAssis();
		nbPlaceAssise.decrementer();
	    }
	}
    }

    public String toString() {
	return ("Arret en cours: " + numeroArret + ", reste des places debout: " + nbPlaceDebout.estVert() + ", reste des places assises:" + nbPlaceAssise.estVert());
    }
}
