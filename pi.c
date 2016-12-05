/*
 * Monte Carlo Simulation to estimate Pi
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int main(void)
{
 int nums[]={1E1, 1E2, 1E3, 1E4, 1E5};
 int len_nums=sizeof(nums)/sizeof(int);

 srand((unsigned) time(NULL));
 
 for (int j=0; j<len_nums; j++){
   int counter=0;
   for (int i=1; i<=nums[j]; i++){
     double rand_x=((double)rand()/(double)(RAND_MAX));
     double rand_y=((double)rand()/(double)(RAND_MAX));
     if ((pow(rand_x,2.0)+pow(rand_y,2.0))<=1)
       counter++;
   }  
   double pi=4.0*((double)counter/nums[j]);
   double error=(fabs(pi-M_PI)/M_PI)*100;
   printf("For N= %6d, Pi=%8.6f, error~%4.2f% \n", nums[j], pi, error);
 }
 
 return 0;
}
