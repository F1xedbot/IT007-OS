#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ipc.h>

#define BUFFER_SIZE 10

int main() {
    const char *name = "bounded_buffer";
    const int SIZE = (BUFFER_SIZE + 1) * sizeof(int); // Increase buffer size by 1 to store stop signal

    // Create or open shared memory for the buffer
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Truncate shared memory to the desired size
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    int *buffer = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Initialize buffer
    for (int i = 0; i <= BUFFER_SIZE; ++i) {
        buffer[i] = 0;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process (Consumer)
        int total = 0;
        while (1) {
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                if (buffer[i] != 0) {
                    printf("Consuming: %d, PID: %d\n", buffer[i], getpid());
                    total += buffer[i];
                    buffer[i] = 0; // Reset the buffer after consuming
                    printf("Current sum = %d\n", total);
                    if (total > 100) {
                        printf("Consumner: Total sum is over 100. Stopping.\n");
                        // Write 1 to indicate to stop the process
                        buffer[BUFFER_SIZE] = 1;
                        exit(0);
                    }
                }
            }
        }
    } else { // Parent process (Producer)
        srand(time(NULL)); // Seed the random number generator
        printf("Parent PID: %d\n", getpid());
        while (1) {
            // Check if buffer is full
            int is_full = 1;
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                if (buffer[i] == 0) {
                    is_full = 0;
                    break;
                }
            }
            if (!is_full) {
                // Generate a random number between 10 and 20
                int num = rand() % 11 + 10;

                // Find an empty slot in the buffer and fill it
                for (int i = 0; i < BUFFER_SIZE; ++i) {
                    if (buffer[i] == 0) {
                        buffer[i] = num;
                        break;
                    }
                }
            }

            // Sleep for a short time before producing the next number
            usleep(1000000); // 1 second
            
            // Check if child process requested to stop
            if (buffer[BUFFER_SIZE] == 1) {
                printf("Producer: Consumer requested to stop. Stopping.\n");
                break;
            }
        }

        // Wait for the child process to terminate
        wait(NULL);

        // Clean up shared memory
        shm_unlink(name);
    }

    return 0;
}
