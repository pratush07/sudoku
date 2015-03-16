
#include <stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include<Windows.h>
#include<malloc.h>


// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0
 
// N is used for size of Sudoku grid. Size will be NxN
#define N 9
 
int big=0;

typedef struct user
{
	char name[30];
	int score;
	float time;
	user *next;
};
user *start1=NULL,*end;

user *createnode(char *name,float time,int score)
{
	user *ptr=(user*)malloc(sizeof(user));
	strcpy(ptr->name,name);
	ptr->time=time;
	ptr->score=score;
	ptr->next=NULL;
	return ptr;
}

void insert (user* np)
{
	if(start1==NULL)
		start1=end=np;
	else
	{
		end->next=np;
		end=end->next;
	}

}

void display()
{
	user *np=start1;

	while(np->next!=NULL)
	{
		printf("NAME: %s ",np->name);
		printf("TIME : %.2f ",np->time);
		printf("SCORE : %d",np->score);
		printf("\n");
		np=np->next;
	}
printf("\n");
}

void makenew(user *np)
{
	free(start1);
}

void findlargest()
{
	user *np=start1;
	while(np!=NULL)
	{
		if(np->score>big)
		big=np->score;
		np=np->next;
	}

}

user* givelargest()
{
	user *np=start1;
	while(np!=NULL)
	{
		if(np->score==big)
		return np;
		np=np->next;
	}

}

void intro()
{  int i;
   printf("SUDOKU\n");
   printf("IT IS GAME THAT TESTS YOUR FOCUS,STRENGTH AND DETERMINATION\n\n\n\n\n\n\n\n\n\n\n\n\n");
   printf("A project by: \nPratush Pandita\nNimish Uppal\nSarang Mittal\n");
   //for(i=0;i<1000000000;i++);
  getch();
}


void instruction()
{
printf("1.In this game u will be given a 9x9 matrix\n");
printf(".U will be given 9 boxes\n");
printf(".U have to fill numbers from 1 to 9 in 3x3 matrix\n");
printf("every row,coloumn & 3x3 subsection of the grid must contain one & only one of each digit \n");
printf("each sudoku puzzle has a unique solution that can be reached logically\n");
printf(".For each 3x3 box no number can repeat itself\n");
printf(".No number can repeat itself inside a coloumn\n");
printf(".No number can repeat itself inside a row\n");
printf(".After u fill all the boxes u will win the game\n");
printf(".U must try to finish the game in minimum time\n");
printf("enjoy the game\n");
}


// This function finds an entry in grid that is still unassigned
bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
 
// Checks whether it will be legal to assign num to the given row,col
bool isSafe(int grid[N][N], int row, int col, int num);
 
/* Takes a partially filled-in grid and attempts to assign values to
 
 all unassigned locations in such a way to meet the requirements
  for Sudoku solution (non-duplication across rows, columns, and boxes) */

bool SolveSudoku(int grid[N][N])
{
    int row, col;
 
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(grid, row, col))
       return true; // success!
 
    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // if looks promising
        if (isSafe(grid, row, col, num))
        {
            // make tentative assignment
            grid[row][col] = num;
 
            // return, if success!
 
			if (SolveSudoku(grid))
                return true;
 
            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}
 
/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}
 
/* Returns a boolean which indicates whether any assigned entry
   in the specified row matches the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a boolean which indicates whether any assigned entry
   in the specified column matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a boolean which indicates whether any assigned entry
   within the specified 3x3 box matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
bool isSafe(int grid[N][N], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}
 
/* A utility function to print grid  */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
		for (int col = 0; col < N; col++)
		{
			if(grid[row][col]==0)
			printf(" _ ");
			else
			printf(" %d ", grid[row][col]);	
		}
			printf("\n\n");
		
	}
}
 
void match(int grid[N][N],int puzzlegrid[N][N])
{
	int i,j,flag=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(grid[i][j]!=puzzlegrid[i][j])
			flag=1;
		}

	}

	if(flag==0)
	printf("congrats..you have solved it !!");
	else
	printf("wrong solution!!");
}

void start()
{	  // 0 means unassigned cells
    time_t first,second;
	int grid[N][N],puzzlegrid[9][9] ;
	int resi[23],resj[23],res=0;

	int numarr1[]={1,2,3,4,5,6,7,8,9};	//reference array

	int seedval,i,j,pos,total,count=1;
	int iran,jran,scorectr;
	int ipos,jpos,inum,flag=0;
	char ch,choice='y',subchoice;
	float timer;
	time_t t;
	
	first=time(NULL);		//time at start 
	FILE *fi;
	char name[20];
	int score=2000;
	user *temp;
	
	seedval= time(&t);
	srand(seedval);
	 total=8;
	for(i=total;i>=0;i--)
	{
		pos=rand() %(i+1);		//choosing random position in the reference array
		
		grid[0][i]=numarr1[pos];	//copying it in the main array (grid)
			for(j=pos;j<i;j++)
			numarr1[j]=numarr1[j+1];	//loop to remove it from the reference array numarr1
	}


	for(i=1;i<N;i++)		//assigning 0 to unassigned cells (grid)
	{   
		for(j=0;j<9;j++)
		grid[i][j]=0;
	}

	for (int row = 0; row < N; row++)	//assigning 0 to puzzle grid
    {
		for (int col = 0; col < N; col++)
		puzzlegrid[row][col]=0;
		
	}
 
	if (SolveSudoku(grid) == true)
	{
		while (count<=22)
		{
			iran=rand() %9;
			jran=rand() %9;
			puzzlegrid[iran][jran]=grid[iran][jran];
			resi[count]=iran;
			resj[count]=jran;
			++count;
		}
		printGrid(puzzlegrid);
	}
	else
	printf("No solution exists");

	
	while(choice=='y')		//loop to input values from the user 
{ 
	printf("enter the number and location in format(row,col,value)");
	scanf("%d %d %d",&inum,&ipos,&jpos);

	for(i=0;i<=22;i++)	//loop to find the restricted values of i and j in the puzzle grid
	{
		if(resi[i]==(ipos-1) && resj[i]==(jpos-1))
			{	res=1;
				break;
			}
	}
	if(res==1)
printf("not allowed");
				
			
	for(i=0;i<N;i++)	//loop to enter the user values in the puzzle grid
	{
		for(j=0;j<N;j++)
		{	
			if(ipos==i+1 && jpos==j+1 && res==0 )
			puzzlegrid[i][j]=inum;
		}
	}
	res=0;
	printf("\n");
	printGrid(puzzlegrid);
	printf("\ninput more values ??");
	fflush(stdin);
	scanf("%c",&choice);
}
	
for(i=0;i<N;i++)		//loop to check unassigned cells in puzzlegrid
{
	for(j=0;j<N;j++)
		{
			if(puzzlegrid[i][j]==0)
			flag=1;
			break;
		}
}

if(flag==0)
{
	printf("want to submit answer??");
	fflush(stdin);
	scanf("%c",&subchoice);
	if(subchoice=='y')
		match(grid,puzzlegrid);
	
	
	second=time(NULL);		//time at submission
	timer=difftime(second,first);
	scorectr=timer;
	while(scorectr>=0)
	{
		score=score-scorectr*10;
		--scorectr;
	}

	printf("time elapsed is %.2f ",timer);
	fi=fopen("usr.txt","a");
	printf("enter name ");
			scanf("%s",name);
			fprintf(fi,"%s %f %d",name,timer,score);
			fprintf(fi,"\n");
			fclose(fi);					
}

printf("want to see solution ??");
	fflush(stdin);
	scanf("%c",&ch);
	if(ch=='y')
	{
		printf("\n\n");
		printGrid(grid);
		
	}
	

	fi=fopen("usr.txt","r");
	while(!feof(fi))
	{   
			fscanf(fi,"%s %f %d",name,&timer,&score);
			temp=createnode(name,timer,score);
			insert(temp);
			
	}
findlargest();
temp=givelargest();
display();
printf("\nlargest score");
printf("\nNAME : %s \t TIME: %0.2f \t SCORE: %d",temp->name,temp->time,temp->score);

fclose(fi);


}
	



int main()
{
    // 0 means unassigned cells
int ch;
char c;
intro();
system("cls"); 

 printf("MENU\n1.NEW GAME\n2.INSTRUCTIONS\n3.EXIT\n\n\n");
 
do
 { 
	printf("Enter your choice\n");
	scanf("%d",&ch);
   
 switch(ch)
  {
    case 1: start();
			break;
    case 2: instruction();
     	    ch='y';
			break;
    
	case 3:  exit(0);
			break;
    default:
    printf("INVALID CHOICE\n");
  }
 printf("\nwant to enter again ?");
 fflush(stdin);
 scanf("%c",&ch);
 makenew(start1);
}while(ch=='y');
	
 getch();
 }