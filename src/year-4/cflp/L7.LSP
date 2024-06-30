(setq space  '| |)
(setq leftp  '|(|)
(setq rightp '|)|)

(defun print-spaces (n)
  (do ((n n (- n 1)))
      ((= n 0))
      (princ space)))


(defun pretty-printy (l n)
 ((princ leftp)  
  (do (l l (cadr l))
      ((null l))
      (cond ((atom (car l)) (prin1 (car l)))
            (t (pretty-print(cadr l))))))
 (princ rightp))
)

(defun pretty-print (l)
  (pretty-printy l 0))


(pretty-print '(bunic (tata1 fiu11 fiu12) (tata2 fiu21 (fiu22 nepotel))))
