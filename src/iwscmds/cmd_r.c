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

#include "cmd_r.h"

int cmd_r(unsigned char a, unsigned char b, unsigned char c){
  switch(a){
    case 'i': //endif
        if(reccount==0) return 3;
        reccount--;
        break;
    case 'k': //endwhileif
        if(reccount==0) return 3;
        pmempos=rec[reccount--];
        reccount--;
        break;
    case 'q': //endsubwhileif
        if(reccount==0) return 3;
        if(sreccount==0) return 3;
        insub--;
        pmempos=srec[sreccount--];
        reccount--;
        reccount--;
        break;
    case 'r': //endsubif
        if(reccount==0) return 3;
        if(sreccount==0) return 3;
        insub--;
        pmempos=srec[sreccount--];
        reccount--;
        break;
    case 's': //endsub
        if(sreccount==0) return 3;
        insub--;
        pmempos=srec[sreccount--];
        break;
    case 'w': //endwhile
        if(reccount==0) return 3;
        pmempos=rec[reccount--];
        break;
  }
  return 0;
}
