package tec;

public class PassagerStandard extends Passager implements Usager {
	private String nom;
  	private int destination;
	Position pos;

  public PassagerStandard(String n, int dest){
		nom = n;
		destination = dest;
		this.pos = Position.create();
	}

	java.lang.String nom(){
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

  	public void monterDans(Transport t) {
	  Vehicule v = (Vehicule) t;
	  if (v.aPlaceAssise())
	    v.monteeDemanderAssis(this);
	  else if(v.aPlaceDebout())
		  v.monteeDemanderDebout(this);
	}

	void nouvelArret(Vehicule v, int numeroArret){
    	if (numeroArret == this.destination){
      	v.arretDemanderSortie(this);
    }
  }
}
