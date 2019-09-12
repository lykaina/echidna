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

#include "cmd_m.h"

unsigned short cmd_m(unsigned short va, unsigned short vb, unsigned short ia, unsigned short ib, unsigned short ic, unsigned short id)
{
    int i;
    unsigned short r=0;
    unsigned char t1=0,t2=0,ta=0,tb=0,tc=0,td=0;
    for(i=15;i>=0;i--){
        t1=(va>>i)%2;
        t2=(vb>>i)%2;
        ta=(ia>>i)%2;
        tb=(ib>>i)%2;
        tc=(ic>>i)%2;
        td=(id>>i)%2;
        r=r<<1;
        if((t1==0)&&(t2==0)) r+=ta;
        else if((t1==0)&&(t2==1)) r+=tb;
        else if((t1==1)&&(t2==0)) r+=tc;
        else if((t1==1)&&(t2==1)) r+=td;
        else r+=0;
    }
    return r;
}
