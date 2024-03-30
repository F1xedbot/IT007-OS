#!/bin/bash

create_user_directory() {
    echo "Nhập họ tên đầy đủ (không dấu)"
    read full_name
    directory_name=$(echo "$full_name" | tr '[:upper:]' '[:lower:]' | tr -d '[:punct:]' | tr -s ' ' | tr ' ' '_')
    mkdir -p "$directory_name"
    echo "Đã tạo thư mục '$directory_name'"
}

create_course_directories() {
    echo "Tạo các thư mục với mã môn tương ứng..."
    while IFS= read -r course_code; do
        mkdir -p "$directory_name/$course_code"
        echo "Đã thư mục cho mã môn $course_code"
    done < monhoc.txt
}

# Main script logic
create_user_directory
create_course_directories
echo "Process completed."
