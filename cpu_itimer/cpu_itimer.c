#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

void print_cpu_itimer_to_kernel(struct cpu_itimer *cpu_itimer) {
    printk("struct cpu_itimer {\n");
    printk("  expires: %llu\n", cpu_itimer->expires);
    printk("  incr: %llu\n", cpu_itimer->incr);
    printk("}");
}

SYSCALL_DEFINE3(cpu_itimer, struct cpu_itimer*, user_cpu_itimer, pid_t, pid, unsigned int, id) { // id = [0, 1]
// ITIMER_PROF|VIRTUAL
    struct cpu_itimer cpu_itimer;
    struct task_struct *process = NULL;

    printk("---- SYS_CPU_ITIMER ----\n");
        
    process = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
    if (id > 1) {
        printk("Invalid ITIMER type!\n");
        return -1;
    }
    
    cpu_itimer = process->signal->it[id];
    print_cpu_itimer_to_kernel(&cpu_itimer);
    
    return copy_to_user(user_cpu_itimer, &cpu_itimer,
				sizeof(struct cpu_itimer));
}

