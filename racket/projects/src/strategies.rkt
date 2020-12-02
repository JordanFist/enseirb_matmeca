#lang racket
(require "validity.rkt")
(require "viable.rkt")

(provide g1 g2)
;===================================STRATEGIE1 ================================
;acheter une usine à chaque tour
(define (g1 g gold init-factories)
  (begin
    (buy-all g (get-buyable-factories (get-suppliable-factories g init-factories) gold) gold)))

;==========================Stratégie 2 ==============================================
;acheter autant d'usines que possible à chaque tour
(define (g2 g gold init-factories)
  (let main([m gold])
    (let loop([i 0])
      (when (not (null? (get-buyable-factories (get-suppliable-factories g init-factories) m)))
        (begin
         (set! m (buy-all g (get-buyable-factories (get-suppliable-factories g init-factories) m) m))
         (loop (add1 i)))))
    m))