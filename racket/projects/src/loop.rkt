#lang racket
(require "parser.rkt")
(require "graph.rkt")
(require "viable.rkt")
(require "validity.rkt")
(require "min-gold.rkt")
(require "strategies.rkt")
(require racket/pretty)

;====================================== RECUPERATION DES ARGUMENTS DE COMMANDE =====================================================
(define arguments (current-command-line-arguments)) 
(define liste (vector->list arguments))
(define len (length liste))
;================================ DEFINITION DES VARIABLES GLOBALES ===========================================================

(define factories '())
(define initial-gold 0)
(define strategy "")
(define rounds 0)
(define CORRECT-NUMBER-OF-ARGUMENTS 4)
(define board (graph '()))


;============================== VERIFIER SI LES ARGUMENTS SONT CORRECTS =============================================================
(if (eq? len CORRECT-NUMBER-OF-ARGUMENTS)
  (begin
    (when (not (file-exists? (car liste)))
      (begin
        (display "Error : NO FILE FOUND \n")
        (exit)))
    (set! factories (cleaned-production-line (production-line (car liste))))
    (set! rounds (string->number (list-ref liste 3)))
    (when (<= rounds 0)
      (begin
        (display "ERROR : MUST GET  A POSITIVE NUMBER OF ROUNDS")
        (exit)))
    (set! initial-gold (string->number (list-ref liste 2)))
    (when (> (min-gold factories) initial-gold)
        (begin
          (display "\n not enough initial gold \n")
          (exit))))
  (begin
    (display "\n Usage : racket command.rkt <definition_file> <strategy_name> <initial_gold> <number_of_turns> \n")
    (exit)))

;========================== BOUCLE PRINCIPALE DU JEU ================================================================================

(define (loop gr gold factories strategy rounds)
  (let main([gained gold])
    (let boucle([cpt 1])
      (if (or (>= cpt rounds) (<= gained 0))
        (begin
          (display "\n Round : ")
          (print cpt )
          (display "\n")
          (set! gained (Browse-production-line gr (strategy gr gained factories)))
          (display (- gold  gained)))
         
        (begin
          (display "\n Round : ")
          (display cpt )
          (display "\n")
          (set! gained (Browse-production-line gr (strategy gr gained factories)))
          (display (- gold gained))
          (display "\n")
          (boucle (add1 cpt)))))
      (begin
        (display "\n initial gold : ")
        (display gold)
        (display "\n final gold ")
        (display gained)
        (display "\n"))))

(loop board initial-gold factories g1 rounds)
