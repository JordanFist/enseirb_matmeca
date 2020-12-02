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

insert into ASSOCIATIONS values (  1 , 'BDE'     , '25-JUN-20' , 'GENERAL'  ) ;
insert into ASSOCIATIONS values (  2 , 'BDS'     , '10-JUN-80' , 'SPORTS'  ) ;
insert into ASSOCIATIONS values (  3 , 'BDA'     , '15-JUN-00' , 'ARTS'      ) ;
insert into ASSOCIATIONS values (  4 , 'BAR'     , '12-JUN-05' , 'BOISSONS'  ) ;
insert into ASSOCIATIONS values (  5 , 'AIRTEL'  , '02-JUN-03' , 'ALTERNANTS' ) ;
insert into ASSOCIATIONS values (  6 , 'EIRBWARE', '09-JUN-05' , 'TECHNOLOGIE') ;
insert into ASSOCIATIONS values (  7 , 'ZIK'     , '27-JUN-90' , 'MUSIQUE'  ) ;
insert into ASSOCIATIONS values (  8 , 'PIXEIRB' , '30-JUN-09' , 'PHOTOS'  ) ;
insert into ASSOCIATIONS values (  9 , 'OENO'    , '26-JUN-15' , 'VINS'  ) ;
insert into ASSOCIATIONS values ( 10 , 'CINEIRB' , '19-JUN-10' , 'FILMS'  ) ;

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
insert into PERSONNES values (  4 , 'AYMARD'  , 'JEAN'     , 'JAYMARD@ENSEIRB.FR'    , 'MATMECA' , 2022, 'JAYMARD', 'CHAMPIGNON' ) ;
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

insert into ADHESIONS values (  1 , 5 , 5, '10-SEP-21', 'OUI' );
insert into ADHESIONS values (  2 , 9 , 10, '15-SEP-16', 'OUI' );
insert into ADHESIONS values (  3 , 1 , 10, '17-SEP-19', 'OUI' );
insert into ADHESIONS values (  4 , 2 , 5, '17-SEP-19', 'NON' );
insert into ADHESIONS values (  5 , 10, 15, '01-SEP-21', 'NON' );
insert into ADHESIONS values (  6 , 5 , 0, '02-SEP-16', 'NON' );
insert into ADHESIONS values (  7 , 7 , 7, '09-SEP-20', 'OUI' );
insert into ADHESIONS values (  8 , 6 , 7, '14-SEP-19', 'NON' );
insert into ADHESIONS values (  9 , 1 , 0, '29-SEP-21', 'NON' );
insert into ADHESIONS values ( 10 , 4 , 25, '21-SEP-16', 'OUI' );

commit ;

-- NEWS 

insert into NEWS values (  1 , 5, 'PREZ VIRE' , 'LE PREZ EST MORT', '22-MAY-15');
insert into NEWS values (  2 , 10, 'NOUVEAU PREZ' , 'REMPLACEMENT RAPIDE', '23-MAY-15');
insert into NEWS values (  3 , 5, 'NOUVEAU BUREAU' , 'CHANGEMENT DE TOUT LE BUREAU', '24-MAY-15');
insert into NEWS values (  4 , 4, 'VOL DE LA TRESORERIE' , 'LE PREZ SE BARRE AVEC LARGENT', '31-MAY-15');
insert into NEWS values (  5 , 6, 'NOUVEAU PREZ' , 'ELU ALEATOIREMENT', '1-JUN-15');
insert into NEWS values (  6 , 1, 'INEFFICACITE' , 'LASSOCIATION DEVIENT NULLE', '10-JUN-15');
insert into NEWS values (  7 , 10, 'COUP DETAT' , 'LE PREZ SE FAIT DECAPITER', '13-JUN-15');
insert into NEWS values (  8 , 1, 'REGIME DEMOCRATIQUE' , 'DEMOCRATIE OUI', '27-JUN-15');
insert into NEWS values (  9 , 7, 'NAISSANCE' , 'LE PREZ A UN FILS', '24-JAN-16');
insert into NEWS values ( 10 , 2, 'ACCIDENT DE TRAIN' , 'LE PREZ EST MORT', '22-MAY-15');

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

insert into ORGANISATIONS values (  1  , 1  , '20-JAN-16', '21-JAN-16');
insert into ORGANISATIONS values (  2  , 2  , '10-FEB-16', '11-FEB-17');
insert into ORGANISATIONS values (  3  , 2  , '19-MAY-16', '25-MAY-16');
insert into ORGANISATIONS values (  4  , 1  , '4-JUN-16', '05-JUN-17');
insert into ORGANISATIONS values (  5  , 3  , '5-JUN-16', '06-JUN-18');
insert into ORGANISATIONS values (  6  , 4  , '30-SEP-13', '08-JAN-16');
insert into ORGANISATIONS values (  7  , 5  , '10-JAN-10', '15-JAN-16');
insert into ORGANISATIONS values (  8  , 7  , '22-MAR-18', '24-MAR-18');
insert into ORGANISATIONS values (  9  , 9  , '7-JUL-15', '09-JUL-16');
insert into ORGANISATIONS values (  10 , 8  , '19-MAY-16', '20-MAY-16');

commit ;

-- FINANCEURS 

insert into FINANCEURS values (  1  , 'SOCIETE GENERALE' );
insert into FINANCEURS values (  2  , 'CAISSE DEPARGNE'  );
insert into FINANCEURS values (  3  , 'PIZZAHUT'         );
insert into FINANCEURS values (  4  , 'BURGER KING'      );
insert into FINANCEURS values (  5  , 'MCDONALDS'        );

commit ;

-- FINANCEMENTS 

insert into FINANCEMENTS values (  1 , 1 , '20-JAN-16', 1005);
insert into FINANCEMENTS values (  2 , 2 , '10-SEP-15', 390);
insert into FINANCEMENTS values (  3 , 2 , '30-JUN-17', 2480);
insert into FINANCEMENTS values (  4 , 1 , '2-DEC-16', 1900);
insert into FINANCEMENTS values (  5 , 4 , '7-MAR-17', 150);
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
