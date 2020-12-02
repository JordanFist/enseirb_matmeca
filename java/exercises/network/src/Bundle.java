import jbotsim.Point;

public class Bundle {
    public Point target;
    public String text;
    public Boolean randomRoute;
    public double distance;

    public Bundle(Point target, String text) {
        this.target = target;
        this.text = text;
        this.randomRoute = false;
        this.distance = 0;
    }
}