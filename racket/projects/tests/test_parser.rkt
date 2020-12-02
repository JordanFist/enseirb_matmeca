#lang racket
(require "../src/parser.rkt")
 ;================================= LA FONCTION PRINCIPALE DE CE FICHIER EST LA FONCTION FINAL PRODUCTION LINE ===================================
;==================================== ELLE EST LE RESULTAT DE TOUTES LES AUTRES FONCTIONS QUI LA PRÈCÈDENT ===========================
(display "\n ****************************************** \n           test de la fonction final-production-line \n")
(display "\n test de final-production-line sur le fichier parser_1.txt \n")
(final-production-line "parser_1.txt")
(display "\n test de final-production-line sur le fichier parser_2.txt \n")

(final-production-line "parser_2.txt")

;============================= TESTS ==================================================
;(final-production-line "file.txt")
(display "\n ********************************* \n         test of function extract-input \n")
(extract-input "[]")
(extract-input "Wheat=1,Herb=2")
(extract-input "[  Wheat=1,Herb=2]")
(display "\n \n ********************************* \n         test of function extract-input \n")
(extract-output "[Flour=5,Bread=2]") ; returns one single ressource
(extract-output "[]") ;---> returns nothing : non valid factory
(display "\n \n ********************************* \n         test of function valid-input \n")
(valid-input? "[Wheat=1,Herb=2]") ;--->expected : #f ; factories in level 1 do take one single argument
(valid-input? "[Wheat=1]") ;----> Expected #t
(display "\n \n ********************************* \n         test de la fonction is-comment? \n")
(is-comment? "#hello world") ;----> ;Expected #t
(display "\n \n ********************************* \n         test de la fonction treat-line and extract-factory \n")
(string-normalize-spaces "[Wheat=1,herb=2] ---->   [Bread=3]   cost=5")



