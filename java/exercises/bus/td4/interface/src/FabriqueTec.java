package tec;

public class FabriqueTec {

    private FabriqueTec() {}

    public static Usager fairePassagerStandard(String nom, int arret) {
	return new PassagerStandard(nom, arret);
    }

    public static Transport faireAutobus(int maxAssis, int maxDebout) {
	return new Autobus(maxAssis, maxDebout);
    }
}
