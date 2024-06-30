(Defun Oreverse (L)
  (cond ((null L) NIL)    
	(t (setq rez (cons (car L) rez))
	   (oreverse (cdr L))
	   )))

(defun add (nr1 nr2)
(setq rez NIL)
(oreverse nr1)
(setq nr1 rez)
(setq rez nil)
(oreverse nr2)
(setq nr2 rez)
(setq addrez nil)

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
    (cond ((> temp 9) (setq rest 1)
	   (setq temp (- temp 10)))
	  (t (setq rest 0)))
    (setq addrez (cons temp addrez))
    ))
(add '(1 2 3 4) '(9 2 9 9))

(mul (nr1 nr2)
(setq rez NIL)
(oreverse nr1)
(setq nr1 rez)
(setq rez nil)
(oreverse nr2)
(setq nr2 rez)
(setq mulrez NIL)
)







