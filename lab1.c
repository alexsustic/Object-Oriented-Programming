#include <stdio.h>
#include <string.h>
int main()
{   char x[20];
    scanf("%s",x);
    while(strcmp(x,"exit")!=0)
      { 
       printf("%s",x);
       printf("\n");
       scanf("%s",x); 
      }
    
    
    return 0;
}

