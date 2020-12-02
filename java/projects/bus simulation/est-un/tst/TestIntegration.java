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

		Memoire memoire = new Memoire();
		Transport serenity = new GreffonAutobus(1, 2, memoire);

		Usager kaylee = new PassagerStandard("Kaylee", 4);
		Usager jayne = new PassagerStandard("Jayne", 4);
		Usager inara = new PassagerStandard("Inara", 5);

		// 0
		System.out.println(serenity);
		serenity.allerArretSuivant();

		// 1
		kaylee.monterDans(serenity);
		jayne.monterDans(serenity);
		inara.monterDans(serenity);

		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		//System.out.println(memoire);
		System.out.println();
		serenity.allerArretSuivant();

		// 2
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		serenity.allerArretSuivant();

		// 3
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		serenity.allerArretSuivant();

		// 4
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		System.out.println(memoire);
		System.out.println();
		serenity.allerArretSuivant();

		// 5
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);
		System.out.println(memoire);
		System.out.println();
	}

	public void testSimple2() throws TecException {

		Fichier fichier = new Fichier();
		Transport serenity = new GreffonAutobus(1, 2, fichier);

		Usager kaylee = new PassagerStandard("Kaylee", 4);
		Usager jayne = new PassagerStandard("Jayne", 4);
		Usager inara = new PassagerStandard("Inara", 5);

		// 0
		System.out.println(serenity);
		serenity.allerArretSuivant();

		// 1
		kaylee.monterDans(serenity);
		jayne.monterDans(serenity);
		inara.monterDans(serenity);

		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		serenity.allerArretSuivant();
		System.out.println();

		// 2
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		serenity.allerArretSuivant();
		System.out.println();

		// 3
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		serenity.allerArretSuivant();
		System.out.println();

		// 4
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);

		serenity.allerArretSuivant();
		System.out.println();

		// 5
		System.out.println(serenity);
		System.out.println(kaylee);
		System.out.println(jayne);
		System.out.println(inara);
		System.out.println();
	}

	/*
	 * public static void main(String[] args) throws TecException { TestIntegration
	 * test = new TestIntegration(); test.testException(); test.testSimple(); }
	 */
}
