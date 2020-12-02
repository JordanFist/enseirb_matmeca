import java.sql.*;
import oracle.jdbc.pool.OracleDataSource;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

public class InterfaceSQL {
    Scanner sc;

    Consultations consultations;
    Statistiques statistiques;
    MiseAJour miseAJour;

    public InterfaceSQL() {
	sc = new Scanner(System.in);
	consultations = new Consultations();
	statistiques = new Statistiques();
	miseAJour = new MiseAJour();
    }

    void bienvenue() {
	System.out.println("Bonjour");
	System.out.println("Bienvenue sur l'interface de la base Associations");
	System.out.println(
			   "Rentrer dans la console les numéros à gauche du message pour rentrer dans le domaine voulu\n");
    }

    void typeDeRecherche() {
	System.out.println("Quel type de recherche voulez-vous faire sur votre base ?");
	System.out.println("1. Consultations");
	System.out.println("2. Statistiques");
	System.out.println("3. Mise à jour");
	System.out.println("4. Quitter l'interface");
	String reponse = sc.nextLine();
	if (reponse.equals("1"))
	    consultations();
	if (reponse.equals("2"))
	    statistiques();
	if (reponse.equals("3"))
	    miseAJour();
	if (reponse.equals("4"))
	    quitter();
    }

    void consultations() {
	System.out.println("\nVoici les types de consultations disponibles");
	System.out.println("1. La liste des adhérents à une association");
	System.out.println("2. La liste des adhérents à une association à une date donnée");
	System.out.println("3. La liste des adhérents qui n'ont pas cotisé à une association à une date donnée");
	System.out.println("4. La liste des personnes participant à un évènement");
	System.out.println("5. La liste des personnes organisant un évènement");
	System.out.println("6. Le nombre de commentaires postés pour une news");
	System.out.println("7. La liste des associations");
	System.out.println("8. La liste des événements");
	System.out.println("9. Retour");

	String reponse = sc.nextLine();
	String date;
	if (reponse.equals("1")) {
	    System.out.println("\nPour quelle association ?");
	    reponse = sc.nextLine();
	    try {
		consultations.choix1(reponse);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("2")) {
	    System.out.println("\nPour quelle association ?");
	    reponse = sc.nextLine();
	    System.out.println("Pour quelle date ?");
	    date = sc.nextLine();
	    try {
		consultations.choix2(reponse, date);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("3")) {
	    System.out.println("\nPour quelle association ?");
	    reponse = sc.nextLine();
	    System.out.println("Pour quelle date ?");
	    date = sc.nextLine();
	    try {
		consultations.choix3(reponse, date);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("4")) {
	    System.out.println("\nPour quelle évènement ?");
	    reponse = sc.nextLine();
	    try {
		consultations.choix4(reponse);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("5")) {
	    System.out.println("\nPour quelle évènement ?");
	    reponse = sc.nextLine();
	    try {
		consultations.choix5(reponse);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("6")) {
	    System.out.println("\nPour quel news ?");
	    reponse = sc.nextLine();
	    try {
		consultations.choix6(reponse);
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("7")) {
	    try {
		consultations.choix7();
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("8")) {
	    try {
		consultations.choix8();
	    } catch (Exception e) {
		erreur();
	    }
	    consultations();
	}
	if (reponse.equals("9"))
	    typeDeRecherche();
    }

    void statistiques() {
	System.out.println("\nVoici les types de statistiques disponibles");
	System.out.println("1. Moyenne des commentaires pour toutes les news");
	System.out.println("2. Moyenne des notes par les participants à un événement");
	System.out.println("3. Classement des événements par notes données par les participants");
	System.out.println("4. Classement des adhérents participant le plus aux événements");
	System.out.println("5. Classement des finances d'une association à une date donnée");
	System.out.println("6. Retour");

	String reponse = sc.nextLine();
	String date;
	if (reponse.equals("1")) {
	    try {
		statistiques.choix1();
	    } catch (Exception e) {
		erreur();
	    }
	    statistiques();
	}
	if (reponse.equals("2")) {
	    System.out.println("\nPour quelle évènement ?");
	    reponse = sc.nextLine();
	    try {
		statistiques.choix2(reponse);
	    } catch (Exception e) {
		erreur();
	    }
	    statistiques();
	}
	if (reponse.equals("3")) {
	    try {
		statistiques.choix3();
	    } catch (Exception e) {
		erreur();
	    }
	    statistiques();
	}
	if (reponse.equals("4")) {
	    try {
		statistiques.choix4();
	    } catch (Exception e) {
		erreur();
	    }
	    statistiques();
	}
	if (reponse.equals("5")) {
	    System.out.println("\nPour quelle association ?");
	    reponse = sc.nextLine();
	    System.out.println("\nPour quelle date ?");
	    date = sc.nextLine();
	    try {
		statistiques.choix5(reponse, date);
	    } catch (Exception e) {
		erreur();
	    }
	    statistiques();
	}
	if (reponse.equals("6")) {
	    typeDeRecherche();
	}
    }

    void miseAJour() {
	System.out.println("\nVoici les types de mises a jour disponibles");
	System.out.println("1. Ajouter un adhérent");
	System.out.println("2. Modifier un adhérent");
	System.out.println("3. Supprimer un adhérent");
	System.out.println("4. Ajouter un évènement");
	System.out.println("5. Modifier un évènement");
	System.out.println("6. Supprimer un évènement");
	System.out.println("7. Ajouter une association");
	System.out.println("8. Modifier une association");
	System.out.println("9. Supprimer une association");
	System.out.println("10. Retour");

	String reponse = sc.nextLine();
	String reponse1;
	String reponse2;
	String reponse3;
	String reponse4;
	String reponse5;
	String reponse6;
	if (reponse.equals("1")) {
	    System.out.println("\nNuméro Adhérent");
	    reponse1 = sc.nextLine();
	    System.out.println("\nNuméro Personne");
	    reponse2 = sc.nextLine();
	    try {
		miseAJour.choix1(reponse1, reponse2);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("2")) {
	    System.out.println("\nNuméro Adhérent");
	    reponse1 = sc.nextLine();
	    System.out.println("\nNuméro Personne");
	    reponse2 = sc.nextLine();
	    try {
		miseAJour.choix2(reponse1, reponse2);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("3")) {
	    System.out.println("\nNumero Personne");
	    reponse1 = sc.nextLine();
	    try {
		miseAJour.choix3(reponse1);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("4")) {
	    System.out.println("\nNumero évènement");
	    reponse1 = sc.nextLine();
	    System.out.println("\nTitre");
	    reponse2 = sc.nextLine();
	    System.out.println("\nDescription");
	    reponse3 = sc.nextLine();
	    System.out.println("\nCout");
	    reponse4 = sc.nextLine();
	    System.out.println("\nLieu");
	    reponse5 = sc.nextLine();
	    System.out.println("\nNombre de places");
	    reponse6 = sc.nextLine();
	    try {
		miseAJour.choix4(reponse1, reponse2, reponse3, reponse4, reponse5, reponse6);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("5")) {
	    System.out.println("\nNumero évènement");
	    reponse1 = sc.nextLine();
	    System.out.println("\nTitre");
	    reponse2 = sc.nextLine();
	    System.out.println("\nDescription");
	    reponse3 = sc.nextLine();
	    System.out.println("\nCout");
	    reponse4 = sc.nextLine();
	    System.out.println("\nLieu");
	    reponse5 = sc.nextLine();
	    System.out.println("\nNombre de places");
	    reponse6 = sc.nextLine();
	    try {
		miseAJour.choix5(reponse1, reponse2, reponse3, reponse4, reponse5, reponse6);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("6")) {
	    System.out.println("\nNumero évènement");
	    reponse1 = sc.nextLine();
	    try {
		miseAJour.choix6(reponse1);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("7")) {
	    System.out.println("\nNumero association");
	    reponse1 = sc.nextLine();
	    System.out.println("\nNom association");
	    reponse2 = sc.nextLine();
	    System.out.println("\nDate de creation");
	    reponse3 = sc.nextLine();
	    System.out.println("\nDescription");
	    reponse4 = sc.nextLine();
	    try {
		miseAJour.choix7(reponse1,reponse2, reponse3, reponse4);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("8")) {
	    System.out.println("\nNumero association");
	    reponse1 = sc.nextLine();
	    System.out.println("\nNom association");
	    reponse2 = sc.nextLine();
	    System.out.println("\nDate de creation");
	    reponse3 = sc.nextLine();
	    System.out.println("\nDescription");
	    reponse4 = sc.nextLine();
	    try {
		miseAJour.choix8(reponse1,reponse2, reponse3, reponse4);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("9")) {
	    System.out.println("\nNumero association");
	    reponse1 = sc.nextLine();
	    try {
		miseAJour.choix9(reponse1);
	    } catch (Exception e) {
		erreur();
	    }
	    miseAJour();
	}
	if (reponse.equals("10")) {
	    typeDeRecherche();
	}
    }

    void quitter() {
	System.exit(0);
    }

    void erreur() {
	System.out.println("La requete est fausse ou erreur de connexion à la base");
	System.exit(1);
    }

    public static void main(String[] args) throws SQLException, ClassNotFoundException, java.io.IOException {
	InterfaceSQL interfaceSql = new InterfaceSQL();
	interfaceSql.bienvenue();
	interfaceSql.typeDeRecherche();
    }
}
