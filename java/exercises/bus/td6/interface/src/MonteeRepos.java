package tec;
abstract class MonteeRepos extends PassagerAbstrait {
    
    MonteeRepos(String nom, int dest, Arret a){
	super(nom, dest, a);
    }

    void choixPlaceMontee(Vehicule v){
	if (v.aPlaceAssise())
	    v.monteeDemanderAssis(this);
	else if (v.aPlaceDebout())
	    v.monteeDemanderDebout(this);
    }
}
