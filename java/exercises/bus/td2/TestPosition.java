class TestPosition {

    public void testInstanciation(){
	Position p = new Position();
	assert p.estDehors():"pas dehors";
	assert !p.estAssis():"assis, devrait être dehors";
	assert !p.estDebout():"debout, devrait être dehors";
	assert !p.estInterieur():"à l'interieur, devrait être dehors";
	System.out.println("testInstanciation : OK");
    }
    
    public void testDebout(){
	Position   p = new Position();
	p = p.debout();
	//assert p.estDebout():"pas debout";
	assert !p.estAssis(): "assis, devrait être debout";
	assert !p.estDehors(): "dehors, devrait être debout";
	assert p.estInterieur():"dehors, devrait être à l'interieur";
	System.out.println("testDebout : OK");
    }
    
    public void testDehors(){
	Position p = new Position();
	p = p.dehors();
	//assert p.estDehors():"pas dehors";
	assert !p.estAssis():"assis, devrait être dehors";
	assert !p.estDebout():"debout, devrait être dehors";
	//assert !p.estInterieur():"à l'interieur, devrait être dehors";
	System.out.println("testDehors : OK");
    }
    
    public void testAssis(){
	Position p = new Position();
	p = p.assis();
	assert !p.estDehors():"dehors, devrait être assis";
	assert p.estAssis():"pas assis";
	//assert !p.estDebout():"debout, devrait être assis";
	assert p.estInterieur():"dehors, devrait être assis";
	System.out.println("testAssis : OK");
    }
    
    public static void main (String[] args) {
	TestPosition test0 = new TestPosition();
	test0.testInstanciation();
	TestPosition test1 = new TestPosition();
	test1.testDebout();
	TestPosition test2 = new TestPosition();
	test2.testDehors();
	TestPosition test3 = new TestPosition();
	//test3.testInterieur();
	TestPosition test4 = new TestPosition();
	test4.testAssis();
    }
}
