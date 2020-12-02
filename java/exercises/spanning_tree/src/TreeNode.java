import jbotsim.Message;
import jbotsim.Node;

import java.util.ArrayList;
import java.util.List;

public class TreeNode extends Node {
    Node parent = null;
    List<Node> children = new ArrayList<Node>();
    static boolean isLeaf = true;
    int replyChildren = 0;

    @Override
    public void onSelection() {
        parent = this; // becomes root
        sendAll(this); // send own reference to neighbors (see explanations)
        setSize(12);
    }

    @Override
    public void onMessage(Message message) {
        if (parent == null) {
            parent = message.getSender();
            getCommonLinkWith(parent).setWidth(4);
            sendAll(parent); // propagate wave to all neighbors (only neighbors)
        } else {
            if (message.getContent() == this) {
                isLeaf = false;
                children.add(message.getSender());
            }
        }
    }
}