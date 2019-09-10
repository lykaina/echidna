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

#ifndef H_MAIN
#define H_MAIN
#include "main.h"
#endif

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int i,j,r=0;
  if(argc < 2){
    fprintf(stderr,"A file name is required.\n");
    return 1;
  }
  else if(argc > 2){
    fprintf(stderr,"Too many arguments.\n");
    return 1;
  }
  for(i=0;i<MEMSIZE;i++) mem[i]=0;
  for(i=0;i<PROGMEMSIZE;i++) pmem[i]=0;
  for(i=0;i<RECSIZE;i++) rec[i]=0;
  //srand((unsigned int)(clock()%65536));
  reccount=0;
  for(i=0;i<SUBMASKSIZE;i++) submask[i]=0;
  insub=0;
  pmempos=0;
  progsize=0;
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
    pmempos=0;
    fseek(myFile, 0L, SEEK_END);
    filesize=ftell(myFile);
    rewind(myFile);
    while(progindex < filesize){
        wcount=0;
        fseek(myFile, progindex, SEEK_SET);
        if(progindex < filesize){
            w=(unsigned char)fgetc(myFile);
            while(((w==9)||(w==10)||(w==13)||(w==32))&&(progindex < filesize)){
                w=(unsigned char)fgetc(myFile);
            }
            pmem[pmempos++]=w;
        }
        if(pmempos >= PROGMEMSIZE) return 1;
        progindex=ftell(myFile);
        if(progindex > filesize) return 0;
    }
    fclose(myFile);
    progsize=pmempos;
    pmempos=0;
    while((pmempos < progsize) && (r==0)){
        for (i=0;i<INSIZE;i++) a[i]=0;
        if(pmempos < progsize){
            a[0]=pmem[pmempos++];
        }
        args=argnums[a[0]];
        if(args!=0){
          i=1;
          while((i<=args)&&(pmempos < progsize)){
              a[i]=pmem[pmempos++];
              i++;
          }
        }
        r=cmds(a);
    }
  }
  return 0;
}
