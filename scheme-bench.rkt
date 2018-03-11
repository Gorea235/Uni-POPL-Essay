;#lang racket

(define (gen-list n)
  (if (= n 0)
      null
      (cons n (gen-list (- n 1)))
      )
  )

; immutable recursive implementation
(define (do-sum-im lst)
  (if (null? lst)
      0
      (+ (car lst) (do-sum-im (cdr lst)))
      )
  )

; mutable looping implementation
(define (do-sum-m lst)
  (let ((total 0))
    (do
        ((clst lst (cdr clst)))
      ((null? clst)
       total
       )
      (set! total (+ total (car clst)))
      )
    )
  )

; taken from https://github.com/stamourv/racket-benchmark/blob/master/benchmark/macro.rkt#L74-L79
; used to time function exectution
(define (time-delta thunk) 
  (let ([start (current-inexact-milliseconds)])
    (thunk)
    (let ([end (current-inexact-milliseconds)])
      (- end start))))

; runs the benchmark on the given function 'left' times
; returns the minimum execution time
(define (benchmark func times)
  (define (benchmark-internal func left)
    (if (> left 0)
        (min (time-delta func) (benchmark-internal func (- left 1)))
        +inf.0)
    )
  (let ((bnc (/ (benchmark-internal func times) 1000)))
    (begin
      (display "> ")
      (display times)
      (display " runs with a minimum time of ")
      (display bnc)
      (displayln " seconds")
      )
    )
  )

; performs all the benchmarks using the given list length
(define def-time-amount 1000)
(define (bench-main n)
  (let ((lst (gen-list n)))
    (begin
      (display "====== benching with list of ")
      (display n)
      (displayln " items ======")
      (displayln "---===--- benchmarking immutable ---===---")
      (benchmark (lambda () (do-sum-im lst)) def-time-amount)
      (displayln "---===--- benchmarking mutable ---===---")
      (benchmark (lambda () (do-sum-m lst)) def-time-amount)
      (newline)
      )
    )
  )

; entry point for benchmarks
(define (bench)
  (begin
    (bench-main 10000) ; 10,000 items
    (bench-main 100000) ; 100,000 items
    (bench-main 1000000) ; 1,000,000 items
    )
  )

(bench)
