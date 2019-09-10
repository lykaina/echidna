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

#ifndef H_CMDS
#define H_CMDS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "defines.h"
#include "globals.h"
#include "hextoval.h"

int cmds(unsigned char[INSIZE]);
unsigned short mval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned short pval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned short nextiw(unsigned char, unsigned char);
unsigned short findand(unsigned char, unsigned char);
unsigned short cmd_l(unsigned short, unsigned short, unsigned short);
unsigned short cmd_m(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
void cmd_r(unsigned short, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void cmd_s(unsigned char, unsigned short, unsigned short);

#endif
