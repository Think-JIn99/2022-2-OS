#include "proc.h"
int sys_memsize(void){
    struct proc *p = myproc();
    return p->sz;
}