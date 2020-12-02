package tec;

class MonteeFatigue extends PassagerAbstrait {
    
    MonteeFatigue(String nom, int dest, Arret a){
	super(nom, dest, a);
    }
    
    void choixPlaceMontee(Vehicule v){
	if (v.aPlaceAssise())
	    v.monteeDemanderAssis(this);
    }
}
