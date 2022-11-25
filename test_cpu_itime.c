#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {

    printf("----cpu_itimer syscall testing----\n");
    struct cpu_itimer itimer = { 0 };
    pid_t pid = atoi(argv[1]);
    unsigned int itimer_type = atoi(argv[2]); // 0 or 1
    
    long int ret_code = syscall(549, &dev, pid, itimer_type);
    printf("syscall ret code: %li\n", ret_code);
    printf("struct cpu_itimer {\n");
    printf("  expires: %d\n", itimer.vendor);
    printf("  incr: %d\n", itimer.device);
    printf("}\n");
    
    return 0;
}

