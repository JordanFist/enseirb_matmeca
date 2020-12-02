import jbotsim.Link;
import jbotsim.Topology;
import jbotsim.event.ConnectivityListener;


public class TopologyRecorder implements ConnectivityListener{
    private Topology tp;
    private Data data;

    public TopologyRecorder(Topology tp, Data data) {
        this.tp = tp;
        tp.addConnectivityListener(this);
        this.data = data;
    }

    @Override
    public void onLinkAdded(Link link) {
        System.out.println("Appearance of " + link);
        int time = tp.getTime();
        if (data.getLastConnectionTime() == time)
            data.addLink(link);
        else
            data.createAndAddLink(link, time);
        //data.printFermetureTransitive();
    }

    @Override
    public void onLinkRemoved(Link link) {
        System.out.println("Disappearance of " + link);
        int time = tp.getTime();
        if (data.getLastConnectionTime() == time)
            data.removeLink(link);
        else
            data.createAndRemoveLink(link, time);
        //data.printFermetureTransitive();
    }

}