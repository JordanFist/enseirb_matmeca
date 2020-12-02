package tec;

abstract class PassagerAbstrait extends Passager implements Usager {

    private String nom;
    private final int destination;
    private Position pos;
    private final Arret comportementArret;

    PassagerAbstrait(String n, int dest, Arret a){
	nom = n;
	destination = dest;
	this.pos = Position.create();
	this.comportementArret = a;
    }

    private int distanceDest(int numeroArret) {
        return (destination - numeroArret);
    }

    String nom(){
	return this.nom;
    }

    boolean estDehors(){
      	return this.pos.estDehors();
    }

    boolean estAssis(){
      	return this.pos.estAssis();
    }

    boolean estDebout(){
      	return this.pos.estDebout();
    }

    void changerEnDehors(){
      	this.pos = Position.create();
    }

    void changerEnAssis(){
      	this.pos = Position.create();
	this.pos = this.pos.assis();
    }

    void changerEnDebout(){
      	this.pos = Position.create();
	this.pos = this.pos.debout();
    }

    abstract void choixPlaceMontee(Vehicule v);
    
    public void monterDans(Transport t) {
        Vehicule v = (Vehicule) t;
        choixPlaceMontee(v);
    }

    void nouvelArret(Vehicule v, int numeroArret) {
	comportementArret.choixPlaceArret(this, v, distanceDest(numeroArret));
        if (distanceDest(numeroArret) == 0)
	    v.arretDemanderSortie(this);
    }

    public String toString() {
	return ("destination: " + this.destination + " position: " + this.pos);
    }
}
