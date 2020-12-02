import java.sql.*;
import oracle.jdbc.pool.OracleDataSource;

public class Statistiques {
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

    void choix1() throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();

	ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("select count(*) /(select count(*) from NEWS) from COMMENTAIRES group by ()");

            while (rset.next()) { // Affichage du resultat.
		System.out.println(rset.getString(1));
            }
        } finally {
            closeBase();
        }
    }


    void choix2(String evenement) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();

	ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("select TITRE, avg(NOTE) from NOTATIONS join EVENEMENTS on NOTATIONS.NUMERO_EVENEMENT = EVENEMENTS.NUMERO_EVENEMENT where TITRE = '"+ evenement +"' group by TITRE");

            while (rset.next()) { // Affichage du resultat.
		System.out.println(rset.getString(2));
            }
        } finally {
            closeBase();
        }
    }


    void choix3() throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();

	ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("select TITRE, avg(NOTE) as \"MOY\" from NOTATIONS join EVENEMENTS on NOTATIONS.NUMERO_EVENEMENT = EVENEMENTS.NUMERO_EVENEMENT group by TITRE order by MOY");

            while (rset.next()) { // Affichage du resultat.
		System.out.println(rset.getString(1) + rset.getString(2));
            }
        } finally {
            closeBase();
        }
    }


    void choix4() throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();

	ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("select NOM_PERSONNE, count(*) as \"NB_EVENEMENTS\" from PARTICIPATIONS join PERSONNES on PARTICIPATIONS.NUMERO_PERSONNE = PERSONNES.NUMERO_PERSONNE group by NOM_PERSONNE order by NB_EVENEMENTS");

            while (rset.next()) { // Affichage du resultat.
		System.out.println(rset.getString(1) + rset.getString(2));
            }
        } finally {
            closeBase();
        }
    }


    void choix5(String assosciation, String date) throws SQLException, ClassNotFoundException, java.io.IOException {
        openBase();

	ResultSet rset = null;

        try {
            conn = ods.getConnection();
            stmt = conn.createStatement();
            rset = stmt.executeQuery("select NUMERO_FINANCEMENT, sum(MONTANT_FINANCEMENT) as \"FINANCES\" from FINANCEURS natural join FINANCEMENTS natural join ASSOCIATIONS where DATE_FINANCEMENT < '" + date +"' group by NUMERO_FINANCEMENT order by FINANCES desc");

            while (rset.next()) { // Affichage du resultat.
		System.out.println(rset.getString(2));
            }
        } finally {
            closeBase();
        }
    }
}
