package tec;

class MonteeSportif extends PassagerAbstrait{

    MonteeSportif(String nom, int dest, Arret a){
	super(nom, dest, a);
    }
    
    void choixPlaceMontee(Vehicule v){
	if (v.aPlaceDebout())
	    v.monteeDemanderDebout(this);
    }
}
