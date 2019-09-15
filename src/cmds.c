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

#include "cmds.h"

int cmds(unsigned char a[INSIZE]){
  int iws=0,lc=0;
  int di;
  if(dbg==1) for(di=0;di < INSIZE;di++) fputc(a[di],stderr);
  if(dbg==1) for(di=0;di<DEBUGSIZE;di++){fputc(mem[di]%256,stderr); fputc((mem[di]>>8)%256,stderr);}
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow.
        iws=iwscmds(a);
        if(iws > 0) return iws;
        break;
    case 'G':
        cmd_g(mval(a[1],a[2],a[3],a[4],a[5]),hextoval(a[6])*16+hextoval(a[7]),hextoval(a[8])*16+hextoval(a[9]),hextoval(a[10])*16+hextoval(a[11]),hextoval(a[12])*16+hextoval(a[13]),hextoval(a[14])*16+hextoval(a[15]),hextoval(a[16])*16+hextoval(a[17]),hextoval(a[18])*16+hextoval(a[19]),hextoval(a[20])*16+hextoval(a[21]));
        break;
    case 'H':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=pval(a[6],a[7],a[8],a[9],a[10]);
        break;
    case 'I':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)(getchar()%256);
        break;
    case 'J':
        putchar(pval(a[1],a[2],a[3],a[4],a[5]));
        break;
    case 'K':
        return 2;
        break;
    case 'L':
        lc=logiccmds(a);
        if(lc > 0) return lc;
        break;
    case 'M':
        mathcmds(a[1],mval(a[2],a[3],a[4],a[5],a[6]),pval(a[7],a[8],a[9],a[10],a[11]),pval(a[12],a[13],a[14],a[15],a[16]));
        break;
    case 'N':
    case 'O':
        iws=iwscmds(a);
        if(iws > 0) return iws;
        break;
    case 'P':
        break;
    case 'Q':
        break;
    case 'R':
        iws=iwscmds(a);
        if(iws > 0) return iws;
        break;
    case 'S':
        cmd_s(a[1],mval(a[2],a[3],a[4],a[5],a[6]),mval(a[7],a[8],a[9],a[10],a[11]),pval(a[12],a[13],a[14],a[15],a[16]),pval(a[17],a[18],a[19],a[20],a[21]));
        break;
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        break;
    default:
        return 2;
  }
  return 0;
}
