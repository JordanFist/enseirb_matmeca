package tec;

class ArretNerveux implements Arret {
    
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDest){
	if (p.estAssis())
	    v.arretDemanderDebout(p);
	else if (p.estDebout())
	    v.arretDemanderAssis(p);
    }

}
