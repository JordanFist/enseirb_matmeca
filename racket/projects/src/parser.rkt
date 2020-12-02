#lang racket
;================================== EXPORTING FUNCTIONS ============================================================
(provide gold? is-comment? extract-res valid-input? create-struct-factory extract-input extract-output extract-factory
         treat-line production-line cleaned-production-line final-production-line)


;================================ FUNCTIONS THAT WILL PARSE A GIVEN FILE =============================================

;===================================== DEFINITION OF STRUCTURES ================================================================

;representing a ressource
(struct ressource (type [quantity #:mutable]) #:transparent)
;representing a factory
(struct factory (Restaken Resproduced [cost #:mutable] [number-owned #:mutable] ) #:transparent); Restaken is a list of struct ressource
;representing one node of the graph of the production line
(struct node ([peak #:mutable] [descendant #:mutable] [parents #:mutable]) #:transparent) ; the type of peak is struct factory 
;representing the entire production line : a set of nodes and count is the number of nodes 
(struct graph ([nodes #:mutable] [count #:mutable]) #:transparent)
;=================================== EXPORTING STRUCTURES =================================================
(provide ressource ressource-type ressource-quantity)
(provide factory factory-Restaken factory-Resproduced factory-cost factory-number-owned)

;=====================================================================================================================
;function that verifies if a line begins with a "#"
(define (is-comment? char)
  (if (string-prefix? char "#")
      #t
      #f))
;=====================================================================================================================
;function that verifies whether a  given input is Gold or not :
;NB : there's no factory that should have GOLD as input : Gold should be produced and not consumed 

(define (gold? input)
  (when (not (equal? "[]" input))
    (let ([aux (string-split (car (string-split (car (string-split (car (string-split input ",")) "[")) "]")) "=")])
      (if (equal? (car aux) "Gold")
        #f
        #t))))
;=====================================================================================================================
;Function that extracts a ressources from  a given string
(define (extract-res ress)
  (begin
    (let* ([aux (string-split ress "=")]
           [type (substring (car aux) 1)]
           [quantity (string->number (substring (last aux) 0 (sub1 (string-length (last aux)))))])
      (ressource type quantity))))

;=====================================================================================================================
;Function that verifies if a factory takes inputs and if there are few or many inputs
;
(define (valid-input? chaine)
  (begin
    (let* ([aux (string-split chaine ",")])
      (if (< (length aux) 2)
          #t
          #f))))

;======================================================================================================================
;function that makes a struct factory from 4 given datas
(define (create-struct-factory input output cost number)
  (factory input output cost number))

;======================================================================================================================
;function that extracts  an intput ressource given a string; returns a list of struct ressource
(define (extract-input input)
  (if (not (equal? "[]" input))
    (let core ([input '()][all-inputs (string-split input ",")])
      (let boucle([i 0])
        (if (equal? i (- (length all-inputs) 1))
            (set! input (append input (list (ressource (car (string-split (car (string-split (car (string-split (list-ref all-inputs i) "]")) "=")) "["))
                                                                               (string->number (car (cdr (string-split (car (string-split (list-ref all-inputs i) "]")) "="))))))))
          (begin
            (set! input(append input (list (ressource (car (string-split (car (string-split (car (string-split (list-ref all-inputs i) "[")) "=")) "]"))
                                                                               (string->number (car (cdr (string-split (car (string-split (list-ref all-inputs i) "]")) "="))))))))
            (boucle (add1 i)))))
      input)
     '()))

;=======================================================================================================================
;function that extracts an output given a string 
(define (extract-output output)
  (when (not (equal? output "[]"))
    (let ([var (string-split (car (string-split (car (string-split (car (string-split output ",")) "[")) "]")) "=")])
      (ressource (car var) (string->number (car (cdr var)))))))

;=========================================================================================

;function that parses the entire file 
(define (production-line file)
    (map treat-line (file->lines file)))

;===========================================================================
;function that creates a struct factory starting from a string (a line from a parser)
(define (extract-factory line)
  (begin
    (let* ([aux line]
           [input (extract-input (car aux))]
           [output (extract-output (caddr aux))]
           [cout (string->number (last aux))])
      (create-struct-factory input output cout 0))))

;=============================================================================
;function that parses a line of a file
(define (treat-line line)
  (begin
    (string-normalize-spaces line)
    (when (not (is-comment? line))
      (when  (and (gold? (car (string-split line))) (valid-input? (caddr (string-split line))))  
        (extract-factory (string-split (string-normalize-spaces line)))))))



;=============================================================================
;function that removes the empty lines from what returned from the function production-line
(define (cleaned-production-line production-line)
  (cond
    [(null? production-line) production-line]
    [(not (void? (car production-line))) (cons (car production-line) (cleaned-production-line (cdr production-line)))]
    [(void? (car production-line)) (cleaned-production-line (cdr production-line))]))



;========================================================================================
;function that returns the final cleaned production-line
(define (final-production-line file)
    (cleaned-production-line (production-line file)))


