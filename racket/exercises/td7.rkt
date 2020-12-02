#lang racket

;=============================================================================
;Exercice 1
;=============================================================================

(define (f x)
  (* 2 x x))

(define (derivee f h)
  (lambda(x) (/ (- (f (+ x h))(f (- x h)))(* 2 h))))

;((derivee f 0.00001) 1)

(define (derivee-nieme f h n)
  (if (zero? n)
      f
      (derivee-nieme (derivee f h) h (sub1 n))))

;((derivee-nieme f 0.00001 1) 1)

(define (derivee2 f h)
  (lambda(x) (/ (- (+ (f (+ x h)) (f (- x h))) (* 2 (f x)))(* h h))))

;((derivee2 f 0.00001) 1)

;=============================================================================
;Exercice 2
;=============================================================================

;((lambda (x y) (+ (* 2 x) y)) 2 3)

;(filter positive? '(0 1 0 2 0 3 0 0 0))

;(filter (lambda (x) (= x 3)) '(0 1 2 3 0 1 2 3))

;(map (lambda (x) (* 2 x)) '(1 2 3))

;=============================================================================
;Exercice 3
;=============================================================================

(define (list-abs-map list)
  (map abs list))

;(list-abs-map '(1 -2 -3))

(define (square x)
  (* x x))

(define (list-squares list)
  (map square list))

;(list-squares '(1 -2 3))

;=============================================================================
;Exercice 4
;=============================================================================

(define (how-many pred list)
  (apply +(map (lambda(x) (if (equal? #t x)
                              1
                              0))
               (map pred list))))

;(how-many even? '(1 2 3 4 6))
;(how-many number? '(1 * b 4))

;=============================================================================
;Exercice 5
;=============================================================================

(define (scalar-product u v)
  (apply + (map * u v)))

;(scalar-product '(1 2 3) '(1 1 1))

(define matrix
  '((1 2 3)
    (1 2 3)
    (1 2 3)))

(define (mat-vect x M)
  (map (lambda(list) (scalar-product x list)) M))

;(mat-rec '(1 1 1) matrix)

(define (transpose M)
  (apply map list M))

;(transpose matrix)

(define (mat-mat M N)
  (transpose (map (lambda (c) (mat-vect M c)) (transpose N))))

;(mat-mat matrix matrix)

;=============================================================================
;Exercice 6
;=============================================================================

;(define (map-and-sum f list)
;  (apply + (map (lambda(x) (f x)) list)))

(define (map-and-sum f l)
  (letrec
      ((map-and-sum-r (lambda (f l s)
                        (if (null? l)
                            s
                            (map-and-sum-r f (cdr l) (+ (f (car l)) s))))))
    (map-and-sum-r f l 0)))

;(map-and-sum f '(1 2 3))

;(define (map-and-prod f list)
;  (apply * (map (lambda(x) (f x)) list)))

(define (map-and-prod f l)
  (letrec
      ((map-and-prod-r (lambda (f l s)
                        (if (null? l)
                            s
                            (map-and-prod-r f (cdr l) (* (f (car l)) s))))))
    (map-and-prod-r f l 1)))

;(map-and-prod f '(1 2 3))

(define (g x y)
  (+ x y))

(define (iter-from-right g l b)
  (if (null? l)
      b
      (g (car l) (iter-from-right g (cdr l) b))))

;(iter-from-right g '(1 2 3) 0)

(define (iter-from-left g l b)
  ( if (null? l)
       b
       (iter-from-left g (cdr l) (g (car l) b))))

;(iter-from-left g '(1 2 3) 0)

(define (my-append l x)
  (iter-from-right cons l x))

;(my-append '(1 2 3) 4)
;(my-append '(1 2 3) '(1 2))

(define (my-map f l)
  (iter-from-right (lambda (e b) (cons (f e) b)) l '()))

;(my-map f '(1 2 3))

(define (prod-iterate f l)
  (iter-from-right (lambda (e b)(* (f e) b)) l 1))

;(prod-iterate sqrt '(4 9 25))

(define (my-reverse l)
  (iter-from-left cons l '()))

;(my-reverse '(1 2 3))

;iter-from-right = foldr
;iter-from-left = foldl

;=============================================================================
;Exercice 7
;=============================================================================

(define (append-map f l)
  (apply append (map f l)))

;(append-map (lambda(x) (list x (* x x))) '(1 2 3 4))

;(define (map-select f l pred)
;  (map (lambda(x) (if (pred x)
;                      (f x)
;                      x))
;       l))

(define (map-select f l pred)
  (append-map (lambda(x) (if (pred x)
                             (list (f x))
                             '()))
              l))

;(map-select (lambda(x) (/ 1 x))
;            '(1 a 10 0 4)
;            (lambda(x) (and (number? x)(not (zero? x)))))

(define (remove-if pred l)
  (map-select identity l (lambda(x) (not (pred x)))))

;(remove-if even? '(1 2 3 4))



