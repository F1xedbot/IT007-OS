#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Hàm xử lý tín hiệu SIGINT (Ctrl+C)
void sigint_handler(int signum) {
    printf("count.sh has stopped\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // In ra dòng chữ chào mừng
    printf("Welcome to IT007, I am <your_Student_ID>!\n");

    // Đăng ký hàm xử lý tín hiệu SIGINT
    signal(SIGINT, sigint_handler);

    // Thực thi file script count.sh
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Không thể tạo tiến trình con\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execl("./count.sh", "./count.sh", "120", NULL);
        fprintf(stderr, "Không thể thực thi count.sh\n");
        exit(EXIT_FAILURE);
    } else {
        // Chờ tiến trình con kết thúc hoặc bị ngắt bởi tín hiệu SIGINT
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
