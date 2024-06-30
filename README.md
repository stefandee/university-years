# University Years

An assortment of code and docs created while attending the Polytechnic University of Timisoara, between 1994-2000.

Code is a mix of Pascal, C, C++, Java, Lisp, assembler and others, mostly your run-of-the-mill lab works. There're also some papers and docs written for labs/courses, on a variety of topics (business, hardware, etc)

Also included is my dissertation paper, "Distributed Neural Network Training".

There's a few things of note, however.

## N2
This is the practical work accompanying the dissertation paper, [a server and a client](src/dissertation/W95) that can be used to distribute the training of a neural network across a network of computers.

It's very much WIP, but it should give an idea of how to approach the problem.

Lots of thanks for my late teacher, Sorin Babii (PhD), for the support.

## ALEX

It's a [full compiler suite](src/year-5/alex), with linker and virtual machine for a Pascal-like programming language.

Mostly to showcase the concepts of a compiler suite. It would require a lot of additional work to make it commercially viable.

If you want to test it, then:
* run ALEX.EXE on a source file (e.g. ALEX.EXE FOR.TXT) - this must be run in a MS-DOS environment;
* run bcb_asin.exe on the result of the above (e.g. ALEX.EXE FOR.LEX). This will generate the "binary" for the virtual machine;
* run mv.exe on the result of the above (e.g. MV.EXE out.kob). This will run the program.

## KAPA 

A [file archiever](src\year-3\kapa), implementing Huffman compression, done for lab work.