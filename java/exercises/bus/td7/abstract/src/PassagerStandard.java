package tec;

public final class PassagerStandard extends MonteeRepos {

    public PassagerStandard(String nom, int dest){
	super(nom, dest, ArretCalme.createArretCalme());
    }

}
