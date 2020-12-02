#lang racket

(require "../src/graph.rkt")
(require "../src/parser.rkt")

(define gold-factory (factory (list (ressource "Marzipan" 10)) (ressource "Gold" 10) 10 0 ))
(define sugar-factory (factory (list (ressource "Sugarcane" 1)) (ressource "Sugar" 1) 3 0 ))
(define almond-factory (factory '() (ressource "Almond" 2) 2 0))
(define herb-factory (factory  '() (ressource "Wheat" 1) 2 0))
(define beer-factory (factory (list (ressource "Herb" 1) (ressource "Wheat" 1)) (ressource "Beer" 1) 2 0 ))
(define marzipan-factory (factory  (list (ressource "Sugar" 1) (ressource "Almond" 2)) (ressource "Marzipan" 1) 4 0 ))
(define wheat-factory (factory  '() (ressource "Herb" 1) 1 0 ))
(define sugarcane-factory (factory '() (ressource "Sugarcane" 1) 1 0))

(define g (graph '()))
 
(display "\n          ************************************* \n            Test de la fonction add-descendant  \n")


(define node1 (node wheat-factory  null null))
(define node2 (node herb-factory null null))
(define node3 (node beer-factory null null))
(define node4 (node marzipan-factory null null))
(define node5 (node sugarcane-factory null null))
(define node6 (node almond-factory null null))
(define node7 (node sugar-factory null null))


(add-descendant g node1 node3)
(add-descendant g node3 node2)
(add-descendant g node4 node7)
(add-descendant g node6 node4)
(add-descendant g node5 node6)
(display "\n           ****************************************************\n                Here are the nodes of the graph \n")
(display "NODE 1: \n" )
(display node1)
(display "NODE 2: \n" )
(display node2)
(display "\n")
(display "NODE 3: \n" )
(display node3)
(display "\n")
(display "NODE 4: \n" )
(display node4)
(display "\n")
(display "NODE 5: \n" )
(display node5)
(display "\n")
(display "NODE 6: \n" )
(display node6)
(display "\n")
(display "NODE 7: \n" )
(display node7)

(display "\n          ************************************* \n        Test de la fonction factories-with-no-inputs \n")
(define G2 (graph (list node1 node3 node7)))
(factories-with-no-inputs G2)

