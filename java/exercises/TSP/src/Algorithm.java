import jbotsim.Point;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


public class Algorithm {

    protected List<Point> points;

    public void setPoints(List<Point> points) {
        this.points = points;
    }

    /**
     * Retourne la distance parcourue en suivant une liste de points données
     * @param lp une liste de points
     * @return res la distance parcourue en pixels
     */
    public double distance(ArrayList<Point> lp) {
        double res = 0;
        for (int i = 0; i < lp.size() - 1; ++i)
            res += lp.get(i).distance(lp.get(i + 1));
        res += lp.get(lp.size() - 1).distance(lp.get(0));
        return res;
    }

    /**
     * Retourne un entier entre 0 et n - 1
     * @param n
     * @return un entier entre 0 et n - 1
     */
    public int randInt(int n) {
        Random rand = new Random();
        return rand.nextInt(n);
    }

    /**
     * Retourne un point dans la liste lp le plus proche de p
     * @param lp la liste de points à ajouter au chemin
     * @param p le dernier point ajouté au chemin
     * @return pointMin l'indice du point dans lp à ajouter au chemin
     */
    public int nearestPoint(ArrayList<Point> lp, Point p) {
        int pointMin = 0;
            double min = lp.get(pointMin).distance(p);
            for (int i = 0; i < lp.size(); ++i) {
                if (lp.get(i).distance(p) < min)
                    pointMin = i;
                    min = lp.get(i).distance(p);
            }
            return pointMin;
    }

    /**
     * Retourne une liste de points en appliquant la méthode de nearestNeighbor
     * @return path une liste de points
     */
    public ArrayList<Point> nearestNeighbor() {
        ArrayList<Point> copyPoints = new ArrayList<>(points);
        ArrayList<Point> path = new ArrayList<>();
        path.add(copyPoints.remove(randInt(copyPoints.size())));

        for (int i = 0; i < points.size() - 1; ++i) {
            int nearestPoint = nearestPoint(copyPoints, path.get(i));
            path.add(copyPoints.remove(nearestPoint));
        }
        return path;
    }

    /**
     * Retourne le meilleur endroit dans le chemin lp courant pour ajouter un nouveau point c'est à dire réalisant
     * la distance la plus courte
     * @param lp le chemin courant
     * @param p le point à ajouter
     * @return indexMin l'indice où doit etre ajouté le nouveau point dans le chemin
     */
    public int bestPlace(ArrayList<Point> lp, Point p) {
        int indexMin = 0;
        lp.add(indexMin, p);
        double min = distance(lp);
        lp.remove(indexMin);
        for (int i = 1; i < lp.size() + 1; ++i) {
            lp.add(i, p);
            double res = distance(lp);
            if (res < min) {
                min = res;
                indexMin = i;
            }
            lp.remove(i);
        }
        return indexMin;
    }

    /**
     * Retourne une liste de points en appliquant la méthode de randomInsertion
     * @return path une liste de points
     */
    public ArrayList<Point> randomInsertion() {
        ArrayList<Point> copyPoints = new ArrayList<>(points);
        ArrayList<Point> path = new ArrayList<>();
        for (int i = 0; i < 3; ++i)
            path.add(copyPoints.remove(randInt(copyPoints.size())));

        for (int i = 0; i < points.size() - 3; ++i) {
            int n = randInt(copyPoints.size());
            int nextPoint = bestPlace(path, copyPoints.get(n));
            path.add(nextPoint, copyPoints.remove(n));
        }
        return path;
    }

    /**
     * Retourne une liste de points en appliquant une des 2 methodes
     * @return path une liste de points
     */
    public ArrayList<Point> getItinerary() {
        //ArrayList<Point> path = nearestNeighbor();
        ArrayList<Point> path = randomInsertion();

        System.out.println("La distance est de " + distance(path) + " pixels");
        return path;
    }
}
