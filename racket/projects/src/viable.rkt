#lang racket
(require "parser.rkt")
(require "graph.rkt")
(require "validity.rkt")

;===============================================================================
;fonction qui se balade dans les inputs d'une usine et verifie si la chaine de production peut fournir cette ressources ou pas 
(define (is-factory-supplied? node)
  (begin
    (define entry (factory-Restaken (node-peak node)))
    (if (null? entry)
      #t
      (let boucle ([bool #t]
                 [i 0]
                 [res entry]
                 [current-res (list-ref entry 0)])
          (if (not (equal? i (- (length res) 1)))
            (boucle (and bool (can-produce-factory? node (list-ref entry i)))
                  (add1 i)
                  res
                  (list-ref entry (add1 i)))
            (and bool ( can-produce-factory? node (list-ref entry i))))))))


;================================================================================
;fonction qui verifie qu'une chaine de production est viable ou pas 
(define (viable-production-line? g)
 (let boucle ([bool #t][i 0][nodes (graph-nodes g)])
   (if (or (equal? i (- (length nodes) 1)) (equal? #f bool))
     bool
     (if (null? (node-parents (list-ref nodes i)))
       (boucle bool (add1 i) nodes)
       (if (valid-node? (list-ref nodes i))
         (boucle #t (add1 i) nodes)
         (boucle #f (add1 i) nodes))))
    bool))


;================================================================================================
;fonction qui dit est ce qu'une usine est productibe à partie de la chaine de production courante
(define (is-suppliable? f parents)
  (let main ([node (node f null parents)])
    (is-factory-supplied? node)))
;=================================================================================================
;retourne une liste d'usine que la chaine de production peut maintenir en vie

(define (get-suppliable-factories g init-factories)
  (if (not (null? init-factories))
    (let main([no-input-factories '()]
              [input-factories '()]
              [suppliable-factories '()])
      (begin
        (let split-factories([i 0])
          (if (equal? i (- (length init-factories) 1))
              (if (null? (factory-Restaken (list-ref init-factories i)))
                  (set! no-input-factories (append no-input-factories (list (list-ref init-factories i))))
                  (set! input-factories (append input-factories (list (list-ref init-factories i)))))
              (if (null? (factory-Restaken (list-ref init-factories i)))
                  (begin
                    (set! no-input-factories (append no-input-factories (list (list-ref init-factories i))))
                    (split-factories (add1 i)))
                  (begin
                    (set! input-factories (append input-factories (list (list-ref init-factories i))))
                    (split-factories (add1 i))))))
        
        (let get-suppliable-factories([i 0])
          (if (not (null? (graph-nodes g)))
              (if (equal? i (- (length init-factories) 1))
                  (when (is-suppliable? (list-ref init-factories i) (factories-with-no-outputs g))
                    (set! suppliable-factories (append suppliable-factories (list (list-ref init-factories i)))))
                  (if (is-suppliable? (list-ref init-factories i) (factories-with-no-outputs g))
                      (begin
                        (set!  suppliable-factories (append suppliable-factories (list (list-ref init-factories i))))
                        (get-suppliable-factories (add1 i)))
                      (get-suppliable-factories (add1 i))))
              '()))
        (if (null? (graph-nodes g))
            no-input-factories
            suppliable-factories)))
    '()))
;=================================================================================
;fonction qui retourne la liste des factory qu'on peut acheter par la quantité de gold qu'on a 
(define (get-buyable-factories suppliable-factories gold)
  (if (not (null? suppliable-factories))
      (let main([buyable-factories'()])
        (let boucle([i 0])
          (if (equal? i (- (length suppliable-factories) 1))
              (when (>= gold (factory-cost (list-ref suppliable-factories i)))
                (set! buyable-factories (append buyable-factories (list (list-ref suppliable-factories i)))))
              (if (>= gold (factory-cost (list-ref suppliable-factories i)))
                  (begin
                    (set! buyable-factories (append buyable-factories (list (list-ref suppliable-factories i))))
                    (boucle (add1 i)))
                  (boucle (add1 i)))))
        buyable-factories)
      '()))

;==============================================================================
;fonction qui retourne la somme des quantités des sorties des usines figurant dans la liste factories
(define (sum-outputs factories sum)
  (if (null? factories)
    sum
    (sum-outputs (cdr factories) (+ (ressource-quantity (factory-Resproduced (node-peak (car factories)))) sum))))


;=============================================================================================
;cette fonction prend en entrée une liste d'usines ayant la meme sortie et verifie si elles peuvent fournir la quantité "quantity"
;
(define (get-needed-factories-among factories quantity)

  (let main([return_list '()][ret 0])
    (let boucle ([i 0])
      (if (equal? i (- (length factories) 1))
        (if (= (ressource-quantity (factory-Resproduced (node-peak (list-ref factories i)))) quantity)
          (set! ret (list-ref factories i))
          (when (< (sum-outputs return_list 0) quantity)
            (set! return_list (append return_list (list (list-ref factories i))))))
        (if (= (ressource-quantity (factory-Resproduced (node-peak (list-ref factories i)))) quantity)
          (set! ret (list-ref factories i))
          (if (< (sum-outputs return_list 0) quantity)
            (begin
              (set! return_list (append return_list (list (list-ref factories i))))
              (boucle (add1 i)))
            (boucle (- (length factories) 1))))))
    (if (equal? ret 0)
      return_list
      (list ret))))
;==========================================================================
;fonction qui retourne une liste de factories ayant la meme sortie
(define (factories-with-same-output g output)
  (if (null? output)
    (raise "given output was null")
      (let main([nodes (factories-with-no-outputs g)][factories '()]) ;factories will contain nodes
        (let boucle ([i 0])
          (if (equal? i (- (length nodes) 1))
            (when (equal? (ressource-type output) (ressource-type (factory-Resproduced (node-peak (list-ref nodes i)))))
              (set! factories (append factories (list (list-ref nodes i)))))
            (if (equal? (ressource-type output) (ressource-type (factory-Resproduced (node-peak (list-ref nodes i)))))
              (begin
                (set! factories (append factories (list (list-ref nodes i))))
                (boucle (add1 i)))
              (boucle (add1 i)))))
       factories)))
;===============================================================================
;fonction qui ajoute un noeud dans le graphe et deduit le cout de l'usine du total de gold ramassé
(define (buy-factory g factory gold)
  (if (not (null? (factory-Restaken factory)))
    (let boucle([i 0][resources (factory-Restaken factory)][node (node factory null null)])
      (begin
        (if (equal? i (- (length resources) 1))
          (append-descendant-to-parents g node (get-needed-factories-among
                                             (factories-with-same-output g (list-ref resources i))
                                             (ressource-quantity (list-ref resources i))))
          (begin
            (append-descendant-to-parents g node (get-needed-factories-among
                                               (factories-with-same-output g (list-ref resources i))
                                               (ressource-quantity (list-ref resources i))))
            (boucle (add1 i) resources node)))
         (- gold (factory-cost factory))))
    (begin
     (add-node g (node factory null null))
     (- gold (factory-cost factory)))))


;============================================================================================================
; acheter toutes les usines qui figurent dasn la liste factories 
(define (buy-all g factories gold)
  (if (not (null? factories))
    (let main([cpt gold])
      (let boucle([i 0])
        (if (equal? i (- (length factories) 1))
          (begin
            (when (>= cpt (factory-cost (list-ref factories i)))
              (begin
                (set! cpt (buy-factory g (list-ref factories i) cpt)))))
            ; )
          (if (>= cpt (factory-cost (list-ref factories i)))
            (begin
              (set! cpt (buy-factory g (list-ref factories i) cpt))
              (boucle (add1 i)))
            (boucle (add1 i)))))
        cpt)
     gold))

;===========================================================================================
; Mise à jour de la chaine de production et calcule le gold obtenu a la fin du tour
;a chaque fois qu'elle trouve une usine
(define (Browse-production-line g gold)
  (let main([nodes (factories-with-no-outputs g)][compte gold])
    (when (not (null? nodes))
      (let boucle([i 0])
        (if (equal? i (- (length nodes) 1))
          (when (equal? (ressource-type (factory-Resproduced (node-peak (list-ref nodes i)))) "Gold")
            (set! compte (+ compte (ressource-quantity (factory-Resproduced (node-peak (list-ref nodes i)))))))
          (if (equal? (ressource-type (factory-Resproduced (node-peak (list-ref nodes i)))) "Gold")
            (begin
              (set! compte (+ compte (ressource-quantity (factory-Resproduced (node-peak (list-ref nodes i))))))
              (boucle (add1 i)))
            (boucle (add1 i))))))
    compte))



(provide (all-defined-out))
