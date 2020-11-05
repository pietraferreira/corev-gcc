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

  ;; CORE-V MAC
  UNSPECV_CV_MACSN
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


(define_insn "cv_macsn"
  [(unspec_volatile
    [(set (match_operand:SI 0 "register_operand" "=r")
        (ashiftrt:SI
                (plus:SI
                        (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
                                 (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))
                        )
                        (match_operand:SI 3 "register_operand" "0")
                )
                (match_operand:SI 4 "five_bit_sleu_operand" "i")
        )
   )]
  UNSPECV_CV_MACSN)]
  "TARGET_COREV_MAC"
  "cv.macsn \t%0,%1,%2,%4"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")]
)

