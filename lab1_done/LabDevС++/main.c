#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
void Push(FILE *stack, int *Size, char *buffer);
void Top (int *Size, char *buffer);
char Pop (FILE *stack, int *Size, char *buffer);
void IsEmpty(int *Size);
//functions: Push, Pop, IsEmpty, Top
 
int main()
{
  FILE *stack = fopen( "Tdraft.txt" , "r+" );
 
  if (stack == NULL)
  {
      puts("Can't open file");
      return 0;
  }
 
  fseek(stack , 0 , SEEK_END);                          
  int Size = ftell(stack);                          
  rewind (stack);                                       
 
  char *buffer = (char*) malloc(sizeof(char) * Size); 
  //fread(buffer, 1, Size, stack);
  fgets(buffer, Size+1, stack);
  rewind(stack);
  printf("Original string: %s\n", buffer);
  
  int choice;
  char q;
  do
  {
  	printf ("Choose right function:\n 1-Push\n  2-Top\n   3-IsEmpty\n    4-Pop\nChoice: ");
  	scanf("%d", &choice);
	  switch(choice)
	  {
	  	case 1:{
	  		Push(stack, &Size, buffer);
			break;
		  }
	  		
		case 2:{
			Top(&Size, buffer);
			break;
		}

		case 3:{
			IsEmpty(&Size);
			break;
		}
		
		case 4: {
			Pop(stack, &Size, buffer);
			break;
		}
	  }
	printf("\nContinue? y/n: ");
	scanf("%s", &q);
  }while (q!='n');
 
 
  fclose (stack);
  //free (buffer);
  return 0;
}


void Push(FILE *stack, int *Size, char *buffer)
{
	char word[15];
	printf("Type word: ");
	scanf("%s", word);
//	printf("%s", word);
	*Size+=strlen(word);
	char buf[*Size+strlen(word)];
	word[strlen(word)]=' ';
	word[strlen(word)+1]='\0';
	strcpy(buf, word);
	strcat(buf, buffer);

//	buffer = (char*) realloc(&buffer,sizeof(char) *(*Size));
	puts(buf);
	rewind(stack);
	fwrite(buf, 1, sizeof(buf), stack);
	//fputs(buf, stack);
	ftell(stack);
	return;
}


void Top (int *Size, char *buffer)
{
	int i;
	char buf[*Size];
	for (i=0; i<*Size; i++)
	{
		if ((buffer[i]!=' ') && (buffer[i]!='.') && (buffer[i]!=','))
		buf[i]=buffer[i];
		else 
		{
			buf[i]='\0';
			break;
		}
	}
	puts(buf);
	return;
}


char Pop (FILE *stack, int *Size, char *buffer)
{
	int i,j;
	char buf[*Size];
  	fgets(buffer, (*Size)+1, stack);
  	rewind(stack);
	for (i=0; i<*Size; i++)
	{
		if ((buffer[i]!=' ') && (buffer[i]!='.') && (buffer[i]!=','))
		buf[i]=buffer[i];
		else 
		{
			buf[i]='\0';
			break;
		}
	}
	for (j=i;j<(*Size-strlen(buf)+1); j++)
	{
		buffer[j-i]=buffer[j+1];
	}
	rewind(stack);
	fwrite(buf, 1, sizeof(buf), stack);
	puts(buf);
	puts(buffer);
	return *buf;
}

void IsEmpty(int *Size)
{
	if (*Size==0)
	puts("Stack is empty!");
	else
	puts("There's sth in it.'");
	return;
}


