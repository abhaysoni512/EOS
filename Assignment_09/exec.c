#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void compile_file(char *file) {
    char *args[] = {"gcc", "-c", file, NULL}; 
    execv("/usr/bin/gcc", args);
    perror("exec() failed");
    _exit(1); // if execv fails, exit with error
}

void link_files() {
    char *args[] = {"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL}; 
    execv("/usr/bin/gcc", args);
    perror("exec() failed");
    _exit(1); // if execv fails, exit with error
}

void run_program() {
    char *args[] = {"./program.out", NULL}; 
    execv(args[0], args);
    perror("exec() failed");
    _exit(1); // if execv fails, exit with error
}

int main() {
    int ret, status;
    pid_t pids[5];

    printf("parent started!\n");

    // Compile circle.c
    if ((pids[0] = fork()) == 0) {
        compile_file("circle.c");
    }

    // Compile rectangle.c
    if ((pids[1] = fork()) == 0) {
        compile_file("rectangle.c");
    }

    // Compile square.c
    if ((pids[2] = fork()) == 0) {
        compile_file("square.c");
    }

    // Compile main.c
    if ((pids[3] = fork()) == 0) {
        compile_file("main.c");
    }

    // Parent process waits for each compilation child to complete
    for (int i = 0; i < 4; i++) {
        ret = waitpid(pids[i], &status, 0);
        if (ret == -1) {
            perror("waitpid() failed");
        } else if (WIFEXITED(status)) {
            printf("Compilation child with PID %d exited with status %d\n", pids[i], WEXITSTATUS(status));
        } else {
            printf("Compilation child with PID %d did not exit successfully\n", pids[i]);
        }
    }

    // Link files
    if ((pids[4] = fork()) == 0) {
        link_files();
    }

    // Wait for linking process to complete
    ret = waitpid(pids[4], &status, 0);
    if (ret == -1) {
        perror("waitpid() failed");
    } else if (WIFEXITED(status)) {
        printf("Linking child with PID %d exited with status %d\n", pids[4], WEXITSTATUS(status));
    } else {
        printf("Linking child with PID %d did not exit successfully\n", pids[4]);
    }

    // Run the program if linking was successful
    if (WEXITSTATUS(status) == 0) {
        pid_t run_pid;
        if ((run_pid = fork()) == 0) {
            run_program();
        }

        // Wait for the running program to complete
        ret = waitpid(run_pid, &status, 0);
        if (ret == -1) {
            perror("waitpid() failed");
        } else if (WIFEXITED(status)) {
            printf("Program run child with PID %d exited with status %d\n", run_pid, WEXITSTATUS(status));
        } else {
            printf("Program run child with PID %d did not exit successfully\n", run_pid);
        }
    }

    printf("parent completed!\n");
    return 0;
}