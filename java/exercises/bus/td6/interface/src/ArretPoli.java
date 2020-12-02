package tec;

class ArretPoli implements Arret {
    
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDest){
	if (!v.aPlaceAssise())
	    v.arretDemanderDebout(p);
    }
    
}
