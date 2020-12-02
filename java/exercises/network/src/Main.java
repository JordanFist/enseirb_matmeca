import jbotsim.Color;
import jbotsim.Node;
import jbotsim.Topology;
import jbotsim.event.SelectionListener;
import jbotsimx.ui.JViewer;

public class Main implements SelectionListener{
    Topology tp;
    GeoNode sourceNode;
    GeoNode targetNode;

    public Main() {
        tp = new Topology();
        tp.setClockSpeed(100); // slow down for visualization
        tp.setDefaultNodeModel(GeoNode.class);
        tp.addSelectionListener(this);
        new JViewer(tp);
        tp.start();
    }

    @Override
    public void onSelection(Node node) {
        GeoNode selectedNode = (GeoNode) node;
        if (sourceNode == null) {
            sourceNode = selectedNode;
            sourceNode.setColor(Color.red);
        } else if (targetNode == null){
            targetNode = selectedNode;
            targetNode.setIcon("/flag.png"); // To be adapted
            targetNode.setSize(14);
            sourceNode.route(new Bundle(targetNode.getLocation(), "HELLO"));
        }
    }

    public static void main(String[] args) {
        new Main();
    }
}