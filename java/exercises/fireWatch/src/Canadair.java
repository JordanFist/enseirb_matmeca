import jbotsim.Message;
import jbotsim.Node;
import jbotsim.Point;

public class Canadair extends WaypointNode {
    static final Point LAKE_POS = new Point(50, 50);
    static final int SENSOR_RANGE = 120;
    private Point parking;
    private Point fireInProgress;
    private boolean mission = false;

    public Canadair(){
        setIcon("/canadair.png");
        setSize(16);
        setCommunicationRange(120);
        setSensingRange(30);
    }

    void setMission(boolean mission) {
        this.mission = mission;
    }

    boolean isInMission() {
        return (mission == true);
    }

    @Override
    public void onMessage(Message message) {
        if (message.getContent() instanceof Point && message.getSender() instanceof Station) {
            addDestination(LAKE_POS);
            fireInProgress = (Point)message.getContent();
            double x = fireInProgress.getX();
            double y = fireInProgress.getY();

            addDestination(x + (SENSOR_RANGE/4), y - (SENSOR_RANGE/4));
            addDestination(x + (SENSOR_RANGE/4), y + (SENSOR_RANGE/4));
            addDestination(x - (SENSOR_RANGE/4) , y + (SENSOR_RANGE/4));
            addDestination(x - (SENSOR_RANGE/4) , y - (SENSOR_RANGE/4));
            addDestination(x + (SENSOR_RANGE/4), y - (SENSOR_RANGE/4));
            addDestination(fireInProgress);
        }
    }

    @Override
    public void onArrival() {
        if (getLocation().equals(fireInProgress)) {
            addDestination(parking);
        }
        if (getLocation().equals(parking)) {
            mission = false;
            sendAll(fireInProgress);
        }
    }

    @Override
    public void onStart() {
        parking = getLocation();
        super.setSpeed(2);
    }


    @Override
    public void onSensingIn(Node node) {
        if (node instanceof Fire)
            ((Fire) node).die();
    }
}