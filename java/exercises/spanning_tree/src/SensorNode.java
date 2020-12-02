import jbotsim.Color;
import jbotsim.Node;
import jbotsim.Message;

import java.util.Random;

public class SensorNode extends TreeNode {
    int value;

    @Override
    public void onSelection() {
        setIcon("/server.png");
        super.onSelection();
    }

    public int randInt(int n) {
        Random rand = new Random();
        return rand.nextInt();
    }

    public void sense() {
        value = randInt(256);
        Color c = new Color(value, 0, 255 - value);
        setColor(c);
    }

    public void protocole() {
        send(parent, value);
    }

    public void maxValue(int childValue) {
        if (childValue > value)
            value = childValue;
    }

    @Override
    public void onMessage(Message message) {
        if (message.getContent() instanceof Node)
            super.onMessage(message);
        else {
            if (message.getContent() instanceof SensorNode) {
                if (children.contains(message.getSender()) == true) {
                    replyChildren += 1;
                    maxValue((int) message.getContent());
                }
            }
            if (replyChildren == children.size()) {
                replyChildren = 0;
                Color c = new Color(value, 0, 255 - value);
                setColor(c);
                if (parent != null)
                    send(parent, value);
            }
        }
    }

}
