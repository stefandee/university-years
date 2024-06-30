(defun presentp ( a L )
  (cond ((atom L)
	 (cond ((equal a L) 
		1)
	       (t 0)))
	(t (mapcar #'(lambda (L) 
		       (presentp a L))
		   L))))
(presentp 'a '(b (c d f)))

(defun subst (L1 L2)
  (cond (atom L1)

(subst '(1 2) '(lambda (X Y) (+ X Y)))
(+ 1 2) 



