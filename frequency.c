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
 if(let-0>=65 && let-0<=90) // if the tetter is uprecase change to lowercase
    let=let+32;
 else if(let==' ' || let=='\r' || let=='\n' ||
  let=='\t' || let=='\0'){ //start a new word from the next char(go back to the root)
   (tmp->count)++; //add 1 to the curr letter's node(end of the word)
   if(tmp!=root){ 
   (tmp->end)=1;
   tmp=root; \\go back to root
   }
   i=0; //mark the i so this letter doe's not get in to the tree 
 }
 else if(let-0<97 || let-0>122)
  i=0; //mark the i so this letter doe's not get in to the tree 

 if(i==1) //if the i does'n marked as 0 enter the letter to the tree
 {
  if(tmp->children[let-97]==NULL){//if this letter (in this place) does'nt exist already 
  //crate a new node
     int len=strlen(tmp->word);
     char *newWord=malloc(len+2); //make a new string (bigger +2 from the current word)
     strcpy(newWord, tmp->word); //copy the cuurr string of tmp node (the word in this place)
     newWord[len]=let; //add the curr char 
     newWord[len+1]='\0';
     tmp->children[let-97]=newNode(let,newWord); //make a new node with this letter and word
     free(newWord); //free this temp string that we use 
     (tmp->childSize)++; //rise the number of child of the curr node in 1
   }
  tmp=tmp->children[let-97];//promote the tmp to the next node (that we added now)
 } 
}
}

 
void Sort_down(node *curr)//print from z to a
{
  //if curr node there is no children and print his word, free his node and word and return
  if(curr->childSize==0 && curr->end==1) 
  {
    printf("%s %d\n", (curr->word), curr->count);
    free(curr->word);
    free(curr);
    return;
  } 
  for(int i=26; i>=0; i--){ //scan all the children of the curr node from the last(z) to first(a)
    if(curr->children[i]!=NULL) 
       Sort_down(curr->children[i]);//do this method on the next children
  }
   if(curr->end==1) //if the node is an end of a word print his word 
    printf("%s %d\n", (curr->word), curr->count);

   free(curr->word);//free the node (after we finish to scan his children)
   free(curr);   
}

void Sort_up(node *curr)//print from a to z
{ 
    //if curr node there is no children and print his word, free his node and word and return
  if(curr->childSize==0 && curr->end==1)
  {
    printf("%s %d\n", (curr->word), curr->count);
    free(curr->word);
    free(curr);
    return;
  } 
  if(curr->end==1) //if the node is an end of a word print his word 
    printf("%s %d\n", (curr->word), curr->count);
  for(int i=0; i<26; i++){ //scan all the children of the curr node from the first(a) to last(z)
    if(curr->children[i]!=NULL)
      Sort_up(curr->children[i]); //do this method on the next children
  }
    free(curr->word); //free the node (after we finish to scan his children)
    free(curr);
}

int main(int argc, char *argcv[])
{
  struct node *root = newNode('-',"");  
  fillTree(root); //fill the tree whith all the letters
  if(argc==1)
    Sort_up(root);
  else if(*argcv[1]=='r')
    Sort_down(root);


return 0;
}

