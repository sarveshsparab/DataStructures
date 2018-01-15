//***********************************************
//*****<--- Start of program --->*****
//Sarvesh S. Parab
//12BT04CSE054
//DSPD-2 : Project :2
//***********************************************

// Assumptions taken under consideration:
// Using a B+ tree to implement database
// Branching factor is : 5
//***********************************************

//headers and constants
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define b_max 5

//***********************************************
//typedefs'
typedef struct employeeData
{
    char name[50];
    char addr[100];
    char desig[50];
    char phone[15];
    char empnum[10];
}empRec;
typedef struct treeType
{
    int key[b_max-1];
    struct treeType *next[b_max];
}treeNode;



















