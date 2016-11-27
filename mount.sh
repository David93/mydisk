#!/bin/bash
fusermount -u hmm
make
./hello hmm
cd hmm
touch a b c
mkdir d