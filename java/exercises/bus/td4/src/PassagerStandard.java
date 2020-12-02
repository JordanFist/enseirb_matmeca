package tec;

public class PassagerStandard implements Passager, Usager{
    private String nom;
    private int destination;
    Position pos;

    public PassagerStandard(String n, int dest){
	      nom = n;
	      destination = dest;
        this.pos = Position.dehors();
    }

    public void changerEnAssis(){
      this.pos = Position.assis();
    }

    public void changerEnDebout(){
      this.pos = Position.debout();
    }
    public void changerEnDehors(){
      this.pos = Position.dehors();
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

    public void monterDans(Transport t){
	Vehicule v = (Vehicule) t;
	if (v.aPlaceAssise()){
	    v.monteeDemanderAssis(this);
	}
	else {
	    if(v.aPlaceDebout()){
		v.monteeDemanderDebout(this);
        }
      }
    }

    public void nouvelArret(Vehicule v, int numeroArret){
      if (numeroArret == this.destination){
        v.arretDemanderSortie(this);
      }
    }

    public java.lang.String nom(){
      return this.nom;
    }
}
