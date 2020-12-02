#lang racket
(require racket/trace)
;============================================================================
;Exercice 1
;============================================================================

;1.
;fact(0) = 1
;fact(n) = n * fact(n - 1)

;2.
;C(n) = 1 + C(n - 1)

;============================================================================
;Exercice 2
;============================================================================

;1.
;sum(x + 1, y) + x = sum(x, y)
;sum(y, y) = y

;2.
(define (somme-inter a b)
  (if (= a b)
      b
      (+ a (somme-inter (add1 a) b))))

;(somme-inter 1 5)

;3.
(define (somme-carres a b)
  (if (= a b)
      (sqr b)
      (+ (sqr a) (somme-carres (add1 a) b))))

;(somme-carres 1 5)

;============================================================================
;Exercice 3
;============================================================================

(define (pgcd a b)
  (if (zero? b)
      a
      (pgcd b (modulo a b))))

;(pgcd 15 5)

;============================================================================
;Exercice 4
;============================================================================

(define (puissance x n)
  (if (zero? n)
      1
      (* x (puissance x (sub1 n)))))

;(puissance 2 3)

(define (puissance-log x n)
  (cond [(zero? n) 1]
        [(even? n) (sqr (puissance-log x (/ n 2)))] ;(even? n) n est-il pair ?
        [else (* x (puissance-log x (sub1 n)))]))

;(puissance-log 5 2)

;============================================================================
;Exercice 5
;============================================================================

(define (pair n)
  (if (zero? n)
      #t
      (impair (sub1 n))))

(define (impair n)
  (if (zero? n)
      #f
      (pair (sub1 n))))

;(impair 4)
;(pair 4)

(define (pair-2 n)
  (or (zero? n) (impair (sub1 n))))

(define (impair-2 n)
  (and (not (zero? n)) (pair-2 (sub1 n))))

;(pair-2 4)
;(impair-2 4)

;============================================================================
;Exercice 6
;============================================================================

;(trace pair)
;(trace impair)
;(pair 10)
;(trace pgcd)
;(pgcd 5 3)

;============================================================================
;Exercice 7
;============================================================================

(define (plus a b)
  (if (zero? b)
      a
      (plus (add1 a) (sub1 b))))

;(plus 5 6)

(define (produit a b)
  (cond [(zero? b) 0]
        [(= b 1) a]
        [else (+ a (produit a (sub1 b)))]))

;(produit 7 6)

;============================================================================
;Exercice 8
;============================================================================

(define (syracuse n)
  (cond [(= n 1) 0]
        [(= #t (pair n)) (+ 1 (syracuse (/ n 2)))]
        [(= #t (impair n)) (+ 1 (syracuse (+ 1 (* 3 n))))]))

;(syracuse 7)

;============================================================================
;Exercice 9
;============================================================================

(define (palindrome mot)
  (for ([i (in-range (string-length mot))]
        [j mot])
    (display j)))

(palindrome "poule")
