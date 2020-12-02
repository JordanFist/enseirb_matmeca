package tec;

class ArretPrudent implements Arret {
		static final private ArretPrudent ARRET_PRUDENT = new ArretPrudent();

	public static ArretPrudent createArretPrudent() {
		return ARRET_PRUDENT;
	}

    public void choixPlaceArret(Passager p, Vehicule v, int distanceDestination){
	if (distanceDestination > 5)
	    v.arretDemanderAssis(p);
	else if (distanceDestination < 3)
	    v.arretDemanderDebout(p);
    }

}
