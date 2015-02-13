#define ADDR_DWORD(a)			(*(dword*)(vm_base + (a)))
#define ADDR_WORD(a)			(*(word*)(vm_base + (a)))
#define ADDR_BYTE(a)			(*(byte*)(vm_base + (a)))

#define STACK_FREE				(ADDR_WORD(vm_sp))
#define STACK_TOP				(ADDR_WORD(vm_sp+2))
#define STACK_MIDDLE			(ADDR_WORD(vm_sp+4))
#define STACK_BOTTOM			(ADDR_WORD(vm_sp+6))
