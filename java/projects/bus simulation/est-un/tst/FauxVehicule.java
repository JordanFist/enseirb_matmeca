package tec;
import tec.Passager;
import tec.Vehicule;
import tec.Transport;

/**
 * Classe faussaire pour le test unitaire fonctionnel
 * de PassagerStandard
 *
 * Ce faussaire ne declenche pas d'appel aux methodes
 * de PassagerStandard.
 *
 * Il ne change pas son etat (la variable d'instance status).
 * C'est le test qui change directement la valeur de cette variable.
 *
 * Il enregistre l'appel aux méthodes qui
 * doivent modifier son etat.
 */
class FauxVehicule extends Vehicule implements Transport {
  static final byte VIDE = 0;
  static final byte DEBOUT  = 1;
  static final byte ASSIS = 2;
  static final byte PLEIN = 4;
  byte status;

  final java.util.List<String> logs = new java.util.LinkedList<String>();

  FauxVehicule() {
    this(VIDE);
  }

  FauxVehicule(byte init) {
    status = init;
  }

  public boolean aPlaceAssise() {
    return status == ASSIS
      || status == VIDE;
  }

  public boolean aPlaceDebout() {
    return status == DEBOUT
      || status == VIDE;
  }

  // Enregistrements des appels effectues par PassagerStandard.
  public void monteeDemanderAssis(Passager p) {
    logs.add("monteeDemanderAssis");
  }

  public void monteeDemanderDebout(Passager p) {
    logs.add("monteeDemanderDebout");
  }

  public void arretDemanderDebout(Passager p) {
    logs.add("arretDemanderDebout");
  }

  public void arretDemanderAssis(Passager p) {
    logs.add("arretDemanderAssis");
  }

  public void arretDemanderSortie(Passager p) {
    logs.add("arretDemanderSortie");
  }

  // PassagerStandard n'utilise pas cette méthode.
  public void allerArretSuivant() {
  }
}
