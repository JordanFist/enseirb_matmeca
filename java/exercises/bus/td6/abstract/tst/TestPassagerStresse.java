package tec;

class TestPassagerStresse extends TestPassagerAbstrait {
    
    public static void main (String[] args) {
	boolean estMisAssertion = false;
	assert estMisAssertion = true;

	if (!estMisAssertion) {
	    System.out.println("Execution impossible sans l'option -ea");
	    return;
	}

	int nbTest = 0;

	//************ Verifier l'instanciation *************
	System.out.print('.'); nbTest++;
	new TestPassagerStresse().testInstanciation();

	//********* Verifier changement d'etat **************
	System.out.print('.'); nbTest++;
	new TestPassagerStresse().testGestionEtat();

	//********* Verifier les interactions  *************
	System.out.print('.'); nbTest++;
	new TestPassagerStresse().testInteractionMontee();

	System.out.print('.'); nbTest++;
	new TestPassagerStresse().testInteractionArret();

	System.out.println("(" + nbTest + "):OK: " + "tec.PassagerStresse");
    }

    protected PassagerAbstrait creerPassager(String nom, int destination) {
	return new PassagerStresse(nom, destination, new ArretPrudent());
    }

    /* Interaction a la montee
     * Trois cas
     *  - des places assises et debout
     *  - pas de place assise
     *  - aucune place.
     */
    void testInteractionMontee() {
     	PassagerStresse p = new PassagerStresse("yyy", 5, new ArretPrudent());

	FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);
	faux = new FauxVehicule(FauxVehicule.ASSIS);
	p.monterDans(faux);

	assert "monteeDemanderAssis" == getLastLog(faux) : "assis";
    
	faux = new FauxVehicule(FauxVehicule.DEBOUT);
	p.monterDans(faux);

	assert 0 == faux.logs.size() : "le passager ne veut pas etre debout";

	faux = new FauxVehicule(FauxVehicule.PLEIN);
	p.monterDans(faux);

	assert 0 == faux.logs.size() : "plein";
    }

    /* Interaction a un arret
     * Deux cas
     *  - numero d'arret < a la destination
     *  - numero d'arret >= a la destination
     */
    void testInteractionArret() {
	PassagerStresse p = new PassagerStresse("yyy", 5, new ArretPrudent());

	FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);

	p.nouvelArret(faux, 1);
	assert 0 == faux.logs.size() : "pas a destination";

	p.nouvelArret(faux, 5);
	assert "arretDemanderSortie" == getLastLog(faux) : "destination";
    }

    private String getLastLog(FauxVehicule f) {
	return f.logs.get(f.logs.size() -1);
    }
    
}
