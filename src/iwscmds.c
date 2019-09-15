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

#include "iwscmds.h"

int iwscmds(unsigned char a[INSIZE]){
  int co,cr;
  unsigned short nsp;
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow.
        insub++;
        break;
    case 'N':
        if(sreccount >= ( SRECSIZE - 1 ) ) return 3;
        srec[++sreccount]=pmempos;
        nsp=pval(a[1],a[2],a[3],a[4],a[5]);
        submask[(insub+1)%SUBMASKSIZE]=nsp;
        if(subtable[nsp]!=0) pmempos=subtable[nsp];
        else{
            if(dbg==0) fprintf(stderr, "Non-existent sub.\n");
            while(1);
        }
        break;
    case 'O':
        co=cmd_o(a[1],pval(a[2],a[3],a[4],a[5],a[6]),pval(a[7],a[8],a[9],a[10],a[11]),a[12],a[13],a[14],a[15],a[16]);
        if(co > 0) return co;
        break;
    case 'R':
        cr=cmd_r(a[1],a[2],a[3],a[4],a[5]);
        if(cr > 0) return cr;
        break;
  }
  return 0;
}
