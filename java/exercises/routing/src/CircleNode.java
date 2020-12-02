import jbotsim.Message;
import jbotsim.Node;

import java.util.ArrayList;

public class CircleNode extends Node {
    private ArrayList<Node> neighbors;
    private ArrayList<Node> footprint;
    private double angle;
    private int firstTime;
    private int secondTime;
    private boolean update;

    public CircleNode() {
        neighbors = new ArrayList<>();
        footprint = new ArrayList<>();
        update = false;
    }

    public void onStart() {
        angle = (Math.random() > 0.5) ? 0.1 : -0.1;
        firstTime = getTime();
    }

    public void onClock() {
        setDirection((getDirection()-angle)%(2.0*Math.PI));
        move(2);
        if (getTime() < firstTime + Math.PI / Math.abs(angle)) {
            sendAll("");
            secondTime = getTime();
        } else if (getTime() < secondTime + Math.PI / Math.abs(angle)) {
            sendAll(footprint);
        }
        if (update == true) {
            //envoyer footprint pendant un tour
        }
    }

    private boolean exclusiveJointure(ArrayList<Node> footprint, ArrayList<Node> list) {
        boolean modif = false;
        for (Node n : list) {
            if (!footprint.contains(n)) {
                footprint.add(n);
                modif = true;
            }
        }
        return modif;
    }

    public void onMessage(Message message) {
        if (message.getContent() instanceof String && !neighbors.contains(message.getSender()) && !footprint.contains(message.getSender())) {
            neighbors.add(message.getSender());
            footprint.add(message.getSender());
        }
        if (message.getContent() instanceof ArrayList)
            update = exclusiveJointure(footprint, (ArrayList<Node>) message.getContent());
    }
}