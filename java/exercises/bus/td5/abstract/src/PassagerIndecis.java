package tec;
import tec.PassagerAbstrait;
public class PassagerIndecis extends PassagerAbstrait implements Usager{

  public PassagerIndecis(String nom, int dest){
    super(nom,dest);
  }
  void choixPlaceMontee(Vehicule v){
    if(v.aPlaceDebout())
      v.monteeDemanderDebout(this);
  }

  void choixPlaceArret(Vehicule v, int arret){
    if (distance(arret) > 0){
    if (estDebout())
      changerEnAssis();
    else if (estAssis())
      changerEnDebout();
  }
}


}
