package tec;

import tec.Position;

class TestPosition {

    /*public void testInstanciation(){
	Position p = new Position();
	assert p.estDehors():"pas dehors";
	assert !p.estAssis():"assis, devrait être dehors";
	assert !p.estDebout():"debout, devrait être dehors";
	assert !p.estInterieur():"à l'interieur, devrait être dehors";
	System.out.println("testInstanciation : OK");
	}*/

    public void testDebout(){
	Position p = Position.create();
	p = p.debout();
	assert p.estDebout():"pas debout";
	assert !p.estAssis(): "assis, devrait être debout";
	assert !p.estDehors(): "dehors, devrait être debout";
	assert p.estInterieur():"dehors, devrait être à l'interieur";
	System.out.println("testPosition: testDebout : OK");
    }

    public void testDehors(){
	Position p = Position.create();
	p = p.dehors();
	assert p.estDehors():"pas dehors";
	assert !p.estAssis():"assis, devrait être dehors";
	assert !p.estDebout():"debout, devrait être dehors";
	assert !p.estInterieur():"à l'interieur, devrait être dehors";
	System.out.println("testPosition: testDehors : OK");
    }

    public void testAssis(){
	Position p = Position.create();
	p = p.assis();
	assert !p.estDehors():"dehors, devrait être assis";
	assert p.estAssis():"pas assis";
	assert !p.estDebout():"debout, devrait être assis";
	assert p.estInterieur():"dehors, devrait être assis";
	System.out.println("testPosition: testAssis : OK");
    }

    public static void main (String[] args) {
	TestPosition test = new TestPosition();
	//test.testInstanciation();
	test.testDebout();
	test.testDehors();
	test.testAssis();
    }
}
