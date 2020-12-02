#lang racket
;============================================================================
;Exercice 1
;============================================================================

(define (f x)
  (+ (* 3 x x) 4.7))

(define (g x)
  (* 2 x))

(define (fonction1 f)
  (f 1))

;(fonction1 f)

(define (xfonction x)
  (lambda(y) (* x y)))

;(fonction1 (xfonction 2))

;============================================================================
;Exercice 2
;============================================================================

(define (compo f g)
  (lambda(x) (f (g x))))

;(fonction1 (compo f g))

;============================================================================
;Exercice 4 et 5
;============================================================================

(define (h x)
  x)

(define (sigma f n p)
  (cond ((> n p) 0)
        (else (+ (f p) (sigma f n (sub1 p))))))

;(sigma h 1 10)

; On peut aussi faire un lettrec avec une fonction res en parametre pour que ce soit recusif terminal

(define (sigma2 f n p op)
  (letrec ((sigma-rec
            (lambda (n res)
              (cond [(> n p) res]
                    [else (sigma-rec (add1 n) (op res(f n)))]))))
    (sigma-rec n (op))))

;(op) renvoie l'element neutre de l'operateur

;(sigma2 h 1 4 *)

;============================================================================
;Exercice 6
;============================================================================

(define (test-arret? an x epsilon)
  (< (abs (- (* an an) x)) epsilon))

(define (suivant an x)
  (* 0.5 (+ an (/ x an))))

(define (racine-carre x)
  (letrec ((racine-rec
            (lambda (start x eps)
              (if (test-arret? start x eps)
                  start
                  (racine-rec (suivant start x) x eps)))))
    (racine-rec 1 x 0.00001)))

(define (test-arret2? an x eps)
  (< (abs (- (* an an an) x)) eps))

(define (suivant2 an x)
  (/ (+ (* 2 an)(/ x (sqr an)) 3)))

(define (fixpoint x test-arret? suivant)
  (letrec ((fixpoint-rec
            (lambda (start eps)
              (if (test-arret? start eps)
                  start
                  (fixpoint-rec(suivant start) eps)))))
    (fixpoint-rec 1 0.00001)))




    
;(racine-carre 2)

 

;============================================================================
;Exercice 7
;============================================================================

