import jbotsim.Color;
import jbotsim.Message;
import jbotsim.Node;

import java.util.Random;
import java.util.List;

public class GeoNode extends Node {
    @Override
    public void onMessage(Message message) {
        Bundle bundle = (Bundle) message.getContent();
        if (bundle.target.equals(getLocation())) {
            System.out.println("Message reçu : " + bundle.text);
        } else {
            route(bundle);
        }
    }

    public Node closestNeighbour(Bundle dest) {
        Node nodeNeighbour = this;
        for (Node n : getNeighbors()) {
            if (n.getLocation().distance(dest.target) < nodeNeighbour.getLocation().distance(dest.target))
                nodeNeighbour = n;
        }
        return nodeNeighbour;
    }

    public int randInt(int numberOfNeighbours) {
        Random rand = new Random();
        return rand.nextInt(numberOfNeighbours);
    }

    public Node randomRoute() {
        List<Node> neighbours = getNeighbors();
        return neighbours.get(randInt(neighbours.size()));
    }

    public void route(Bundle bundle) {
        setColor(Color.red);
        Node neighbour = this.closestNeighbour(bundle); //pas obligé de marquer this il y est deja
        if (this.equals(neighbour)) {
            bundle.randomRoute = true;
            bundle.distance = neighbour.distance((bundle.target));
        }
        if (bundle.randomRoute == true) {
            neighbour = randomRoute();
            if (neighbour.distance(bundle.target) < bundle.distance)
                bundle.randomRoute = false;
        }
        setColor(Color.blue);
        neighbour.setColor(Color.red);
        send(neighbour, bundle);
    }
}