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

#include "mathcmds.h"

void mathcmds(unsigned char in, unsigned short a, unsigned short b, unsigned short c){
  switch(in){
    case 't':
        mem[a]=(unsigned short)((b+c)%65536);
        break;
    case 'u':
        mem[a]=(unsigned short)((65536+b-c)%65536);
        break;
    case 'v':
        mem[a]=(unsigned short)((b*c)%65536);
        break;
    case 'w':
        mem[a]=(unsigned short)((b/c)%65536);
        break;
    case 'x':
        mem[a]=(unsigned short)((b%c)%65536);
        break;
    case 'y':
        mem[a]=(unsigned short)((b<<(c%16))%65536);
        break;
    case 'z':
        mem[a]=(unsigned short)((b>>(c%16))%65536);
        break;
  }
}
