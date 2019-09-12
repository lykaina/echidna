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

#include "cmd_s.h"

void cmd_s(unsigned char ci, unsigned short m1, unsigned short m2, unsigned short p1, unsigned short p2)
{
  long r,t;
  switch(ci){
    case 'R':
        srand(clock());
        r=(rand())%(p1+p2*65536);
        mem[m1]=(unsigned short)(r%(1<<16));
        mem[m2]=(unsigned short)(r>>16);
        break;
    case 'T':
        t=time(NULL);
        mem[m1]=(unsigned short)(t%65536);
        mem[m2]=(unsigned short)(t/65536);
        break;
  }
}
