#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
  int data;;
  struct node *left;
  struct node *right;
}Node;


//Double pointer points at the structure
void insert(Node **rt, int num)
{
  Node *tmp;
  if(*rt==NULL)
    {
      tmp = (Node *) malloc(sizeof(Node));
      if(tmp==NULL)
	{
	  printf("Error");
	  exit(1);
	}
      // char *name = malloc(strlen(name)+1); 
      // strcpy(tmp->Employee,name);
      tmp->data=num;
      *rt=tmp;    
    }
  else
    {
      if(tmp->left==NULL)
	{
	  insert(&(*rt)->left,num);
	}
      if(tmp->right==NULL)
	{
	  insert(&(*rt)->right,num);
	}

    }
}
int main(char *argv[])
{
  char *name="test";
  printf("Please enter the employee name\n");
  //  fgets(name,20,stdin);
  //  printf("%s",name);
   Node *root=NULL;
  

  return 0;
}


