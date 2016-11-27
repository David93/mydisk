#!/bin/bash
fusermount -u ok
make
./hello ok
cd ok
touch a b c
mkdir d
cd d
touch b
mkdir kek
cd ..
rmdir d
