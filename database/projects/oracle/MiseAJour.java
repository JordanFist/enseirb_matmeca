import java.sql.*;
import oracle.jdbc.pool.OracleDataSource;
import java.util.concurrent.ExecutionException;

public class MiseAJour {
    public OracleDataSource ods;
    public Connection conn;
    public Statement stmt;

    void openBase() {
        try {
            ods = new OracleDataSource();
            ods.setUser("jsandri");
            ods.setPassword("jsandri");
            ods.setURL("jdbc:oracle:thin:@localhost:1521/oracle");

            conn = null;
            stmt = null;
        } catch (Exception e) {
        }
    }

    void closeBase() {
        try {
            if (stmt != null) {
                stmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        } catch (Exception e) {
        }
    }

    boolean isEmpty(String s) {
        return (s.equals(""));
    }

    void choix1(String numeroAdherent, String numeroPersonne)
            throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("insert into ADHERENTS (NUMERO_ADHERENT, NUMERO_PERSONNE) values ("
                    + numeroAdherent + ", " + numeroPersonne + ")");
        } finally {
            System.out.println("\najouté");
            closeBase();
        }
    }

    void choix2(String numeroAdherent, String numeroPersonne)
            throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            if (!isEmpty(numeroPersonne))
                rset = stmt.executeQuery("update ADHERENTS set NUMERO_PERSONNE =" + numeroPersonne
                        + "where NUMERO_ADHERENT = " + numeroAdherent);
        } finally {
            System.out.println("\nmodifié");
            closeBase();
        }
    }

    void choix3(String numeroAdherent) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery(
                    "delete from NOTATIONS where NUMERO_ADHERENT in (select NUMERO_ADHERENT from ADHERENTS where NUMERO_ADHERENT ="
                            + numeroAdherent + ")");
            rset = stmt.executeQuery(
                    "delete from GESTIONS where NUMERO_ADHERENT in (select NUMERO_ADHERENT from ADHERENTS where NUMERO_ADHERENT ="
                            + numeroAdherent + ")");
            rset = stmt.executeQuery(
                    "delete from COMMENTAIRES where NUMERO_ADHERENT in (select NUMERO_ADHERENT from ADHERENTS where NUMERO_ADHERENT ="
                            + numeroAdherent + ")");
            rset = stmt.executeQuery(
                    "delete from ADHESIONS where NUMERO_ADHERENT in (select NUMERO_ADHERENT from ADHERENTS where NUMERO_ADHERENT ="
                            + numeroAdherent + ")");
            rset = stmt.executeQuery("delete from ADHERENTS where NUMERO_ADHERENT =" + numeroAdherent);
        } finally {
            System.out.println("\nsupprimé");
            closeBase();
        }
    }

    void choix4(String numeroEvenement, String titre, String description, String cout, String lieu,
            String nombreDePlaces) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery(
                    "insert into EVENEMENTS (NUMERO_EVENEMENT, TITRE, DESCRIPTION, COUT, LIEU, NOMBRE_DE_PLACES) values ("
                            + numeroEvenement + ", " + "'" + titre + "'" + ", " + "'" + description + "'" + ", " + cout
                            + ", " + "'" + lieu + "'" + ", " + nombreDePlaces + ")");
        } finally {
            System.out.println("\najouté");
            closeBase();
        }
    }

    void choix5(String numeroEvenement, String titre, String description, String cout, String lieu,
            String nombreDePlaces) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            if (!isEmpty(titre))
                rset = stmt.executeQuery("update EVENEMENTS set TITRE =" + "'" + titre + "'"
                        + "where NUMERO_EVENEMENT = " + numeroEvenement);
            if (!isEmpty(description))
                rset = stmt.executeQuery("update EVENEMENTS set DESCRIPTION =" + "'" + description + "'"
                        + "where NUMERO_EVENEMENT = " + numeroEvenement);
            if (!isEmpty(cout))
                rset = stmt.executeQuery(
                        "update EVENEMENTS set COUT =" + cout + "where NUMERO_EVENEMENT = " + numeroEvenement);
            if (!isEmpty(lieu))
                rset = stmt.executeQuery("update EVENEMENTS set LIEU =" + "'" + lieu + "'" + "where NUMERO_EVENEMENT = "
                        + numeroEvenement);
        } finally {
            System.out.println("\nmodifié");
            closeBase();
        }
    }

    void choix6(String numeroEvenement) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery(
                    "delete from PARTICIPATIONS where NUMERO_EVENEMENT in (select NUMERO_EVENEMENT from EVENEMENTS where NUMERO_EVENEMENT = "
                            + numeroEvenement + ")");
            rset = stmt.executeQuery(
                    "delete from NOTATIONS where NUMERO_EVENEMENT in (select NUMERO_EVENEMENT from EVENEMENTS where NUMERO_EVENEMENT ="
                            + numeroEvenement + ")");
            rset = stmt.executeQuery(
                    "delete from GESTIONS where NUMERO_EVENEMENT in (select NUMERO_EVENEMENT from EVENEMENTS where NUMERO_EVENEMENT ="
                            + numeroEvenement + ")");
            rset = stmt.executeQuery(
                    "delete from ORGANISATIONS where NUMERO_EVENEMENT in (select NUMERO_EVENEMENT from EVENEMENTS where NUMERO_EVENEMENT ="
                            + numeroEvenement + ")");
            rset = stmt.executeQuery("delete from EVENEMENTS where NUMERO_EVENEMENT =" + numeroEvenement);
        } finally {
            System.out.println("\nsupprimé");
            closeBase();
        }
    }

    void choix7(String numeroAssosciation, String nomAssociation, String dateDeCreation, String description)
            throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;

        System.out.println(
                "insert into ASSOCIATIONS (NUMERO_ASSOCIATION, NOM_ASSOCIATION, DATE_DE_CREATION, DESCRIPTION) values ("
                        + numeroAssosciation + ", " + "'" + nomAssociation + "'" + ", " + "'" + dateDeCreation + "'"
                        + ", " + "'" + description + "'" + ")");
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery(
                    "insert into ASSOCIATIONS (NUMERO_ASSOCIATION, NOM_ASSOCIATION, DATE_DE_CREATION, DESCRIPTION) values ("
                            + numeroAssosciation + ", " + "'" + nomAssociation + "'" + ", " + "'" + dateDeCreation + "'"
                            + ", " + "'" + description + "'" + ")");
        } finally {
            System.out.println("\najouté");
            closeBase();
        }
    }

    void choix8(String numeroAssosciation, String nomAssociation, String dateDeCreation, String description)
            throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            if (!isEmpty(nomAssociation))
                rset = stmt.executeQuery("update ASSOCIATIONS set NOM_ASSOCIATION =" + "'" + nomAssociation + "'"
                        + "where NUMERO_ASSOCIATIONS = " + numeroAssosciation);
            if (!isEmpty(dateDeCreation))
                rset = stmt.executeQuery("update ASSOCIATIONS set DATE_DE_CREATION =" + "'" + dateDeCreation + "'"
                        + "where NUMERO_ASSOCIATIONS = " + numeroAssosciation);
            if (!isEmpty(description))
                rset = stmt.executeQuery(
                        "update ASSOCIATIONS set DESCRIPTION =" + description + "where NUMERO_ASSOCIATIONS = " + numeroAssosciation);
        } finally {
            System.out.println("\nmodifié");
            closeBase();
        }
    }

    void choix9(String numeroAssociation) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();
        ResultSet rset = null;
        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery(
                    "delete from ADHESIONS where NUMERO_ASSOCIATION in (select NUMERO_ASSOCIATION from ASSOCIATIONS where NUMERO_ASSOCIATION = " 
                            + numeroAssociation + ")");
            rset = stmt.executeQuery(
                    "delete from FINANCEMENTS where NUMERO_ASSOCIATION in (select NUMERO_ASSOCIATION from ASSOCIATIONS where NUMERO_ASSOCIATION = " 
                            + numeroAssociation + ")");
            
            rset = stmt.executeQuery(
                    "delete from ORGANISATIONS where NUMERO_ASSOCIATION in (select NUMERO_ASSOCIATION from ASSOCIATIONS where NUMERO_ASSOCIATION = " 
                            + numeroAssociation + ")");
            rset = stmt.executeQuery(
                    "delete from ASSOCIATIONS where NUMERO_ASSOCIATION = " + numeroAssociation);
        } finally {
            System.out.println("\nsupprimé");
            closeBase();
        }
    }
}