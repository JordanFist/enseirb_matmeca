package tec;

public final class FabriqueTec {

    private FabriqueTec() {}

    public static Usager fairePassagerStandard(String nom, int destination) {
        return new PassagerStandard(nom, destination);
    }

    public static Usager fairePassagerIndecis(String nom, int destination) {
	return new PassagerIndecis(nom, destination);
    }

    public static Usager fairePassagerStresse(String nom, int destination) {
        return new PassagerStresse(nom, destination);
    }

    public static Transport faireAutobus(int maxAssis, int maxDebout) {
	return new Autobus(maxAssis, maxDebout);
    }
}
