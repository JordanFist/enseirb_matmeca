package tec;

class TestIntegration {

	public void testException() throws TecException {

		Usager jayne = new PassagerStandard("Jayne", 4);

		// Montée dans un transport qui n'est pas un véhicule
		FauxCamion faux = new FauxCamion();

		try {
			jayne.monterDans(faux);
			assert false : "faux véhicule";
		} catch (TecException e) {
		}

	}

	public void testSimple() throws TecException {
		Transport serenity = new Autobus(1, 2);
		Memoire memoire = new Memoire();
		Greffon greffonSerenity = new Greffon((Vehicule)serenity, memoire);

		Usager kaylee = new PassagerStandard("Kaylee", 4);
		Usager jayne = new PassagerStandard("Jayne", 4);
		Usager inara = new PassagerStandard("Inara", 5);

		// 0
		System.out.println(greffonSerenity);
		greffonSerenity.allerArretSuivant();

		// 1
		kaylee.monterDans(serenity);
		jayne.monterDans(serenity);
		inara.monterDans(serenity);

		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		greffonSerenity.allerArretSuivant();

		// 2
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		greffonSerenity.allerArretSuivant();

		// 3
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		greffonSerenity.allerArretSuivant();

		// 4
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		greffonSerenity.allerArretSuivant();

		// 5
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
	}

	public void testSimple2() throws TecException {
		Transport serenity = new Autobus(1, 2);
		Fichier fichier = new Fichier();
		Greffon greffonSerenity = new Greffon((Vehicule)serenity, fichier);

		Usager kaylee = new PassagerStandard("Kaylee", 4);
		Usager jayne = new PassagerStandard("Jayne", 4);
		Usager inara = new PassagerStandard("Inara", 5);

		// 0
		System.out.println(greffonSerenity);
		greffonSerenity.allerArretSuivant();

		// 1
		kaylee.monterDans(serenity);
		jayne.monterDans(serenity);
		inara.monterDans(serenity);

		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		greffonSerenity.allerArretSuivant();

		// 2
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		greffonSerenity.allerArretSuivant();

		// 3
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		greffonSerenity.allerArretSuivant();

		// 4
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		greffonSerenity.allerArretSuivant();

		// 5
		System.out.println(greffonSerenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);
	}

	/*
	 * public static void main(String[] args) throws TecException { TestIntegration
	 * test = new TestIntegration(); test.testException(); test.testSimple(); }
	 */
}
