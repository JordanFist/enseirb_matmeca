import jbotsim.Color;
import jbotsim.Message;
import jbotsim.Node;
import jbotsim.Point;

import java.util.ArrayList;
import java.util.List;

public class Sensor extends Node {
    private Node parent = null;
    private List<Fire> sensedFires = new ArrayList<>();
    private int time;

    private boolean isEmpty() {
        return (sensedFires.size() == 0);
    }

    @Override
    public void onClock() {
        if (!isEmpty())
            send(parent, this.getLocation()); // Envoyer la position du feu ?
        if (this.getTime() == time + 10)
            setColor(null);
    }

    @Override
    public void onStart() {
        setIcon("/sensor.png");
        setSize(16);
        setCommunicationRange(120);
        setSensingRange(60);
    }

    @Override
    public void onMessage(Message message) {
        if (parent == null) {
            parent = message.getSender();
            getCommonLinkWith(parent).setWidth(4);
            sendAll(message);
        }
        if (message.getContent() instanceof Point && message.getSender() instanceof Sensor) {
            time = getTime();
            setColor(Color.yellow);
            send(parent, message);
        }
    }

    @Override
    public void onSensingIn(Node node) {
        if (node instanceof Fire) {
            sensedFires.add((Fire) node);
            setColor(Color.red);
        }
    }

    @Override
    public void onSensingOut(Node node) {
        if (node instanceof Fire) {
            sensedFires.remove(node);
            if (isEmpty())
                setColor(null);
        }
    }

}