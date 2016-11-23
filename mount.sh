#!/bin/bash
fusermount -u /home/dmjoshy/hmm
make
./mydisk /home/dmjoshy/hmm
cd ../hmm