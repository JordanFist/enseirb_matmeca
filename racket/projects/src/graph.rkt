#lang racket
(require racket/base)
(require rnrs/mutable-pairs-6)


;================================   EXPORTING FUNCTIONS     ==================================================


(provide add-node factories-with-no-inputs factories-with-no-outputs add-descendant append-descendant-to-parents )

;================================= DEFINITION OF THE GRAPH ===============================================================
(struct node ([peak #:mutable] [descendant #:mutable] [parents #:mutable]) #:transparent) ; the type of peak is struct factory 
;representing the entire production line 
(struct graph ([nodes #:mutable]) #:transparent)

(provide node node-peak node-descendant node-parents)
(provide graph graph-nodes)
;===================== THIS FILE CONTAINS FUNCTION THAT ALLOW TO MANIPULATE A GRAPH =========================================
;============================================================================================================================
;Function that returns the list of factories that have no inputs
;That is to say : we search for nodes which do not have a parent

(define (factories-with-no-inputs g)
  (if (null? (graph-nodes g))
    '()
    (let main ([nodes (graph-nodes g)][i 0][no-parents '()])
      (if (not (equal? i (- (length nodes) 1)))
        (if (null? (node-parents (list-ref nodes i)))
          (main nodes (add1 i) (append no-parents (list (list-ref nodes i))))
          (main nodes (add1 i) no-parents))
        (if (null? (node-parents (list-ref nodes i)))
          (append no-parents (list (list-ref nodes i)))
          no-parents)))))

;============================================================================================================================
;Function that returns the list of nodes which do not produce something. This function will be utile in the main file to
;verify that the production-line is-valid


(define (factories-with-no-outputs g)
  (if (not (null? (graph-nodes g)))
    (let main ([no-outputs '()][nodes (graph-nodes g)])
      (let loop([i 0])
        (if (equal? i (- (length nodes) 1))
          (when (null? (node-descendant (list-ref nodes i)))
            (set! no-outputs (append no-outputs (list (list-ref nodes i)))))
          (if (null? (node-descendant (list-ref nodes i)))
            (begin
              (set! no-outputs (append no-outputs (list (list-ref nodes i))))
              (loop (add1 i)))
            (loop (add1 i)))))
      no-outputs)
      '()))

;=========================================================================================================
;function that adds a factory to graph
(define (add-node g node)
  (begin
    (set! g (append (graph-nodes g) (list node)))))
;=========================================================================================================
;function that links a node to it's parent
(define (add-descendant graph N des)
  (if (or (null? node) (null? des))
    (raise "ERROR : YOU ARE TRYING TO APPENDS A NON EXISTING NODE ")
    (begin
      (when (null? (node-parents des))
        (set! graph (append (graph-nodes graph) (list des)))) 
      (set-node-descendant! N des) 
      (set! des (append (node-parents des) (list node))))))

;===========================================================================================================
; function that append a node to a list of parents
(define (append-descendant-to-parents g descendant parents)
  (if (or (null? parents) (null? descendant))
      (raise "THERE IS AN ERROR : YOU HAVE TO APPEND SOMETHING WHICH ISN'T VOID !")
      (begin
        (set! g (append (graph-nodes graph) (list descendant))) 
        (set! descendant (append (node-parents descendant) parents))
        (let loop ([i 0])
          (if (equal? i (- (length parents) 1))
              (set-node-descendant!  (list-ref parents i)  descendant)
              (loop (add1 i)))))))

