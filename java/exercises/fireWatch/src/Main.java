import jbotsim.*;
import jbotsim.Color;
import jbotsimx.ui.JViewer;

/**
 * Il n'est pas essentiel de comprendre ce qu'il y a dans cette classe.
 */
public class Main {
    public static void deploySensors(Topology topology){
        for (int i=0; i<6; i++)
            for (int j=0; j<4; j++)
                topology.addNode(i*100+180-(j%2)*30, j*100+100, new Sensor());
        topology.addNode(50, 400, new Station());
        for (Link link : topology.getLinks())
            link.setColor(Color.gray);
    }
    public static void main(String[] args) {
        Topology topology = new Topology(800,600);
        topology.setLinkResolver(new LinkResolver(){
            @Override
            public boolean isHeardBy(Node n1, Node n2) {
                if ((n1 instanceof Sensor && n2 instanceof Canadair) ||
                        (n2 instanceof Sensor && n1 instanceof Canadair))
                    return false;
                return (n1.isWirelessEnabled() && n2.isWirelessEnabled()
                        && n1.distance(n2) < n1.getCommunicationRange());
            }
        });
        topology.setMessageEngine(new jbotsimx.messaging.DelayMessageEngine(10));
        deploySensors(topology);
        topology.addNode(50, 500, new Canadair());
        topology.addNode(100, 500, new Canadair());
        topology.addNode(50, 50, new Lake());
        topology.setClockSpeed(30);
        topology.setDefaultNodeModel(Fire.class);
        new JViewer(topology);
        topology.start();
    }
}