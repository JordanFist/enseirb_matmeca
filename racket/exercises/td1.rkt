#lang racket

;============================================================================
;Exercice 1
;============================================================================

;; Computes the factorial of the integer n
(define (factorial n)
  (if (<= n 1)
    1
    (* n (factorial (sub1 n)))))

;============================================================================
;Exercice 2
;============================================================================

;(factorial 5)

;(- 2 1)
;(+ (*) (+))
;(+) renvoie l'element neutre de l'operateur ie 0 soit (+ 1 0)

;(* (+ 2 5) (opérateur(* 3 4) (- 1 2)))
;(+ 12 (* 3 4))
;(+ 2 (* 5 (log 8)))
;(+ 1 2 3 4 5 6)
;(log -2)
;(define 3 (+ 2 1)) on ne peut pas appeler son programme 3

;============================================================================
;Exercice 3
;============================================================================

(define (square n)
  (* n n))

;(square 6)

(define (mean n m)
  (/ (+ n m) 2))

;(mean 2 4)

(define (eval-square a b c x)
  (+ (* a (square x)) (* b x) c))

;(eval-square 1 1 1 1)

;============================================================================
;Exercice 4
;============================================================================

(define (a)
  (sqrt (+ 1 (sqrt (+ 2 (sqrt 3))))))

(define (b)
  (*(+ 2 3)(+ 4 5 6)))

(define (c)
  (log (+ (square 99) 3)))

(define (d)
  (/ (+ (a) (b))(- (a) (b))))

(define (e)
  (- (/ (+ (a) (b))
        (+ (a) (* 2 (b))))
     (sqrt (/ (+ (a) (* 2 (b)))
                 (+ (a) (* 2 (b)))))))
  
;(a)
;(b)
;(c)
;(d)
;(e)

;============================================================================
;Exercice 5
;============================================================================

(define (discriminant a b c)
  (- (square b)(* 4 a c)))

;(discriminant 1 4 3)

(define (racine1 a b c)
  (/ (- (- b) (sqrt (discriminant a b c))) (* 2 a)))

(define (racine2 a b c)
 (/ (+ (- b) (sqrt (discriminant a b c))) (* 2 a)))

;(racine1 1 4 3)
;(racine2 1 4 3)

(define (carac-racines-trinome a b c)
  (cond [(> (discriminant a b c) 0) "two distinct real roots"]
        [(= (discriminant a b c) 0) "one real root of multiplicity 2"]
        [else "two complex conjugate roots"]))

(define (carac-racines-trinome2 a b c)
  (cond [(> (discriminant a b c) 0) "two distinct real roots"]
        [(= (discriminant a b c) 0) "one real root of multiplicity 2"]
        [else "two complex conjugate roots"]))

;(carac-racines-trinome 1 -2 1)

;============================================================================
;Exercice 6
;============================================================================
(define (puissance x n)
  (if (= n 0)
      1
      (* x (puissance x (- n 1)))))

(define (binaire n degre base)
  (if (= n 0)
      0
      (if (> (remainder n base) 0)
          (+ (* (remainder n base) ( puissance 10 degre)) (binaire (quotient n base) (+ 1 degre) base))
          (binaire (quotient n base) (+ 1 degre) base))))

  
(binaire 10 0 2)

