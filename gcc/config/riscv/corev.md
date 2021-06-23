;; Machine description for CORE-V operations.
;; Copyright (C) 2011-2020 Free Software Foundation, Inc.
;; Contributed by Jessica Mills (jessica.mills@embecosm.com),
;;                Mary Bennett (mary.bennett@embecosm.com),
;;                Pietra Ferreira (pietra.ferreira@embecosm.com).
;; Based on MIPS target for GNU compiler.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;;
;;  ............................
;;
;;      CORE-V GENERAL ALU INSN
;;
;;  ............................
;;

(define_insn "cv_abs"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (lt:SI (match_operand:SI 1 "register_operand" "r")
               (const_int 0))
        (neg:SI (match_dup 1))
        (match_dup 1)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.abs\t%0,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_slet"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (le:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (const_int 1)
        (const_int 0)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.slet\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_sletu" /*TODO: unsigned */
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (le:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (const_int 1)
        (const_int 0)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.sletu\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_min"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (lt:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (match_dup 1)
        (match_dup 2)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.min\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_minu" /*TODO: unsigned */
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (lt:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (match_dup 1)
        (match_dup 2)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.minu\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)
  
(define_insn "cv_max"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (lt:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (match_dup 2)
        (match_dup 1)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.max\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_maxu" /*TODO: unsigned */
    [(set (match_operand:SI 0 "register_operand" "=r")
      (if_then_else:SI
        (lt:SI (match_operand:SI 1 "register_operand" "r")
               (match_operand:SI 2 "register_operand" "r"))
        (match_dup 2)
        (match_dup 1)
      )
  )]
  "TARGET_COREV_ALU"
  "cv.maxu\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_exths"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
  )]
  "TARGET_COREV_ALU"
  "cv.exths\t%0,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_exthz"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (zero_extend:SI (match_operand:HI 1 "register_operand" "r"))
  )]
  "TARGET_COREV_ALU"
  "cv.exthz\t%0,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_extbs"
    [(set (match_operand:SI 0 "register_operand" "=r")
      (sign_extend:SI (match_operand:QI 1 "register_operand" "r"))
  )]
  "TARGET_COREV_ALU"
  "cv.extbs\t%0,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_extbz"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (zero_extend:SI (match_operand:QI 1 "register_operand" "r"))
  )]
  "TARGET_COREV_ALU"
  "cv.extbz\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

; TODO: SOMEONE NEEDS TO CHECK THESE!!!

; (define_insn "cv_clip"
;if   [(if_then_else:SI                                                ; if
;cond     (le:SI (match_operand 1 "register_operand" "r")              ; rs1 <= -2^(Is2-1)
;                (neg:SI (ashift:SI
;                           (const_int 1)
;                           (minus:SI (match_operand 2 "immediate_operand" "i")
;                                     (const_int 1)
;                           )
;                        )
;                )
;         )
;then     (set (match_operand:SI 0 "register_operand" "=r")
;              (neg:SI (ashift:SI
;                         (const_int 1)
;                         (minus:SI (match_dup 2)
;                                     (const_int 1)
;                         )
;                      )
;              )
;         )                                                            ; then rD = -2^(Is2-1)
;else if  (if_then_else:SI                                             ; else, if
;cond        (ge:SI (match_dup 1)                                      ; rs1 >= 2^(ls2–1)-1
;                   (minus:SI (ashift:SI
;                                (const_int 1)
;                                (minus:SI (match_dup 2)
;                                          (const_int 1)
;                                )
;                             )
;                             (const_int 1)
;                   )
;             )
;then         (set (match_dup 0)                                       ; then rd = 2^(Is2-1)-1
;                  (minus:SI (ashift:SI
;                               (const_int 1)
;                               (minus:SI (match_dup 2)
;                                          (const_int 1)
;                               )
;                            )
;                            (const_int 1)
;                  )
;             )
;else         (set (match_dup 0) (match_dup 1))                         ; else rd = rs1
;          )
;     )]
;   "TARGET_COREV_ALU"
;   "cv.clip\t%0,%1,%2"
;   [(set_attr "type" "arith")
;    (set_attr "mode" "SI")]
; )

; (define_insn "cv_clipr"
;if   [(if_then_else:SI                                                ; if
;cond     (le:SI (match_operand 1 "register_operand" "r")              ; rs1 <= -2^(Is2-1)
;                (neg:SI (ashift:SI
;                           (const_int 1)
;                           (minus:SI (match_operand 2 "immediate_operand" "i")
;                                     (const_int 1)
;                           )
;                        )
;                )
;         )
;then     (set (match_operand:SI 0 "register_operand" "=r")
;              (neg:SI (ashift:SI
;                         (const_int 1)
;                         (minus:SI (match_dup 2)
;                                     (const_int 1)
;                         )
;                      )
;              )
;         )                                                            ; then rD = -2^(Is2-1)
;else if  (if_then_else:SI                                             ; else, if
;cond        (ge:SI (match_dup 1)                                      ; rs1 >= rs2
;                   (match_dup 2)
;            )
;then        (set (match_dup 0)                                       ; then rd = rs2
;                 (match_dup 2)
;            )
;els         (set (match_dup 0) (match_dup 1))                         ; else rd = rs1
;         )
;    )]
;   "TARGET_COREV_ALU"
;   "cv.clipr\t%0,%1,%2"
;   [(set_attr "type" "arith")
;    (set_attr "mode" "SI")]
; )


; (define_insn "cv_clipu"
;if   [(if_then_else:SI                                                ; if
;cond     (le:SI (match_operand 1 "register_operand" "r")              ; rs1 <= 0
;                (const_int 0)
;         )
;then     (set (match_operand:SI 0 "register_operand" "=r") 
;              (const_int 0))                                          ; then rD = 0
;else if  (if_then_else:SI                                             ; else, if
;cond        (ge:SI (match_dup 1)                                      ; rs1 >= 2^(ls2–1)-1
;                   (minus:SI (ashift:SI
;                                (const_int 1)
;                                (minus:SI (match_operand 2 "immediate_operand" "i")
;                                          (const_int 1)
;                                )
;                             )
;                             (const_int 1)
;                   )  
;             )          
;then         (set (match_dup 0)                                       ; then rd = 2^(Is2-1)-1
;                  (minus:SI (ashift:SI
;                               (const_int 1)
;                               (minus:SI (match_dup 2)
;                                          (const_int 1)
;                               )
;                            )
;                            (const_int 1)
;                  )
;             )    
;else         (set (match_dup 0) (match_dup 1))                         ; else rd = rs1     
;          )
;     )]
;   "TARGET_COREV_ALU"
;   "cv.clipu\t%0,%1,%2"
;   [(set_attr "type" "arith")
;    (set_attr "mode" "SI")]
; )

; (define_insn "cv_clipur"
;if   [(if_then_else:SI                                                ; if
;cond     (le:SI (match_operand 1 "register_operand" "r")              ; rs1 <= 0
;                (const_int 0)
;         )
;then     (set (match_operand:SI 0 "register_operand" "=r") 
;              (const_int 0))                                          ; then rD = 0
;else if  (if_then_else:SI                                             ; else, if
;cond        (ge:SI (match_dup 1)                                      ; rs1 >= rs2
;                   (match_operand 2 "immediate_operand" "i")
;            )
;then        (set (match_dup 0)                                        ; then rd = rs2
;                 (match_dup 2)
;            )   
;else        (set (match_dup 0) (match_dup 1))                         ; else rd = rs1
;         )
;      )]
;   "TARGET_COREV_ALU"
;   "cv.clipur\t%0,%1,%2"
;   [(set_attr "type" "arith")
;    (set_attr "mode" "SI")]
; )


; Following PULP's implementation

(define_insn "cv_clip_maxmin"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(smax:SI (smin:SI (match_operand:SI 1 "register_operand" "r")
			  (match_operand:SI 2 "immediate_operand" "i"))
		 (match_operand:SI 3 "immediate_operand" "i"))
  )]
  "TARGET_COREV_ALU"
  ; Note that here we use B2 
  "cv.clip\t%0,%1,%B2"
  [(set_attr "type" "logical")
   (set_attr "mode" "SI")]
)

(define_insn "cv_clip_minmax"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(smin:SI (smax:SI (match_operand:SI 1 "register_operand" "r")
			  (match_operand:SI 2 "immediate_operand" "i"))
		 (match_operand:SI 3 "immediate_operand" "i"))
  )]
  "TARGET_COREV_ALU"
  "cv.clip\t%0,%1,%B3"
  [(set_attr "type" "logical")
   (set_attr "mode" "SI")]
)

(define_insn "cv_clipr_minmax"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(smin:SI (smax:SI (match_operand:SI 1 "register_operand" "r")
			  (neg:SI (plus:SI (match_operand:SI 2 "register_operand" "r") (const_int 1)))
		 )
		 (match_dup 2))
  )]
  "TARGET_COREV_ALU"
  "cv.clipr\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "SI")]
)

(define_insn "cv_clipr_maxmin"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(smax:SI (smin:SI (match_operand:SI 1 "register_operand" "r")
			  (match_operand:SI 2 "register_operand" "r")
		 )
		 (neg:SI (plus:SI (match_dup 2) (const_int 1))))
  )]
  "TARGET_COREV_ALU"
  "cv.clipr\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "SI")]
)

; Following PULP's implementation, cv.clipu's template is the same as clip, the only obvious difference being in the "TARGET..." line

(define_insn "cv_clipu_maxmin"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smax:SI (smin:SI (match_operand:SI 1 "register_operand" "r")
                          (match_operand:SI 2 "immediate_operand" "i"))
                 (match_operand:SI 3 "immediate_operand" "i"))
  )]
  "TARGET_COREV_ALU"
  "cv.clipu\t%0,%1,%B2"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "cv_clipu_minmax"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smin:SI (smax:SI (match_operand:SI 1 "register_operand" "r")
                          (match_operand:SI 2 "immediate_operand" "i"))
                 (match_operand:SI 3 "immediate_operand" "i"))
  )]
  "TARGET_COREV_ALU"
  "cv.clipu\t%0,%1,%B3"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "cv_clipur_maxmin"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smax:SI (smin:SI (match_operand:SI 1 "register_operand" "r")
                          (match_operand:SI 2 "register_operand" "r")
                 )
                 (const_int 0)
        )
  )]
  "TARGET_COREV_ALU"
  "p.clipur\t%0,%1,%2"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "cv_clipur_minmax"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smin:SI (smax:SI (match_operand:SI 1 "register_operand" "r") (const_int 0))
                 (match_operand:SI 2 "register_operand" "r"))
  )]
  "TARGET_COREV_ALU"
  "cv.clipur\t%0,%1,%2"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "cv_addn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "register_operand" "r")
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "register_operand" "r")
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addun\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (plus:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI (match_operand:SI 3 "immediate_operand" "i")
                    (const_int 1)
          )
        )
      )
      (match_dup 3)
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addrn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addurn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (plus:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")
        )
        (ashiftrt:SI
          (const_int 1)
          (minus:SI (match_operand:SI 3 "immediate_operand" "i")
                    (const_int 1)
          )
        )
      )
      (match_dup 3)
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addurn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (match_dup 0)
        (match_operand:SI 1 "register_operand" "r")
      )
      (and:SI
        (match_operand:QI 2 "register_operand" "r")
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addnr\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addunr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (match_operand:SI 1 "register_operand" "r"
        (match_operand:SI 2 "register_operand" "r")
      )
      (and:SI
        ;; TODO doesn't work with SI (applies to other insn)
        (match_operand:HI 3 "register_operand" "r")
        (const_int 31) 
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addunr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addrnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (plus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI
            (and:SI
              (match_operand:HI 3 "register_operand" "r")
              (const_int 31)
            )
            (const_int 1)
          )
        )
      )
      (and:SI
        (match_dup 3)
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addrnr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_addurnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (plus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI
            (and:SI
              (match_operand:HI 3 "register_operand" "r")
              (const_int 31)
            )
            (const_int 1)
          )
        )
      )
      (and:SI
        (match_dup 3)
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.addurnr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (minus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "reg_or_0_operand" "rJ")
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (minus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "reg_or_0_operand" "rJ")
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subun\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (minus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI
            (match_operand:HI 3 "immediate_operand" "i")
            (const_int 1)
          )
        )
      )
      (match_dup 3)
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subrn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_suburn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (minus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI
            (match_operand:HI 3 "immediate_operand" "i")
            (const_int 1)
          )
        )
      )
      (match_dup 3)
    )
  )]
  "TARGET_COREV_ALU"
  "cv.suburn\t%0,%1,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (minus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "register_operand" "r")
      )
      (and:SI
        (match_operand:HI 3 "register_operand" "r")
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subnr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subunr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (minus:SI
        (match_operand:SI 1 "register_operand" "r")
        (match_operand:SI 2 "register_operand" "r")
      )
      (and:SI
        (match_operand:HI 3 "register_operand" "r")
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subunr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_subrnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
        (minus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
            (minus:SI
            (and:SI
              (match_operand:HI 3 "register_operand" "r")
              (const_int 31)
            )
            (const_int 1)
          )
        )
      )
      (and:SI
        (match_dup 3)
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.subrnr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)

(define_insn "cv_suburnr"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
        (minus:SI
          (match_operand:SI 1 "register_operand" "r")
          (match_operand:SI 2 "register_operand" "r")
        )
        (ashift:SI
          (const_int 1)
          (minus:SI
            (and:SI
              (match_operand:HI 3 "register_operand" "r")
              (const_int 31)
            )
            (const_int 1)
          )
        )
      )
      (and:SI
        (match_dup 3)
        (const_int 31)
      )
    )
  )]
  "TARGET_COREV_ALU"
  "cv.suburnr\t%0,%2,%3"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]
)
