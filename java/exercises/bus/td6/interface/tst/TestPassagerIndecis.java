package tec;

class TestPassagerIndecis extends TestPassagerAbstrait {

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
	new TestPassagerIndecis().testInstanciation();

	//********* Verifier changement d'etat **************
	System.out.print('.'); nbTest++;
	new TestPassagerIndecis().testGestionEtat();

	//********* Verifier les interactions  *************
	System.out.print('.'); nbTest++;
	new TestPassagerIndecis().testInteractionMontee();

	System.out.print('.'); nbTest++;
	new TestPassagerIndecis().testInteractionArret();

	System.out.println("(" + nbTest + "):OK: " + "tec.PassagerIndecis");
    }

    protected PassagerAbstrait creerPassager(String nom, int destination) {
	return (PassagerAbstrait) FabriqueTec.fairePassagerIndecis(nom, destination);
    }

    /* Interaction a la montee
     * Trois cas
     *  - des places assises et debout
     *  - pas de place assise
     *  - aucune place.
     */
    void testInteractionMontee() {
	PassagerIndecis p = new PassagerIndecis("yyy", 5);

	FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);
        p.monterDans(faux);
        assert "monteeDemanderDebout" == getLastLog(faux) : "debout";

        faux = new FauxVehicule(FauxVehicule.DEBOUT);
        p.monterDans(faux);
        assert "monteeDemanderDebout" == getLastLog(faux) : "une place debout";

        faux = new FauxVehicule(FauxVehicule.PLEIN);
        p.monterDans(faux);
        assert 0 == faux.logs.size() : "pas de place";
    }

    /* Interaction a un arret
     * Deux cas
     *  - numero d'arret < a la destination
     *  - numero d'arret >= a la destination
     */
    void testInteractionArret() {
	PassagerIndecis p = new PassagerIndecis("yyy", 5);

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
