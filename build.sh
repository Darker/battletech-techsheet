#!/usr/bin/env bash

mkdir -p build
g++ -I include test/test_structure_manager.cpp -o build/test_structure_manager --std=c++17
