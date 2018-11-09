#include<stdio.h>
#include<stdlib.h>

#define N 1000
#define S 30

int makeDictionaly(char **, char *);
//void openReadFile(FILE *, char *);
//void openWriteFile(FILE *, char *);
void closeFile(FILE *);
int countWords(FILE *, char **);
void mallocDictionaly(char **);
void freeDictionaly(char **);
void printDictionaly(char **,int);
int comparison1(char, char);
int comparison2(char, char);
int strlen(char *);
void strcopy(char *, char *);
void strswp(char *, char *);
void sortDictionaly(char **, int);
void changeLow(char *);

int main(int argc, char *argv[]){
  char *dictionaly[N];
  int cnt;

  if(argc<2){
    printf("please input file\n");
    exit(1);
  }
  else cnt=makeDictionaly(dictionaly,argv[1]);

  printDictionaly(dictionaly, cnt);

  freeDictionaly(dictionaly);

  return 0;
}

int makeDictionaly(char *dictionaly[], char dicName[]){
  FILE *fp;
  int cntWords;

  //openReadFile(fp, dicName);

  if((fp=fopen(dicName,"r"))==NULL){
    fprintf(stderr,"File to open file\n");
  }
    
  mallocDictionaly(dictionaly);
  
  cntWords = countWords(fp, dictionaly);

  fclose(fp);

  sortDictionaly(dictionaly, cntWords);
  
  return cntWords;
}

/*
void openReadFile(FILE *fp, char dicName[]){
  if((fp=fopen(dicName,"r"))==NULL){
    fprintf(stderr,"File to open file\n");
  }
}
*/

/*
void openWriteFile(FILE *fp, char *dicName[]){
  if((fp=fopen(dicName,"a"))==NULL){
    fprintf(stderr,"File to open file\n");
  }
}
*/

int countWords(FILE *fp, char *dictionaly[]){
  int i=0;
  while(fscanf(fp,"%s",dictionaly[i])!=EOF)i++;
  return i;
}

void mallocDictionaly(char *dictionaly[]){
  int i;
  for(i=0; i<N; i++)dictionaly[i]=malloc(S);
}

void printDictionaly(char *dictionaly[], int cnt){
  int i;
  
  printf("dictionaly:\n");
  for(i=0;i<cnt;i++)printf("%s\n",dictionaly[i]);
}

void freeDictionaly(char *dictionaly[]){
  int i;
  for(i=0; i<N; i++)free(dictionaly[i]);
}

// if c1 < c2 is true, return 1
// A < a is true
// a < 1 is true
// 1 < ? is true
int comparison1(char c1, char c2){
  if(c1>='A'&&c1<='Z'){
    if(c2>='A'&&c2<='Z')return c1<=c2 ? 0 : 1;
    else return 0;
  }
  else if(c1>='a'&&c1<='z'){
    if(c2>='A'&&c2<='Z')return 1;
    else if(c2>='a'&&c2<='z')return c1<=c2 ? 0 : 1;
    else return 0;
  }
  else if(c1>='0'&&c1<='9'){
    if(c2>='A'&&c2<='Z')return 1;
    else if(c2>='a'&&c2<='z')return 1;
    else if(c2>='0'&&c2<='9')return c1<=c2 ? 0 : 1;
    else return 0;
  }
  else{
    if(c2>='A'&&c2<='Z')return 1;
    else if(c2>='a'&&c2<='z')return 1;
    else if(c2>='0'&&c2<='9')return 1;
    else return c1<=c2 ? 0 : 1;
  }
}

int comparison2(char c1, char c2){
  int diff = 'a'-'A';

  if(c1>='A'&&c1<='Z'){
    if(c2>='a'&&c2<='z'){
      c2-=diff;
      return c1<=c2 ? 0:1;
    }
    else if(c2>='A'&&c2<='Z')return c1<=c2 ? 0:1;
    else return 0;
  }

  if(c1>='a'&&c1<='z'){
    if(c2>='a'&&c2<='z')return c1<=c2 ? 0:1;
    else if(c2>='A'&&c2<='Z'){
      c1-=diff;
      return c1<=c2 ? 0:1;
    }
    else return 0;
  }
  
  else{
    if(c2>='A'&&c2<='Z')return 1;
    else if(c2>='a'&&c2<='z')return 1;
    else if(c2>='0'&&c2<='9')return 1;
    else return c1<=c2 ? 0 : 1;
  }
}


int strlen(char str[]){
  int i;
  for(i=0; str[i]!='\0'; i++);
  return i;
}

//str2 copy to str1.
void strcopy(char *str1, char str2[]){
  int str2len = strlen(str2),i;
  for(i=0; i<str2len; i++){
    str1[i]=str2[i];
  }str1[i]='\0';
}

void strswp(char *str1, char *str2){
  char buf[S];
  strcopy(buf,str1);
  strcopy(str1,str2);
  strcopy(str2,buf);
}

void sortDictionaly(char *dictionaly[],int cnt){
  int i,j,n;

  for(i=0; i<cnt; i++){
    changeLow(dictionaly[i]);
  }
  
  for(i=0; i<cnt; i++){
    for(j=0; j<cnt-1; j++){
      if(comparison2(dictionaly[j][0],dictionaly[j+1][0])){
	strswp(dictionaly[j],dictionaly[j+1]);
      }
    }
  }
}

void changeLow(char *str){
  int len = strlen(str),i;

  for(i=0; i<len; i++){
    if(str[i]>='A'&&str[i]<='Z'){
      str[i]+='a'-'A';
    }
  }
}
