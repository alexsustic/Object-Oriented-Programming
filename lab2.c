#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int array[256],index=0,initial_lenght=0,maximum_lenght=0,first_position,last_position;
    char input[10];
    scanf("%s",input);
    while (strcmp(input,"exit")!=0)
    {
     int value=atoi(input);
     array[index]=value;
     index=index+1;
     scanf("%s",input);
    }
    first_position=0;
    last_position=index-1;
    for(int i=0;i<index-1;i++)
    {
        int prime=1;
        int number=array[i+1]-array[i];
        if(number==0 || number==1)
            prime=0;
        else
            for(int k=2;k*k<=number;k++)
              if (number%k==0)
                 prime=0;
        if(prime==1)
        {
            initial_lenght++;

        }
        else
        {
            if(maximum_lenght<initial_lenght)
            {

                 maximum_lenght=initial_lenght;
                 last_position=i;
                 first_position=i-initial_lenght;
            }
            initial_lenght=0;
        }
    }
   for(int i=first_position;i<=last_position;i++)
     printf("%d " "",array[i]);
   return 0;
  }

