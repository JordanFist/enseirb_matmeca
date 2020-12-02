-- ============================================================
--    suppression des donnees
-- ============================================================

delete from FINANCEMENTS ;
delete from FINANCEURS ;
delete from ORGANISATIONS ;
delete from GESTIONS ;
delete from NOTATIONS ;
delete from COMMENTAIRES ;
delete from NEWS ;
delete from ADHESIONS ;
delete from ADHERENTS ;
delete from PARTICIPATIONS ;
delete from PERSONNES ;
delete from EVENEMENTS ;
delete from ASSOCIATIONS ;

commit ;

-- ============================================================
--    creation des donnees
-- ===========================================================

-- ASSOCIATIONS

insert into ASSOCIATIONS values (  1 , 'BDE'     , '2020-06-25' , 'GENERAL'  ) ;
insert into ASSOCIATIONS values (  2 , 'BDS'     , '1980-06-10' , 'SPORTS'  ) ;
insert into ASSOCIATIONS values (  3 , 'BDA'     , '2000-06-15' , 'ARTS'      ) ;
insert into ASSOCIATIONS values (  4 , 'BAR'     , '2005-06-12' , 'BOISSONS'  ) ;
insert into ASSOCIATIONS values (  5 , 'AIRTEL'  , '2003-06-02' , 'ALTERNANTS' ) ;
insert into ASSOCIATIONS values (  6 , 'EIRBWARE', '2005-06-09' , 'TECHNOLOGIE') ;
insert into ASSOCIATIONS values (  7 , 'ZIK'     , '1990-06-27' , 'MUSIQUE'  ) ;
insert into ASSOCIATIONS values (  8 , 'PIXEIRB' , '2009-06-30' , 'PHOTOS'  ) ;
insert into ASSOCIATIONS values (  9 , 'OENO'    , '2015-06-26' , 'VINS'  ) ;
insert into ASSOCIATIONS values ( 10 , 'CINEIRB' , '2010-06-19' , 'FILMS'  ) ;

commit ;

-- EVENEMENTS

insert into EVENEMENTS values (1, 'CONCERT DE NOEL'  , 'CONCERT'           , 4 , 'ENSEIRB', 100);
insert into EVENEMENTS values (2, 'OLINP'            , 'SPORT'             , 3 , 'ENSEIRB', 300);
insert into EVENEMENTS values (3, 'GALA'             , 'REMISE DE DIPLOMES', 2 , 'CHATEAU', 200);
insert into EVENEMENTS values (4, 'KRACH BOURSIER'   , 'SOIREE'            , 1 , 'BAR'    , 150);
insert into EVENEMENTS values (5, 'WEI'              , 'INTEGRATION'       , 9 , 'CAMPING', 500);
insert into EVENEMENTS values (6, 'WEN'              , 'NATURE'            , 8 , 'CAMPAGNE', 50);
insert into EVENEMENTS values (7, 'WIS'              , 'SPORT INTEGRATION' , 6 , 'IBIZA'  , 100);
insert into EVENEMENTS values (8, 'WES'              , 'SKI'               , 7 , 'SERRE CHEVALIER', 100);
insert into EVENEMENTS values (9, 'SOIREE BARBAPAPA' , 'BARBAPAPA'         , 10, 'BAR'    , 150);
insert into EVENEMENTS values (10, 'DEPART 3A'        , 'ADIEU'             , 5, 'ENSEIRB' , 200);

commit ;

-- PERSONNES

insert into PERSONNES values (  1 , 'SANDRI'   , 'JORDAN'       , 'JSANDRI@ENSEIRB.FR'    , 'INFO' , 2020 , 'JSANDRI', '1234512345') ;
insert into PERSONNES values (  2 , 'LEECHAOSHIT'    , 'TERENCE'      , 'TLCS@ENSEIRB.FR'    , 'INFO' , 2020 , 'TLCS', 'LONGNOM') ;
insert into PERSONNES values (  3 , 'PERIS'  , 'SARAH'     , 'SPERIS@ENSEIRB.FR'    , 'INFO' , 2020, 'SPERIS', 'NAINE' ) ;
insert into PERSONNES values (  4 , 'AY03D'  , 'JEAN'     , 'JAY03D@ENSEIRB.FR'    , 'MATMECA' , 2022, 'JAY03D', 'CHAMPIGNON' ) ;
insert into PERSONNES values (  5 , 'ZOLE'  , 'CAMILLE'     , 'CZOLE@ENSEIRB.FR'    , 'MATMECA' , 2017, 'CZOLE', 'ENFERMEE' ) ;
insert into PERSONNES values (  6 , 'TERIEUR'  , 'ALAIN'     , 'ATERIEUR@ENSEIRB.FR'    , 'ELEC' , 2022, 'ATERIEUR', 'INTERIEUR' ) ;
insert into PERSONNES values (  7 , 'KAN'  , 'JERRY'     , 'JKAN@ENSEIRB.FR'    , 'ELEC' , 2010, 'JKAN', 'BIDON' ) ;
insert into PERSONNES values (  8 , 'BAR' , 'LENNY'       , 'LBAR@ENSEIRB.FR'   , 'INFO', 2025,  'LBAR', 'BUSTE' ) ;
insert into PERSONNES values (  9 , 'VERSAIRE'  , 'ANNIE'     , 'AVERSAIRE@ENSEIRB.FR'    , 'TELE' , 2020, 'AVERSAIRE', 'BONNEFETE' ) ;
insert into PERSONNES values ( 10 , 'CONDA'     , 'ANNA'       , 'ACONDA@ENSEIRB.FR' , 'ELEC', 2010, 'ACONDA', 'SERPENT' ) ;

commit ;

-- PARTICIPATIONS

insert into PARTICIPATIONS values (  1 , 6  , 5 );
insert into PARTICIPATIONS values (  2 , 8  , 5 );
insert into PARTICIPATIONS values (  3 , 10 , 3 );
insert into PARTICIPATIONS values (  4 , 1  , 3 );
insert into PARTICIPATIONS values (  5 , 10 , 4 );
insert into PARTICIPATIONS values (  6 , 4  , 4 );
insert into PARTICIPATIONS values (  7 , 3  , 10);
insert into PARTICIPATIONS values (  8 , 2  , 2 );
insert into PARTICIPATIONS values (  9 , 5  , 2 );
insert into PARTICIPATIONS values ( 10 , 6  , 6 );

commit ;

-- ADHERENTS

insert into ADHERENTS values (  1  , 4 );
insert into ADHERENTS values (  2  , 3 );
insert into ADHERENTS values (  3  , 2 );
insert into ADHERENTS values (  4  , 1 );
insert into ADHERENTS values (  5  , 9 );
insert into ADHERENTS values (  6  , 8 );
insert into ADHERENTS values (  7  , 6 );
insert into ADHERENTS values (  8  , 7 );
insert into ADHERENTS values (  9  , 10);
insert into ADHERENTS values (  10 , 5 );

commit ;


-- ADHESIONS

insert into ADHESIONS values (  1 , 5 , 5, '2021-09-19', 'OUI' );
insert into ADHESIONS values (  2 , 9 , 10, '2015-09-15', 'OUI' );
insert into ADHESIONS values (  3 , 1 , 10, '2019-09-17', 'OUI' );
insert into ADHESIONS values (  4 , 2 , 5, '2019-09-17', 'NON' );
insert into ADHESIONS values (  5 , 10, 15, '2021-09-01', 'NON' );
insert into ADHESIONS values (  6 , 5 , 0, '2016-09-02', 'NON' );
insert into ADHESIONS values (  7 , 7 , 7, '2020-09-09', 'OUI' );
insert into ADHESIONS values (  8 , 6 , 7, '2019-09-14', 'NON' );
insert into ADHESIONS values (  9 , 1 , 0, '2021-09-29', 'NON' );
insert into ADHESIONS values ( 10 , 4 , 25, '2016-09-21', 'OUI' );

commit ;

-- NEWS

insert into NEWS values (  1 , 5, 'PREZ VIRE' , 'LE PREZ EST MORT', '2015-05-22');
insert into NEWS values (  2 , 10, 'NOUVEAU PREZ' , 'REMPLACEMENT RAPIDE', '2015-05-23');
insert into NEWS values (  3 , 5, 'NOUVEAU BUREAU' , 'CHANGEMENT DE TOUT LE BUREAU', '2015-05-24');
insert into NEWS values (  4 , 4, 'VOL DE LA TRESORERIE' , 'LE PREZ SE BARRE AVEC LARGENT', '2015-05-31');
insert into NEWS values (  5 , 6, 'NOUVEAU PREZ' , 'ELU ALEATOIREMENT', '2015-06-01');
insert into NEWS values (  6 , 1, 'INEFFICACITE' , 'LASSOCIATION DEVIENT NULLE', '2015-06-10');
insert into NEWS values (  7 , 10, 'COUP DETAT' , 'LE PREZ SE FAIT 12APITER', '2015-06-13');
insert into NEWS values (  8 , 1, 'REGIME DEMOCRATIQUE' , 'DEMOCRATIE OUI', '2015-06-27');
insert into NEWS values (  9 , 7, 'NAISSANCE' , 'LE PREZ A UN FILS', '2016-01-24');
insert into NEWS values ( 10 , 2, 'ACCIDENT DE TRAIN' , 'LE PREZ EST MORT', '2015-05-22');

commit ;

-- COMMENTAIRES

insert into COMMENTAIRES values (  1 , 6 ,'GENIAL' );
insert into COMMENTAIRES values (  2 , 8 , 'TROP COURT');
insert into COMMENTAIRES values (  3 , 10 , 'SYMPAS');
insert into COMMENTAIRES values (  4 , 1  , 'NUL');
insert into COMMENTAIRES values (  5 , 7 , 'JE ME SUIS BIEN AMUSE');
insert into COMMENTAIRES values (  6 , 4  , 'FATIGANT');
insert into COMMENTAIRES values (  7 , 3  , 'ENFIN');
insert into COMMENTAIRES values (  8 , 2  , 'HOURRA');
insert into COMMENTAIRES values (  9 , 5  , 'POURQUOI PAS');
insert into COMMENTAIRES values ( 10 , 6  , 'SERIEUX?');

commit ;

-- NOTATIONS

insert into NOTATIONS values (  1 , 6  , 5 , 2);
insert into NOTATIONS values (  2 , 8  , 5 , 5);
insert into NOTATIONS values (  3 , 10 , 3 , 10);
insert into NOTATIONS values (  4 , 1  , 3 , 15);
insert into NOTATIONS values (  2 , 10 , 4 , 20);
insert into NOTATIONS values (  6 , 4  , 4 , 18);
insert into NOTATIONS values (  7 , 3  , 10 , 13);
insert into NOTATIONS values (  8 , 2  , 2 , 14);
insert into NOTATIONS values (  9 , 5  , 2 , 9);
insert into NOTATIONS values ( 10 , 6  , 6 , 15);

commit ;

-- GESTIONS

insert into GESTIONS values (  1 , 6  );
insert into GESTIONS values (  2 , 8  );
insert into GESTIONS values (  3 , 10 );
insert into GESTIONS values (  4 , 1  );
insert into GESTIONS values (  5 , 10 );
insert into GESTIONS values (  6 , 4  );
insert into GESTIONS values (  7 , 3  );
insert into GESTIONS values (  8 , 2  );
insert into GESTIONS values (  9 , 5  );
insert into GESTIONS values ( 10 , 6  );

commit ;

-- ORGANISATIONS

insert into ORGANISATIONS values (  1  , 1  , '2016-01-20', '2016-01-21');
  insert into ORGANISATIONS values (  2  , 2  , '2016-02-10', '2017-02-11');
insert into ORGANISATIONS values (  3  , 2  , '2016-05-19', '2016-05-25');
insert into ORGANISATIONS values (  4  , 1  , '2016-06-04', '2017-06-05');
insert into ORGANISATIONS values (  5  , 3  , '2016-06-05', '2018-06-06');
insert into ORGANISATIONS values (  6  , 4  , '2013-09-30', '2016-01-08');
insert into ORGANISATIONS values (  7  , 5  , '2010-01-10', '2016-01-15');
insert into ORGANISATIONS values (  8  , 7  , '2018-03-22', '2018-03-24');
insert into ORGANISATIONS values (  9  , 9  , '2015-07-07', '2016-07-09');
insert into ORGANISATIONS values (  10 , 8  , '2016-05-19', '2016-05-20');

commit ;

-- FINANCEURS

insert into FINANCEURS values (  1  , 'SOCIETE GENERALE' );
insert into FINANCEURS values (  2  , 'CAISSE DEPARGNE'  );
insert into FINANCEURS values (  3  , 'PIZZAHUT'         );
insert into FINANCEURS values (  4  , 'BURGER KING'      );
insert into FINANCEURS values (  5  , 'MCDONALDS'        );

commit ;

-- FINANCEMENTS

insert into FINANCEMENTS values (  1 , 1 , '2016-01-20', 1005);
insert into FINANCEMENTS values (  2 , 2 , '2015-09-10', 390);
insert into FINANCEMENTS values (  3 , 2 , '2017-06-30', 2480);
insert into FINANCEMENTS values (  4 , 1 , '2016-12-02', 1900);
insert into FINANCEMENTS values (  5 , 4 , '2017-03-07', 150);
commit ;

-- ============================================================
--    verification des donnees
-- ============================================================

select count(*),'= 10 ?','ASSOCIATIONS' from ASSOCIATIONS
union
select count(*),'= 10 ?','PERSONNES' from PERSONNES
union
select count(*),'= 10 ?','ADHESIONS' from ADHESIONS
union
select count(*),'= 10 ?','NEWS' from NEWS
union
select count(*),'= 10 ?','COMMENTAIRES' from COMMENTAIRES
union
select count(*),'= 10 ?','PARTICIPATIONS' from PARTICIPATIONS
union
select count(*),'= 10 ?','NOTATIONS' from NOTATIONS
union
select count(*),'= 10 ?','GESTIONS' from GESTIONS
union
select count(*),'= 5 ?','FINANCEMENTS' from FINANCEMENTS
union
select count(*),'= 10 ?','ORGANISATIONS' from ORGANISATIONS
union
select count(*),'= 10 ?','ADHERENTS' from ADHERENTS
union
select count(*),'= 5 ?','FINANCEURS' from FINANCEURS
union
select count(*),'= 10 ?','EVENEMENTS' from EVENEMENTS
