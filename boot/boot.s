.section .text.init
 
.option norvc
 
.type start, @function
.global _start
_start:
    .cfi_startproc
    
/*    csrw    satp, zero
 
	la      sp, _stack_top
    
    # Clear the BSS section
	la      t5, _bss_start
	la      t6, _bss_end
bss_clear:
	sw      zero, (t5)
	addi    t5, t5, 4
	bgeu    t5, t6, bss_clear
 
	la      t0, KernelEntry
	csrw    mepc, t0
 
	# Jump to kernel
 
    tail KernelEntry
 */
    lui t0, 0x10000

    andi t1, t1, 0
    addi t1, t1, 72
    sw t1, 0(t0)

    andi t1, t1, 0
    addi t1, t1, 101
    sw t1, 0(t0)

    andi t1, t1, 0
    addi t1, t1, 108
    sw t1, 0(t0)

    andi t1, t1, 0
    addi t1, t1, 108
    sw t1, 0(t0)

    andi t1, t1, 0
    addi t1, t1, 111
    sw t1, 0(t0)

    andi t1, t1, 0
    addi t1, t1, 10
    sw t1, 0(t0)

finish:
    beq t1, t1, finish
    
    
 
    .cfi_endproc
.end
