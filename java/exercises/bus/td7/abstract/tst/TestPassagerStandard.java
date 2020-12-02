package tec;

class TestPassagerStandard extends TestPassagerAbstrait{

    /*
      public static void main (String[] args) throws TecException {
      boolean estMisAssertion = false;
      assert estMisAssertion = true;

      if (!estMisAssertion) {
      System.out.println("Execution impossible sans l'option -ea");
      return;
      }

      int nbTest = 0;

      //************ Verifier l'instanciation *************
      System.out.print('.'); nbTest++;
      new TestPassagerStandard().testInstanciation();

      //********* Verifier changement d'etat **************
      System.out.print('.'); nbTest++;
      new TestPassagerStandard().testGestionEtat();

      //********* Verifier les interactions  *************
      System.out.print('.'); nbTest++;
      new TestPassagerStandard().testInteractionMontee();

      System.out.print('.'); nbTest++;
      new TestPassagerStandard().testInteractionArret();

      //********* Verifier les cas limites  *************
      System.out.print('.'); nbTest++;
      new TestPassagerStandard().testExceptionCasLimite();

      System.out.println("(" + nbTest + "):OK: " + "tec.PassagerStandard");
      }
    */

    protected PassagerAbstrait creerPassager(String nom, int destination) {
	return new PassagerStandard(nom, destination);
    }

    /* Interaction a la montee
     * Trois cas
     *  - des places assises et debout
     *  - pas de place assise
     *  - aucune place.
     */
    public void testInteractionMontee() throws TecException {
	PassagerStandard p = new PassagerStandard("yyy", 5);

	FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);
	faux = new FauxVehicule(FauxVehicule.ASSIS);
	p.monterDans(faux);

	assert "monteeDemanderAssis" == getLastLog(faux) : "assis";

	faux = new FauxVehicule(FauxVehicule.DEBOUT);
	p.monterDans(faux);

	assert "monteeDemanderDebout" == getLastLog(faux) : "debout";

	faux = new FauxVehicule(FauxVehicule.PLEIN);
	p.monterDans(faux);

	assert 0 == faux.logs.size() : "pas de place";
    }

    /* Interaction a un arret
     * Deux cas
     *  - numero d'arret < a la destination
     *  - numero d'arret >= a la destination
     */
    public void testInteractionArret() {
	PassagerStandard p = new PassagerStandard("yyy", 5);

	FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);

	p.nouvelArret(faux, 1);
	assert 0 == faux.logs.size() : "pas a destination";

	p.nouvelArret(faux, 5);
	assert "arretDemanderSortie" == getLastLog(faux) : "destination";
    }

    private String getLastLog(FauxVehicule f) {
	return f.logs.get(f.logs.size() - 1);
    }
}
