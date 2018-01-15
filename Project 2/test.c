#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
void pathCreate(char []);
void pathConvert(char []);
int main()
{
    char path[150];
    GetModuleFileName(NULL, path, sizeof(path));
    pathConvert(path);

    puts(path);
}

//Path creation function
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
//Path convert function
void pathConvert(char path[])
{
    int i,len=strlen(path);
    for(i=len;path[i]!='\\';i--)
    {
        path[i]='\0';
    }
    pathCreate(path);
}
