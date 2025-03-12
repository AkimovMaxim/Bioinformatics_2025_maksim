#!/bin/bash

for file in *.tsv; do

	dir_name="${file%.tsv}"

	mkdir -p "$dir_name"

	mv "$file" "$dir_name/"
done

echo "Files are organized"

