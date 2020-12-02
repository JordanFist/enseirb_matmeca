package tec;

public final class PassagerStresse extends MonteeFatigue {
    
    public PassagerStresse(String nom, int dest) {
	super(nom, dest, ArretPrudent.createArretPrudent());
    }

}
