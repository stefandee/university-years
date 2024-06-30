
(defun fact (n)
  (cond ((zerop n) 1)
	(t (* n (fact (- n 1))))))
(fact 69)

(defun fib (n)
   (cond ((= n 0) 1)
	 ((= n 1) 1) 
	 (t (+ (fib (- n 1))
	       (fib (- n 2))
))))
(fib 5)

(defun uselessadd (m n)
  (cond ((= n 0) m) 
	(t (uselessadd (+ m 1) (- n 1)))))
(uselessadd (- 3) 5)

(defun cnt (l)
  (cond ((null l) 0)
	((atom l) 1)
	(t (+ (cnt (car l))
	      (cnt (cdr l))))))
(cnt '(a b c (a d c)))

(defun fact (n)
(do ((c n (- c 1))
     (rez 1 (* rez c)))
     ((= c 0) rez)))
(fact 3)

(defun PresentP (wh L)
  (cond ((null L) nil)
	((atom L) (equal L wh))
	((equal wh (car L)) wh)
	(t (or (PresentP wh (car L))
	   (PresentP wh (cdr L))))))
(PresentP 'f '(e (b (a d))))

(defun Depth (L)
  (cond ((null L) 1)
	((atom L) 0)
	(t (+ 1 (apply 'max (mapcar 'Depth L))))))
(depth '(a (b c (d f))))

(defun OurUnion (L1 L2)
  (







