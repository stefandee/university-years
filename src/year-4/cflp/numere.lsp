;proiect la CFLP - operatii aritmetice cu numere lungi

;adunarea
(defun add (nr1 nr2)

(setq nr1 (reverse nr1))
(setq nr2 (reverse nr2))
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

;functie auxiliara pentru inmultire
(defun digimul (digit nr)
(setq pass '0)
(setq digirez NIL)
(do ()
    ((null nr) digirez)
    ; chinuiala - nu e optimizata !!!
    (setq temp (* (car nr) digit))
    (setq temp (+ temp pass))
    (setq rest (mod temp 10))
    (setq digirez (append digirez rest))
    (setq pass (/ (- temp rest) 10))
    (setq nr (cdr nr))
)
(cond ((not (equal '(0) pass)) (setq digirez (append digirez pass))) 
      (t digirez)
))

;INMULTIREA
(defun mul (nr1 nr2)

(setq nr1 (reverse nr1))
(setq nr2 (reverse nr2))

(setq mulrez NIL)
(setq digirez NIL)

(do ((zeros NIL))
    ((null nr2) mulrez)
    
    (setq digirez (digimul (list(car nr2)) nr1))
    (setq digirez (reverse digirez))
    (setq digirez (append digirez zeros))
    (setq mulrez (reverse mulrez))
    
    (setq mulrez (add digirez mulrez))
   
    (setq mulrez (reverse mulrez))
    (setq zeros (append zeros '(0)))
    (setq nr2 (cdr nr2)))
(setq mulrez (reverse mulrez)) 
)

(defun maimare(nr1 nr2)
  (cond ((> (car nr1) (car nr2)) t)
	((< (car nr1) (car nr2)) NIL)
	(t (maimare (cdr nr1) (cdr nr2)))
  )
)

(defun firstzero (nr1)
  (cond ((= (car nr1) 0) (firstzero (cdr nr1)))
	(t (setq nr1 nr1))))

(defun subsbr (nr1 nr2 sign)
  (setq subrez NIL)
  (setq nr1 (reverse nr1))
  (setq nr2 (reverse nr2))
  (do ((borrow '0))
      ((null nr1) subrez)
      (setq temp '0)
      (cond ((null nr1) nil)
	    (t (setq temp (+ temp (car nr1)))
	       (setq nr1 (cdr nr1))))
      (cond ((null nr2) nil)
	    (t (setq temp (- temp (car nr2)))
	       (setq nr2 (cdr nr2))))
      (setq temp (- temp borrow))
      (cond ((> 0 temp) (setq temp (+ temp 10))
	     (setq borrow 1))
	    (t (setq borrow 0)))
      (setq subrez (cons temp subrez))
  )
  (setq subrez (cons sign (firstzero subrez)))
)

(defun sub (nr1 nr2)
  (cond ((> (length nr2) (length nr1)) (subsbr nr2 nr1 '-))
	((< (length nr2) (length nr1)) (subsbr nr1 nr2 '+))
	((= (length nr2) (length nr1)) 
	 (cond ((equal nr1 nr2) '(0)) 
	       ((maimare nr2 nr1) (subsbr nr2 nr1 '-))
	       (t (subsbr nr1 nr2 '+))))))
(sub '(5 9 9) '(6 0 2))
(add '(8 8 9) '(1 1 1))








