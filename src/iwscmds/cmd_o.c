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

#include "cmd_o.h"

int cmd_o(unsigned char a, unsigned short b, unsigned short c, unsigned char d, unsigned char e, unsigned char f){
  if(reccount >= ( RECSIZE - 1 ) ) return 3;
  rec[++reccount]=pmempos-15;
  switch(a){
    case 'e':
        if(b==c);
        else if(d=='w'){pmempos=nextwh(e,f); reccount--;}
        else if(d=='i') pmempos=nextif(e,f);
        else return 4;
        break;
    case 'g':
        if(b>c);
        else if(d=='w'){pmempos=nextwh(e,f); reccount--;}
        else if(d=='i') pmempos=nextif(e,f);
        else return 4;
        break;
    case 'l':
        if(b<c);
        else if(d=='w'){pmempos=nextwh(e,f); reccount--;}
        else if(d=='i') pmempos=nextif(e,f);
        else return 4;
        break;
    case 'n':
        if(b!=c);
        else if(d=='w'){pmempos=nextwh(e,f); reccount--;}
        else if(d=='i') pmempos=nextif(e,f);
        else return 4;
        break;
  }
  return 0;
}
