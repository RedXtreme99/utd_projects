#lang racket
(provide (all-defined-out))

;recursively apply the function to the first element of the list and then the rest of the list until the list is null
(define my-map
  (lambda (func lst)
    (if (null? lst)
      null
      (cons (func (car lst)) (my-map func (cdr lst))))))

;recursively check that as long as neither list is empty, take their first elements and make a list out of the pairs
;and call the function with the rest of their lists building the answer list
(define pair-up
  (lambda (lst1 lst2)
    (if (or (null? lst1) (null? lst2))
        null
        (cons (list (car lst1) (car lst2)) (pair-up (cdr lst1) (cdr lst2))))))

;classify defines two helper functions, that apply the boolean test and produce lists for when the boolean test is true or false
;classify itself only calls these two helper functions with the list and the boolean test
;each helper function recursively traverses the list in order and only adds an element to its final list when it is supposed to,
;so the apply function builds a list of true elements and the negate function returns the false elements
(define classify
  (lambda (bt lst)
    (define bool-apply-h
      (lambda (bt lst)
        (if (null? lst)
            null
            (if (bt (car lst))
                (cons (car lst) (bool-apply-h bt (cdr lst)))
                (bool-apply-h bt (cdr lst))))))
    (define bool-negate-h
      (lambda (bt lst)
        (if (null? lst)
            null
            (if (not (bt (car lst)))
                (cons (car lst) (bool-negate-h bt (cdr lst)))
                (bool-negate-h bt (cdr lst))))))
    (list (bool-apply-h bt lst) (bool-negate-h bt lst))))

;implements selection sort by first defining a helper function that finds the "smallest" element in the list according to our comparator.
;It does this by using foldl to apply a conditional check onto an entire list, finding the element that needs to be placed next in the list.
;my-sort then checks if the list is empty, and if so returns the empty list. If the list has length 1, it is already sorted.
;Then recursively it adds the smallest element in the list and then calls the function with the list excluding that element to keep finding the next smallest.
(define my-sort
  (lambda (inlist comp)
    (define find-smallest
      (lambda (lst)
        (foldl 
         (lambda (x y) (if (comp x y) x y))
         (first lst)
         (rest lst))))
      (cond
        [(null? inlist) '()]
        [(= (length inlist) 1) inlist]
        [(cons (find-smallest inlist) (my-sort (remove (find-smallest inlist) inlist) comp))])))

;base case is the empty list, in which case the empty list is returned. Then the first element of the list is checked.
;If that itself is a list, then we append the first element of that sublist onto the rest of the sublist, flattening the sublist.
;If it is not a sublist, then we continue on to the next element. This recursion occurs with the rest of the list until all sublists are flattened.
(define my-flatten
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [(list? (car lst)) (append (my-flatten (car lst)) (my-flatten (cdr lst)))]
      [else (cons (car lst) (my-flatten (cdr lst)))])))

;check in the beginning if the position given will be out of bounds by checking if its greater than the list length - 1; if it is, throw an error.
;Otherwise, recursively call my-list-ref with the rest of the list and the position being one less until the position is 0, then return the car of the list.
(define my-list-ref
  (lambda (lst pos)
    (cond
      [(> pos (- (length lst) 1)) (error "ERROR: Index out of bounds")]
      [(= pos 0) (car lst)]
      [else (my-list-ref (cdr lst) (sub1 pos))])))

;deep reverse takes a list for input and the recursive base case is the empty list. Every element of the list is checked, and if it is a sublist,
;it is deep reversed recursively, and if it is not a sublist the element is listed, and both those results are appended to the end of the
;recursive call so that the elements are added to the list properly in reverse order.
(define deep-reverse
  (lambda (lst)
    (if (null? lst)
        null
        (if (list? (car lst))
            (append (deep-reverse (cdr lst)) (list (deep-reverse (car lst))))
            (append (deep-reverse (cdr lst)) (list (car lst)))))))

;recursive implementation of addition. Base case, empty list returns 0. Otherwise it checks for when the first element of the list equals 0
;based on the sign of the integer it will either need to add1 or subtract1 and decrement the item in the first position until it is 0, continuing with the rest of the list.
;Ultimately the recursion is a bunch of add1s and sub1s operating on 0. my-flatten needs to be called every time because since integer+ takes a variable number of arguments,
;recursive calls to integer+ wrap the singular list we want inside of another list, so we flatten so car and cdr give us the integers we want.
(define integer+
  (lambda nums
    (if (null? (my-flatten nums))
        0
        (if (= (car (my-flatten nums)) 0)
            (integer+ (cdr (my-flatten nums)))
            (if (> (car (my-flatten nums)) 0)
                (add1 (integer+ (cons (sub1 (car (my-flatten nums))) (cdr (my-flatten nums)))))
                (sub1 (integer+ (cons (add1 (car (my-flatten nums))) (cdr (my-flatten nums))))))))))
