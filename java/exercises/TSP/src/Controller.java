import jbotsim.Node;
import jbotsim.Point;
import jbotsim.Topology;
import jbotsimx.ui.CommandListener;
import jbotsimx.ui.JTopology;
import jbotsimx.ui.JViewer;
import jbotsimx.ui.painting.BackgroundPainter;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Controller implements CommandListener, BackgroundPainter {

    public static final String COMMAND_COMPUTE_TSP = "Compute TSP";

    private Topology topology;
    private JTopology jTopology;

    private List<Point> points = new ArrayList<>();

    public Controller() {
        topology = new Topology();
        topology.setDefaultNodeModel(Target.class);

        jTopology = new JTopology(topology);
        jTopology.addCommand(COMMAND_COMPUTE_TSP);
        jTopology.addCommandListener(this);
        jTopology.addBackgroundPainter(this);

        /* 1er set de points

        topology.addNode(58.0, 128.0);
        topology.addNode(157.0, 51.0);
        topology.addNode(224.0, 150.0);
        topology.addNode(339.0, 68.0);
        topology.addNode(460.0, 39.0);
        topology.addNode(537.0, 150.0);
        topology.addNode(568.0, 358.0);
        topology.addNode(458.0, 306.0);
        topology.addNode(222.0, 353.0);
        topology.addNode(113.0, 289.0);
        topology.addNode(437.0, 119.0);
        topology.addNode(360.0, 280.0);
        topology.addNode(128.0, 219.0);
        topology.addNode(271.0, 81.0);
        topology.addNode(504.0, 222.0);

        */

        // 2eme set de points

        topology.addNode(591.0, 229.0);
        topology.addNode(548.0, 99.0);
        topology.addNode(396.0, 255.0);
        topology.addNode(531.0, 79.0);
        topology.addNode(476.0, 263.0);
        topology.addNode(322.0, 332.0);
        topology.addNode(519.0, 10.0);
        topology.addNode(234.0, 381.0);
        topology.addNode(43.0, 72.0);
        topology.addNode(271.0, 56.0);
        topology.addNode(406.0, 152.0);
        topology.addNode(574.0, 174.0);
        topology.addNode(382.0, 245.0);
        topology.addNode(161.0, 297.0);
        topology.addNode(361.0, 362.0);
        topology.addNode(104.0, 155.0);
        topology.addNode(466.0, 44.0);
        topology.addNode(342.0, 10.0);
        topology.addNode(252.0, 35.0);
        topology.addNode(321.0, 136.0);

        new JViewer(jTopology);
    }

    @Override
    public void onCommand(String command) {
        if (command.equals(COMMAND_COMPUTE_TSP)) {
            points.clear();
            for (Node node : topology.getNodes())
                if (node instanceof Target)
                    points.add(node.getLocation());

            Algorithm algorithm = new Algorithm();
            algorithm.setPoints(points);
            List<Point> itinerary = algorithm.getItinerary();
            // We will later replace this line by a proper algorithm call

            points = itinerary; // Make sure that the itinerary will be drawn

            assignToNode(itinerary);
        }
    }

    @Override
    public void paintBackground(Graphics2D g2d, Topology tp) {
        for (int i = 0; i < points.size(); i++) {
            Point from = points.get(i);
            Point to = points.get((i + 1) % points.size());
            g2d.drawLine((int) from.getX(), (int) from.getY(),
                    (int) to.getX(), (int) to.getY());
        }
    }

    protected void assignToNode(List<Point> itinerary) {
        if (!itinerary.isEmpty()) {
            WaypointNode node = new WaypointNode();
            node.setLocation(itinerary.get(0));
            for (int i = 1; i < itinerary.size() + 1; i++)
                node.addDestination(itinerary.get(i % itinerary.size()));
            topology.addNode(node);
        }
    }
}

