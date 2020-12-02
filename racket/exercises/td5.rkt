#lang racket
;============================================================================
;Exercice 1
;=============================================================================

(define (is-list? l)
  (or (null? list) (and (pair? l) (is-list? (cdr l)))))

(define (dotless-list? l)
  (or (null?)
      (and (pair? l)
           (or (dotless-list? (car l)) (not (pair? (car l))))
           (dotless-list? (cdr l)))))

;============================================================================
;Exercice 2
;=============================================================================

(define (iota-bis n)
  (if (< n 0)
      '()
      (cons n (iota-bis (sub1 n)))))

(define (iota n)
  (reverse (iota-bis n)))

;Ne pas faire de append sinon complexite quadratique

;(iota 5)

(define (scalar-product l1 l2)
  (apply + (map * l1 l2)))

;(scalar-product '(1 2 3) '(1 1 1))

(define (divisors n)
  (letrec ((div-parcours
            (lambda (i n div-list)
              (cond
                [(zero? i) div-list]
                [(integer? (/ n i) (div-parcours (sub1 i) n (cons i div-list)))]
                [else (div-parcours (sub1 i) n div-list)]
                ))))
  (div-parcours n n '())))

;============================================================================
;Exercice 3
;=============================================================================

(define list2 '((1) (2 3) 4))

(define (list-flatten l)
  (cond ((null? l) '())
        ((pair? l) (append (list-flatten (car l)) (list-flatten (cdr l))))
        (else (list l))))

;(list-flatten list2)
