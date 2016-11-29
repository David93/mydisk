#!/bin/bash
fusermount -u wow
make
./ramdisk wow 512 
