package tec;
import tec.Passager;
import tec.Usager;
public abstract class PassagerAbstrait extends Passager {

  		private String nom;
    	private final int destination;
  		private Position pos;

       PassagerAbstrait(String n, int dest){
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

     public void monterDans(Transport t){
        Vehicule v = (Vehicule) t;
        this.choixPlaceMontee(v);
      }

  	void nouvelArret(Vehicule v, int numeroArret){
      	if (this.distance(numeroArret) == 0){
        	v.arretDemanderSortie(this);
          this.choixPlaceArret(v, numeroArret);
      }
    }
    //nombre d'arret avant la sortie du Vehicule.
     int distance(int numeroArret){
      return this.destination - numeroArret;
    }

    abstract void choixPlaceMontee(Vehicule v);
    abstract void choixPlaceArret(Vehicule v, int arret);
    public String toString() {
          return ("destination: " + this.destination + " position: " + this.pos);
      }
  }
