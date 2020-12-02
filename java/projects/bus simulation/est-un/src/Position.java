package tec;
/**
 * Cette classe represente la position d'un passager par rapport a un transport.
 * Une position a trois etats possibles : assis dans un transport,
 * debout dans un transport et dehors d'un transport.
 *
 * Les instances de cette classe sont des objets constants.
 *
 * @author Georgy
 * @since 2007-2016
 **/
class Position {
  static final private Position DEHORS = new Position();
  static final private Position ASSIS = new Position();
  static final private Position DEBOUT = new Position();

  /**
   * construit une l'instance dans la position dehors.
   *
   */

    private Position() {
    }

    static public Position create() {
	return DEHORS;
    }

  /**
   * Construit une instance en precisant un des positions du passager.
   *
   * @param e valeur de l'etat.
   */
   /*
  private Position(int e) {
    this = e;
  }
*/

  /**
   * La position est-elle dehors ?
   *
   * @return vrai si l'etat de l'instance est dehors;
   */
  public boolean estDehors() {
    return this == DEHORS;
  }

  /**
   * La position est-elle assis ?
   *
   * @return vrai si l'etat de l'instance est assis;
   */
  public boolean estAssis() {
    return this == ASSIS;
  }

  /**
   * La position est-elle debout ?
   *
   * @return vrai si l'etat de l'instance est debout;
   */
  public boolean estDebout() {
    return this == DEBOUT;
  }

  /**
   * La position est-elle assis ?
   *
   * @return vrai la position est assis ou debout.
   */
  public boolean estInterieur() {
    return this != DEHORS;
  }


  /**
   * Fournit une position assis.
   *
   * @return instance dans l'etat assis.
   */
  public Position assis() {
    return ASSIS;
  }

  /**
   * Fournit une position debout.
   *
   * @return instance dans l'etat debout.
   */

  public Position debout() {
    return DEBOUT;
  }

  /**
   * Fournit une position dehors.
   *
   * @return instance dans l'etat dehors.
   */

  public Position dehors() {
    return DEHORS;
  }

  /**
   * Cette methode est heritee de la classe {@link java.lang.Object}.
   * Tres utile pour le debogage, elle permet de fournir une
   * chaine de caracteres correspondant a l'etat d'un objet.
   * Mais, il faut adapter le code de cette methode a chaque classe.
   *
   * @return une des chaines "<endehors>", "<assis>", "<debout>"
   * en fonction de la position thise.
   */
  @Override
  public String toString() {
    String nom = null;
    if (estDehors())
      nom = "endehors";
    if (estAssis())
      nom = "assis";
    if (estDebout())
      nom = "debout";

    return "<" + nom + ">";
  }
}
