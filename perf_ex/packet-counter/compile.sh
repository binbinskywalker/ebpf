#!/bin/bash
set -xe

clang -o2 -target bpf -c $1 -o $2
