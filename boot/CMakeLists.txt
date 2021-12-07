
list(APPEND ASM_SOURCE
	boot.s)

add_library(boot OBJECT ${ASM_SOURCE})
