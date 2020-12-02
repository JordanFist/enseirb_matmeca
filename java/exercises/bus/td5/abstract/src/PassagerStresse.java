package tec;
import tec.Passager;
import tec.PassagerAbstrait;
public class PassagerStresse extends PassagerAbstrait implements Usager{
    public PassagerStresse(String nom, int dest){
      super(nom,dest);
    }
    void choixPlaceMontee(Vehicule v){
      if(v.aPlaceAssise())
        v.monteeDemanderAssis(this);
      else
      if (v.aPlaceDebout())
        v.monteeDemanderDebout(this);
    }

    void choixPlaceArret(Vehicule v, int arret){
      if (this.distance(arret) < 3)
        this.changerEnDebout();
    }
}
