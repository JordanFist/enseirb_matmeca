#lang racket
(require "parser.rkt")
(provide min min-gold)

; fonction qui determine le minimum d'une liste
(define (min l initial-min)
  (cond
    [(null? l) initial-min]
    [(>= initial-min (car l)) (min (cdr l) (car l))]
    [else (min (cdr l) initial-min)]))


; fonction qui determine le minimum de gold necessaire pour produire une usine qui ne prend rien en entrée
(define (min-gold production-line)
  (let* ([possible-to-buy (cleaned-production-line (map (lambda (x) (when (null? (factory-Restaken x)) (factory-cost x))) production-line))])
        (if (null? possible-to-buy)
          (begin
            (display "\n")
            (exit))
          (min possible-to-buy (car possible-to-buy)))))