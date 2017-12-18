// CGitCack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#define TEST test3

// Testing assignment to const variations (compile-only)
void test3()
{
    const char *kings1[] = { "Antigonus", "Seleucus", "Ptolemy" };
    // kings1[0][0] = 'B'; // error C3892: 'kings': you cannot assign to a variable that is const
    kings1[1] = "Bob";

    char const *kings2[] = { "Antigonus", "Seleucus", "Ptolemy" };
    // kings2[0][0] = 'B'; // error C3892 : 'kings2' : you cannot assign to a variable that is const
    kings2[1] = "Bob";

    char * const kings3[] = { "Antigonus", "Seleucus", "Ptolemy" };
    kings3[0][0] = 'B';
    // kings3[1] = "Bob"; // error C3892: 'kings3': you cannot assign to a variable that is const

    const int x1 = 1;
    int const x2 = 2;
    // x1 = 5; // C3892
    // x2 = 5; // C3892

    int y = 1, z = 2;
    const int *py1 = &y;
    int const *py2 = &y;
    int * const py3 = &y;
    py1 = &z;
    py2 = &z;
    // py3 = &z; // c3892

    // *py1 = 5; // c3892
    // *py2 = 5; // c3892
    *py3 = 5;
}

// Obfuscated Fibonacci generator

// 1-9: print that number of characters
// C print ": "
// F fgets
// A max(n3)=atoi(buf)
// P: print: 1=%d%d n0 n1; 2=%d n2
// S: subtract from max
// G: get next in sequence
// D: decrease max(n3) and bailout if zero
char *Ctrl = " 05foufs6ovncfs2pg5ufsntCFARP1S2GP2D";

void fibonacci2()
{
    int n0 = printf("Welcome to Dave's Fibonacci generator\n") / (int)
        "comment: print greeting", n1
        = printf("-------------------------------------\n")
        * 0 - +-1;int n2 = 3.1415926 / 2.718281 + 365.25;
    int n3;
    char n4[' '];
    int n5 = 0;
    char *ctrl = Ctrl;

    while (*ctrl) {
        switch (n5) {
        case 0: {switch (*ctrl) {
            case
                'S':ctrl++;n3 -= *ctrl - '0';break;case 'D':n3--;if (n3)
                ctrl -= 4;break;case 'G':n2 = n0;n0 = n1;n1 += n2;break;case
                'P':n5 = 2;break;case 'R':if (n3<3)ctrl = Ctrl + 1;break;
                case 'A':n3 = atoi(n4);break;case 'F':fgets(n4, ' ' - 2,
                    stdin);case 'C':putchar(':');putchar(' ');break;
                    default:if (*ctrl >= '2' && *ctrl <= '6') {
                        n5 = 1;n3 = *ctrl
                            - Ctrl[1];
                    }break;
        }}break;case 1: {putchar(*ctrl - 1);n3--;
        if (!n3) { putchar(32);n5 = 0; }break;}case 2: {if (*ctrl ==
            '1')printf("%d ", n0);printf("%d ", n1);n5 = 0;break;}
        }
        ctrl++;
    }printf("\n");
}

void fibonacci()
{
    int n0 = printf("Welcome to Dave's Fibonacci generator\n") / (int)"comment: print greeting";
    int n1 = printf("-------------------------------------\n") * 0 - -1;
    int n2 = 3.1415926 / 2.718281 + 365.25;
    int n3;
    char n4[' '];
    char n4a[' '];
    int n5 = 0;
    char *ctrl = Ctrl;
    while (*ctrl)
    {
        switch (n5)
        {
        case 0:
        {
            switch (*ctrl)
            {
            case 'S':
                ctrl++;
                // printf("S:sub %d from n3(%d)\n",*ctrl+'0',n3);
                n3 -= *ctrl - '0';
                break;

            case 'D':
                n3--;
                if (n3)
                    ctrl -= 4;
                // printf("D: ctrl='%s'\n",ctrl);
                break;

            case 'G':
                // printf("G-:n0123=%d %d %d %d\n",n0,n1,n2,n3);
                n2 = n0; // n0+n1;
                n0 = n1;
                n1 += n2; // n1=n2;
                          // printf("G+:n0123=%d %d %d %d\n",n0,n1,n2,n3);
                          // fgets(n4a,30,stdin);
                break;

            case 'P':
                n5 = 2;
                break;

            case 'R':
                if (n3<3)
                    ctrl = Ctrl + 1;
                break;

            case 'A':
                n3 = atoi(n4);
                break;

            case 'F':
                fgets(n4, ' ' - 2, stdin);

            case 'C':
                putchar(':');
                putchar(' ');
                break;

            default:
                if (*ctrl >= '2' && *ctrl <= '6')
                {
                    n5 = 1;
                    n3 = *ctrl - Ctrl[1];
                }
                break;
            }
        }
        break;
        case 1:
        {
            putchar(*ctrl);
            n3--;
            if (!n3)
            {
                putchar(32);
                n5 = 0;
            }
            break;
        }
        case 2: // handle 'P'...char *Ctrl=" 05enter6number2of5termsCFARP1S2";
        {
            if (*ctrl == '1')
                printf("%d ", n0);
            printf("%d ", n1);
            n5 = 0;
            break;
        }
        }
        ctrl++;
        // printf("ctrl++: ctrl='%s'\n",ctrl);
    }
    /*
    int n0=0, n1=1, n2;
    int max;
    char buf[32];
    do {
    printf("Enter number of terms: ");
    fgets(buf,30,stdin);
    max=atoi(buf);
    } while (max<3);
    printf("%d %d ",n0,n1);
    max-=2;
    while (max--)
    {
    n2=n0+n1;
    n0=n1;
    n1=n2;
    printf("%d ",n1);
    }*/
    printf("\n");
}

// Hex to decimal converter
void hex2dec()
{
    printf("Enter hex number : ");
    char hexnum[32];
    fgets(hexnum, 30, stdin);
    int result = 0;
    for (int i = 0; hexnum[i]; i++)
    {
        if (hexnum[i] >= '0' && hexnum[i] <= '9')
            result = result * 16 + hexnum[i] - '0';
        else if (hexnum[i] >= 'a' && hexnum[i] <= 'f')
            result = result * 16 + hexnum[i] - 'a' + 10;
        else if (hexnum[i] >= 'A' && hexnum[i] <= 'F')
            result = result * 16 + hexnum[i] - 'A' + 10;
    }
    printf("Result is %d\n", result);
}

// Generate 20MB XML data
void gen_20mb_xml()
{
    int total, i = 0;
    total = printf("<Twenty meg test data>\n") * 2 + 1;
    while (total<20 * 1048576)
    {
        total += printf("<test data %d>blah blah blah blah</test data %d>\n", i, i);
        i++;
    }
    total = printf("</Twenty meg test data>\n") * 2 + 1;
}

// converting double to hex and back https://stackoverflow.com/q/46668785/5937167
void test2()
{
    printf("sizeof double=%zd\n", sizeof(double)); // 8

    union
    {
        unsigned char bytes[8];
        double dbl;
    } urep;

    urep.dbl = -0.15625;
    printf("Hex representation of %f is ", urep.dbl);
    for (int i = 0; i < 8; i++)
        printf("%02x ", urep.bytes[i]);
    printf("\n");
    // Hex representation of 27.395000 is 85 eb 51 b8 1e 65 3b 40

    memset(&urep, 0, sizeof(urep));
    urep.bytes[0] = 0x85;
    urep.bytes[1] = 0xeb;
    urep.bytes[2] = 0x51;
    urep.bytes[3] = 0xb8;
    urep.bytes[4] = 0x1e;
    urep.bytes[5] = 0x65;
    urep.bytes[6] = 0x3b;
    urep.bytes[7] = 0x40;
    printf("String to double result: %f\n", urep.dbl);
}

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
