#!/bin/bash

# Student ID
my_mssv="22520007"

echo "Nhập tên của bạn:"
read name

while true; do
    echo "Nhập MSSV:"
    read mssv

    if [ "$mssv" = "$my_mssv" ]; then
        echo "Tên: $name"
        echo "MSSV: $mssv"
        echo "Trùng khớp!"
        break
    else
        echo "Không trùng khớp, vui lòng nhập lại."
    fi
done
