(read (hk, j j))
(setq L 'a)
(setq L (read))
lkjlkj
L
(princ '|jjfjhjfhdjhfd |)
(terpri)
(prin1 L)

{ de aci incepe programul }

(defun fct (L)
  (cond ((atom L) (princ '|( |) (print L) )
	((null L) (princ '|)|))
	(t (fct (car L))
	   (fct (cdr L)))))
(fct '(A b (C d e) f))
(fct '(a))
