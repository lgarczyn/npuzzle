#!/bin/bash

make -C ..
EXE=../npuzzle

$EXE ./S-4-400-T1.txt | tail -n 7
$EXE ./S-4-400-T2.txt | tail -n 7
$EXE ./S-5-400-T3.txt | tail -n 8
$EXE ./S-5-400-T4.txt | tail -n 8
$EXE ./S-5-400-T5.txt | tail -n 8
$EXE ./S-6-2000-T6.txt | tail -n 9
$EXE ./S-7-2000-T7.txt | tail -n 10
