/*
 * Self-Avoiding Random Walk
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define ROWS 10
#define COLS 10

void initialize(char (*snake)[COLS], bool (*trace)[COLS+2], int *dim);
void move(int *ij, int d);

int main(void)
{
 char snake[ROWS][COLS]={'\0'};
 bool trace[ROWS+2][COLS+2]={false};
 int dim[]={ROWS, COLS};
 char ch='A';
 const int dir[5][3]={{0,0,0},
                      {4,1,2}, 
                      {1,2,3}, 
                      {2,3,4}, 
                      {3,4,1}};

 srand((unsigned) time(NULL));
 
 // initialize elements of matrix
 initialize(snake, trace, dim);

 int counter=0; // count loop run times
 int i=0, j=0; // the index of snake matrix, initial position (i,j)=(0,0)
 int l=0, m=0; // the index of trace matrix, initial position (l,m)=(1,1), since trace was expansin
 int d=(rand() % 2)+1; // the selection of direction
 while (counter< 26)
 {
  int pre_i=0, pre_j=0, next_d=0;
  int ij[2]={0,0}; // recording forward or backward for every step
  
  snake[i][j]=ch++;
  l=i+1; m=j+1;
  trace[l][m]=true;
  //full condition
  if (trace[l][m+1] && trace[l+1][m] && trace[l][m-1] && trace[l-1][m]) break;
  
  pre_i=i; pre_j=j; // recording previous position before next random walk
  next_d=dir[d][rand()%3]; // random walk

  // momement
  move(ij, next_d);
  i+=*(ij);
  j+=*(ij+1);
  
  // array boundary condition, do not beyound array size
  if (i<0 || i>ROWS-1 || j<0 || j>COLS-1){
    i=pre_i; j=pre_j;
    ch--;
    continue;
  }
  // self-avoiding
  else if (trace[i+1][j+1]){
    i=pre_i; j=pre_j;
    ch--;
    continue;
  }

  d=next_d;
  counter++;
 }
 
 // print on screen
 printf("Self-Avoiding Random Walk\n");
 for (int p=0; p<ROWS; p++){
   for (int q=0; q<COLS; q++){
     printf("%c ", snake[p][q]);
   }
   printf("\n");
 }
 printf("\n");
 
 printf("Trace Recording\n");
 for (int p=1; p<ROWS+1; p++){
   for (int q=1; q<COLS+1; q++){
     printf("%d ", trace[p][q]);
   }
   printf("\n");
 }
 printf("\n");

 printf("Terminal letter is %c\n", --ch);
 return 0;
}

void initialize(char (*snake)[COLS], bool (*trace)[COLS+2], int *dim)
{
 char *p_snake=NULL;
 // dim[]={ROWS, COLS}; 

 for(p_snake=&snake[0][0]; p_snake<&snake[dim[0]][dim[1]]; p_snake++)
   *p_snake='.';
 for(int k=0; k<dim[1]+2; k++){
  trace[0][k]=true;
  trace[dim[0]+1][k]=true;
  trace[k][0]=true;
  trace[k][dim[1]+1]=true;
 }
}

void move(int *ij, int d)
{
 /*
 *  case 1 (i,j+1)
 *  case 2 (i+1,j)
 *  case 3 (i,j-1)
 *  case 4 (i-1,j)
 */
 switch(d){
   case 1: ij[1]++; break;
   case 2: ij[0]++; break;
   case 3: ij[1]--; break;
   case 4: ij[0]--; break;
   default:         break;
 }
 return;
}
