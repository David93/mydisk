#!/bin/bash
fusermount -u hmm
make
./hello hmm
cd hmm
echo "LOL" > a