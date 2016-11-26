#!/bin/bash
fusermount -u hmm
make
./mydisk hmm
cd hmm