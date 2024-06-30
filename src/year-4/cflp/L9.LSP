(setq vlista '((a b c)(d e f )(g h i ) (j k l)))

(defun in-stuff (matrice lista )
 (do ((i 0 (+ i 1))
      (ilista lista (cdr ilista)))
     ((= i (array-dimension matrice 0)) matrice)
     (do ((j 0 (+ j 1))
	  (jlista (car ilista) (cdr jlista)))
         ((= j (array-dimension matrice 1)))
         (setf (aref matrice i j) (car jlista)))))

(defun stuff-array (l)
 (in-stuff (make-array (list (length l) (length(car l)))) l))

(stuff-array vlista)
(continue 1)

(defun print-array (matrice)
 (do ((i 0)
      (j 0 (+ j 1)))
     ((= i (array-dimension matrice 0)) matrice)
     (cond ((< j (array-dimension matrice 1))
                       (princ (aref matrice i j))
		       (princ '_))
	   (t (print '_)
	      (setq i (+ i 1))
	      (setq j (- 1))))))

(print-array (stuff-array vlista))
       
      







(setq l '(1 3 5 -1 6 7 -10))
(max l)
(min '1 '2 '3 l)
(remove 5 l)
remove
(defun dec (x)
       (list (- x 1)))
(mapcan   'dec '(1 2 3 4))
