#!/bin/bash

while true; do
    echo "Nhập số n (n >= 10):"
    read n

    if [ "$n" -ge 10 ]; then
        break
    else
        echo "Số n phải lớn hơn hoặc bằng 10. Vui lòng nhập lại."
    fi
done

sum=0
for ((i = 1; i <= n; i++)); do
    sum=$((sum + i))
done

echo "Tổng các số từ 1 đến $n là: $sum"
