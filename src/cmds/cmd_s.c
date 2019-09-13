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
  unsigned long l;
  switch(ci){
    case 'G':
        printf("%lu",p1+p2*65536);
        break;
    case 'H':
        printf("%li",p1+p2*65536);
        break;
    case 'I':
        printf("%i",p1);
        break;
    case 'J':
        printf("%u",p1);
        break;
    case 'K':
        l=time(NULL);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'R':
        srand(clock());
        l=(rand())%(p1+p2*65536);
        mem[m1]=(unsigned short)(l%(1<<16));
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'T':
        l=(mem[m1]+mem[m2]*65536)+(p1+p2*65536);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'U':
        l=(mem[m1]+mem[m2]*65536)-(p1+p2*65536);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'V':
        l=(mem[m1]+mem[m2]*65536)*(p1+p2*65536);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'W':
        l=(mem[m1]+mem[m2]*65536)/(p1+p2*65536);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'X':
        l=(mem[m1]+mem[m2]*65536)%(p1+p2*65536);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'Y':
        l=(mem[m1]+mem[m2]*65536)<<((p1+p2*65536)%32);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
    case 'Z':
        l=(mem[m1]+mem[m2]*65536)>>((p1+p2*65536)%32);
        mem[m1]=(unsigned short)(l%65536);
        mem[m2]=(unsigned short)(l>>16);
        break;
  }
}
