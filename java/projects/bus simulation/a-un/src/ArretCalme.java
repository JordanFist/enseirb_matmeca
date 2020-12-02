package tec;

class ArretCalme implements Arret {
    static final private ArretCalme ARRET_CALME = new ArretCalme();

	public static ArretCalme createArretCalme() {
		return ARRET_CALME;
	}
    public void choixPlaceArret(Passager p, Vehicule v, int distanceDestination) {
    }
}
