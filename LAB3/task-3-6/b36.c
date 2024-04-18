#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    // Kiểm tra đầu vào
    if (argc != 2) {
        printf("Sử dụng: %s <số nguyên dương>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Số nguyên dương không hợp lệ.\n");
        return 1;
    }

    // Tạo hoặc mở buffer bộ nhớ chia sẻ
    int *buffer = mmap(0, BUFFER_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Fork một tiến trình con
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Tiến trình con
        printf("Child PID: %d\n", getpid());

        int index = 0;
        while (n != 1 && index < BUFFER_SIZE) {
            buffer[index++] = n;
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            sleep(1); // Mô phỏng sự trễ giữa các bước
            printf("Đang tính toán số thứ: %d, PID: %d\n", index, getpid());
        }
        buffer[index++] = 1;

        // Ghi -1 vào phần tử tiếp theo của buffer để thông báo kết thúc
        buffer[index] = -1;

        printf("Hoàn thành tính toán chuỗi\n");

        // Thoát tiến trình con
        exit(0);
    } else { // Tiến trình cha
        printf("Parent PID: %d\n", getpid());
        // Đợi tiến trình con kết thúc và lấy kết quả từ buffer
        wait(NULL);
        printf("Chuỗi kết quả: ");
        for (int i = 0; buffer[i] != -1; ++i) {
            printf("%d ", buffer[i]);
        }
        printf(", PID: %d", getpid());
        printf("\n");

        // Giải phóng buffer bộ nhớ chia sẻ
        munmap(buffer, BUFFER_SIZE * sizeof(int));
    }

    return 0;
}
