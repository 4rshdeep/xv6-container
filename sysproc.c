#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int 
sys_create_container(void)
{
  int cid;
  if (argint(0, &cid) < 0)  {
    return -1;
  }
  return create_container_helper(cid);
}

int
sys_join_container(void) 
{
  int cid;
  if (argint(0, &cid) < 0) {
    return -1;
  }
  return join_container_helper(cid);
}

int 
sys_leave_container(void) 
{
  return leave_helper();
}

int 
sys_destroy_container(void)
{
  int cid;
  if (argint(0, &cid) < 0)
  {
    return -1;
  }
  return destroy_helper(cid);
}

int sys_scheduler_log_on(void) {
  if (log_toggle==1) {
    return -1;
  }
  log_toggle = 1;
  return 0;
}

int 
sys_scheduler_log_off(void) {
  if (log_toggle == 0) {
    return -1;
  }
  log_toggle = 0;
  return 0;
}

int 
sys_ps(void) {
  procdump_container();
  return 0;
}

int sys_get_cid(void) {
  return get_cid_helper();
}

int sys_maintain_inum(void) {
// maintain_inum(myproc()->cid, ip->inum, new_ip->inum
  int cid;
  int inum;
  int new_inum;
  if (argint(0, &cid) < 0)
  {
    return -1;
  }
  if (argint(1, &inum) < 0)
  {
    return -1;
  }
  if (argint(2, &new_inum) < 0)
  {
    return -1;
  }

  return maintain_inum_helper(cid, (uint)inum, (uint)new_inum);  

}
int sys_maintain_creations(void) {
// maintain_inum(myproc()->cid, ip->inum, new_ip->inum
  int cid;
  int inum;
  // int new_inum;
  if (argint(0, &cid) < 0)
  {
    return -1;
  }
  if (argint(1, &inum) < 0)
  {
    return -1;
  }

  return maintain_creations_helper(cid, (uint)inum);  

}

int sys_accessibility(void) {
// accessibility(cid, st.ino)==1 )
  int cid;
  int inum;
  if (argint(0, &cid) < 0)
  {
    return -1;
  }
  if (argint(1, &inum) < 0)
  {
    return -1;
  }
  return accessibility_helper(cid, (uint)inum);
}

int sys_find_source(void) {
// accessibility(cid, st.ino)==1 )
  int cid;
  int inum;
  if (argint(0, &cid) < 0)
  {
    return -1;
  }
  if (argint(1, &inum) < 0)
  {
    return -1;
  }
  return find_source_helper(cid, (uint)inum);
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
