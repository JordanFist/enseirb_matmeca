package tec;

class TestIntegration {

    public void TestException() throws TecException {

	Usager jayne = FabriqueTec.fairePassagerStandard("Jayne", 4);

	// Montée dans un transport qui n'est pas un véhicule
	FauxCamion faux = new FauxCamion();

	try {
	    jayne.monterDans(faux);
	    assert false: "faux véhicule";
	} catch (TecException e) {}
	
    }

    public void testSimple() throws TecException {
	Transport serenity = new Autobus(1, 2);

	Usager kaylee = FabriqueTec.fairePassagerStandard("Kaylee", 4);
	Usager jayne = FabriqueTec.fairePassagerStandard("Jayne", 4);
	Usager inara = FabriqueTec.fairePassagerStandard("Inara", 5);

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

	// 2
	System.out.println(serenity);
	System.out.println(kaylee);
	System.out.println(jayne);
	System.out.println(inara);

	serenity.allerArretSuivant();

	// 3
	System.out.println(serenity);
	System.out.println(kaylee);
	System.out.println(jayne);
	System.out.println(inara);

	serenity.allerArretSuivant();

	// 4
	System.out.println(serenity);
	System.out.println(kaylee);
	System.out.println(jayne);
	System.out.println(inara);

	serenity.allerArretSuivant();

	// 5
	System.out.println(serenity);
	System.out.println(kaylee);
	System.out.println(jayne);
	System.out.println(inara);

    }
}

