package tec;

public final class PassagerIndecis extends MonteeSportif {

    public PassagerIndecis(String nom, int dest){
	super(nom, dest, ArretNerveux.createArretNerveux());
    }
}
