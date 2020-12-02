package tec;

class ArretPoli implements Arret {
    static final private ArretPoli ARRET_POLI = new ArretPoli();

	public static ArretPoli createArretPoli() {
		return ARRET_POLI;
	}
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
	if (!v.aPlaceAssise())
	    v.arretDemanderDebout(p);
    }
}
