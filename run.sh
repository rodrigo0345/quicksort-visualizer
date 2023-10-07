#!/bin/bash

cd build

cmake ..
make

./gamefight $1
