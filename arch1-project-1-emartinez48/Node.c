#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 80

typedef struct node
{
  char *Emp;
  struct node *left; 
  struct node *right;
}mynode;

void Menu()  //Below is a Menu Function which simply reads the options to the user
{
  printf("Hello what would you like to do???\n");
  printf("Press 1 to print the names of the employees\n");
  printf("Press 2 to add a person\n");
  printf("Press 3 to remove a person\n");
  printf("Press 4 to import from Getnames.txt\n");
  printf("Press 5 to export to list.txt\n");
  printf("Press q to exit\n");
}

void Deletenode(mynode **rt, char *Target)
{  //Copied most of my own insert method to run through a tree
 mynode *tmp;
 mynode *Parent;
 if(*rt==NULL)
     {
       return;
     }
   else
     {
       int comparison =strcmp(Target,(*rt)->Emp);
       if(comparison ==0)//We found the person we are deleting
	 {
	   printf("We found the person we are firing\n");
	   if( (*rt)->left==NULL && (*rt)->right==NULL)
	     { //Easy if there is no children just remove
	       free(*rt);
	       *rt=NULL;
	       return;
	     }
           else if( (*rt)->left==NULL && (*rt)->right!=NULL) 	  
	     {
	       printf("The left child is null");
	       return;
	     }
	   else if( (*rt)->right==NULL && (*rt)->left!=NULL) 	  
	     {
	       printf("The right child is null");
	       return;
	     }	
	 }
       else
	 { //Since we are looking through small tree I did not optimize
	   Deletenode(&(*rt)->left,Target);
	   Deletenode(&(*rt)->right,Target);
	 }       
     }
}

//To my understanding double pointer points to the BST
void insert(mynode **rt, char *Emp) 
{
  mynode *tmp; // Points at the current node
   if(*rt==NULL)
    {
      tmp=(mynode *) malloc(sizeof(mynode)); // Allocate for size of node
      tmp->Emp=malloc(strlen(Emp)+1); //Allocate for size of string
      strcpy(tmp->Emp,Emp); //You cant use equals for strings in c so I use str
      *rt=tmp;
    }
  else
    {
      int comparison = strcmp(Emp,(*rt)->Emp);
      //strcmp returns a int determining which Letter is bigger
      if(comparison<=0) //If the new string is smaller
        {             //Recursive call to insert
	  insert(&(*rt)->left,Emp);
	}
      if(comparison>0) //If larger
	{
	  insert(&(*rt)->right,Emp);
        }
    }
}

void printnodes(mynode *root)
{ //Simple print method that recursively calls itself
   if(root!=NULL)
    {
      //printing node in order
      printnodes(root->left);
      printf("%s\n",root->Emp);    
      printnodes(root->right);
    }
}

void export(FILE* fp, mynode* root)
{   //Same as print method however it writes instead of printing
    if(root!=NULL)
      {
	export(fp,root->left);
	fprintf(fp,root->Emp);
	fprintf(fp," ");
	export(fp,root->right);  
    }   
}

void import(FILE* fp, mynode* root,char * Get)
{  //I could not figure out a EOF so I used Lines variable to get a couple of
  //names
  int i=0;
  int Lines=5;
  while(Lines--)
    {
      fscanf(fp,"%s",Get);
      i++;
      insert(&root,&Get[0]);
    }
}

int main(int argc, char *argv[])
{ //Instansiating Variables
  char Getter[Max]; //Storing names we import
  mynode *root =NULL;
  char name[]="Eduardo"; //Inserting my name
  insert(&root,&name[0]);
  char aname[Max]; //Possible size of names set to 80
  char pick;       //Our menu options which are displayed below
  Menu();
  FILE *fp;       //Point to a file
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
       case'3':
	  printf("Who would you like to Delete??\n");
          scanf("%s",aname);
          fflush(stdout);
	  Deletenode(&root,&aname[0]);
	  Menu();
	 break;
       case'4':
	 fp = fopen("Getnames.txt","r");
	 import(fp,root,&Getter[0]);
	 fclose(fp);
	 Menu();
	 break;
       case'5':
        fp =fopen("list.txt", "w");
        export(fp,root);
        fclose(fp);
	Menu();
	 break;
       }
   }
   while(pick!='q');
  return 0;
}

  
