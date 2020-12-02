-- Ajout d'un adhérent
insert into ADHERENTS (NUMERO_ADHERENT, NUMERO_PERSONNE)
values (11, 11);

-- Suppression d'un adhérent 
delete from NOTATIONS
where NUMERO_ADHERENT in (
    select NUMERO_ADHERENT
    from ADHERENTS
    where NUMERO_PERSONNE = 8
);

delete from GESTIONS
where NUMERO_ADHERENT in (
    select NUMERO_ADHERENT
    from ADHERENTS
    where NUMERO_PERSONNE = 8
);

delete from COMMENTAIRES
where NUMERO_ADHERENT in (
    select NUMERO_ADHERENT
    from ADHERENTS
    where NUMERO_PERSONNE = 8
);

delete from ADHESIONS
where NUMERO_ADHERENT in (
    select NUMERO_ADHERENT
    from ADHERENTS
    where NUMERO_PERSONNE = 8
);

delete from ADHERENTS
where NUMERO_PERSONNE = 8;


-- Modification d'un adhérent
update ADHERENTS
set NUMERO_PERSONNE = 3 where NUMERO_PERSONNE = 2; 



-- Ajout d'un évènement  
insert into EVENEMENTS (NUMERO_EVENEMENT, TITRE, DESCRIPTION, COUT, LIEU, NOMBRE_DE_PLACES)
values (15, 'TEST', 'SUPER', 42, 'MARSEILLE', 50);

-- Suppression d'un évènement 
delete from PARTICIPATIONS
where NUMERO_EVENEMENT in (
    select NUMERO_EVENEMENT
    from EVENEMENTS
    where TITRE = 'GALA'
);

delete from NOTATIONS
where NUMERO_EVENEMENT in (
    select NUMERO_EVENEMENT
    from EVENEMENTS
    where TITRE = 'GALA'
);

delete from GESTIONS
where NUMERO_EVENEMENT in (
    select NUMERO_EVENEMENT
    from EVENEMENTS
    where TITRE = 'GALA'
);

delete from ORGANISATIONS
where NUMERO_EVENEMENT in (
    select NUMERO_EVENEMENT
    from EVENEMENTS
    where TITRE = 'GALA'
);

delete from EVENEMENTS
where TITRE = 'GALA';

-- Modification d'un évènement
update EVENEMENTS
set COUT = COUT + 1; 



-- Ajout d'une association  
insert into ASSOCIATIONS (NUMERO_ASSOCIATION, NOM_ASSOCIATION, DATE_DE_CREATION, DESCRIPTION)
values (11, 'GCC', '22-JAN-16', 'Blablabla');

-- Suppresion d'une association 

delete from ADHESIONS
where NUMERO_ASSOCIATION in (
    select NUMERO_ASSOCIATION
    from ASSOCIATIONS
    where NOM_ASSOCIATION = 'BDE'
);

delete from FINANCEMENTS
where NUMERO_ASSOCIATION in (
    select NUMERO_ASSOCIATION
    from ASSOCIATIONS
    where NOM_ASSOCIATION = 'BDE'
);

delete from ORGANISATIONS
where NUMERO_ASSOCIATION in (
    select NUMERO_ASSOCIATION
    from ASSOCIATIONS
    where NOM_ASSOCIATION = 'BDE'
);

delete from ASSOCIATIONS
where NOM_ASSOCIATION = 'BDE';


-- Modification d'une association
update ASSOCIATIONS
set DATE_DE_CREATION = '26-JUN-20' where DATE_DE_CREATION = '25-JUN-20';
