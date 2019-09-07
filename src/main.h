/* Copyright (C) 2019 Sara Berman.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MEMSIZE 65536
#define INSIZE 32
#define RECSIZE 128
#define SUBMASKSIZE 64

unsigned long progindex;
unsigned long filesize;
FILE *myFile;
unsigned int mem[MEMSIZE];
unsigned int rec[RECSIZE];
unsigned char reccount;
unsigned char submask[SUBMASKSIZE];
unsigned char insub;

const unsigned char argnums[256] = {
/*    0 1 2 3 4 5 6 7 8 9 A B C D E F     */
/*0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*0*/
/*1*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*1*/
/*2*/ 0,0,0,0,0,0,4,0,0,0,0,0,0,1,0,0, /*2*/
/*3*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*3*/
/*4*/ 0,0,0,0,0,0,0,0,10,5,5,0,20,16,6,11, /*4*/
/*5*/ 11,11,5,15,15,15,15,15,15,15,15,0,0,0,0,1, /*5*/
/*6*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*6*/
/*7*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*7*/
/*8*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*8*/
/*9*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*9*/
/*A*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*A*/
/*B*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*B*/
/*C*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*C*/
/*D*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*D*/
/*E*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*E*/
/*F*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  /*F*/
/*    0 1 2 3 4 5 6 7 8 9 A B C D E F     */
};

int cmds(unsigned char[INSIZE], unsigned int);
unsigned char readprog(unsigned long);
unsigned int mval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned int pval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char hextoval(char);
unsigned long nextiw(unsigned char);
unsigned long findand(unsigned char, unsigned char, unsigned char, unsigned char);
unsigned int cmd_l(unsigned int, unsigned int, unsigned int);
unsigned int cmd_m(unsigned int, unsigned int, unsigned char);
