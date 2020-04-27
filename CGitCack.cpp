// CGitCack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
#include <complex>
#include <tuple>
#include <limits>
#include <fstream>

#define TEST test4
using std::cin;
using std::cout;
using std::endl;

// Puzzling at StackExchange
// How to get 32 using +1 +1 *3 *3 /2 /2 ^2 ^2
// All ops are reversible on the complex plane. So let's start from 32 and work backwards to all possible starting points, then plot the points.
// We'll probably need a recursive function, taking in a complex point and a list of operations
// This will loop over the ops (no need for permutations) and call itself with the resulting point (or points for sqrt)

typedef std::tuple<std::complex<double>, std::vector <std::string>> Node_t;
typedef std::vector<Node_t> NodeList_t;

void test5()
{
    using namespace std::complex_literals;

    std::complex<double> num = 9. + 4i;
    std::complex<double> principleRoot = std::sqrt(num);
    std::complex<double> secRoot = principleRoot * -1.0;
    cout << "Square roots of " << num << " are " << principleRoot << " and " << secRoot << endl;
}

void test4a(std::complex<double> start, std::vector<std::string> ops, NodeList_t &NL)
{
    std::for_each(ops.begin(), ops.end(), [&](const std::string s) {
        // Work out newOps which is ops minus the current string s.
        // Doesn't look like there's a remove by value newOps=ops; newOps.whatever(s);
        //cout << "Processing operation [" << s << "]\n";
        std::vector<std::string> newOps;
        bool removed = false;
        std::for_each(ops.begin(), ops.end(), [&](const std::string t) {
            if (t == s && !removed) {
                removed = true;
            }
            else {
                newOps.push_back(t);
            }
        });

        if (s == "-1") {
            std::complex<double> newStart = start - 1.0;
            NL.push_back(std::make_tuple(newStart, newOps));
            test4a(newStart, newOps, NL);
        }
        else if (s == "/3") {
            std::complex<double> newStart = start / 3.0;
            NL.push_back(std::make_tuple(newStart, newOps));
            test4a(newStart, newOps, NL);
        }
        else if (s == "*2") {
            std::complex<double> newStart = start * 2.0;
            NL.push_back(std::make_tuple(newStart, newOps));
            test4a(newStart, newOps, NL);
        }
        else if (s == "sqrt") {
            std::complex<double> newStart = std::sqrt(start);

            // There are 2 square roots of a complex number: std::sqrt gives us the principle, and the secondary is just the principle * -1.0
            NL.push_back(std::make_tuple(newStart, newOps));
            test4a(newStart, newOps, NL);
            NL.push_back(std::make_tuple(newStart * -1.0, newOps));
            test4a(newStart * -1.0, newOps, NL);
        }
    });
}
#include <string.h>

#define TEST test6

// Bracketed CSV to INSERT statements (not generic in any sense)
// ER: add quote handling [O'Hara] -> 'O'Hara' -> string not properly terminated
// ER: check 'A &. B' inserts 'A & B' and handle that, without needing to SET DEFINE OFF
void test6()
{
    // char *filename = "C:\\Users\\david.spencer\\Documents\\__Tasks\\Goliat PrtScrs 10 July\\OraData\\arr_data.txt";
    char *filename = "C:\\Users\\david.spencer\\Documents\\__Tasks\\Goliat PrtScrs 10 July\\OraData\\pob_data.txt";
    char *opfile = "C:\\Users\\david.spencer\\Documents\\__Tasks\\Goliat PrtScrs 10 July\\OraData\\INSERTs_pob.txt";

    char output[1024];
    char line[1024];
    FILE *fp;
    errno_t foo1 = fopen_s(&fp, filename, "r");
    FILE *ofp;
    errno_t foo2 = fopen_s(&ofp, opfile, "a");

    if (!foo1 && !foo2)
    {
        for (;;)
        {
            if (feof(fp))
                break;

            if (fgets(line, 1022, fp))
            {
                // Ignore lines that don't start with [
                if (line[0] == '[')
                {
                    printf("Found line starting '['\n");
                    //strcpy_s(output, 1024, "insert into v_arr__data(RESERVATION_ID,DW_ID,PERSON_ID,LAST_NAME,FIRST_NAME,DATE_OF_BIRTH,SALEM_TAG,S3ID_HID_PID,TRANSPORTATION_DATE,TRANSPORTATION_NO,START_LOCATION,END_LOCATION,LIFEBOAT_NO,SHIFT_CODE,EMERGENCY_TEAM_CODE_ID,EMERGENCY_ROLE_CODE,COMPANY,COMPANY_NAME,BED_INSTALLATION,BED_CABIN,BED_NO) values (");
                    strcpy_s(output, 1024, "insert into v_pob__data(INSTALLATION,DW_ID,PERSON_ID,LAST_NAME,FIRST_NAME,DATE_OF_BIRTH,SALEM_TAG,S3ID_HID_PID,LIFEBOAT_NO,SHIFT_CODE,EMERGENCY_TEAM_CODE_ID,EMERGENCY_ROLE_CODE,COMPANY,COMPANY_NAME,BED_INSTALLATION,BED_CABIN,BED_NO) values (");
                    char tok[128];
                    int t = 0;
                    int stat = 0;
                    int col = 0;
                    for (int i = 0; i < strlen(line); i++)
                    {
                        switch (stat)
                        {
                        case 0: // looking for [ to start the token
                            if (line[i] == '[')
                            {
                                printf("Found [ starting new token\n");
                                tok[t = 0] = 0;
                                stat = 1;
                            }
                            break;

                        case 1: // build up the token, ending at ]. Truncate token at 126.
                            if (line[i] == ']')
                                stat = 2;
                            else if (t < 126)
                            {
                                printf("Adding '%c' to token\n", line[i]);
                                tok[t++] = line[i];
                                tok[t] = 0;
                            }
                            break;

                        case 2: // Process the token
                        {
                            printf("Process token '%s' for column %d\n", tok, col);
                            switch (col)
                            {
                            case 1: // NUMBER; the token just gets added in
                                printf("case %d: NUMBER type concat <%s,>\n", col, tok);
                                strcat_s(output, 1024, tok);
                                strcat_s(output, 1024, ",");
                                break;
                            case 5: // DATEs
                                printf("case %d: DATE - <TO_DATE('%s','DD-MON-RR'),>\n", col, tok);
                                strcat_s(output, 1024, "TO_DATE('");
                                strcat_s(output, 1024, tok);
                                strcat_s(output, 1024, "','DD-MON-RR'),");
                                break;
                            case 16: // VARCHAR2 but also the last token
                                printf("case %d: Last VARCHAR2 <'%s'>);\n", col, tok);
                                strcat_s(output, 1024, "'");
                                strcat_s(output, 1024, tok);
                                strcat_s(output, 1024, "');");
                                break;
                            default: // everything else is VARCHAR2 and not last
                                printf("default(col=%d): non-last VARCHAR2 <'%s'>\n", col, tok);
                                strcat_s(output, 1024, "'");
                                strcat_s(output, 1024, tok);
                                strcat_s(output, 1024, "',");
                                break;
                            }
                            col++;
                            // As we didn't process line[i] push it back
                            i--;
                            stat = 3;
                        }
                        break;

                        case 3: // Skip the comma separator
                            if (line[i] == ',')
                            {
                                printf("Skip comma separator\n");
                                stat = 0;
                            }
                            break;
                        }
                    }
                    fputs(output, ofp);
                    fputs("\n", ofp);
                }
            }
        }
        fclose(fp);
        fclose(ofp);
    }
}

/* A Pythagorean triplet is a set of three natural numbers a<b<c for which a^2+b^2=c^2.
For example, 3^2+4^2=9+16=25=5^2.
There exists exactly one Pythagorean triplet for which a+b+c=1000. Find the product abc. */
// https://codereview.stackexchange.com/q/224132/155266
void test5()
{
    int checks = 0;
    for (int a=1; a<=332; a++)
    {
        for (int b=a+1; b<=998; b++)
        {
            int c = 1000 - a - b;

            // By construction a+b+c=1000 so we don't need to check for this.

            // So let's just check if a^2+b^2=c^2
            checks++;
            if (a*a + b * b == c * c)
                printf("a=%d; b=%d; c=%d; abc=%d\n", a, b, c, a*b*c);
        }
    }
    printf("Performed %d checks in total\n", checks);
}

/* At an exotic bird market sale, ostriches are $10 each, emus are $5 each 
and puffins go for $0.50. You cannot buy any fractional birds. How many 
ostriches, emus and puffins can be bought with $100 to make 100 birds in all? */
void test4()
{
    for (int puf = 0; puf <= 100; puf++)
    {
        for (int emu = 0; emu <= 20; emu++)
        {
            for (int ost = 0; ost <= 10; ost++)
            {
                if (puf * 50 + emu * 500 + ost * 1000 == 10000 && puf + emu + ost == 100)
                {
                    printf("%d puffins, %d emus and %d ostriches\n", puf, emu, ost);
                }
            }
        }
    }
}
// Solver for https://puzzling.stackexchange.com/questions/97439/how-to-get-32-by-using-1-1-%c3%973-%c3%973-%c3%b72-%c3%b72-2-2/97564#97564
// How to get 32 by using +1 , +1 , ×3 , ×3 , ÷2 , ÷2, ^2, ^2?
// Starting from 32 we reverse the operations to -1, /3, *2 and sqrt then just traverse the resulting tree.
void test4()
{
    NodeList_t NodeList;

    // Set the initial value of 32 and list of operations
    std::complex<double> init = 32.0;
    std::vector<std::string> ops = { "-1", "-1", "/3", "/3", "*2", "*2", "sqrt", "sqrt" };

    // Recursively build the node list
    test4a(init, ops, NodeList);

    std::ofstream plt("C:\\Dev\\nodes.plt");
    plt << "set xrange [-15: 7]\n";
    plt << "set yrange [-9: 9]\n";
    plt << "set format x \" % 3.5f\"\n";
    plt << "set format y \" % 3.5f\"\n";
    plt << "set tics\n";
    plt << "unset key\n";
    plt << "plot '-' with points\n";

    // Display the created nodes
    int lineCount = 0;
    int resultCount = 0;
    double minReal=DBL_MAX, maxReal=-DBL_MAX, minImag=DBL_MAX, maxImag=-DBL_MAX;
    std::vector<std::complex<double>> uniqueResults;
    std::for_each(NodeList.begin(), NodeList.end(), [&](auto& node) {
        auto ops = std::get<1>(node);
        // Only display the nodes with no remaining operations, i.e. the leaves
        if (!ops.size()) {
            auto c = std::get<0>(node);
            resultCount++;

            // Add c to uniqueResults if it's not already in there
            if (std::all_of(uniqueResults.begin(), uniqueResults.end(), [&](auto r) {
                return std::abs(c.real() - r.real()) > 0.0001 || std::abs(c.imag() - r.imag()) > 0.0001; }))
            {
                uniqueResults.push_back(c);
            }

            cout << "(" << c.real();

            if (std::abs(c.imag()) < 0.00001) {
                cout << " + i0) ";
            }
            else if (c.imag() <= -0.00001) {
                cout << " - i" << c.imag() * -1.0 << ") ";
            }
            else {
                cout << " + i" << c.imag() << ") ";
            }
            if (c.real() < minReal) minReal = c.real();
            if (c.real() > maxReal) maxReal = c.real();
            if (c.imag() < minImag) minImag = c.imag();
            if (c.imag() > maxImag) maxImag = c.imag();

            plt << c.real() << " " << c.imag() << endl;
        }
        //cout << "Node at point (" << .real() << " + i" << std::get<0>(node).imag() << ") has remaining ops: ";
        //std::for_each(ops.begin(), ops.end(), [](const std::string& s) {cout << s + " "; });
        //cout << endl;
        //linecount++;
        //if (linecount > 45) {
        //    linecount = 0;
        //    cin.ignore();
        //}
        });
    plt.close();
    cout << "\nTotal results: " << resultCount << endl;
    cout << "Real axis from " << minReal << " to " << maxReal << endl;
    cout << "Imaginary axis from " << minImag << " to " << maxImag << endl;
    cout << "uniqueResults size=" << uniqueResults.size() << endl;
}

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
//    int n0 = printf("Welcome to Dave's Fibonacci generator\n") / (int)
//        "comment: print greeting", n1
//        = printf("-------------------------------------\n")
//        * 0 - +-1;int n2 = 3.1415926 / 2.718281 + 365.25;
//    int n3;
//    char n4[' '];
//    int n5 = 0;
//    char *ctrl = Ctrl;
//
//    while (*ctrl) {
//        switch (n5) {
//        case 0: {switch (*ctrl) {
//            case
//                'S':ctrl++;n3 -= *ctrl - '0';break;case 'D':n3--;if (n3)
//                ctrl -= 4;break;case 'G':n2 = n0;n0 = n1;n1 += n2;break;case
//                'P':n5 = 2;break;case 'R':if (n3<3)ctrl = Ctrl + 1;break;
//                case 'A':n3 = atoi(n4);break;case 'F':fgets(n4, ' ' - 2,
//                    stdin);case 'C':putchar(':');putchar(' ');break;
//                    default:if (*ctrl >= '2' && *ctrl <= '6') {
//                        n5 = 1;n3 = *ctrl
//                            - Ctrl[1];
//                    }break;
//        }}break;case 1: {putchar(*ctrl - 1);n3--;
//        if (!n3) { putchar(32);n5 = 0; }break;}case 2: {if (*ctrl ==
//            '1')printf("%d ", n0);printf("%d ", n1);n5 = 0;break;}
//        }
//        ctrl++;
//    }printf("\n");
}

void fibonacci()
{
//    int n0 = printf("Welcome to Dave's Fibonacci generator\n") / (int)"comment: print greeting";
//    int n1 = printf("-------------------------------------\n") * 0 - -1;
//    int n2 = 3.1415926 / 2.718281 + 365.25;
//    int n3;
//    char n4[' '];
//    char n4a[' '];
//    int n5 = 0;
//    char *ctrl = Ctrl;
//    while (*ctrl)
//    {
//        switch (n5)
//        {
//        case 0:
//        {
//            switch (*ctrl)
//            {
//            case 'S':
//                ctrl++;
//                // printf("S:sub %d from n3(%d)\n",*ctrl+'0',n3);
//                n3 -= *ctrl - '0';
//                break;
//
//            case 'D':
//                n3--;
//                if (n3)
//                    ctrl -= 4;
//                // printf("D: ctrl='%s'\n",ctrl);
//                break;
//
//            case 'G':
//                // printf("G-:n0123=%d %d %d %d\n",n0,n1,n2,n3);
//                n2 = n0; // n0+n1;
//                n0 = n1;
//                n1 += n2; // n1=n2;
//                          // printf("G+:n0123=%d %d %d %d\n",n0,n1,n2,n3);
//                          // fgets(n4a,30,stdin);
//                break;
//
//            case 'P':
//                n5 = 2;
//                break;
//
//            case 'R':
//                if (n3<3)
//                    ctrl = Ctrl + 1;
//                break;
//
//            case 'A':
//                n3 = atoi(n4);
//                break;
//
//            case 'F':
//                fgets(n4, ' ' - 2, stdin);
//
//            case 'C':
//                putchar(':');
//                putchar(' ');
//                break;
//
//            default:
//                if (*ctrl >= '2' && *ctrl <= '6')
//                {
//                    n5 = 1;
//                    n3 = *ctrl - Ctrl[1];
//                }
//                break;
//            }
//        }
//        break;
//        case 1:
//        {
//            putchar(*ctrl);
//            n3--;
//            if (!n3)
//            {
//                putchar(32);
//                n5 = 0;
//            }
//            break;
//        }
//        case 2: // handle 'P'...char *Ctrl=" 05enter6number2of5termsCFARP1S2";
//        {
//            if (*ctrl == '1')
//                printf("%d ", n0);
//            printf("%d ", n1);
//            n5 = 0;
//            break;
//        }
//        }
//        ctrl++;
//        // printf("ctrl++: ctrl='%s'\n",ctrl);
//    }
//    /*
//    int n0=0, n1=1, n2;
//    int max;
//    char buf[32];
//    do {
//    printf("Enter number of terms: ");
//    fgets(buf,30,stdin);
//    max=atoi(buf);
//    } while (max<3);
//    printf("%d %d ",n0,n1);
//    max-=2;
//    while (max--)
//    {
//    n2=n0+n1;
//    n0=n1;
//    n1=n2;
//    printf("%d ",n1);
//    }*/
//    printf("\n");
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
