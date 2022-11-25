#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct cpu_itimer {
    uint64_t expires;
    uint64_t incr;
};

int main(int argc, char** argv) {

    printf("----cpu_itimer syscall testing----\n");
    struct cpu_itimer itimer;
    pid_t pid = atoi(argv[1]);
    unsigned int itimer_type = atoi(argv[2]); // 0 or 1
    
    long int ret_code = syscall(549, &itimer, pid, itimer_type);
    printf("syscall ret code: %li\n", ret_code);
    printf("struct cpu_itimer {\n");
    printf("  expires: %ld\n", itimer.expires);
    printf("  incr: %ld\n", itimer.incr);
    printf("}\n");
    
    return 0;
}
