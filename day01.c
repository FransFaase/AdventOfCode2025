// *** includes ***

#line 6 "Std.md"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "unistd.h"

// *** defines ***

#line 16 "Std.md"
#define FALSE 0
#define TRUE 1

// *** enum declarations ***


// *** typedefs ***

#line 14 "Std.md"
typedef long long num_t;
typedef int bool;
#line 24 "Std.md"
typedef char *char_p;

// *** struct declarations ***


// *** variable declarations ***


char **d;
int n;
int m;
bool use_sample =FALSE ;

// *** function forward declarations ***



void read_input(const char *day);
#line 76 "Std.md"
char dd(int i, int j);


void pre();
#line 83 "Std.md"
int main(int argc, char *argv[]);
#line 106 "Std.md"
bool is_digit(char c);

num_t parse_number(char **s);
#line 127 "Std.md"
num_t gcd(num_t a, num_t b);
#line 138 "Std.md"
num_t scm(num_t a, num_t b);
num_t num_t_abs(num_t a);
int num_t_sign(num_t a);
#line 147 "Std.md"
char *copy_str(char *s);
#line 9 "Day01.md"
void solve1();
#line 79 "Day01.md"
void solve2();

// *** functions ***


#line 31 "Std.md"
void read_input(const char *day)
{
    n = 0;
    m = 0;
    char filename[50];
    sprintf(filename, use_sample ? "day%s.txt":  "input/day%s.txt", day);
    FILE *f = fopen(filename, "r");
    if( f == 0)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);}

    int fh = fileno(f);
    size_t length = lseek(fh, 0,  SEEK_END);
    lseek(fh, 0,  SEEK_SET);
    char *data =( char*)malloc(length);
    length = read(fh, data, length);
    fclose(f);


    for( int i =0;  i < length; i++)
        if( data[i] == '\n')
            n++;

    d = (char**)malloc(n * sizeof(char_p));
    char *s =data ;
    for( int i =0;  i < n; i++)
    {
        d[i] = s;

        int j =0  ;
        while( *s != '\n')
        {
            if( *s == '\r')
                *s = '\0';
               else
                   j++
#line 66 "Std.md"
               ;

            s++;}

        if( j > m)
            m = j;
        *s++ = '\0';}}
#line 76 "Std.md"
char dd(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m ? d[i][j]:  ' ';}


void pre()
{}


int main(int argc, char *argv[])
{
    int len = strlen(argv[0]);
    if( len <= 2)
    {
        printf("Program name should be longer than two.\n");
        return 0;}


    pre();

    read_input(argv[0] + len - 2);

    solve1();
    solve2();}
#line 106 "Std.md"
bool is_digit(char c) { return '0' <= c && c <= '9';}

num_t parse_number(char **s)
{
    int sign =1 ;
    if( **s == '-')
    {
        sign = -1;
        (*s)++;}

    num_t value =0 ;
    for(; is_digit(**s); (*s)++)
        value = 10 * value + **s - '0';
    return sign * value;}
#line 127 "Std.md"
num_t gcd(num_t a, num_t b)
{
    while( a != 0)
    {
        num_t c = b%  a;
        b = a;
        a = c;}

    return b;}


num_t scm(num_t a, num_t b) { return a * (b / gcd(a, b));}
num_t num_t_abs(num_t a) { return a < 0 ? -a:  a;}
int num_t_sign(num_t a) { return a < 0 ? -1:  a > 0 ? 1:  0;}
#line 147 "Std.md"
char *copy_str(char *s)
{
    char *r =( char*)malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;}
#line 9 "Day01.md"
void solve1()
{
    num_t pos =50 ;
    int count =0 ;
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        char dir =* s++;
        num_t clicks = parse_number(&s);
        if( dir == 'R')
            pos = (pos + clicks) % 100;
        else{

            pos -= clicks;
            while( pos < 0)
                pos += 100;}

        if( pos == 0)
            count++;}

    printf("%d\n", count);}
#line 79 "Day01.md"
void solve2()
{
    num_t pos =50 ;
    int count =0 ;
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        char dir =* s++;
        num_t clicks = parse_number(&s);
        if( dir == 'R')
        {
            for( int j =0;  j < clicks; j++)
            {
                pos++;
                if( pos == 100)
                {
                    pos = 0;
                    count++;}}}
#line 100 "Day01.md"
        else{

            for( int j =0;  j < clicks; j++)
            {
                pos--;
                if( pos == 0)
                    count++;
                if( pos < 0)
                    pos += 100;}}}
#line 112 "Day01.md"
    printf("%d\n", count);}

// *** others ***
