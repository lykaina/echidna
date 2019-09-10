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

#ifndef HC_STDIO
#define HC_STDIO
#include <stdio.h>
#endif

#ifndef H_DEFINES
#define H_DEFINES
#include "defines.h"
#endif

extern unsigned long progindex;
extern unsigned long filesize;
extern FILE *myFile;
extern unsigned short mem[MEMSIZE];
extern unsigned char pmem[PROGMEMSIZE];
extern unsigned int rec[RECSIZE];
extern unsigned char reccount;
extern unsigned char submask[SUBMASKSIZE];
extern unsigned char insub;
extern unsigned short pmempos;
extern unsigned short progsize;