import jbotsim.Message;
import jbotsim.Node;
import jbotsim.Point;

import java.util.ArrayList;
import java.util.List;

public class Station extends Node {
    private List<Point> handledFires = new ArrayList<>();
    private List<Canadair> canadairs = new ArrayList<>();

    public Station() {
        setIcon("/station.png");
        setSize(25);
        setCommunicationRange(120);
    }

    private Canadair getCanadairFree() {
        for (Canadair c : canadairs) {
            if (!c.isInMission()) {
                c.setMission(true);
                return c;
            }
        }
        return null;
    }

    @Override
    public void onSensingIn(Node node) {
        if (node instanceof Canadair && !canadairs.contains(node)) {
            canadairs.add((Canadair)node);
        }
    }

    @Override
    public void onSensingOut(Node node) {
        if (node instanceof Canadair && canadairs.contains(node)) {
            canadairs.remove(node);
        }
    }

    @Override
    public void onStart() {
        for (Node node : getNeighbors()) {
            if (node instanceof Canadair)
                canadairs.add((Canadair)node);
        }
        sendAll(new Message()); //Envoie seulement a ses voisins elle en a qu'un
    }

    @Override
    public void onMessage(Message message) {
        if (message.getSender() instanceof Sensor && message.getContent() instanceof Point && !handledFires.contains(message.getContent())) {
            Canadair c = getCanadairFree();
            if (c != null) {
                handledFires.add((Point)message.getContent());
                send(c, message.getContent());
            }
        }
        if (message.getSender() instanceof Canadair)
            handledFires.remove(message.getContent());
    }
}