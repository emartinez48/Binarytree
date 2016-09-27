y#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Max 80

typedef struct node
{
  char *Emp;
  struct node *left; 
  struct node *right;
}mynode;

void Menu()
{
  printf("Hello what would you like to do???\n");
  printf("Press 1 to print the names of the employees\n");
  printf("Press 2 to add a person\n");
  printf("Press 3 to remove a person\n");
  printf("Press 4 to import a text file\n");
  printf("Press 5 to export to names.txt\n");
  printf("Press q to exit\n");
}

void Deletenode(mynode *root, char *Target)
{   //Base case
    if(root==NULL)
    {
      return;
    }
    else
    {
      int compare = strcmp(Target,root->Emp);
      if(compare==1)
      {
      printf("He does work here");
      return;
      }
      //Searching inefficent
      Deletenode(root->left,Target);
      Deletenode(root->right,Target);
    }  
}


void insert(mynode **rt, char *Emp)
{
  mynode *tmp;
   if(*rt==NULL)
    {
      tmp=(mynode *) malloc(sizeof(mynode));
      tmp->Emp=malloc(strlen(Emp)+1);
      strcpy(tmp->Emp,Emp);
      *rt=tmp;
    }
  else
    {
      int comparison = strcmp(Emp,(*rt)->Emp);
        if(comparison<=0)
	{
	  insert(&(*rt)->left,Emp);
	}
	if(comparison>0)
	{
	  insert(&(*rt)->right,Emp);
        }
    }
}

void printnodes(mynode *root)
{
   if(root!=NULL)
    {
      //printing node in order
      printnodes(root->left);
      printf("%s\n",root->Emp);
      printnodes(root->right);
    }
}

void export(mynode *root)
{
  FILE *fp;  
  fp =fopen("nombres.txt", "w");
  if(root==NULL)
    {
      printf("We got to the bottom of a list");
    }
  else
    {      
      export(root->left);
      fprintf(fp,root->Emp);
      printf("%s\n",root->Emp);     
      export(root->right);
    }
    fclose(fp);
}


int main(int argc, char *argv[])
{
  mynode *root =NULL;
  char name[]="Eduardo Martinez";
  insert(&root,&name[0]);
  char names[]="Enrique Martinez";
  insert(&root,&names[0]);
  char aname[Max];
  char pick;  

  
  printnodes(root);
  Menu();
 do
   {
     scanf("%c",&pick);
     fflush(stdout);
     switch(pick)
       {
       case'1':
	 printnodes(root);
	 Menu();
	   break;
       case'2':
	  printf("Who would you like to add??\n");
          scanf("%s",aname);
          fflush(stdout);
         insert(&root,&aname[0]);
	 Menu(); 
	 break;
       case'5':
	 printf("We started the export\n");
	 export(root);
	 printf("We finished the export\n");
	 break;
       }
   }
   while(pick!='q');
  
  return 0;
}

  
