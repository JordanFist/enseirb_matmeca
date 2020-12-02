import jbotsim.Point;
import java.util.Random;

public class RWPNode extends WaypointNode {
    public static int MAX_SPEED = 10;

    @Override
    public void onArrival() {
        Point p = new Point(randInt(getTopology().getWidth()), randInt(getTopology().getHeight()));
        addDestination(p);
    }

    private int randInt(int n) {
        Random rand = new Random();
        return rand.nextInt(n);
    }

    @Override
    public void setSpeed(double s) {
        speed = randInt(MAX_SPEED);
    }

    @Override
    public void onStart() {
        Point p = new Point(randInt(getTopology().getWidth()), randInt(getTopology().getHeight()));
        addDestination(p);
        setSpeed(speed);
    }
}
