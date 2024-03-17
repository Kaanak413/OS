#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
pid_t child_pid;
child_pid = fork();
if (child_pid < 0) {
// Fork failed
  perror("Fork failed");
  return 1;
} else if (child_pid == 0) {
// Child process
  printf("Child process: My PID is %d\n", getpid());
  exit(0);//process dies
} else {
// Parent process
  printf("Parent process: My PID is %d\n", getpid());
  sleep(10);
}
return 0;
}