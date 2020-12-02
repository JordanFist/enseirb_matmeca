import jbotsim.Link;
import jbotsim.Node;
import java.util.ArrayList;

public class DataOneClock {
    private ArrayList<Link> connectionsOneClock;
    private ArrayList<Node> nodes;
    private int time;

    public DataOneClock(DataOneClock doc, int time) {
        this.time = time;
        if (doc == null)
            connectionsOneClock = new ArrayList<>();
        else
            connectionsOneClock = new ArrayList<>(doc.connectionsOneClock);
    }

    //================================================================================================================
    // Fonctions d'abstractions
    //================================================================================================================

    /**
     * Retourne le nombre de nodes dans la topologie
     * @param n
     * @return int
     */
    private int numberOfNodes(Node n) {
        return n.getTopology().getNodes().size();
    }

    private Link numericOrder(Link link) {
        if (link.source.getID() < link.destination.getID())
            return link;
        else
            return new Link(link.destination, link.source);
    }

    /**
     * Retourne si une node est dans un lien
     * @param link
     * @param n
     * @return
     */
    private boolean isInLink(Link link, Node n) {
        return (n.equals(link.source) || n.equals(link.destination));
    }

    //================================================================================================================
    // Corps du code
    //================================================================================================================

    /**
     * Retourne le temps pour un DataOneClock
     * @return int
     */
    int getTime() {
        return time;
    }

    /**
     * Retourne le tableau de liens de la structure donnée
     * @return
     */
    ArrayList<Link> getConnectionsOneClock() {
        return connectionsOneClock;
    }

    /**
     * Ajoute un lien fléché dans connectionsOneClock
     * @param n1
     * @param n2
     */
    void addLinkDirected(Node n1, Node n2) {
        connectionsOneClock.add(new Link(n1, n2, Link.Type.DIRECTED));
    }

    /**
     * Ajoute un lien dans connectionsOneClock
     * @param link
     */
    void addLink(Link link) {
        connectionsOneClock.add(numericOrder(link));
    }

    /**
     * Supprime un lien dans connectionsOneClock
     * @param link
     */
    void removeLink(Link link) {
        connectionsOneClock.remove(link);
    }

    /**
     * Retourne vrai si le lien existe deja dans la structure
     * @param link
     * @return boolean
     */
    boolean contain(Link link) {
        for (Link l : connectionsOneClock) {
            if (l.source.equals(link.source) && l.destination.equals(link.destination))
                return true;
        }
        return false;
    }

    /**
     * Retourne vrai si n se lie avec toutes les autres nodes de la structure
     * @param n
     * @return boolean
     */
    boolean NodeLinkEveryone(Node n) {
        int res = 0;
        for (Link link : connectionsOneClock) {
            if (isInLink(link, n))
                ++res;
            if (res == numberOfNodes(n) - 1)
                return true;
        }
        return false;
    }

    /**
     * Renvoie une structure DataOneClock avec des liens fléchés
     * @return
     */
    DataOneClock undirectedToDirected() {
        DataOneClock doc = new DataOneClock(null, this.time);
        for (Link link : connectionsOneClock) {
            doc.addLinkDirected(link.source, link.destination);
            doc.addLinkDirected(link.destination, link.source);
        }
        return doc;
    }

    /**
     * Creer les connections pour la fermeture transitive stricte
     * @param empreinte
     * @param linkToAdd
     * @param l
     */
    void connectivity(DataOneClock empreinte, ArrayList<Link> linkToAdd, Link l) {
        for (Link link : empreinte.connectionsOneClock) {

            if (((isInLink(link, l.source)) || (isInLink(link, l.destination))) && !(((isInLink(link, l.source))) && (isInLink(link, l.destination)))) {
                for (Link linkList : linkToAdd) {
                    if (linkList.destination.equals(l.source) && !contain(new Link(linkList.source, l.destination))) {
                        addLinkDirected(linkList.source, l.destination);
                    }
                    if (linkList.destination.equals(l.destination) && !contain(new Link(linkList.source, l.source))) {
                        addLinkDirected(linkList.source, l.source);
                    }
                }

                if (link.source.equals(l.source)) { //&& contain(new Link(link.destination, l.destination, Link.Type.DIRECTED))) {
                    addLinkDirected(link.destination, l.destination);
                    linkToAdd.add(new Link(link.destination, l.destination, Link.Type.DIRECTED));
                }

                if (link.destination.equals(l.source)) { //&& contain(new Link(link.source, l.destination, Link.Type.DIRECTED))) {
                    addLinkDirected(link.source, l.destination);
                    linkToAdd.add(new Link(link.source, l.destination, Link.Type.DIRECTED));
                }

                if (link.source.equals(l.destination)) { //&& contain(new Link(link.destination, l.source, Link.Type.DIRECTED))) {
                    addLinkDirected(link.destination, l.source);
                    linkToAdd.add(new Link(link.destination, l.source, Link.Type.DIRECTED));

                    if (link.destination.equals(l.destination)) { //&& contain(new Link(link.source, l.source, Link.Type.DIRECTED))) {
                        addLinkDirected(link.source, l.source);
                        linkToAdd.add(new Link(link.source, l.source, Link.Type.DIRECTED));
                    }
                }
            }
        }
    }

    /**
     * Renvoie vrai si la node n peut atteindre toutes les autres
     * @param n
     * @return boolean
     */
    boolean nodeReach(Node n) {
        int res = 0;
        for (Link link : connectionsOneClock) {
            if(n.equals(link.source))
                ++res;
            if (res == numberOfNodes(n) - 1)
                return true;
        }
        return false;
    }

    /**
     * Fais la concaténation entre 2 DataOneClock
     * @param doc
     */
    void concatenation(DataOneClock doc) {
        for (Link link : doc.connectionsOneClock) {
            if (!contain(link))
                connectionsOneClock.add(link);
        }
    }
}
