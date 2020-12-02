#lang racket
(require "parser.rkt")
(require "graph.rkt")

;========================EXPORTER LES FONCTIONS=======================================================
(provide enough-gold? is-valid? can-produce-factory? ressources-exist? valid-node? no-input-ressources? valid-production-line?)
;=============================================================================================================

(provide no-input-ressources? enough-gold? is-valid? can-produce-factory? ressources-exist?
         valid-node? valid-production-line?)
;===============================================================================================================
;fonction qui verifie qu'une usine n'a aucune entrée
(define (no-input-ressources? f)
  (if (null? (factory-Restaken f))
    #t
    #f))
;==================================================================================================================
;cette fonction renvoie vrai si toutes les usines (ne prenant aucune entrée) d'une chaine de production sont créables et que la quantié de gold initiale
;est suffisante
(define (enough-gold? factories init-gold)
  (let boucle ([res #f][i 0][l factories])
    (if (null? l)
      #f
      (if (equal? i (- (length l) 1))
        res
        (if (and (>= init-gold (factory-cost (list-ref l i))) (no-input-ressources? (list-ref l i)))
          #t
          (boucle res (add1 i) l))))))
;==========================================================================================================

;cette fonction verifie si  une chaine est valid ou pas : il devrait y avoir au moins une usine qui peut être achetée

(define (is-valid? g init-factories init-gold)
  (begin
    (if (enough-gold? init-factories init-gold)
      (let boucle ([bool #t][i 0][nodes (graph-nodes g)])
        (if (or (equal? i (- (length nodes) 1)) (equal? #f bool))
          bool
          (if (null? (node-parents (list-ref nodes i)))
            (boucle bool (add1 i) nodes)
            (if (valid-node? (list-ref nodes i))
              (boucle #t (add1 i) nodes)
              (boucle #f (add1 i) nodes)))))
       #f)))
;==========================================================================================================
;cette fonction parcourt tous les parents d'un noeud, cherche toutes les sorties de meme type que l'entrée du noeud considéré
;et additionne les quantités de ces  sorties. Puis elle verifie que la somme obtenue est >= à la quantité necessaire  à l'usine
;pour qu'elle soit produite
(define (can-produce-factory? node source)
  (begin
    (define type (ressource-type source)) 
    (define amount (ressource-quantity source))
    (if (null? (node-parents node))
      #t
      (let boucle ([count 0]
                 [i 0]
                 [parents (node-parents node)]
                 [fact-output-name (ressource-type (factory-Resproduced (node-peak (list-ref (node-parents node) 0))))]
                 [fact-output-quantity (ressource-quantity (factory-Resproduced (node-peak (list-ref (node-parents node) 0))))])
        (begin
          (if (not (equal? i (- (length parents) 1)))
            (if (equal? fact-output-name type)
              (boucle (+ count fact-output-quantity)
                    (add1 i) parents
                    (ressource-type (factory-Resproduced (node-peak (list-ref parents (add1 i)))))
                    (ressource-quantity (factory-Resproduced (node-peak (list-ref parents (add1 i))))))
              (boucle count
                    (add1 i) parents
                    (ressource-type (factory-Resproduced (node-peak (list-ref parents (add1 i)))))
                    (ressource-quantity (factory-Resproduced (node-peak (list-ref parents (add1 i)))))))
            (begin
              (if (equal? fact-output-name type)            
                (if (>= (+ count fact-output-quantity) amount)   
                  #t
                  #f)
                (if (>= count amount)                         
                  #t
                  #f)))))))))

;===================================================================================================================
;fonction qui verifie qu'on donne à une usine les ressources necessaires pour la crééer ou pas  
(define (ressources-exist? node)
  (begin
    (define inputs (factory-Restaken (node-peak node)))
    (if (null? inputs)
      #t
      (let boucle ([bool #t]
                 [i 0]
                 [res inputs]
                 [current-res (list-ref inputs 0)])
          (if (not (equal? i (- (length res) 1)))
            (boucle (and bool (can-produce-factory? node (list-ref inputs i)))
                  (add1 i)
                  res
                  (list-ref inputs (add1 i)))
            (and bool (can-produce-factory? node (list-ref inputs i))))))))
;================================================================================================================
;fonction qui verifie qu'un noeud du graphe est valide ; ie toutes les ressources dont il a besoin existent
(define (valid-node? node)
  (ressources-exist? node))


;===================================================================================================
;fonction qui nous sera utile dans le main vu qu'elle verifie a chaque fois que la chaine de production est valide ou pas 
(define (valid-production-line? g)
 (let boucle ([valid #t][i 0][nodes (graph-nodes g)])
   (if (or (equal? i (- (length nodes) 1)) (equal? #f valid))
     valid
     (if (null? (node-parents (list-ref nodes i)))
       (boucle valid (add1 i) nodes)
       (if (valid-node? (list-ref nodes i))
         (boucle #t (add1 i) nodes)
         (boucle #f (add1 i) nodes))))
    valid))