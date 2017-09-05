// CGitCack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define TEST test1

// Can we create a filename with a question mark in it?  Not with this approach, we consistently get err 22.
void test1()
{
    char *filename = "D:\\Hello\077World.txt";
    FILE *fp;
    int err = fopen_s(&fp, filename, "w");
    if (err)
    {
        printf("err=%d\n", err);
    }
    else
    {
        fprintf(fp, "Greetings earthling!\n");
        fclose(fp);
    }
}

int main()
{
    TEST();
    return 0;
}
