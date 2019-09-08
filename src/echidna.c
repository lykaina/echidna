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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MEMSIZE 65536
#define INSIZE 32
#define RECSIZE 256
#define SUBMASKSIZE 192

int cmds(unsigned char[INSIZE], unsigned int);
unsigned char readprog(unsigned long);
unsigned int mval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned int pval(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char hextoval(char);
unsigned long nextiw(unsigned char);
unsigned long findand(unsigned char, unsigned char);
unsigned int cmd_l(unsigned int, unsigned int, unsigned int);
unsigned int cmd_m(unsigned int, unsigned int, unsigned char);
void cmd_s(unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

unsigned long progindex;
unsigned long filesize;
FILE *myFile;
unsigned int mem[MEMSIZE];
unsigned int rec[RECSIZE];
unsigned char reccount;
unsigned char submask[SUBMASKSIZE];
unsigned char insub;

const unsigned char argnums[256] = {
/*    0 1 2 3 4 5 6 7 8 9 A B C D E F     */
/*0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*0*/
/*1*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*1*/
/*2*/ 0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0, /*2*/
/*3*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*3*/
/*4*/ 0,0,0,0,0,0,0,0,10,5,5,0,20,16,2,11, /*4*/
/*5*/ 11,11,5,21,15,15,15,15,15,15,15,0,0,0,0,1, /*5*/
/*6*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*6*/
/*7*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*7*/
/*8*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*8*/
/*9*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*9*/
/*A*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*A*/
/*B*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*B*/
/*C*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*C*/
/*D*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*D*/
/*E*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*E*/
/*F*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  /*F*/
/*    0 1 2 3 4 5 6 7 8 9 A B C D E F     */
};

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int i,r=0;
  if(argc < 2){
    fprintf(stderr,"A file name is required.\n");
    return 1;
  }
  else if(argc > 2){
    fprintf(stderr,"Too many arguments.\n");
    return 1;
  }
  for(i=0;i<MEMSIZE;i++) mem[i]=0;
  for(i=0;i<RECSIZE;i++) rec[i]=0;
  srand((unsigned int)(clock()%65536));
  reccount=0;
  for(i=0;i<SUBMASKSIZE;i++) submask[i]=0;
  insub=0;
  unsigned char a[INSIZE],args,w;
  unsigned int wcount;
  char *fMode = "rb";
  char *progname = argv[1];
  filesize=0;
  progindex=0;
  for (i=0;i<INSIZE;i++) a[i]=0;
  myFile = fopen(progname,fMode);
  if(myFile==NULL){
    fprintf(stderr,"Invalid or Nonexistent File Name.\n");
    return 1;
  }
  else{
    fseek(myFile, 0L, SEEK_END);
    filesize=ftell(myFile);
    rewind(myFile);
    while((progindex < filesize) && (r==0)){
        wcount=0;
        for (i=0;i<INSIZE;i++) a[i]=0;
        fseek(myFile, progindex, SEEK_SET);
        if(progindex < filesize){
            w=(unsigned char)fgetc(myFile);
            while((w==9)||(w==10)||(w==13)||(w==32)) w=(unsigned char)fgetc(myFile);
            a[0]=w;
        }
        args=argnums[a[0]];
        progindex=ftell(myFile);
        if(args!=0){
          i=1;
          while((i<=args)&&(progindex < filesize)){
              w=(unsigned char)fgetc(myFile);
              while((w==9)||(w==10)||(w==13)||(w==32)) {w=(unsigned char)fgetc(myFile); wcount++;}
              a[i]=w;
              i++;
              progindex=ftell(myFile);
          }
        }
        if(progindex > filesize) return 0;
        r=cmds(a,wcount);
        if(progindex == filesize) return 0;
    }
    fclose(myFile);
  }
  return 0;
}

int cmds(unsigned char a[INSIZE], unsigned int wcount){
  int i;
  switch(a[0]){
    case '&': //Used to start a subroutine. Two hex follow. No Whitespace.
        insub++;
        break;
    case '-':
        if(reccount==0) return 3;
        else progindex=rec[reccount--];
        if(readprog(progindex)=='-') insub--;
        break;
    case '_':
        if(reccount==0) return 3;
        else reccount--;
        break;
    case 'G':
        //return 2;
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
        rec[++reccount]=progindex;
        submask[(insub+1)%SUBMASKSIZE]=hextoval(a[1])*16+hextoval(a[2]);
        progindex=findand(a[1],a[2]);
        break;
    case 'O':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=progindex-12-wcount;
        if(pval(a[1],a[2],a[3],a[4],a[5])==pval(a[6],a[7],a[8],a[9],a[10]));
        else progindex=nextiw(a[11]);
        break;
    case 'P':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=progindex-12-wcount;
        if(pval(a[1],a[2],a[3],a[4],a[5])<pval(a[6],a[7],a[8],a[9],a[10]));
        else progindex=nextiw(a[11]);
        break;
    case 'Q':
        if(reccount >= ( RECSIZE - 1 ) ) return 3;
        rec[++reccount]=progindex-12-wcount;
        if(pval(a[1],a[2],a[3],a[4],a[5])!=pval(a[6],a[7],a[8],a[9],a[10]));
        else progindex=nextiw(a[11]);
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

unsigned char readprog(unsigned long bytepos)
{
  unsigned char u;
  if(bytepos >= filesize) while(1);
  fseek(myFile, bytepos, SEEK_SET);
  u=(unsigned char)fgetc(myFile);
  fseek(myFile, progindex, SEEK_SET);
  return u;
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

unsigned char hextoval(char in)
{
    if((in>='0')&&(in<='9')) return in-'0';
    else if((in>='A')&&(in<='F')) return in+10-'A';
    else if((in>='a')&&(in<='f')) return in+10-'a';
    else return 0;
}

unsigned long nextiw(unsigned char label)
{
    unsigned char b=0,c=0;
    unsigned long p=progindex;
    while(!(((b=='-')||(b=='_'))&&(c==label))){
        b=readprog(p++);
        c=readprog(p);
    }
    return p-1;
}

unsigned long findand(unsigned char l1, unsigned char l2)
{
    unsigned char b=0,c=0,d=0,e=0,f=0;
    unsigned long p=0;
    while(!((b=='&')&&(c==l1)&&(d==l2))){
        b=readprog(p++);
        c=readprog(p);
        d=readprog(p+1);
    }
    return p-1;
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
