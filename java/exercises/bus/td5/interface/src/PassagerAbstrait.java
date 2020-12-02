package tec;

abstract class PassagerAbstrait implements Passager, Usager{
    private String nom;
    private final int destination;
    Position pos;

    PassagerAbstrait(String n, int dest){
	    nom = n;
	    destination = dest;
        this.pos = Position.create();
    }

    public int distanceDest(int numeroArret) {
        return (destination - numeroArret);
    }

    public void changerEnAssis(){
	    this.pos = Position.create();
        this.pos = this.pos.assis();
    }

    public void changerEnDebout(){
	    this.pos = Position.create();
        this.pos = this.pos.debout();
    }

    public void changerEnDehors(){
	    this.pos = Position.create();
    }

    public boolean estAssis(){
	    return this.pos.estAssis();
    }

    public boolean estDebout(){
	    return this.pos.estDebout();
    }

    public boolean estDehors(){
	    return this.pos.estDehors();
    }

    abstract void choixPlaceMontee(Vehicule v);

    abstract void choixPlaceArret(Vehicule v, int arret);

    public void monterDans(Transport t){
	    Vehicule v = (Vehicule) t;
        choixPlaceMontee(v);
    }

    public void nouvelArret(Vehicule v, int numeroArret){
        choixPlaceArret(v, numeroArret);
	    if (distanceDest(numeroArret) == 0)
	        v.arretDemanderSortie(this);
    }

    public java.lang.String nom(){
    	return this.nom;
    }

    public String toString() {
        return ("destination: " + destination + " position: " + pos);
    }
}
