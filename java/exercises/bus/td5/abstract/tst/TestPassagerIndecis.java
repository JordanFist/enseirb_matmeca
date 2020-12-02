package tec;

import tec.PassagerIndecis;

class TestPassagerIndecis extends TestPassagerAbstrait{
  public static void main(String[] args) {
    boolean estMisAssertion = false;
    assert estMisAssertion = true;

    if (!estMisAssertion) {
      System.out.println("Execution impossible sans l'option -ea");
      return;





    }
    int nbTest = 0;
    System.out.print("Test Passager Indecis: ");


    //************ Verifier l'instanciation *************
    System.out.print('.'); nbTest++;
    new TestPassagerIndecis().testInstanciation();

    //********* Verifier changement d'etat **************
    System.out.print('.'); nbTest++;
    new TestPassagerIndecis().testGestionEtat();

    //********* Verifier les interactions  *************
    System.out.print('.'); nbTest++;
    new TestPassagerIndecis().testMontee();

    System.out.print('.'); nbTest++;
    new TestPassagerIndecis().testInteractionArret();

    System.out.println(" OK");

  }

  public void testMontee() {
    PassagerIndecis p1 = new PassagerIndecis("aze",4);
    PassagerIndecis p2 = new PassagerIndecis("rty",4);
    Autobus a = new Autobus(1,1);
    p1.monterDans(a);
    assert p1.estDebout() : "p1 pas debout";
    p2.monterDans(a);
    assert p2.estDehors() : "p2 pas dehors";

  }

  public void testInteractionArret() {
    PassagerIndecis p1 = new PassagerIndecis("aze",3);
    Autobus a = new Autobus(1,2);
    p1.monterDans(a);
    p1.choixPlaceArret(a,1);

    assert p1.estAssis() : "p1 pas assis";
  }
}
