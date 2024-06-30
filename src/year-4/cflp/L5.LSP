(defun parc (rad arb)
  (print rad)
  (ParcAux (car(cdr(assoc rad arb))) arb))

(defun ParcAux (L Arb)
  (cond ((null l))
         (t (parc (car l) arb)
            (ParcAux (cdr l) arb))))
(setq arb '((a(b c d))(c(e f))))
(parc 'a arb)
(continue 1)

(GET atom valoare)
(SETF (GET 'masa 'culoare) 'verde)
(REMPROP atom propr)

(setq vegetale '(mar para morcov cartofi))
(setf (get 'mar 'kindof) 'fruit)
(setf (get 'para 'kindof) 'fruit)

(defun FruitP(atom)
   (equal (get atom 'kindof) 'fruit))

(defun ListaFructe(l)
  (mapcar 'fruitp l))

(ListaFructe vegetale)

(lambda <=> defun-annonymous)
        #'
(MAPCAR '(LAMBDA (x)
          (equal (get x 'kindof) 'fruit))

(defun count (type l)
   (cond ((atom l) (cond((equal (get l 'kindof) type) 1)
                        (t 0)))
         (t (apply '+ (mapcar #'(lambda (e)
                                  (count type e))l)))))
(count 'fruit vegetale)
(continue 3)
(defun PresentP (a E)
  (cond ((atom e) (cond((equal a e) 1)
                       (t 0)))
        ((null(zerop(apply '+ (mapcar #'(lambda (x)
                                 (PresentP a x))
			      e)))))))
(PresentP 'mar vegetale) 


(defun subtspar (l lambda)
   ())

(substpar '(1 2) #'(lambda (x y)
                     (+ (*x y)(*x y))))


