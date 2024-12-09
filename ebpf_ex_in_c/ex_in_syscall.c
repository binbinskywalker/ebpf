#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>
 
static int __attribute__((noinline)) my_function(int x) {
    printf("my_function called with argument: %d\n", x);
    return x * 2;
}
 
int main() {
    int result;
    pid_t pid = getpid();
 
    // Attach uprobe to my_function
    long ret = syscall(__NR_uprobe, "/path/to/my_binary", "my_function", 0);
 
    if (ret < 0) {
        perror("Failed to attach uprobe");
        exit(EXIT_FAILURE);
    }
 
    // Call my_function
    result = my_function(42);
    printf("Result: %d\n", result);
 
    return 0;
}
