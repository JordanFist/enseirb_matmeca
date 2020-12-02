#lang typed/racket

;============================================================================
;Exercice 1
;============================================================================
;type -> Null
;la valeur -> null

;exemple :
;(struct document (author title))
;(define livre (document "toto" "foo"))
;(document-author livre)->"toto"

(define-type My-list (U Null My-cons))

(struct: My-cons
  ([my-car : Number]
   [my-cdr : My-list]))

;(My-cons 1 (My-cons 2 (My-cons 3 null)))

;printl prend My-list et return Void
(: printl(My-list -> Void))
(define (printl l)
  (match l
    ['() (void)]
    [(My-cons a b)(print a)
                  (display #\ )
                  (printl b)]))

;(printl (My-cons 1 (My-cons 2 (My-cons 3 null))))

(: carl (My-list -> Number))
(define (carl l)
  (match l
    ['() (raise "error carl: empty list")]
    [(My-cons a b) a]))

;(carl (My-cons 1 (My-cons 2 (My-cons 3 null))))

(: iota-gen-rec (Number Number My-list -> My-list))
(define (iota-gen-rec a b res)
  (cond [(equal? a (add1 b)) res]
       [else (iota-gen-rec a (sub1 b) (My-cons b res))]))

;(printl (iota-gen-rec 0 10 '()))

(: iota-gen (Number Number -> My-list))
(define (iota-gen a b)
  (iota-gen-rec a b '()))

;============================================================================
;Exercice 2
;============================================================================

(define-type (My-list2 a) (U Null (My-cons2 a)))
(struct: (a) My-cons2 ([my-car : a][my-cdr : (My-list2 a)]))

(: carl2 (All(a) ((My-list2 a) -> a)))
(define (carl2 l)
  (match l
    ['() (raise "error carl2: empty list")]
    [(My-cons a b) a]))

;meme fonction pour printl
               




