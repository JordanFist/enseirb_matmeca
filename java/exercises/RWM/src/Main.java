import jbotsim.Link;
import jbotsim.Node;
import jbotsim.Topology;
import jbotsimx.ui.CommandListener;
import jbotsimx.ui.JTopology;
import jbotsimx.ui.JViewer;

import java.awt.*;
import java.util.ArrayList;

public class Main implements CommandListener{
    public static final String COMMAND_COMPUTE_C3 = "Compute C3";
    public static final String COMMAND_COMPUTE_C4 = "Compute C4";
    public static final String COMMAND_COMPUTE_C5 = "Compute C5";
    public static final String COMMAND_COMPUTE_C6 = "Compute C6";

    public Data data;
    public Topology tp;

    public Main() {
        tp = new Topology();
        JTopology jtp = new JTopology(tp);
        data = new Data(tp);

        tp.setDefaultNodeModel(RWPNode.class);

        new TopologyRecorder(tp, data);

        addNewCommand(jtp);
        jtp.addCommandListener(this);

        for (int i = 0; i < 4; i++)
            tp.addNode(-1, -1);

        new JViewer(jtp);
        tp.start();
    }

    public void addNewCommand(JTopology jtp) {
        jtp.addCommand(COMMAND_COMPUTE_C3);
        jtp.addCommand(COMMAND_COMPUTE_C4);
        jtp.addCommand(COMMAND_COMPUTE_C5);
        jtp.addCommand(COMMAND_COMPUTE_C6);
    }

    public void display(ArrayList<Node> nodes, String s) {
        if (nodes.size() != 0) {
            System.out.println("Le graphe temporel actuel est " + s + " : true");
            data.printNode(nodes);
        } else
            System.out.println("Le graphe temporel actuel est " + s + " : false");
    }


    //TODO

    @Override
    public void onCommand(String command) {
        ArrayList<Node> nodes;
        if (command.equals(COMMAND_COMPUTE_C3)) {
            nodes = data.isC3(tp.getTime());
            display(nodes, "C3");
        }
        if (command.equals(COMMAND_COMPUTE_C4))
            System.out.println("Le graphe temporel actuel est C4 : " + data.isC4(tp.getTime()));
        if (command.equals(COMMAND_COMPUTE_C5)) {
            nodes = data.isC5(tp.getTime());
            display(nodes, "C5");
        }
        if (command.equals(COMMAND_COMPUTE_C6))
            System.out.println("Le graphe temporel actuel est C6 : " + data.isC6(tp.getTime()));

    }

    public static void main(String args[]) {
        new Main();
    }
}
