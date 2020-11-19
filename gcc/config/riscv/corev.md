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

(define_c_enum "unspecv" [
  ;; CORE-V HWLP
  UNSPECV_CV_STARTI
  UNSPECV_CV_ENDI
  UNSPECV_CV_COUNT
  UNSPECV_CV_COUNTI
  UNSPECV_CV_SETUP
  UNSPECV_CV_SETUPI
  UNSPECV_HWLP_MEMCPY

UNSPECV_CV_MULU
UNSPECV_MACS_MACSRNF
])

(define_c_enum "unspec" [
  UNSPEC_MULU
])

;;
;;  ....................
;;
;;      CORE-V HWLP INSN
;;
;;  ....................
;;

;;TODO: choose this or the other one

(define_insn "cv_starti"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (label_ref (match_operand 1 "label_or_sleu_operand"))] UNSPECV_CV_STARTI)
   (use (label_ref (match_dup 1)))]
  "TARGET_COREV_HWLP"
  "cv.starti %0, %1")

(define_insn "cv_endi"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (match_operand 1 "label_or_sleu_operand")] UNSPECV_CV_ENDI)];;*PUT SYM_OR_SLEU HERE*
  "TARGET_COREV_HWLP"
  "cv.endi %0, %1")

(define_insn "cv_count"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (match_operand 1 "register_operand" "r")] UNSPECV_CV_COUNT)] ;; TODO: READ? Note: the r contraints to general purpose register, couldnt use a floating point one
  "TARGET_COREV_HWLP"
  "cv.count %0, %1")

(define_insn "cv_counti"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (match_operand 1 "const_int_operand")] UNSPECV_CV_COUNTI)] ;;TODO: Same as above
  "TARGET_COREV_HWLP"
  "cv.counti %0, %1")

(define_insn "cv_setup"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (match_operand 1 "register_operand" "r");; TODO READ ONLY?
                     (match_operand 2 "label_or_sleu_operand")] UNSPECV_CV_SETUP)];;*PUT SYM_OR_SLEU HERE*
  "TARGET_COREV_HWLP"
  "cv.setup %0, %1, %2")

(define_insn "cv_setupi"
  [(unspec_volatile [(match_operand 0 "one_bit_operand")
                     (match_operand 1 "sleu_operand")
                     (match_operand 2 "five_bit_sleu_or_label_operand")] UNSPECV_CV_SETUPI)];;TODO: uimmS is a label?? NEED TO CREATE A 5 BIT SLEU***
  "TARGET_COREV_HWLP"
  "cv.setupi %0, %1, %2")

;;TODO: Maybe hardcode t0 temp reg and clobber -> to decide
(define_insn "hwlp_memcpy"
  [(unspec_volatile [(match_operand 0 "register_operand")
                     (match_operand 1 "register_operand")
                     (match_operand 2 "register_operand")
                     (match_operand 3 )] UNSPECV_HWLP_MEMCPY)]
  "TARGET_COREV_HWLP"
  "cv.setupi 0,%3,0f\n\t.option\tpush\n\t.option\tnorvc\n\tlb\t%2,0(%1)
   \tsb\t%2,0(%0)\n\taddi\t%1,%1,1\n\n0:\taddi\t%0,%0,1\n\t.option\tpop\n"
)

;;
;;  ....................
;;
;;      CORE-V MAC INSN
;;
;;  ....................
;;

(define_insn "cv_mac"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (plus:SI (mult:SI (match_operand:SI 2 "register_operand" "r")
		      (match_operand:SI 3 "register_operand" "r")
	     )
	     (match_operand:SI 1 "register_operand" "0")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mac\t%0,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_msu"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (minus:SI (mult:SI (match_operand:SI 2 "register_operand" "r")
		       (match_operand:SI 3 "register_operand" "r")
	      )
	      (match_operand:SI 1 "register_operand" "0")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.msu\t%0,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_muls"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (mult: SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
	      (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
    )
  )]
  "TARGET_COREV_MAC"
  "cv.muls\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhs"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (mult:SI (sign_extend:SI (lshiftrt:SI
			       (match_operand:SI 1 "register_operand" "r")
			       (const_int 16)))
	     (sign_extend:SI (lshiftrt:SI
			       (match_operand:SI 2 "register_operand" "r")
			       (const_int 16)))
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulhhs\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulsn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
	       (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulsn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhsn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (mult:SI (sign_extend:SI (lshiftrt:SI
			         (match_operand:SI 1 "register_operand" "r")
				 (const_int 16)))
	       (sign_extend:SI (lshiftrt:SI
			         (match_operand:SI 2 "register_operand" "r")
				 (const_int 16)))
      )
      (match_operand:SI 3 "immediate_operand" "i")
    ) 
  )]
  "TARGET_COREV_MAC"
  "cv.mulhhsn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulsrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
		 (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
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
  "TARGET_COREV_MAC"
  "cv.mulsrn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhsrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
	(mult:SI (ashiftrt:SI (match_operand:SI 1 "register_operand" "r")
			      (const_int 16))
		 (ashiftrt:SI (match_operand:SI 2 "register_operand" "r")
			      (const_int 16))
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
  "TARGET_COREV_MAC"
  "cv.mulhhsrn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulu"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (mult: SI (zero_extend:SI (match_operand:HI 1 "register_operand" "r"))
	      (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulu\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhu"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (mult:SI (lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
			  (const_int 16))
	     (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
			  (const_int 16))
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulhhu\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (mult:SI (zero_extend:SI (match_operand:HI 1 "register_operand" "r"))
	       (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulun\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (mult:SI (lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
			    (const_int 16))
	       (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
			    (const_int 16))
      )
      (match_operand:SI 3 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.mulhhun\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulurn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(mult:SI (zero_extend:SI (match_operand:HI 1 "register_operand" "r"))
		 (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
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
  "TARGET_COREV_MAC"
  "cv.mulurn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_mulhhurn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(mult:SI (lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
			      (const_int 16))
		 (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
			      (const_int 16))
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
  "TARGET_COREV_MAC"
  "cv.mulhhurn\t%0,%1,%2,%3"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_macsn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
	(mult:SI (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
		 (sign_extend:SI (match_operand:HI 3 "register_operand" "r"))
	)
	(match_operand:SI 1 "register_operand" "0")
      )
      (match_operand:SI 4 "five_bit_sleu_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.macsn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_machhsn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
	(mult:SI (ashiftrt:SI (match_operand:SI 2 "register_operand" "r")
			      (const_int 16))
		 (ashiftrt:SI (match_operand:SI 3 "register_operand" "r")
			      (const_int 16))
	)
	(match_operand:SI 1 "register_operand" "0")
      )
      (match_operand:SI 4 "five_bit_sleu_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.machhsn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_macsrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
	(plus:SI
	  (mult:SI (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
		   (sign_extend:SI (match_operand:HI 3 "register_operand" "r"))
	  )
	  (match_operand:SI 1 "register_operand" "0")
	)
	(ashift:SI 
	  (const_int 1)
	  (minus:SI (match_operand:SI 4 "immediate_operand" "i") 
		    (const_int 1)
	  )
	)
      )
      (match_dup 4)
    )
  )]
  "TARGET_COREV_MAC"
  "cv.macsrn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_machhsrn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ashiftrt:SI
      (plus:SI
	(plus:SI
	  (mult:SI (ashiftrt:SI (match_operand:SI 2 "register_operand" "r")
				(const_int 16))
		   (ashiftrt:SI (match_operand:SI 3 "register_operand" "r")
				(const_int 16))
	  )
	  (match_operand:SI 1 "register_operand" "0")
	)
	(ashift:SI
	  (const_int 1)
	  (minus:SI (match_operand:SI 4 "immediate_operand" "i")
		    (const_int 1)
	  )
	)
      )
      (match_dup 4)
    )
  )]
  "TARGET_COREV_MAC"
  "cv.machhsrn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_macun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(mult:SI (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
		 (zero_extend:SI (match_operand:HI 3 "register_operand" "r"))
	)
	(match_operand:SI 1 "register_operand" "0")
      )
      (match_operand:SI 4 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.macun\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_machhun"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(mult:SI (lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
			      (const_int 16))
		 (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
			      (const_int 16))
	)
	(match_operand:SI 3 "register_operand" "0")
      )
      (match_operand:SI 4 "immediate_operand" "i")
    )
  )]
  "TARGET_COREV_MAC"
  "cv.machhun\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_macurn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(plus:SI
	  (mult:SI (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
		   (zero_extend:SI (match_operand:HI 3 "register_operand" "r"))
	  )
	  (match_operand:SI 1 "register_operand" "0")
	)
	(ashift:SI
	  (const_int 1)
	  (minus:SI (match_operand:SI 4 "immediate_operand" "i")
		    (const_int 1)
	  )
	)
      )
      (match_dup 4)  
    )
  )]
  "TARGET_COREV_MAC"
  "cv.macurn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

(define_insn "cv_machhurn"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (lshiftrt:SI
      (plus:SI
	(plus:SI
	  (mult:SI (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
				(const_int 16))
		   (lshiftrt:SI (match_operand:SI 3 "register_operand" "r")
				(const_int 16))
	  )
	  (match_operand:SI 1 "register_operand" "0")
	)
	(ashift:SI
	  (const_int 1)
	  (minus:SI (match_operand:SI 4 "immediate_operand" "i")
		    (const_int 1)
	  )
	)
      )
      (match_dup 4)
    )
  )]
  "TARGET_COREV_MAC"
  "cv.machhurn\t%0,%2,%3,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

;;
;;  ....................
;;
;;      CORE-V ALU INSN
;;
;;  ....................
;;

;;TODO: CHANGE TARGET TO COREV_ALU

(define_insn "cv_addunr"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (lshiftrt:SI
                (plus:SI
                        (match_operand:SI 1 "register_operand" "r")
                        (match_operand:SI 2 "register_operand" "r")
                )
                (and:SI 
			(match_operand:HI 3 "register_operand" "r") ;;TODO: why doesnt this like SI? DO I NEED A CHECK FOR %0 == %1
			(const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                        			(const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
                			)
                    			(const_int 1)
          			)

        		)
		)
		(and:SI
	                (match_dup 3) 
        	        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                                                (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
                                        )
                                        (const_int 1)
                                )

                        )
                )
                (and:SI
                        (match_dup 3)                                                      
                        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                        (match_operand:HI 3 "register_operand" "r") ;;TODO: why doesnt this like SI? DO I NEED A CHECK FOR %0 == %1
                        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                        (match_operand:HI 3 "register_operand" "r") ;;TODO: why doesnt this like SI? DO I NEED A CHECK FOR %0 == %1
                        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                                                (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
                                        )
                                        (const_int 1)
                                )

                        )
                )
                (and:SI
                        (match_dup 3)
                        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
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
                                                (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
                                        )
                                        (const_int 1)
                                )

                        )
                )
                (and:SI
                        (match_dup 3)
                        (const_int 31) ;;TODO: IS THIS CORRECT, cast to short and cut off top bits then and with 11111
                )

        )
)]
  "TARGET_COREV_ALU"
  "cv.suburnr\t%0,%2,%3"
  [(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

