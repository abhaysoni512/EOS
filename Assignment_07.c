#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childA, childB, childC, childD;
    int i;

    childA = fork();
    if (childA < 0) {
        // Error handling
        perror("fork");
        return 1;
    }

    if (childA == 0) {
        printf("Child A (PID: %d) is created\n", getpid());

        childB = fork();
        if (childB < 0) {
            // Error handling
            perror("fork");
            return 1;
        }

        if (childB == 0) {
            printf("Child B (PID: %d) is created\n", getpid());

            childC = fork();
            if (childC < 0) {
                // Error handling
                perror("fork");
                return 1;
            }

            if (childC == 0) {
                printf("Child C (PID: %d) is created\n", getpid());

                childD = fork();
                if (childD < 0) {
                    // Error handling
                    perror("fork");
                    return 1;
                }

                if (childD == 0) {
                    printf("Child D (PID: %d) is created\n", getpid());
                    sleep(5);
                    printf("Child D (PID: %d) terminated\n", getpid());
                    return 0;
                }
                sleep(5);
                printf("Child C (PID: %d) terminated\n", getpid());
                return 0;
            }
            sleep(5);
            printf("Child B (PID: %d) terminated\n", getpid());
            return 0;
        }
        sleep(5);
        printf("Child A (PID: %d) terminated\n", getpid());
        return 0;
    }

    // Parent process waits for all children
    for (i = 0; i < 4; i++) {
        wait(NULL);
    }
    
    printf("Parent (PID: %d) terminated\n", getpid());
    return 0;
}

