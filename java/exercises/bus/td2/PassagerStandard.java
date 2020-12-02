//utiliser la classe position.
public class PassagerStandard implements Passager{
    private String nom;
    private int destination;
    private Position pos;

    public PassagerStandard(String n, int dest){
	     nom = n;
	     destination = dest;
       this.pos = new Position();
    }
    public void changerEnAssis(){
      Position p = new Position();
      p = p.assis();
      this.pos = p;
    }

    public void changerEnDebout(){
      Position p = new Position();
      p = p.debout();
      this.pos = p;
    }
    public void changerEnDehors(){
      Position p = new Position();
      p = p.dehors();
      this.pos = p;
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

    public void monterDans(Vehicule v){
      if (v.aPlaceAssise()){
        v.monteeDemanderAssis(this);
        //this.changerEnAssis();
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

    public String toString()){
      return "Nom: " + nom + ", destination: " + destination + ", est assis: " + estAssis() + ", est dehors: " + estDehors();
    }
}
