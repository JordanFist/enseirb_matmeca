package tec;

class MonteeTetu extends PassagerAbstrait {
    
    MonteeTetu(String nom, int dest, Arret a){
	super(nom, dest, a);
    }

    void choixPlaceMontee(Vehicule v){
	v.monteeDemanderDebout(this);
    }
}
