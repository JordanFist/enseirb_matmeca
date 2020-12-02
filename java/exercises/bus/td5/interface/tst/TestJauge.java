package tec;

import tec.Jauge;

class TestJauge {

    public void testInstanciation() {
        Jauge j1 = new Jauge(10, 0);
        assert j1.estVert(): "TestJauge: testInstanciation1 ERREUR";
        assert !j1.estRouge(): "TestJauge: testInstanciation1 ERREUR";

        Jauge j2 = new Jauge(5, 6);
        assert !j2.estVert(): "TestJauge: testInstanciation2 ERREUR !estVert doit etre vrai";
        assert j2.estRouge(): "TestJauge: testInstanciation2 ERREUR estRouge doit etre vrai";

        System.out.println("testJauge: testInstanciation ..... OK");
    }

    public void testIncrementer() {
        Jauge j1 = new Jauge(10, 9);
        j1.incrementer();
        assert j1.estRouge(): "TestJauge: testIncrementer1 ERREUR estRouge doit etre vrai";
        assert !j1.estVert(): "TestJauge: testIncrementer1 ERREUR !estVert doit etre vrai";

        Jauge j2 = new Jauge(10, 4);
        j2.incrementer();
        assert !j2.estRouge(): "TestJauge: testIncrementer2 ERREUR !estRouge doit etre vrai";
        assert j2.estVert(): "TestJauge: testIncrementer2 ERREUR estVert doit etre vrai";
        
        System.out.println("testJauge: testIncrementer ..... OK");

    }

    public void testDecrementer() {
        Jauge j1 = new Jauge(10, 11);
        j1.decrementer();
        assert j1.estRouge(): "TestJauge: testDecrementer1 ERREUR estRouge devrait etre vrai";
        assert !j1.estVert(): "TestJauge: testDecrementer1 ERREUR estVert devrait etre faux";

        Jauge j2 = new Jauge(10, 10);
        j2.decrementer();
        assert !j2.estRouge(): "TestJauge: testDecrementer2 ERREUR !estRouge devrait etre vrai";
        assert j2.estVert(): "TestJauge: testDecrementer2 ERREUR estVert devrait etre vrai";
        
        System.out.println("testJauge: testDecrementer ..... OK");
    }

    public void testEstRouge() {
        Jauge j1 = new Jauge(10, 15);
        assert (j1.estRouge() == !j1.estVert()): "TestJauge: testEstRouge ERREUR";
        
        System.out.println("testJauge: testEstRouge ..... OK");
    }

    public void testEstVert() {
        Jauge j1 = new Jauge(10, 5);
        assert (!j1.estRouge() == j1.estVert()): "TestJauge: testEstVert ERREUR";
        
        System.out.println("testJauge: testEstVert ..... OK");
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
