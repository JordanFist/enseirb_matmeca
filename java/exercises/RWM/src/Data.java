import jbotsim.Link;
import jbotsim.Node;
import jbotsim.Topology;
import java.util.ArrayList;

public class Data {
    private ArrayList<DataOneClock> connections;
    private Topology tp;

    public Data(Topology tp) {
        this.tp = tp;
        connections = new ArrayList<>();
    }

    //================================================================================================================
    // Fonctions d'abstractions
    //================================================================================================================

    /**
     * Renvoie vrai si connections est vide
     * @return boolean
     */
    private boolean isEmpty() {
        return (connections.size() == 0);
    }

    /**
     * Renvoie la 1er structure DataOneClock de connections
     * @return DataOneClock
     */
    private DataOneClock getFirstConnections() {
        if (!isEmpty())
            return connections.get(0);
        return null;
    }

    /**
     * Renvoie la dernière structure DataOneClock de connections
     * @return DataOneClock
     */
    private DataOneClock getLastConnections() {
        if (!isEmpty())
            return connections.get(connections.size() - 1);
        return null;
    }

    /**
     * Renvoie le nombre de nodes dans la topologie
     * @return int
     */
    private int numberOfNodes() {
        return tp.getNodes().size();
    }

    /**
     * Renvoie le nombre de permutations possible
     * @param i
     * @return int
     */
    private int permutation(int i) {
        if (i == 0)
            return 1;
        return i * permutation(i - 1);
    }

    /**
     * renvoie le nombre de combinaisons possible
     * @param n
     * @param k
     * @return int
     */
    private int combination(int n, int k) {
        return (permutation(n) / (permutation(k) * permutation(n - k)));
    }

    /**
     * Renvoie vrai si la node est dans le tableau de nodes
     * @param list
     * @param node
     * @return boolean
     */
    private boolean contain(ArrayList<Node> list, Node node) {
        for (Node n : list) {
            if (node.equals(n))
                return true;
        }
        return false;
    }

    //================================================================================================================
    // Corps du code
    //================================================================================================================

    /**
     * Renvoie le temps de la dernière structure ajouté dans connections
     * @return int
     */
    int getLastConnectionTime() {
        if (isEmpty())
            return -1;
        return (getLastConnections().getTime());
    }

    /**
     * Ajoute un lien dans la derniere connection faite
     * @param link
     */
    void addLink(Link link) {
        getLastConnections().addLink(link);
    }

    /**
     * Creer un nouveau lien ajouté dans connections
     * @param link
     * @param time
     */
    void createAndAddLink(Link link, int time) {
        DataOneClock doc = new DataOneClock(getLastConnections(), time);
        connections.add(doc);
        addLink(link);
    }

    /**
     * Supprime un lien dans la dernière structure de connections
     * @param link
     */
    void removeLink(Link link) {
        getLastConnections().removeLink(link);
        /*
        if (getLastConnections().isEmpty())
            connections.remove(getLastConnections());*/
    }

    /**
     * Creer et supprime un lien dans la derniere structure de connections
     * @param link
     * @param time
     */
    void createAndRemoveLink(Link link, int time) {
        DataOneClock doc = new DataOneClock(getLastConnections(), time);
        connections.add(doc);
        removeLink(link);
    }

    /**
     * Renvoie les liens à une date donnée
     * @param time
     * @return DataOneClock
     */
    DataOneClock getLinksAt(int time) {
        DataOneClock oldDoc = null;
        for (DataOneClock doc : connections) {
            if (time == doc.getTime())
                return doc;
            if (time < doc.getTime())
                return oldDoc;
            oldDoc = doc;
        }
        return getLastConnections();
    }

    //================================================================================================================
    // Empreinte et Fermeture Transitive
    //================================================================================================================

    /**
     * Renvoie l'empreinte à un temps donnée
     * @param time
     * @return DataOneClock
     */
    DataOneClock empreinte (int time) {
        DataOneClock docRet = new DataOneClock(null, time);
        for (DataOneClock doc : connections) {
            if (doc.getTime() > time)
                break;
            for (Link link : doc.getConnectionsOneClock()) {
                if (!docRet.contain(link)) {
                    docRet.addLink(link);
                }
            }
        }
        return docRet;
    }

    /**
     * Renvoie la fermeture transitive stricte à un temps donnée
     * @param time
     * @return DataOneClock
     */
    DataOneClock fermetureTransitiveStricte(int time) {
        DataOneClock fts = new DataOneClock(getFirstConnections(), time);
        fts = fts.undirectedToDirected();
        ArrayList<Link> linkToAdd = new ArrayList<>();
        for (int i = 1; i < connections.size(); ++i) {

            fts.concatenation(connections.get(i).undirectedToDirected());


            if (connections.get(i).getTime() > time)
                break;

            for (Link link : connections.get(i).getConnectionsOneClock()) {
                fts.connectivity(empreinte(connections.get(i - 1).getTime()), linkToAdd, link);
            }
        }
        return fts;
    }

    //================================================================================================================
    // Tests de propriétés
    //================================================================================================================

    /**
     * Renvoie les nodes qui respectent la condition C3
     * @param time
     * @return tableau de nodes
     */
    ArrayList<Node> isC3(int time) {
        ArrayList<Node> nodes = new ArrayList<>();
        DataOneClock fts = fermetureTransitiveStricte(time);
        for (Link link : fts.getConnectionsOneClock()) {
            if (fts.nodeReach(link.source) && !contain(nodes, link.source)) {
                nodes.add(link.source);
            }
            if (fts.nodeReach(link.destination) && !contain(nodes, link.destination)) {
                nodes.add(link.destination);
            }
        }
        return nodes;
    }

    /**
     * Renvoie true si la condition C4 est vérifiée à t = time
     * @param time
     * @return boolean
     */
    boolean isC4(int time) {
        ArrayList<Node> nodes = new ArrayList<>();
        DataOneClock doc = fermetureTransitiveStricte(time);
        for (Link link : doc.getConnectionsOneClock()) {
            if (doc.nodeReach(link.source) && !contain(nodes, link.source))
                nodes.add(link.source);
            if (doc.nodeReach(link.destination) && !contain(nodes, link.destination))
                nodes.add(link.destination);
        }
        if (nodes.size() == tp.getNodes().size())
            return true;
        return false;
    }

    /**
     * Renvoie les nodes qui respectent la condition C5
     * @param time
     * @return tableau de nodes
     */
    ArrayList<Node> isC5(int time) {
        ArrayList<Node> nodes = new ArrayList<>();
        DataOneClock doc = empreinte(time);
        for (Link link : doc.getConnectionsOneClock()) {
            if (doc.NodeLinkEveryone(link.source) && !contain(nodes, link.source))
                nodes.add(link.source);
            if (doc.NodeLinkEveryone(link.destination) && !contain(nodes, link.destination))
                nodes.add(link.destination);
        }
        return nodes;
    }

    /**
     * Renvoie true si la condition C6 est vérifiée à t = time
     * @param time
     * @return boolean
     */
    boolean isC6(int time) {
        DataOneClock doc = empreinte(time);
        return (doc.getConnectionsOneClock().size() == combination(numberOfNodes(), 2));
    }

    //================================================================================================================
    // Fonctions print
    //================================================================================================================

    /**
     * Print les nodes dans le tableau list
     * @param list
     */
    void printNode(ArrayList<Node> list) {
        System.out.print("Nodes qui respectent la propriété : ");
        for (int i = 0; i < list.size(); ++i) {
            if (i != list.size() - 1)
                System.out.print(list.get(i).getID() + ", ");
            else
                System.out.print(list.get(i).getID());
        }
        System.out.println();
    }


    void printFermetureTransitive() {
        System.out.println("FermetureTransitive");
        DataOneClock doc = fermetureTransitiveStricte(tp.getTime());
        for(Link link: doc.getConnectionsOneClock())
            System.out.println(link);
        System.out.println();
        System.out.println("fin");
    }

    /*
    void printEmpreinte() {
        System.out.println("Empreinte");
        DataOneClock doc = empreinte(tp.getTime());
        for(Link link: doc.getConnectionsOneClock())
            System.out.println(link);
        System.out.println();
        System.out.println("fin");
    }


    void printConnections() {
        System.out.println("Connections");
        for (DataOneClock doc : connections) {
            System.out.println("time :" + doc.getTime());
            for(Link link : doc.getConnectionsOneClock())
                System.out.println(link);
            System.out.println();
        }
        System.out.println("fin");
        System.out.println();
    }
    */
}
