#lang racket
(require "parser.rkt")
(require racket/base)
;================================ EXPORTING FUNCTIONS ===========================================================
(provide index-of-ingredient increase-ressource decrease-ressource increase-ressource decrease-cost 
          apply-inputs apply-outputs)

;================================== THIS FILE CONTAINS UTIL UNITARY FUNCTIONS AND FUNCTIONS THAT ALLOW  TO MANIPULATE THE PRODUCTION-LINE ===============================


;=====================================================================================================================
; function that searches for the index of a ressource in a production line

(define (index-of-ingredient production-line ingredient)
  (let boucle ([i 0])
    (if (not (equal? i (- (length production-line) 1)))
      (if (not (equal? (ressource-type (list-ref production-line i)) (ressource-type ingredient)))
        (boucle (add1 i))
        i)
      (if (eq? (ressource-type (list-ref production-line i)) (ressource-type ingredient))
          i
          #f))))


;=====================================================================================================================
;function that increases the quantity of a ressource if it already exists in the line-production
;else it adds the ressource in the production line
(define (increase-ressource production-line ingredient)
  (if (eq? (index-of-ingredient production-line ingredient) #f)
    (append production-line (list ressource))
    (let* ([i (index-of-ingredient production-line ingredient)]
           [elem (list-ref production-line i)]
           [old-q (ressource-quantity elem)]
           [to-add (ressource-quantity ingredient)])
      (list-set production-line i (struct-copy ressource ingredient [quantity (+ to-add old-q)])))))

;=====================================================================================================================
;function that decreses the quantity of a ressource if it already exists in the production-line
;else it adds it to the production line
(define (decrease-ressource production-line ingredient)
  (if (equal? (index-of-ingredient production-line ingredient) #f)
    (append production-line (list (struct-copy ressource ingredient [quantity (- (ressource-quantity ingredient))])))
    (let* ([i (index-of-ingredient production-line ingredient)]
          [elem (list-ref production-line i)]
          [old-q (ressource-quantity elem)]
          [to-substract (* -1 (ressource-quantity ingredient))])
        (list-set ingredient i (struct-copy ressource ingredient [quantity (+ old-q to-substract)])))))

;======================================================================================================================

 
(define (decrease-cost production-line Factory)
  (decrease-ressource production-line (ressource "Gold" (factory-cost Factory))))


;=======================================================================================================================
;Function that applies the effects ,to a production line ,of a list of ingredients l 
(define (apply-inputs production-line l)
  (if (null? l)
    production-line
    (let ([begin (car l)]
          [rest(cdr l)])
          (apply-inputs (decrease-ressource production-line begin ) rest))))
;=======================================================================================================================
;Function that adds the outputs of a factory to a production line and substracts cost of factory

(define (apply-outputs production-line l)
  (if (null? l)
    production-line
    (let ([begin (car l)]
          [rest (cdr l )])
          (apply-outputs (increase-ressource production-line begin ) rest))))

;========================================================================================================================

