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

#include "nextif.h"

unsigned short nextif(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0,e=0;
    unsigned short p=pmempos;
    if(p >= progsize) while(1);
    b=pmem[p++];
    c=pmem[p++];
    d=pmem[p++];
    e=pmem[p++];
    while(!((b=='R')&&(c=='i')&&(d==l1)&&(e==l2))){
        if(p >= progsize) while(1);
        b=c;
        c=d;
        d=e;
        e=pmem[p++];
    }
    return (unsigned short)(p-3);
}
