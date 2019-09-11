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
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)(getchar()%256);
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
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=cmd_m(pval(a[6],a[7],a[8],a[9],a[10]),pval(a[11],a[12],a[13],a[14],a[15]),pval(a[16],a[17],a[18],a[19],a[20]),pval(a[21],a[22],a[23],a[24],a[25]),pval(a[26],a[27],a[28],a[29],a[30]),pval(a[31],a[32],a[33],a[34],a[35]));
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
        else if(a[11]=='W') pmempos=nextiw(a[11],a[12])+3;
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'P':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])<pval(a[6],a[7],a[8],a[9],a[10]));
        else if(a[11]=='W') pmempos=nextiw(a[11],a[12])+3;
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'Q':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=pmempos-13;
        if(pval(a[1],a[2],a[3],a[4],a[5])!=pval(a[6],a[7],a[8],a[9],a[10]));
        else if(a[11]=='W') pmempos=nextiw(a[11],a[12])+3;
        else pmempos=nextiw(a[11],a[12]);
        break;
    case 'R':
        cmd_r(mval(a[1],a[2],a[3],a[4],a[5]),hextoval(a[6])*16+hextoval(a[7]),hextoval(a[8])*16+hextoval(a[9]),hextoval(a[10])*16+hextoval(a[11]),hextoval(a[12])*16+hextoval(a[13]),hextoval(a[14])*16+hextoval(a[15]),hextoval(a[16])*16+hextoval(a[17]),hextoval(a[18])*16+hextoval(a[19]),hextoval(a[20])*16+hextoval(a[21]));
        break;
    case 'S':
        cmd_s(a[1],mval(a[2],a[3],a[4],a[5],a[6]),mval(a[7],a[8],a[9],a[10],a[11]));
        break;
    case 'T':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])+pval(a[11],a[12],a[13],a[14],a[15]))%65536);
        break;
    case 'U':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((65536+pval(a[6],a[7],a[8],a[9],a[10])-pval(a[11],a[12],a[13],a[14],a[15]))%65536);
        break;
    case 'V':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])*pval(a[11],a[12],a[13],a[14],a[15]))%65536);
        break;
    case 'W':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])/pval(a[11],a[12],a[13],a[14],a[15]))%65536);
        break;
    case 'X':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])%pval(a[11],a[12],a[13],a[14],a[15]))%65536);
        break;
    case 'Y':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])<<(pval(a[11],a[12],a[13],a[14],a[15])%16))%65536);
        break;
    case 'Z':
        mem[mval(a[1],a[2],a[3],a[4],a[5])]=(unsigned short)((pval(a[6],a[7],a[8],a[9],a[10])>>(pval(a[11],a[12],a[13],a[14],a[15])%16))%65536);
        break;
    default:
        return 2;
  }
  return 0;
}

unsigned short mval(unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
    unsigned short r=0;
    if(b=='!') r=mem[hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f)];
    else if(b=='@') r=(unsigned short)(hextoval(c)*4096+hextoval(d)*256+hextoval(e)*16+hextoval(f));
    else
    {
        fprintf(stderr,"ERROR: MVAL INPUT");
        while(1);
        r=0;
    }
    return r;
}


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

unsigned short nextiw(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0;
    unsigned short p=pmempos;
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
    return (unsigned short)(p-3);
}

unsigned short findand(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0;
    unsigned short p=0;
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
    return (unsigned short)(p-3);
}

unsigned short cmd_l(unsigned short v, unsigned short ia, unsigned short ib)
{
    int i;
    unsigned short r=0;
    unsigned char t=0,ta=0,tb=0;
    for(i=15;i>=0;i--){
        t=(v>>i)%2;
        ta=(ia>>i)%2;
        tb=(ib>>i)%2;
        r=r<<1;
        r+=((t==0)?ta:tb);
    }
    return r;
}

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

void cmd_r(unsigned short addr, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g, unsigned char h)
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

void cmd_s(unsigned char ci, unsigned short a1, unsigned short a2)
{
  long t;
  switch(ci){
    case 'R':
        srand((unsigned int)(clock()%65536));
        mem[a1]=rand()%65536;
        mem[a2]=mem[a2];
        break;
    case 'T':
        t=time(NULL);
        mem[a1]=(unsigned short)(t%65536);
        mem[a2]=(unsigned short)(t/65536);
        break;
  }
}