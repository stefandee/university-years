(defun init ()
(setq nr1 '(5))
(setq nr2 '(5))
(setq rez NIL)
(defun oreverse (L)
  (cond ((null L) NIL)    
	(t (setq rez (cons (car L) rez))
	   (oreverse (cdr L))
	   )))
(oreverse nr1)
(setq nr1 rez)
(setq rez nil)
(oreverse nr2)
(setq nr2 rez)
; functia DO
; do ((<param1> <init value 1> <update for 1>)
;     (<param2> <init value 2> <update for 2>)
;     ...
;     (<paramn> ...                          ))
;     (<term test> <zero or more intermediate forms> <result form>)
;      <body>)
; si cond
; acum fac un test - parcurg cele 2 liste
(setq addrez nil))

(do ((addrez NIL)
     (rest '0)
     (temp '0))
    ((and (null nr1) (null nr2) (= 0 rest)) addrez)
    ; aici se face adunarea
    (setq temp '0)
    (cond ((null nr1) nil)
	  (t (setq temp (+ temp (car nr1)))
	     (setq nr1 (cdr nr1))))
    (cond ((null nr2) nil)
	  (t (setq temp (+ temp (car nr2)))
	     (setq nr2 (cdr nr2))))
    (setq temp (+ temp rest))
    (cond ((> temp 9) (setq rest (- temp 9))
	   (setq temp (- temp 10)))
	  (t (setq rest 0)))
    (setq addrez (cons temp addrez))
    (print addrez)
    )
(init)
(print addrez)






