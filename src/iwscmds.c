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
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow.
        insub++;
        break;
/*    case '-':
        if(reccount==0) return 3;
        if(a[1]=='W') pmempos=rec[reccount--];
        else if(a[1]=='I') reccount--;
        else return 3;
        break; */
    case 'N':
        if(sreccount >= ( SRECSIZE - 1 ) ) return 3;
        srec[++sreccount]=pmempos;
        submask[(insub+1)%SUBMASKSIZE]=hextoval(a[1])*16+hextoval(a[2]);
        pmempos=findand(a[1],a[2]);
        break;
    case 'O':
        co=cmd_o(a[1],pval(a[2],a[3],a[4],a[5],a[6]),pval(a[7],a[8],a[9],a[10],a[11]),a[12],a[13],a[14]);
        if(co > 0) return co;
        break;
//        if(reccount >= ( RECSIZE - 1 ) ) return 3;
//        rec[++reccount]=pmempos-15;
//        if(pval(a[1],a[2],a[3],a[4],a[5])==pval(a[6],a[7],a[8],a[9],a[10]));
//        else if(a[11]=='w'){pmempos=nextwh(a[12],a[13]); reccount--;}
//        else if(a[11]=='i') pmempos=nextif(a[12],a[13]);
//        else return 4;
//        break;
//    case 'P':
//        if(pval(a[1],a[2],a[3],a[4],a[5])<pval(a[6],a[7],a[8],a[9],a[10]));
//    case 'Q':
//        if(pval(a[1],a[2],a[3],a[4],a[5])!=pval(a[6],a[7],a[8],a[9],a[10]));
    case 'R':
        cr=cmd_r(a[1],a[2],a[3]);
        if(cr > 0) return cr;
        break;
  }
  return 0;
}
