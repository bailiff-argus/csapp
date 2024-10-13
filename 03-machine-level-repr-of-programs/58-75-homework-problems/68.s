setVal:
  movslq     8(%rsi),   %rax       ;; &(q->t) = (p offset by 1 * B rounded up to 4) -> B in [5, 8]
  addq       32(%rsi),  %rax       ;; &(q->u) = (p offset by 8 + 4 + 2A rounded up to 8) -> (2A + 12) in [25, 32] -> A in [7,10]
  movq       %rax,      184(%rdi)  ;; 4 * A * B = 184 or 180 -> A * B in [45, 46]
  ret

;; 46 = 23 * 2, 23 is too high
;; 45 = 5 * 9 = 15 * 3, 15 is too high
;; Out of {5, 9}, B can only be 5, then A is 9
;;
;; A = 9
;; B = 5

