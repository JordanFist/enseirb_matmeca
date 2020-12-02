package tec;
public abstract class TestPassagerAbstrait{
  //********************************************************
  /* Etat apres instanciation
   * Un seul cas
   */
  public void testInstanciation() {
    PassagerStandard p = new PassagerStandard("xxx", 3);

    assert false == p.estAssis();
    assert false == p.estDebout();
    assert true == p.estDehors();
  }

  /* Gestion des changement d'état.
   *
   * Changer Debout puis Dehors puis assis.
   */
  public void testGestionEtat() {
    PassagerStandard p = new PassagerStandard("yyy", 3);

    p.changerEnDebout();
    assert false == p.estAssis();
    assert true == p.estDebout();
    //assert false == p.estDehors();

    p.changerEnDehors();
    assert false == p.estAssis();
    assert false == p.estDebout();
    assert true == p.estDehors();

    p.changerEnAssis();
    assert true == p.estAssis();
    assert false == p.estDebout();
    assert false == p.estDehors();
  }

  /* Interaction a la montee
   * Trois cas
   *  - des places assises et debout
   *  - pas de place assise
   *  - aucune place.
   */
  public void testInteractionMontee() {
    PassagerStandard p = new PassagerStandard("yyy", 5);

    FauxVehicule faux = new FauxVehicule(FauxVehicule.VIDE);
    //faux = new FauxVehicule(FauxVehicule.ASSIS);
    p.monterDans(faux);

    assert "monteeDemanderAssis" == getLastLog(faux) : "assis";

    faux = new FauxVehicule(FauxVehicule.DEBOUT);
    p.monterDans(faux);

    assert "monteeDemanderDebout" == getLastLog(faux) : "debout";

    faux = new FauxVehicule(FauxVehicule.PLEIN);
    p.monterDans(faux);

    assert 0 == faux.logs.size() : "pas de place";
  }


     String getLastLog(FauxVehicule f) {
      return f.logs.get(f.logs.size() -1);
}

}
