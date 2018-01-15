#include<stdio.h>
#include<string.h>

void pathCreate(char []);

main()
{
    char path[200];
    printf("enter: \n");
    scanf("%s",path);
    pathCreate(path);
    puts(path);
}
void pathCreate(char path[])
{
    char retPath[200];
    int i=0,j=0;
    if(strlen(path)!=0)
    {
        while(path[i]!='\0')
        {
            if(path[i]=='\\')
            {
                retPath[j]='\\';
                j++;
                retPath[j]='\\';
            }
            else
            {
                retPath[j]=path[i];
            }
            i++;
            j++;
        }
        retPath[j]='\0';
        strcpy(path,retPath);
    }
}
