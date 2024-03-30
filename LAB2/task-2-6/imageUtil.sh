#!/bin/bash

# Script execution location
user_dir="$(pwd)"
image_dir="$user_dir/OS_LAB2_IMG"
png_dir="$user_dir/PNG"
jpg_dir="$user_dir/JPG"

# Function to create directories if not exist
create_directories() {
    if [ ! -d "$1" ]; then
        mkdir -p "$1"
        echo "Created directory: $1"
    fi
}

# Function to move images and count them
move_images() {
    from_dir="$1"
    to_dir="$2"
    extension="$3"
    count=$(find "$from_dir" -maxdepth 1 -iname "*.$extension" | wc -l)
    if [ $count -gt 0 ]; then
        mv "$from_dir"/*.$extension "$to_dir"
        echo "Moved $count $extension images to $to_dir"
    fi
}

# Main script logic
echo "Checking for PNG and JPG directories..."
create_directories "$png_dir"
create_directories "$jpg_dir"

echo "Moving PNG images..."
move_images "$image_dir" "$png_dir" "png"

echo "Moving JPG images..."
move_images "$image_dir" "$jpg_dir" "jpg"

echo "Process completed."
