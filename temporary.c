//global container in action banao
int container_in_action = 0


void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  // bool entered = false;
  // bool exited = false;
  bool found;
  int container_in_action = 0;
  for(;;){
    // Enable interrupts on this processor.
    found = false;
    sti(); //yeh kya hai

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE || p->cid != container_in_action )
        continue;

      found = true;
      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      container_in_action = (container_in_action + 1)%CPROCS;
      if(log_toggle == 1){
        printf("Container + %d : Scheduling process + %d\n", p->cid, p->pid );
      }
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();


      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
      // found = false;
    }
    if(!found){
      container_in_action = (container_in_action + 1)%CPROCS;
      // if(container_in_action==0) container_in_action = 1;
    }

    // if (!found){
    //   do{
    //     container_in_action = (container_in_action + 1)%100
    //   }while((ctable[container_in_action].uid!= 0))
    // }
    // if (found){
    //   container_in_action = (container_in_action + 1)%100
    // }
    //can remove the if
    release(&ptable.lock);

  }
}