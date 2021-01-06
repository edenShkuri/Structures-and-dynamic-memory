#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_LETTERS 26

typedef struct node {
char letter;
char *word;
int count;
int end;
int childSize;
struct node* children[NUM_LETTERS];
} node;

struct node* newNode(char letter, char *newWord) 
{  
  struct node* node = (struct node*)malloc(sizeof(struct node));
  node->letter = letter;
  node->count = 0; 
  node->end=0;
  node->word=malloc(strlen(newWord));
  strcpy(node->word, newWord);
  node->childSize=0; 
  for(int i=0; i<NUM_LETTERS; i++)
    node->children[i]= NULL ;
  return(node); 
} 


void fillTree(node *root)
{
char let;
int i;
struct node *tmp=root;
while((let=fgetc(stdin))!=-1)
{
 i=1;
 if(let-0>=65 && let-0<=90) // change to lowercase
    let=let+32;
 else if(let==' ' || let=='\r' || let=='\n' || let=='\t' || let=='\0'){ //start a new word from the next char
   (tmp->count)++;
   if(tmp!=root){
   (tmp->end)=1;
   tmp=root;
   }
   i=0;
 }
 else if(let-0<97 || let-0>122)
  i=0;

 if(i==1)
 {
  if(tmp->children[let-97]==NULL){
     int len=strlen(tmp->word);
     char *newWord=malloc(len+2);
     strcpy(newWord, tmp->word);
     newWord[len]=let;
     newWord[len+1]='\0';
     tmp->children[let-97]=newNode(let,newWord);
     free(newWord);
     (tmp->childSize)++; 
   }
  tmp=tmp->children[let-97];
 } 
}
}

 
void Sort_down(node *curr)
{
  if(curr->childSize==0 && curr->end==1)
  {
    printf("%s %d\n", (curr->word), curr->count);
    free(curr->word);
    free(curr);
    return;
  } 
  for(int i=26; i>=0; i--){
    if(curr->children[i]!=NULL)
       Sort_down(curr->children[i]);
  }
   if(curr->end==1)
    printf("%s %d\n", (curr->word), curr->count);

   free(curr->word);
   free(curr);   
}

void Sort_up(node *curr)
{ 
  if(curr->childSize==0 && curr->end==1)
  {
    printf("%s %d\n", (curr->word), curr->count);
    free(curr->word);
    free(curr);
    return;
  } 
  if(curr->end==1)
    printf("%s %d\n", (curr->word), curr->count);
  for(int i=0; i<26; i++){
    if(curr->children[i]!=NULL)
      Sort_up(curr->children[i]);
  }
    free(curr->word);
    free(curr);
}

int main(int argc, char *argcv[])
{
  struct node *root = newNode('-',"");  
  fillTree(root);
  if(argc==1)
    Sort_up(root);
  else if(*argcv[1]=='r')
    Sort_down(root);


return 0;
}

