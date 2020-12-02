package tec;

public class PassagerStandard implements Passager{
    private String nom;
    private int destination;
    Position pos;

    public PassagerStandard(String n, int dest){
	      nom = n;
	      destination = dest;
        this.pos = Position.DEHORS;
    }

    public void changerEnAssis(){
      this.pos = Position.ASSIS;
    }

    public void changerEnDebout(){
      this.pos = Position.DEBOUT;
    }
    public void changerEnDehors(){
      this.pos = Position.DEHORS;
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
