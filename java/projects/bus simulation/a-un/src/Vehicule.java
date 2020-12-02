package tec;
/**
 * Cette interface fixe/définit/spécifie les services d'un véhicule
 * qui accepte des passsagers (sous-types de l'interface Passager).
 *
 * <p>
 * Le client déclenche le trajet vers un nouvel arrêt par la méthode
 * allerArretSuivant().
 *
 * <p>
 * Un véhicule a un nombre déterminé de places assises et de places debout.
 * Les places assises (ou debout) ne sont pas repérables.
 * Le nombre de places assises et debouts est fixé à l'instanciation .
 *
 * <p>
 * Un véhicule authorise un passager à monter pour occuper soit une place debout
 * soit une place assise. Si l'entrée est acceptée le véhicule déclenche les
 * modificateurs de passager (changement de la position du passager).
 * <p>
 * Le véhicule prévient ses passagers de chaque nouvel arret par appel
 * à la méthode nouvelArret() sur chaque passager.
 * <p>
 * À chaque arrêt, un véhicule permet aux passagers soit de sortir,
 * soit de changer de place (d'assise en debout, ou l'inverse).
 * Si la demande est acceptée, le véhicule déclenche les méthodes de
 * modification de l'état du passager.
 */

abstract class Vehicule {

    /**
     * Indique au véhicule l'arrêt suivant en déclenche sur chaque passager
     * la méthode arretSuivant().
     */
    abstract void allerArretSuivant();
    /**
     *  Y-a-t-il des places assises libres ?
     * @return vrai si nombre max de places assises n'est pas atteinte.
     */
    abstract boolean aPlaceAssise();

    /**
     *  Y-a-t-il des places debout libres ?
     * @return vrai si nombre max de places debout n'est pas atteinte.
     */
    abstract boolean aPlaceDebout();

    /**
     * Le passager entre dans le véhicule en demandant une place assise.
     * la position du passager est forcément dehors.
     * Cette méthode est appelée par un passager.
     * @param p le passager qui demande à montée.
     */
    abstract void monteeDemanderAssis(Passager p);

    /**
     * Le passager entre dans le véhicule en demandant une place debout.
     * la position du passager est forcément dehors.
     * Cette méthode est appelée par un passager.
     * @param p le passager qui demande à montée.
     */
    abstract void monteeDemanderDebout(Passager p);

    /**
     * Change un passager d'une place assise vers une place debout
     * pour un passager déjà dans le véhicule.
     * @param p le passager avec une position assis dans le véhicule.
     */
    abstract void arretDemanderDebout(Passager p);

    /**
     * Change un passager d'une place debout vers une place assise
     * pour un passager déjà dans le véhicule.
     * @param p le passager avec une position debout dans le véhicule.
     */
    abstract void arretDemanderAssis(Passager p);
    
    /**
     * Fait sortir un passager du véhicule.
     * @param p le passager avec une position soit assise soit debout
     *          dans le véhicule.
     */
    abstract void arretDemanderSortie(Passager p);
}
