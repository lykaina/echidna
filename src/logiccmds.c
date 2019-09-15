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

#include "logiccmds.h"

int logiccmds(unsigned char a[INSIZE]){
  switch(a[0]){
    case 'L': // 1-bit bitwise
        //mem[mval(a[1],a[2],a[3],a[4],a[5])]=cmd_l(pval(a[6],a[7],a[8],a[9],a[10]),pval(a[11],a[12],a[13],a[14],a[15]),pval(a[16],a[17],a[18],a[19],a[20]));
        switch(a[1]){
            case 'a':
                mem[mval(a[2],a[3],a[4],a[5],a[6])]=pval(a[7],a[8],a[9],a[10],a[11]) & pval(a[12],a[13],a[14],a[15],a[16]);
                break;
            case 'n':
                mem[mval(a[2],a[3],a[4],a[5],a[6])]= ~pval(a[7],a[8],a[9],a[10],a[11]);
                break;
            case 'o':
                mem[mval(a[2],a[3],a[4],a[5],a[6])]=pval(a[7],a[8],a[9],a[10],a[11]) | pval(a[12],a[13],a[14],a[15],a[16]);
                break;
            case 'x':
                mem[mval(a[2],a[3],a[4],a[5],a[6])]=pval(a[7],a[8],a[9],a[10],a[11]) ^ pval(a[12],a[13],a[14],a[15],a[16]);
                break;
        }
        break;
/*    case 'M': // 2-bit bitwise
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=cmd_m(pval(a[6],a[7],a[8],a[9],a[10]),pval(a[11],a[12],a[13],a[14],a[15]),pval(a[16],a[17],a[18],a[19],a[20]),pval(a[21],a[22],a[23],a[24],a[25]),pval(a[26],a[27],a[28],a[29],a[30]),pval(a[31],a[32],a[33],a[34],a[35]));
        break; */
  }
  return 0;
}
