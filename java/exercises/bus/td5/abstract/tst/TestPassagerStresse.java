package tec;

import tec.PassagerStresse;

class TestPassagerStresse extends TestPassagerAbstrait{
  public static void main(String[] args) {
    boolean estMisAssertion = false;
    assert estMisAssertion = true;

    if (!estMisAssertion) {
      System.out.println("Execution impossible sans l'option -ea");
      return;





    }
    int nbTest = 0;
    System.out.print("Test Passager Stresse: ");

    //************ Verifier l'instanciation *************
    System.out.print('.'); nbTest++;
    new TestPassagerStresse().testInstanciation();

    //********* Verifier changement d'etat **************
    System.out.print('.'); nbTest++;
    new TestPassagerStresse().testGestionEtat();

    //********* Verifier les interactions  *************
    System.out.print('.'); nbTest++;
    new TestPassagerStresse().testMontee();

    System.out.print('.'); nbTest++;
    new TestPassagerStresse().testInteractionArret();

    System.out.println(" OK");

  }

  public void testMontee() {
    PassagerStresse p1 = new PassagerStresse("aze",4);
    PassagerStresse p2 = new PassagerStresse("rty",4);
    PassagerStresse p3 = new PassagerStresse("uio",4);
    Autobus a = new Autobus(1,1);
    p1.monterDans(a);
    assert p1.estAssis() : "p1 pas assis";
    p2.monterDans(a);
    assert p2.estDebout() : "p2 pas debout";
    p3.monterDans(a);
    assert p3.estDehors() : "p3 pas dehors";

  }

  public void testInteractionArret() {
    PassagerStresse p1 = new PassagerStresse("aze",3);
    Autobus a = new Autobus(1,2);
    p1.monterDans(a);
    p1.choixPlaceArret(a,1);
    assert p1.estDebout() : "p1 pas debout";
  }
}
