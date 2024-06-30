(setq var '(first example))
`(this is an ,@var)
; parametri optionali
(defun punctuate (l &optional mark)
  (cond ((not mark) (append l '(period)))
	(t (append l (list mark)))))
; daca mark nu e definit, adauga la sfirsitul lui l '.'; altfel mark
; sau cu mark initializat, ca sa nu mai fie nevoie de cond
(defun punctuate (l &optional (mark 'period))
  (append l (list mark)))
; daca se doresc mai multi parametri (indiferent de numarul lor)
(defun punctuate (l &rest marks)
  (cond ((null marks) (append l '(period)))
	(t (append l marks))))
; macrouri - nu evalueaza argumentele
(defmacro demo (par)
  (print par))
(setq this 'value-of-this)
(demo this)
; afiseaza this/value-of-this
  