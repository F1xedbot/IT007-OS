#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Kiểm tra số lượng đối số đầu vào
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct timeval start_time, end_time;

    // Lấy thời gian hiện tại trước khi thực thi lệnh shell
    gettimeofday(&start_time, NULL);

    // Tạo một tiến trình con để thực thi lệnh shell
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Không thể tạo tiến trình con\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Tiến trình con
        // Sử dụng hàm execl để thực thi lệnh shell
        execl("/bin/sh", "sh", "-c", argv[1], NULL);
        // Hàm execl chỉ trả về nếu có lỗi xảy ra
        fprintf(stderr, "Lệnh không thể thực thi\n");
        exit(EXIT_FAILURE);
    } else { // Tiến trình cha
        int status;
        // Chờ tiến trình con kết thúc
        wait(&status);

        // Lấy thời gian hiện tại sau khi thực thi lệnh shell
        gettimeofday(&end_time, NULL);

        // Tính toán thời gian thực thi
        double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                                (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

        // In ra thời gian thực thi
        printf("Thời gian thực thi: %.5f giây\n", execution_time);
    }

    return 0;
}
