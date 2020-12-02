
/**
 * Classe faussaire pour le test unitaire fonctionnel
 * d'Autobus. 
 *
 * Ce faussaire ne declenche pas d'appel aux methodes
 * d'Autobus.
 *
 * Il ne change pas son etat (la variable d'instance status). 
 * C'est le test qui change directement la valeur de cette variable. 
 *
 * Il enregistre l'appel aux méthodes qui doivent modifier son etat.
 */
class FauxPassager implements Passager {
  static final byte DEHORS = 0;
  static final byte ASSIS  = 1;
  static final byte DEBOUT = 2;
  byte status = DEHORS;

  final java.util.List<String> logs = new java.util.LinkedList<String>();

  FauxPassager() {
    this(DEHORS);
  }

  FauxPassager(byte init) {
    status = init;
  }

  public String nom() {
    return null;
  }

  public boolean estDehors() {
    return status == DEHORS;
  }
  
  public boolean estAssis() {
    return status == ASSIS;
  }
  
  public boolean estDebout() {
    return status == DEBOUT;
  }

  // Enregistrements des appels effectues par Autobus.
  public void changerEnDehors() {
    logs.add("changerEnDehors");
  }

  public void changerEnAssis() {
    logs.add("changerEnAssis");
  }

  public void changerEnDebout() {
    logs.add("changerEnDebout");
  }

  public void nouvelArret(Vehicule bus, int numeroArret) {
    logs.add("nouvelArret");
  }

  // Autobus n'utilise pas cette méthode.
  public void monterDans(Vehicule t) { 
  }
}
