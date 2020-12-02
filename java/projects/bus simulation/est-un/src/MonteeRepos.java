package tec;

class MonteeRepos extends PassagerAbstrait {

    MonteeRepos(String n, int dest, Arret a){
	super(n, dest, a);
    }
	
    void choixPlaceMontee(Vehicule v) {
        if (v.aPlaceAssise())
            v.monteeDemanderAssis(this);
        else if (v.aPlaceDebout())
            v.monteeDemanderDebout(this);
    }
}
