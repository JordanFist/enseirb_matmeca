package tec;

class PassagerStresse extends MonteeFatigue {

    PassagerStresse(String n, int dest) {
        super(n , dest, ArretPrudent.createArretPrudent());
    }

}
