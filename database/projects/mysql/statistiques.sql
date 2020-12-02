/*  Moyenne des commentaires pour une news */

select count(*) /(select count(*) from NEWS) from COMMENTAIRES group by () ;

/* Moyenne des notes par les participants à un événement */

select TITRE, count(*) as "Nb notes" from EVENEMENTS join NOTATIONS on EVENEMENTS.NUMERO_EVENEMENT = NOTATIONS.NUMERO_EVENEMENT group by TITRE;

select TITRE, avg(NOTE) as "MOY" from NOTATIONS join EVENEMENTS on NOTATIONS.NUMERO_EVENEMENT = EVENEMENTS.NUMERO_EVENEMENT group by TITRE;

/* classement des événements par notes données par les participants */

select TITRE, avg(NOTE) as "MOY" from NOTATIONS join EVENEMENTS on NOTATIONS.NUMERO_EVENEMENT = EVENEMENTS.NUMERO_EVENEMENT group by TITRE order by MOY;

/* classement des adhérents participant le plus aux événements */

select NOM_PERSONNE, count(*) as "NB_EVENEMENTS" from PARTICIPATIONS join PERSONNES on PARTICIPATIONS.NUMERO_PERSONNE = PERSONNES.NUMERO_PERSONNE group by NOM_PERSONNE order by NB_EVENEMENTS;

/* classement des finances des associations à une date donnée */

select NUMERO_FINANCEMENT, sum(MONTANT_FINANCEMENT) as "FINANCES" from FINANCEURS natural join FINANCEMENTS where DATE_FINANCEMENT < '30-JUN-17' group by NUMERO_FINANCEMENT order by FINANCES desc;

/*MYSQL*/
select NUMERO_FINANCEMENT, sum(MONTANT_FINANCEMENT) as "FINANCES" from FINANCEURS natural join FINANCEMENTS where DATE_FINANCEMENT < '2017-06-30' group by NUMERO_FINANCEMENT order by FINANCES desc;


select TITRE_NEWS, count(*) as "NB_COM" from NEWS join COMMENTAIRES on NEWS.NUMERO_NEWS = COMMENTAIRES.NUMERO_NEWS group by TITRE_NEWS;
