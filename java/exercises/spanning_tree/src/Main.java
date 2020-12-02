import jbotsim.Node;
import jbotsim.Topology;
import jbotsimx.ui.CommandListener;
import jbotsimx.ui.JTopology;
import jbotsimx.ui.JViewer;

public class Main {
    public static void main(String[] args) {
        Topology tp = new Topology();
        tp.setDefaultNodeModel(SensorNode.class);
        JTopology jtp = new JTopology(tp);
        jtp.addCommand("Update values");
        jtp.addCommandListener(new CommandListener() {
            @Override
            public void onCommand(String command) {
                if (command.equals("Update values"))
                    for (Node node : tp.getNodes()) {
                        ((SensorNode) node).sense();
                        if (((TreeNode)node).isLeaf = true)
                            ((SensorNode) node).protocole();
                    }
            }
        });
        tp.start();
        new JViewer(jtp);
    }
}
