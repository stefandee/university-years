(setq a '(1 2 3 4 5))
(setq b '(3 2 5 1 4))

(defun reuniune (A B)
  (cond ((null A) B)
        ((member (car a) b) (reuniune  (cdr a) b))
        (t (reuniune (cdr a) (cons (car a) b)))))
(reuniune a b)

(defun intersectie (A B)
  (cond ((null a) nil)
        ((member (car a) b)
                        (cons (car a) (intersectie (cdr a) b)))
        (t (intersectie (cdr a) b))))
(intersectie a b)

(defun diferenta (A B)
  (cond ((null a) nil)
        ((member (car a) b)
                 (diferenta (cdr a) b))
        (t (cons (car a) (diferenta (cdr a) b)))))
(diferenta a b))
(defun egalitate (A B)
  (cond ((and 
            (null (diferenta A B))
            (null (diferenta B A)))
                      t)
        (t nil)))
(egalitate a b)

(defun l2nand (l)
   
 )


