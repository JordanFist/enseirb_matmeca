package tec;

class ArretNerveux implements Arret {
	static final private ArretNerveux ARRET_NERVEUX = new ArretNerveux();

	public static ArretNerveux createArretNerveux() {
		return ARRET_NERVEUX;
	}
    
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDest){
	if (p.estAssis())
	    v.arretDemanderDebout(p);
	else if (p.estDebout())
	    v.arretDemanderAssis(p);
    }

}
