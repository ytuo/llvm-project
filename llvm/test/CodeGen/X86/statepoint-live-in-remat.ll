; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -code-model=large -verify-machineinstrs -O3 -restrict-statepoint-remat=true < %s | FileCheck %s
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

declare void @bar() #0

; This stresses our rematerialization handling.
; Target of statepoint is able to be re-materialized.
define void @test(i32 %a, i32 %b, i32 %c, i32 %d, i32 %e, i32 %f, i32 %g, i32 %h, i32 %i, i32 %j, i32 %k, i32 %l, i32 %m, i32 %n, i32 %o, i32 %p, i32 %q, i32 %r, i32 %s, i32 %t, i32 %u, i32 %v, i32 %w, i32 %x, i32 %y, i32 %z) gc "statepoint-example" {
; The code for this is terrible, check simply for correctness for the moment
; CHECK-LABEL: test:
; CHECK:       ## %bb.0:
; CHECK-NEXT:    pushq %rbp
; CHECK-NEXT:    .cfi_def_cfa_offset 16
; CHECK-NEXT:    pushq %r15
; CHECK-NEXT:    .cfi_def_cfa_offset 24
; CHECK-NEXT:    pushq %r14
; CHECK-NEXT:    .cfi_def_cfa_offset 32
; CHECK-NEXT:    pushq %r13
; CHECK-NEXT:    .cfi_def_cfa_offset 40
; CHECK-NEXT:    pushq %r12
; CHECK-NEXT:    .cfi_def_cfa_offset 48
; CHECK-NEXT:    pushq %rbx
; CHECK-NEXT:    .cfi_def_cfa_offset 56
; CHECK-NEXT:    subq $104, %rsp
; CHECK-NEXT:    .cfi_def_cfa_offset 160
; CHECK-NEXT:    .cfi_offset %rbx, -56
; CHECK-NEXT:    .cfi_offset %r12, -48
; CHECK-NEXT:    .cfi_offset %r13, -40
; CHECK-NEXT:    .cfi_offset %r14, -32
; CHECK-NEXT:    .cfi_offset %r15, -24
; CHECK-NEXT:    .cfi_offset %rbp, -16
; CHECK-NEXT:    movl %r9d, %r14d
; CHECK-NEXT:    movl %r8d, %r15d
; CHECK-NEXT:    movl %ecx, %r12d
; CHECK-NEXT:    movl %edx, %r13d
; CHECK-NEXT:    movl %esi, %ebx
; CHECK-NEXT:    movl %edi, %ebp
; CHECK-NEXT:    movabsq $_bar, %rax
; CHECK-NEXT:    callq *%rax
; CHECK-NEXT:    movl %ebp, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl %ebx, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl %r13d, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl %r12d, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl %r15d, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl %r14d, %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax
; CHECK-NEXT:    movq %rax, {{[-0-9]+}}(%r{{[sb]}}p) ## 8-byte Spill
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %ebp
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r12d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r15d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r14d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %ebx
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r11d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r10d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r9d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %r8d
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %edi
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %esi
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %edx
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %ecx
; CHECK-NEXT:    movl {{[0-9]+}}(%rsp), %eax

; Re-materialization happened.

; CHECK-NEXT:    movabsq $_bar, %r13
; CHECK-NEXT:    callq *%r13 ## 96-byte Folded Reload
; CHECK-NEXT:  Ltmp0:
; CHECK-NEXT:    addq $104, %rsp
; CHECK-NEXT:    popq %rbx
; CHECK-NEXT:    popq %r12
; CHECK-NEXT:    popq %r13
; CHECK-NEXT:    popq %r14
; CHECK-NEXT:    popq %r15
; CHECK-NEXT:    popq %rbp
; CHECK-NEXT:    retq

; This is a call to hoist the loading of the target of the call for statepoint.
  call void @bar()
  br label %entry

entry:
  %a64 = zext i32 %a to i64
  %b64 = zext i32 %b to i64
  %c64 = zext i32 %c to i64
  %d64 = zext i32 %d to i64
  %e64 = zext i32 %e to i64
  %f64 = zext i32 %f to i64
  %g64 = zext i32 %g to i64
  %h64 = zext i32 %h to i64
  %i64 = zext i32 %i to i64
  %j64 = zext i32 %j to i64
  %k64 = zext i32 %k to i64
  %l64 = zext i32 %l to i64
  %m64 = zext i32 %m to i64
  %n64 = zext i32 %n to i64
  %o64 = zext i32 %o to i64
  %p64 = zext i32 %p to i64
  %q64 = zext i32 %q to i64
  %r64 = zext i32 %r to i64
  %s64 = zext i32 %s to i64
  %t64 = zext i32 %t to i64
  %u64 = zext i32 %u to i64
  %v64 = zext i32 %v to i64
  %w64 = zext i32 %w to i64
  %x64 = zext i32 %x to i64
  %y64 = zext i32 %y to i64
  %z64 = zext i32 %z to i64
  %statepoint_token1 = call token (i64, i32, void ()*, i32, i32, ...) @llvm.experimental.gc.statepoint.p0f_isVoidf(i64 2882400000, i32 0, void ()* @bar, i32 0, i32 2, i32 0, i32 26, i64 %a64, i64 %b64, i64 %c64, i64 %d64, i64 %e64, i64 %f64, i64 %g64, i64 %h64, i64 %i64, i64 %j64, i64 %k64, i64 %l64, i64 %m64, i64 %n64, i64 %o64, i64 %p64, i64 %q64, i64 %r64, i64 %s64, i64 %t64, i64 %u64, i64 %v64, i64 %w64, i64 %x64, i64 %y64, i64 %z64)
  ret void
}

declare token @llvm.experimental.gc.statepoint.p0f_isVoidf(i64, i32, void ()*, i32, i32, ...)

attributes #0 = { "deopt-lowering"="live-in" }
