#lang racket

;============================================================================
;Exercice 1
;============================================================================

;(cons '(A B C) '(1 2 3))
;(append '(A B C) '((1 2) 3))
;(last '((A 1) (B 2) (C 3)))
;(drop-right '((A 1) (B 2) (C 3)) 1) ;supprime 1 element a droite soit (C 3)
;(car '((A (B C)) D (E F)))
;(cdr '((A (B C)) D (E F)))
;(caddr'((A (B C)) D (E F)))
;(cons 'NOBODY (cons 'IS '(PERFECT)))
;(list (add1 2) (sub1 5) 6)
;(cdr '(a b))
;(cdr '(a . b))
;'(a . (b . (c . ())))
;'(a . (b . (c . d)))
;(assoc 'bleu '([rouge . red] [vert . green] [bleu . blue] [jaune . pink]))

;============================================================================
;Exercice 2
;============================================================================

;(cadddr '(A B C D))
;(car (cdadar '((A (B C)) E)))
;(caaar '(((FLUTE) ENCORE) UNE))
;(cadar '(((FLUTE) ENCORE) UNE))

;============================================================================
;Exercice 3
;============================================================================

(define list '(-1 -2 -3))

(define (inverse list)
  (cons ( caddr list) (cons (cadr list) (cons (car list) '()))))

;(inverse list)

(define (inverse-2 list)
  (cons (third list) (cons (second list) (cons (first list) '()))))

;(inverse-2 list)

;(append '(1 2) (car '((3 4))) (cons 5 '()))

;============================================================================
;Exercice 4
;============================================================================

(define (absolue list)
  (if (null? list)
      list
      (cons (abs (car list))(absolue (cdr list)))))
        
;(absolue list)

(define (absolue-term list1 list2)
  (if (null? list1)
      list2
      (absolue-term (cdr list1) (cons (abs (car list1))list2))))

;(absolue-term list '())

;============================================================================
;Exercice 5
;============================================================================

(define list1 '(a b c))
(define list2 '(b c))
(define list3 (cons 'a list2))

;(eqv? (cdr list1) list2)
;(eqv? (cdr list3) list2)
;(equal? (cdr list1) list2)
;eqv verifie que c'est la meme liste
;equal verifie que les elements de la liste sont egals

;============================================================================
;Exercice 6
;============================================================================

(define (insert x list)
(cond ((null? list)
       (list x))
      ((<= x (car list))
       (cons x list))
       (else
        (cons (car list)
              (insert x (cdr list))))))
  
;(insert 3 '(2 6 9))

(define (sort-number l)
  (define (aux l1 l2)
    (if (empty? l1)
        l2
        (aux (cdr l1) (insert (car l1) l2))))
  (aux l '()))

(sort-number '(3 2 9))
                    
