import tec.Transport;
import tec.Usager;
import tec.Autobus;
import tec.PassagerStandard;
import tec.ArretCalme;

class Simple {

  /*
   * Affiche l'etat des deux instances passees en parametre.
   * La methode println(Object x) de la classe PrintWriter
   * declenche la methode toString() sur l'objet passe
   * en parametre (x.toString()) et affiche la chaine
   * de caracteres obtenue..
   */
  static private void deboguerEtat (Transport t, Usager p) {
    System.out.println(p);
    System.out.println(t);
  }

  static public void main (String[] args) {
    Transport serenity = new Autobus(1, 2);

    ArretCalme ac = new ArretCalme();
    Usager kaylee = new PassagerStandard("Kaylee", 4, ac);
    Usager jayne = new PassagerStandard("Jayne", 4, ac);
    Usager inara = new PassagerStandard("Inara", 5, ac);

    //0
    System.out.println(serenity);

    serenity.allerArretSuivant();
    //1
    kaylee.monterDans(serenity);

    System.out.println(serenity);
    System.out.println(kaylee);

    serenity.allerArretSuivant();
    //2
    jayne.monterDans(serenity);

    System.out.println(serenity);
    System.out.println(kaylee);
    System.out.println(jayne);

    serenity.allerArretSuivant();
    //3
    inara.monterDans(serenity);

    System.out.println(serenity);
    System.out.println(kaylee);
    System.out.println(jayne);
    System.out.println(inara);

    serenity.allerArretSuivant();
    //4
    System.out.println(serenity);
    System.out.println(kaylee);
    System.out.println(jayne);
    System.out.println(inara);

    serenity.allerArretSuivant();
    //5
    System.out.println(serenity);
    System.out.println(kaylee);
    System.out.println(jayne);
    System.out.println(inara);
  }
}

/* Resultat de l'execution: "Kaylee", 4;
[arret 0] assis<1> debout<2>
[arret 1] assis<0> debout<2>
Kaylee <assis>
[arret 2] assis<0> debout<1>
Kaylee <assis>
Jayne <debout>
[arret 3] assis<0> debout<0>
Kaylee <assis>
Jayne <debout>
Inara <debout>
[arret 4] assis<1> debout<1>
Kaylee <endehors>
Jayne <endehors>
Inara <debout>
[arret 5] assis<1> debout<2>
Kaylee <endehors>
Jayne <endehors>
Inara <endehors>
*/

/* Resultat de l'execution: "Kaylee", 3;
[arret 0] assis<1> debout<2>
[arret 1] assis<0> debout<2>
Kaylee <assis>
[arret 2] assis<0> debout<1>
Kaylee <assis>
Jayne <debout>
[arret 3] assis<0> debout<1>
Kaylee <endehors>
Jayne <debout>
Inara <assis>
[arret 4] assis<0> debout<2>
Kaylee <endehors>
Jayne <endehors>
Inara <assis>
[arret 5] assis<1> debout<2>
Kaylee <endehors>
Jayne <endehors>
Inara <endehors>
*/
