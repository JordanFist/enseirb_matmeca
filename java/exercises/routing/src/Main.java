import jbotsim.Node;
import jbotsim.Topology;
import jbotsim.event.SelectionListener;
import jbotsimx.ui.JViewer;

public class Main implements SelectionListener {
    private Topology tp;

    public Main () {
        tp = new Topology();
        tp.setDefaultNodeModel(CircleNode.class);
        tp.addSelectionListener(this);

        new JViewer(tp);
        tp.start();
    }

    @Override
    public void onSelection(Node node) {

    }

    public static void main(String[] args) {
        new Main();
    }
}
