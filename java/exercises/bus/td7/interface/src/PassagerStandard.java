package tec;

class PassagerStandard extends MonteeRepos {

    PassagerStandard(String n, int dest) {
        super(n, dest, ArretCalme.createArretCalme());
    }

}
