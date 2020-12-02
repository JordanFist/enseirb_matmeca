import java.util.ArrayList;
import java.util.Random;

import jbotsim.Node;

/* Gardez cette classe telle quelle */

public class Fire extends Node {
    static ArrayList<Fire> allFires = new ArrayList<>();
    Random r=new Random();

    public Fire(){
        allFires.add(this);
        disableWireless();
        setIcon("/fire.png");
    }
    public void onClock(){
        if (Math.random() < 0.01 && allFires.size() < 100)
            propagate();
    }
    public void propagate(){
        double x = getX() + r.nextDouble() * 20 - 10;
        double y = getY() + r.nextDouble() * 20 - 10;
        for (Fire fire : allFires) {
            if (fire.distance(x, y) < 10)
                return;
        }
        getTopology().addNode(x, y, new Fire());

    }
    public void die(){
        allFires.remove(this);
        getTopology().removeNode(this);
    }
}