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

#ifndef HC_STDLIB
#define HC_STDLIB
#include <stdlib.h>
#endif

#ifndef HC_STDBOOL
#define HC_STDBOOL
#include <stdbool.h>
#endif

#ifndef H_DEFINES
#define H_DEFINES
#include "defines.h"
#endif

#ifndef H_GLOBALS
#define H_GLOBALS
#include "globals.h"
#endif

#ifndef H_HEXTOVAL
#define H_HEXTOVAL
#include "hextoval.h"
#endif

int cmds(unsigned char[INSIZE]);
unsigned int mval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned int pval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned int nextiw(unsigned char, unsigned char);
unsigned int findand(unsigned char, unsigned char);
unsigned int cmd_l(unsigned int, unsigned int, unsigned int);
unsigned int cmd_m(unsigned int, unsigned int, unsigned char);
void cmd_s(unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
