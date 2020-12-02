--Consultation de la base

-- 1. La liste des adhérents à une association à une date donnée et celle des adhérents qui n'ont pas encore cotisé
select NOM_PERSONNE, PRENOM_PERSONNE
from PERSONNES
natural join ADHERENTS natural join ADHESIONS natural join ASSOCIATIONS
where NOM_ASSOCIATION = 'BDE' and DATE_ADHESION > '10-JUN-10' and COTISATION_ADHERENT = 0;


/*MYSQL*/
select NOM_PERSONNE, PRENOM_PERSONNE
from PERSONNES
natural join ADHERENTS natural join ADHESIONS natural join ASSOCIATIONS
where NOM_ASSOCIATION = 'BDE' and DATE_ADHESION > '2010-06-10' and COTISATION_ADHERENT = 0;

-- 2.La liste des personnes participant à un évènement
select NOM_PERSONNE, PRENOM_PERSONNE
from PERSONNES
natural join PARTICIPATIONS natural join EVENEMENTS
where TITRE = 'GALA';

--3. La liste des personnes organisant à un évènement
select NOM_PERSONNE, PRENOM_PERSONNE
from PERSONNES
natural join ADHERENTS natural join GESTIONS natural join EVENEMENTS
where TITRE = 'OLINP';

--4. Savoir le nombre de commentaires postés pour une news
select TITRE_NEWS, count(*) as NOMBRE
from NEWS
join COMMENTAIRES on NEWS.NUMERO_NEWS = COMMENTAIRES.NUMERO_NEWS group by TITRE_NEWS;
