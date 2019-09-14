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

#include "pval.h"

unsigned short pval(unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
    unsigned short r=0;
    if(b=='@') r=mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)];
    else if(b=='!') r=mem[mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)]];
    else if(b=='=') r=(unsigned short)(hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f));
    else
    {
        fprintf(stderr,"ERROR: PVAL INPUT");
        while(1);
        r=0;
    }
    return r;
}
