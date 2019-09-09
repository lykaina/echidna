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

#ifndef H_CMDS
#define H_CMDS
#include "cmds.h"
#endif

int cmds(unsigned char a[INSIZE]){
  int i;
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow. No Whitespace.
        insub++;
        break;
    case '-':
        if(reccount==0) return 3;
        if((a[1]=='S')&&(a[2]=='-')){
            insub--;
            pmempos=rec[reccount--];
        }
        else if(a[1]=='W') pmempos=rec[reccount--];
        else if(a[1]=='I') reccount--;
        else return 3;
        break;
    case 'G':
        printf("%u",pval(a[1],a[2],a[3],a[4],a[5]));
        break;
    case 'H':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=pval(a[6],a[7],a[8],a[9],a[10]);
        break;
    case 'I':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=getchar()%256;
        break;
    case 'J':
        putchar(pval(a[1],a[2],a[3],a[4],a[5]));
        break;
    case 'K':
        return 2;
        break;
    case 'L': // 1-bit bitwise
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=cmd_l(pval(a[6],a[7],a[8],a[9],a[10]),pval(a[11],a[12],a[13],a[14],a[15]),pval(a[16],a[17],a[18],a[19],a[20]));
        break;
    case 'M': // 2-bit bitwise
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=cmd_m(pval(a[6],a[7],a[8],a[9],a[10]),pval(a[11],a[12],a[13],a[14],a[15]),hextoval(a[16]));
        break;
    case 'N':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos;
        submask[(insub+1)%SUBMASKSIZE]=hextoval(a[1])*16+hextoval(a[2]);
        pmempos=findand(a[1],a[2]);
        break;
    case 'O':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])==pval(a[6],a[7],a[8],a[9],a[10]));
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'P':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])<pval(a[6],a[7],a[8],a[9],a[10]));
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'Q':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])!=pval(a[6],a[7],a[8],a[9],a[10]));
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'R':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=rand()%65536;
        break;
    case 'S':
        cmd_s(mval(a[1],a[2],a[3],a[4],a[5]),hextoval(a[6])*16+hextoval(a[7]),hextoval(a[8])*16+hextoval(a[9]),hextoval(a[10])*16+hextoval(a[11]),hextoval(a[12])*16+hextoval(a[13]),hextoval(a[14])*16+hextoval(a[15]),hextoval(a[16])*16+hextoval(a[17]),hextoval(a[18])*16+hextoval(a[19]),hextoval(a[20])*16+hextoval(a[21]));
        break;
    case 'T':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])+pval(a[11],a[12],a[13],a[14],a[15]))%65536;
        break;
    case 'U':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(65536+pval(a[6],a[7],a[8],a[9],a[10])-pval(a[11],a[12],a[13],a[14],a[15]))%65536;
        break;
    case 'V':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])*pval(a[11],a[12],a[13],a[14],a[15]))%65536;
        break;
    case 'W':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])/pval(a[11],a[12],a[13],a[14],a[15]))%65536;
        break;
    case 'X':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])%pval(a[11],a[12],a[13],a[14],a[15]))%65536;
        break;
    case 'Y':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])<<(pval(a[11],a[12],a[13],a[14],a[15])%16))%65536;
        break;
    case 'Z':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(pval(a[6],a[7],a[8],a[9],a[10])>>(pval(a[11],a[12],a[13],a[14],a[15])%16))%65536;
        break;
    default:
        return 2;
  }
  return 0;
}

unsigned int mval(unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
    unsigned int r=0;
    if(b=='!') r=mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)];
    else if(b=='@') r=(unsigned int)(hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f));
    else
    {
        fprintf(stderr,"ERROR: MVAL INPUT");
        while(1);
        r=0;
    }
    return r;
}


unsigned int pval(unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
    unsigned int r=0;
    if(b=='@') r=mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)];
    else if(b=='!') r=mem[mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)]];
    else if(b=='=') r=(unsigned int)(hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f));
    else
    {
        fprintf(stderr,"ERROR: PVAL INPUT");
        while(1);
        r=0;
    }
    return r;
}

unsigned int nextiw(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0;
    unsigned int p=pmempos;
    if(p >= progsize) while(1);
    b=pmem[p++];
    c=pmem[p++];
    d=pmem[p++];
    while(!((b=='-')&&(c==l1)&&(d==l2))){
        if(p >= progsize) while(1);
        b=c;
        c=d;
        d=pmem[p++];
    }
    return p-3;
}

unsigned int findand(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0;
    unsigned int p=0;
    if(p >= filesize) while(1);
    b=pmem[p++];
    c=pmem[p++];
    d=pmem[p++];
    while(!((b=='&')&&(c==l1)&&(d==l2))){
        if(p >= progsize) while(1);
        b=c;
        c=d;
        d=pmem[p++];
    }
    return p-3;
}

unsigned int cmd_l(unsigned int ia, unsigned int ib, unsigned int ic)
{
    int i;
    unsigned int r=0;
    unsigned char ta=0,tb=0,tc=0;
    for(i=15;i>=0;i--){
        ta=(ia>>i)%2;
        tb=(ib>>i)%2;
        tc=(ic>>i)%2;
        r=r<<1;
        r+=((ta==0)?tb:tc);
    }
    return r;
}

unsigned int cmd_m(unsigned int ia, unsigned int ib, unsigned char c)
{
    int i;
    unsigned int r=0;
    unsigned char ta=0,tb=0,c0,c1,c2,c3;
    c0=c%2;
    c1=(c>>1)%2;
    c2=(c>>2)%2;
    c3=(c>>3)%2;
    for(i=15;i>=0;i--){
        ta=(ia>>i)%2;
        tb=(ib>>i)%2;
        r=r<<1;
        r+=(ta==0)?((tb==0)?c0:c1):((tb==0)?c2:c3);
    }
    return r;
}

void cmd_s(unsigned int addr, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g, unsigned char h)
{
    mem[addr]=a;
    mem[(addr+1)%65536]=b;
    mem[(addr+2)%65536]=c;
    mem[(addr+3)%65536]=d;
    mem[(addr+4)%65536]=e;
    mem[(addr+5)%65536]=f;
    mem[(addr+6)%65536]=g;
    mem[(addr+7)%65536]=h;
}
