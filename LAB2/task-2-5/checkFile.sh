#!/bin/bash

echo "Nhập vào chuỗi cần kiểm tra:"
read string

# Kiểm tra xem tệp văn bản test.txt có tồn tại không
if [ -f "test.txt" ]; then
    # Kiểm tra xem chuỗi có tồn tại trong tệp văn bản hay không
    if grep -q "$string" "test.txt"; then
        echo "Chuỗi '$string' tồn tại trong tệp test.txt."
    else
        echo "Chuỗi '$string' không tồn tại trong tệp test.txt."
    fi
else
    echo "Tệp test.txt không tồn tại trong thư mục hiện tại."
fi
