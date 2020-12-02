package tec;

import java.util.ArrayList;

public class Memoire extends Collecte {
    ArrayList<Data> array;

    public Memoire() {
        array = new ArrayList<Data>();
    }

    void changerArret() {
        Data data = new Data(nbPassagersEntres, nbPassagersSortis, numeroArret);
        array.add(data);
        super.changerArret();
    }

    public String toString() {
        return("numeroArret : " + array.get(array.size() - 1).numeroArret + ", nbPassagersEntres : " + 
        array.get(array.size() - 1).nbPassagersEntres + ", nbPassagersSortis : " + array.get(array.size() - 1).nbPassagersSortis);
    }

}