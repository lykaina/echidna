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
  //int i;
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow.
        insub++;
        break;
    case '-':
        if(reccount==0) return 3;
        if(a[1]=='W') pmempos=rec[reccount--];
        else if(a[1]=='I') reccount--;
        else return 3;
        break;
    case 'N':
        if(sreccount >= ( SRECSIZE - 1 ) ) return 3;
        srec[++sreccount]=pmempos;
        submask[(insub+1)%SUBMASKSIZE]=hextoval(a[1])*16+hextoval(a[2]);
        pmempos=findand(a[1],a[2]);
        break;
    case 'O':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])==pval(a[6],a[7],a[8],a[9],a[10]));
        else if(a[11]=='W'){pmempos=nextiw(a[11],a[12])+3;reccount--;}
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'P':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])<pval(a[6],a[7],a[8],a[9],a[10]));
        else if(a[11]=='W'){pmempos=nextiw(a[11],a[12])+3;reccount--;}
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'Q':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])!=pval(a[6],a[7],a[8],a[9],a[10]));
        else if(a[11]=='W'){pmempos=nextiw(a[11],a[12])+3;reccount--;}
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'R':
        insub--;
        pmempos=srec[sreccount--];
        break;
  }
  return 0;
}
