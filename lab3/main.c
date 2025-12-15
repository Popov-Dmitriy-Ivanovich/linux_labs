#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

#define BUF_SIZE 64

int main() {
    int fd[2];
    char buf[BUF_SIZE];

    pipe(fd);

    pid_t pid = fork();

    if (pid > 0) {
        /* ===== Процесс 1 (родитель) ===== */
        close(fd[0]); // читающая сторона

        while (1) {
            ssize_t n = read(STDIN_FILENO, buf, BUF_SIZE - 1);
            if (n <= 0) break;

            buf[n - 1] = '\0'; // убрать '\n'
            write(fd[1], buf, strlen(buf) + 1);

            if (strcmp(buf, "exit") == 0)
                break;
        }

        close(fd[1]);
    } else {
        /* ===== Процесс 2 (дочерний) ===== */
        close(fd[1]); // пишущая сторона

        while (1) {
            ssize_t n = read(fd[0], buf, BUF_SIZE);
            if (n <= 0) break;

            if (strcmp(buf, "cpu") == 0) {
                long cpu = sysconf(_SC_NPROCESSORS_ONLN);
                dprintf(STDOUT_FILENO,
                        "CPU (logical cores): %ld\n", cpu);
            }
            else if (strcmp(buf, "mem") == 0) {
                struct sysinfo info;
                sysinfo(&info);
                long mem_mb = (info.totalram * info.mem_unit) / (1024 * 1024);

                dprintf(STDOUT_FILENO,
                        "MEM (total): %ld MB\n", mem_mb);
            }
            else if (strcmp(buf, "exit") == 0) {
                dprintf(STDOUT_FILENO, "Bye\n");
                break;
            }
            else {
                dprintf(STDOUT_FILENO, "Unknown command\n");
            }
        }

        close(fd[0]);
    }

    return 0;
}
