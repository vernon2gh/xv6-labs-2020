#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int if_primes(int primes)
{
    int i;

    for(i=2; i<primes; i++) {
        if(primes%i == 0)
            return 0;
    }

    return 1;
}

int main(int argc, char **argv)
{
    int pipefd[2];
    int pid;
    int i, tmp;

    pipe(pipefd);

    for(i=2; i <=35; i++) {
        if(if_primes(i)) {
            write(pipefd[1], &i, sizeof(i));

            pid = fork();
            if(pid == 0) { // the child process
                read(pipefd[0], &tmp, sizeof(tmp));
                printf("primes %d\n", tmp);
                break;
            }
            else {         // the parent process
                wait((int *)0);
            }
        }
    }

    exit(0);
}
