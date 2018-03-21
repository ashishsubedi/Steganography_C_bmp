#include<stdio.h>

struct emp
{
    char name[10];
    int age;
};

void main()
{
    struct emp e;
    FILE *p,*q;
    p = fopen("text.txt", "w");
    q = fopen("text.txt", "r");
    printf("Enter Name and Age:");
    scanf("%s %d", e.name, &e.age);
    fprintf(p,"%s %i", e.name, e.age);
    fclose(p);
    do
    {
        fscanf(q,"%s %d",e.name,&e.age);
        printf("%s %d", e.name, e.age);
    }  while(!feof(q));

}