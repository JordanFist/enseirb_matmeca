public class Autobus implements Vehicule {
    private Passager passagers[];
    public int nbPlaceAssise;
    public int nbPlaceDebout;
    private int numeroArret;

    
    public Autobus(int maxAssis, int maxDebout) {
	nbPlaceAssise = maxAssis;
	nbPlaceDebout = maxDebout;
	passagers = new Passager[nbPlaceAssise + nbPlaceDebout];
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
	return (nbPlaceAssise > 0);
    }
    
    public boolean aPlaceDebout() {
	return (nbPlaceDebout > 0);
    }

    public void arretDemanderAssis(Passager p) {
	p.changerEnAssis();
	nbPlaceAssise--;
	nbPlaceDebout++;
	    
    }

    public void arretDemanderDebout(Passager p) {
	p.changerEnDebout();
	nbPlaceAssise++;
	nbPlaceDebout--;
    }

    public void arretDemanderSortie(Passager p) {
	if (p.estDehors() == false) {
	    if (p.estAssis() == true)
		nbPlaceAssise++;
	    else
		nbPlaceDebout++;
	}
	p.changerEnDehors();
	passagers[chercherPassager(p)] = null;
    }

    public void monteeDemanderAssis(Passager p) {
	int emplacement = chercherEmplacementVide();
	if (emplacement != -1) {
	    passagers[emplacement] = p;
	    if (nbPlaceAssise > 0) {
		p.changerEnAssis();
		nbPlaceAssise--;
	    }
	    else if (nbPlaceDebout > 0) {
		p.changerEnDebout();
		nbPlaceDebout--;
	    }
	}
    }

    public void monteeDemanderDebout(Passager p) {
	int emplacement = chercherEmplacementVide();
	if (emplacement != -1) {
	    passagers[emplacement] = p;
	    if (nbPlaceDebout > 0) {
		p.changerEnDebout();
		nbPlaceDebout--;
	    }
	    else if (nbPlaceAssise > 0)  {
		p.changerEnAssis();
		nbPlaceAssise--;
	    }
	}
    }

}
