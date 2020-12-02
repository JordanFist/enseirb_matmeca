class TestJauge {

    public void testInstanciation() {
	Jauge j1 = new Jauge(10, 0);
	assert j1.estVert(): "TestJauge: testInstanciation1 ERREUR";
	assert !j1.estRouge(): "TestJauge: testInstanciation1 ERREUR";

	Jauge j2 = new Jauge(5, 6);
	//assert !j2.estVert(): "TestJauge: testInstanciation2 ERREUR !estVert doit etre vrai";
	assert j2.estRouge(): "TestJauge: testInstanciation2 ERREUR estRouge doit etre vrai";

	/* On s'attendait a ce que j2.estVert retourne faux puisque le niveau de la jauge depasse le maximum or ce n'est pas le cas */
    }

    public void testIncrementer() {
	Jauge j1 = new Jauge(10, 9);
	j1.incrementer();
	//assert j1.estRouge(): "TestJauge: testIncrementer1 ERREUR estRouge doit etre vrai";
	assert !j1.estVert(): "TestJauge: testIncrementer1 ERREUR !estVert doit etre vrai";

	/* On s'attendait a ce que j1.estRouge retourne vrai puisque la jauge aurait du atteindre 10 qui est le maximum */

	Jauge j2 = new Jauge(10, 4);
	j2.incrementer();
	assert !j2.estRouge(): "TestJauge: testIncrementer2 ERREUR !estRouge doit etre vrai";
	//assert j2.estVert(): "TestJauge: testIncrementer2 ERREUR estVert doit etre vrai";

	/* On s'attendait a ce que j2.estvert retourne vrai puisque la jauge aurait du atteindre 5 qui est inferieur au maximum */
	
    }

    public void testDecrementer() {
	Jauge j1 = new Jauge(10, 11);
	j1.decrementer();
	assert j1.estRouge(): "TestJauge: testDecrementer1 ERREUR estRouge devrait etre vrai";
	//assert !j1.estVert(): "TestJauge: testDecrementer1 ERREUR estVert devrait etre faux";

	/* On s'attendait a ce que j1.estVert soit faux puisque la jauge aurait du attendre 10 qui est le maximum */

	Jauge j2 = new Jauge(10, 10);
	j2.decrementer();
	assert !j2.estRouge(): "TestJauge: testDecrementer2 ERREUR !estRouge devrait etre vrai";
	assert j2.estVert(): "TestJauge: testDecrementer2 ERREUR estVert devrait etre vrai";

	// Decrementer a l'air de fonctionner
    }

    public void testEstRouge() {
	Jauge j1 = new Jauge(10, 15);
	//assert (j1.estRouge() == !j1.estVert()): "TestJauge: testEstRouge ERREUR";

	/* estRouge devrait etre vrai car 15 est superieur au maximum et !estVert devrait etre vrai ce test devrait marcher */
    }

    public void testEstVert() {
	Jauge j1 = new Jauge(10, 5);
	assert (!j1.estRouge() == j1.estVert()): "TestJauge: testEstVert ERREUR";
    }

    public static void main (String[] args) {
	boolean estMisAssertion = false;
	assert estMisAssertion = true;
	if (!estMisAssertion) 
	    System.out.println("Execution impossible sans l'option -ea");
	    
	TestJauge testJauge = new TestJauge();
	testJauge.testInstanciation();
	testJauge.testIncrementer();
	testJauge.testDecrementer();
	testJauge.testEstRouge();
	testJauge.testEstVert();
    }
}
