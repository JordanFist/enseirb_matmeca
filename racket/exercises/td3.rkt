#lang racket
;============================================================================
;Exercice 1 
;============================================================================

(define (plus-rec a b)
  (if (zero? b)
      a
      (plus-rec (add1 a)(sub1 b))))

;(plus-rec 5 6)

(define (fois-rec a b r)
  (if (zero? b)
      r
      (fois-rec a (sub1 b) (+ a r))))

(define (produit a b)
  (fois-rec a b 0))

;(produit 5 6)

(define ( puissance a b r)
  (cond [(zero? b) r]
        [(zero? (remainder b 2)) (puissance (sqr a) (/ b 2) r)]
        [(= 1 (remainder b 2)) (puissance (sqr a) (/ (sub1 b) 2) (* r a))]))

;(puissance 2 5 1)

;============================================================================
;Exercice 2 
;============================================================================
(define (fibo n)
  (cond [(zero? n) 1]
        [(= 1 n) 1]
        [else (+ (fibo (sub1 n))(fibo (sub1 (sub1 n))))]))

;(time (fibo 32))
;on appelle plusieurs fois les memes valeurs

(define (fibo-rapide n)
  (letrec  ;imbrication de fonction => on ne demande que n on initialise a b
      ((fibo-gen (lambda (n a b)
                  (cond [(zero? n) a]
                        [(= n 1) b]
                        [(fibo-gen (sub1 n) b (+ a b))]))))
    (fibo-gen n 1 1)))

;(time (fibo-rapide 32))

;============================================================================
;Exercice 3
;============================================================================

;(let ([x 5]
;      [y (sqrt 9)]
;      [z (* 4 (+ 3 (sqrt 4)(sqrt 9)))])
;  (+ x y (* 5 z)))
;168

;(+ (let ([a 12]) (+ a a))
;   (let ([b 30]) (+ b
;                  (let ([b 20])
;                    (+ b b)))))
;94

(define x 12)
(define y 5)
(define q1 (let ([x y]
                 [y x])
             (- x y)))
;x=5 y=12 => 5 - 12= -7 taper q1 dans le shell

(define q2 (let* ([x y]
                  [y x])
             (- x y)))
;x=5 y=5 => 5 - 5 = 0

(define q3 (let ([x y]) ; x = 5, y = 5, on ferme le let
             (let ([y x]) ;y = 5 la nouvelle valeur de x
               (- x y))))

(define (racine a b c)
  (let ([d (- (sqr b) (* 4 a c))]
        [r1 (/ (- (sqrt d) b) (* 2 a))]
        [r2 (/ (- (+ (sqrt d) b) (* 2 a)))]
        (values r1 r2))))

;============================================================================
;Exercice 4
;============================================================================

(define (new-if predicate clause-then clause-else)
  (if (= predicate 1) (clause-then) (clause-else)))

(define a 0)
(new-if (zero? a) #t #f)
(new-if (zero? a)
        (print "a est nul")
        (print " a est non nul"))


