-- ============================================================
--   Nom de la base   :  ASSOCIATION
--   Nom de SGBD      :  ORACLE Version 7.0
--   Date de creation :  13/11/18  16:35
-- ============================================================

drop table if exists ASSOCIATIONS cascade ;

drop table if exists PERSONNES cascade ;

drop table if exists ADHERENTS cascade ;

drop table if exists PARTICIPATIONS cascade ;

drop table if exists EVENEMENTS cascade ;

drop table if exists NEWS cascade ;

drop table if exists COMMENTAIRES cascade ;

drop table if exists ADHESIONS cascade ;

drop table if exists FINANCEMENTS cascade ;

drop table if exists FINANCEURS cascade ;

drop table if exists ORGANISATIONS cascade ;

drop table if exists GESTIONS cascade ;

drop table if exists NOTATIONS cascade ;

-- ============================================================
--   Table : ASSOCIATIONS
-- ============================================================
create table ASSOCIATIONS
(
    NUMERO_ASSOCIATION		INT(3)              not null,
    NOM_ASSOCIATION		    VARCHAR(20)               not null,
    DATE_DE_CREATION		DATE                   not null,
    DESCRIPTION             VARCHAR(100)                      ,
    constraint pk_associations primary key (NUMERO_ASSOCIATION)
);


-- ============================================================
--   Table : PERSONNES
-- ============================================================

create table PERSONNES
(
    NUMERO_PERSONNE		INT(3)		not null,
    NOM_PERSONNE		VARCHAR(20)		not null,
    PRENOM_PERSONNE		VARCHAR(20)			,
    MAIL_PERSONNE		VARCHAR(30)			,
    FILIERE_PERSONNE		VARCHAR(20)		not null,
    PROMO_PERSONNE		INT(4)			,
    LOGIN_PERSONNE		VARCHAR(20)		not null,
    MOT_DE_PASSE		VARCHAR(20)			,
    constraint pk_personnes primary key (NUMERO_PERSONNE)
);

-- ============================================================
--   Table : ADHERENTS
-- ============================================================

create table ADHERENTS
(
    NUMERO_ADHERENT		INT(3)		not null,
    NUMERO_PERSONNE		INT(3)			,
    constraint pk_adherents primary key (NUMERO_ADHERENT)
);

-- ============================================================
--   Table : ADHESIONS
-- ============================================================

create table ADHESIONS
(
    NUMERO_ADHERENT		INT(3)		not null,
    NUMERO_ASSOCIATION		INT(3)		not null,
    COTISATION_ADHERENT		INT(3)		        ,
    DATE_ADHESION		DATE			        ,
    ETRE_AU_BUREAU		VARCHAR(3)	         	        ,
    constraint pk_adhesions primary key (NUMERO_ADHERENT, NUMERO_ASSOCIATION)
);

-- ============================================================
--   Table : NEWS
-- ============================================================

create table NEWS
(
    NUMERO_NEWS			INT(3)		not null,
    NUMERO_ADHERENT		INT(3)			,
    TITRE_NEWS			VARCHAR(30)		not null,
    TEXTE_NEWS			VARCHAR(100)			,
    DATE_DE_CREATION_NEWS	DATE				,
    constraint pk_news primary key (NUMERO_NEWS)
);

-- ============================================================
--   Table : EVENEMENTS
-- ============================================================

create table EVENEMENTS
(
    NUMERO_EVENEMENT		INT(3)		not null,
    TITRE			VARCHAR(20)		not null,
    DESCRIPTION			VARCHAR(100)			,
    COUT			INT(3)			,
    LIEU			VARCHAR(20)			,
    NOMBRE_DE_PLACES		INT(3)			,
    constraint pk_evenements primary key (NUMERO_EVENEMENT)
);

-- ============================================================
--   Table : FINANCEMENTS
-- ============================================================

create table FINANCEMENTS
(
    NUMERO_FINANCEMENT		INT(3)		not null,
    NUMERO_ASSOCIATION		INT(3)		not null,
    DATE_FINANCEMENT		DATE			not null,
    MONTANT_FINANCEMENT		INT(5)			,
    constraint pk_financements primary key (NUMERO_FINANCEMENT, NUMERO_ASSOCIATION)
);

-- ============================================================
--   Table : PARTICIPATIONS
-- ============================================================

create table PARTICIPATIONS
(
    NUMERO_PERSONNE		INT(3)		not null,
    NUMERO_EVENEMENT		INT(3)		not null,
    TARIF			VARCHAR(20)			,
    constraint pk_participations primary key (NUMERO_PERSONNE,NUMERO_EVENEMENT)
);

-- ============================================================
--   Table : NOTATIONS
-- ============================================================

create table NOTATIONS
(
    NUMERO_EVENEMENT		INT(3)		not null,
    NUMERO_ADHERENT		INT(20)		not null,
    NUMERO_PERSONNE		INT(3)		not null,
    NOTE			INT(2)		        ,
    constraint pk_notations primary key (NUMERO_EVENEMENT, NUMERO_ADHERENT, NUMERO_PERSONNE)
);

-- ============================================================
--   Table : COMMENTAIRES
-- ============================================================

create table COMMENTAIRES
(
    NUMERO_ADHERENT		INT(3)		not null,
    NUMERO_NEWS 		INT(3)		not null,
    COMMENTAIRE			VARCHAR(200)			,
    constraint pk_commentaires primary key (NUMERO_ADHERENT, NUMERO_NEWS)
);

-- ============================================================
--   Table : GESTIONS
-- ============================================================

create table GESTIONS
(
    NUMERO_EVENEMENT		INT(3)		not null,
    NUMERO_ADHERENT		INT(3)		not null,
    constraint pk_gestions primary key (NUMERO_EVENEMENT, NUMERO_ADHERENT)
);

-- ============================================================
--   Table : FINANCEURS
-- ============================================================

create table FINANCEURS
(
    NUMERO_FINANCEMENT		INT(3)		not null,
    SOURCE_FINANCEMENT		VARCHAR(20)		not null,
    constraint pk_financeurs primary key (NUMERO_FINANCEMENT)
);

-- ============================================================
--   Table : ORGANISATIONS
-- ============================================================

create table ORGANISATIONS
(
    NUMERO_EVENEMENT INT(3)		not null,
    NUMERO_ASSOCIATION		INT(3)		not null,
    DATE_DEBUT			DATE				,
    DATE_FIN			DATE				,
    constraint pk_organisations primary key (NUMERO_EVENEMENT, NUMERO_ASSOCIATION)
);


alter table PARTICIPATIONS
    add constraint fk1_participations foreign key (NUMERO_PERSONNE)
       references PERSONNES (NUMERO_PERSONNE);

alter table PARTICIPATIONS
    add constraint fk2_participations foreign key (NUMERO_EVENEMENT)
       references EVENEMENTS (NUMERO_EVENEMENT);

alter table NOTATIONS
    add constraint fk1_notations foreign key (NUMERO_EVENEMENT)
       references EVENEMENTS (NUMERO_EVENEMENT);

alter table NOTATIONS
    add constraint fk2_notations foreign key (NUMERO_ADHERENT)
       references ADHERENTS (NUMERO_ADHERENT);

alter table NOTATIONS
    add constraint fk3_notations foreign key (NUMERO_PERSONNE)
       references PERSONNES (NUMERO_PERSONNE);

alter table GESTIONS
    add constraint fk1_gestions foreign key (NUMERO_EVENEMENT)
       references EVENEMENTS (NUMERO_EVENEMENT);

alter table GESTIONS
    add constraint fk2_gestions foreign key (NUMERO_ADHERENT)
       references ADHERENTS (NUMERO_ADHERENT);

alter table COMMENTAIRES
    add constraint fk1_commentaires foreign key (NUMERO_ADHERENT)
       references ADHERENTS (NUMERO_ADHERENT);

alter table COMMENTAIRES
    add constraint fk2_commentaires foreign key (NUMERO_NEWS)
       references NEWS (NUMERO_NEWS);

alter table ADHESIONS
    add constraint fk1_adhesions foreign key (NUMERO_ADHERENT)
       references ADHERENTS (NUMERO_ADHERENT);

alter table ADHESIONS
    add constraint fk2_adhesions foreign key (NUMERO_ASSOCIATION)
       references ASSOCIATIONS (NUMERO_ASSOCIATION);

alter table FINANCEMENTS
    add constraint fk1_financements foreign key (NUMERO_FINANCEMENT)
       references FINANCEURS (NUMERO_FINANCEMENT);

alter table FINANCEMENTS
    add constraint fk2_financements foreign key (NUMERO_ASSOCIATION)
       references ASSOCIATIONS (NUMERO_ASSOCIATION);

alter table ORGANISATIONS
    add constraint fk1_organisations foreign key (NUMERO_EVENEMENT)
       references EVENEMENTS (NUMERO_EVENEMENT);

alter table ORGANISATIONS
    add constraint fk2_organisations foreign key (NUMERO_ASSOCIATION)
       references ASSOCIATIONS (NUMERO_ASSOCIATION);
