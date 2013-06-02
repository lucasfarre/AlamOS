#ifndef _stackchk_h
#define _stackchk_h

void __stack_chk_guard_setup();
void __attribute__((noreturn)) __stack_chk_fail();

#endif