// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day07.md

// *** includes ***

#line 6 "Std.md"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

// *** defines ***

#line 17 "Std.md"
#define FALSE 0
#define TRUE 1
#line 212 "Day07.md"
#define M 200

// *** enum declarations ***


// *** typedefs ***

#line 15 "Std.md"
typedef long long num_t;
typedef int bool;
#line 25 "Std.md"
typedef char *char_p;

// *** struct declarations ***


// *** variable declarations ***


char **d;
int n;
int m;
#line 295 "Day07.md"
bool use_sample =FALSE ;

// *** function forward declarations ***


#line 32 "Std.md"
void read_input(const char *day);
#line 82 "Std.md"
char dd(int i, int j);


void pre();
#line 89 "Std.md"
int main(int argc, char *argv[]);
#line 112 "Std.md"
bool is_digit(char c);

num_t parse_number(char **s);
#line 133 "Std.md"
num_t gcd(num_t a, num_t b);
#line 144 "Std.md"
num_t scm(num_t a, num_t b);
num_t num_t_abs(num_t a);
int num_t_sign(num_t a);
#line 153 "Std.md"
char *copy_str(char *s);
#line 57 "Day07.md"
void solve1();
#line 252 "Day07.md"
void solve2();

// *** functions ***


#line 32 "Std.md"
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
    if( length == 0)
    {
        printf("File %s is empty\n", filename);
        exit(1);}
#line 57 "Std.md"
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
#line 72 "Std.md"
               ;

            s++;}

        if( j > m)
            m = j;
        *s++ = '\0';}}
#line 82 "Std.md"
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
#line 112 "Std.md"
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
#line 133 "Std.md"
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
#line 153 "Std.md"
char *copy_str(char *s)
{
    char *r =( char*)malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;}
#line 57 "Day07.md"
void solve1()
{
    num_t count =0 ;

    for( int j =0;  j < m; j++)
        if( d[0][j] == 'S')
        {
            d[1][j] = '|';
            break;}

    for( int i =1;  i + 1 < n; i++)
        for( int j =1;  j + 1 < m; j++)
            if( d[i][j] == '|')
            {
                if( d[i+1][j] == '^')
                {
                    count++;
                    d[i+1][j-1] = '|';
                    d[i+1][j+1] = '|';}

                else
                    d[i+1][j] = '|'
#line 77 "Day07.md"
                ;}


    printf("%lld\n", count);}
#line 252 "Day07.md"
void solve2()
{
    num_t beams[M];
    for( int j =0;  j < m; j++)
        beams[j] = 0;


    for( int j =0;  j < m; j++)
        if( d[0][j] == 'S')
        {
            beams[j] = 1;
            break;}

    for( int i =2;  i < n; i += 2)
    {
        num_t next_beams[M];
        for( int j =0;  j < m; j++)
            next_beams[j] = 0;
        for( int j =0;  j < m; j++)
            if( beams[j] > 0)
            {
                if( d[i][j] == '^')
                {
                    next_beams[j-1] += beams[j];
                    next_beams[j+1] += beams[j];}

                else
                    next_beams[j] += beams[j]
#line 278 "Day07.md"
                ;}


        for( int j =0;  j < m; j++)
            beams[j] = next_beams[j];
        num_t count =0 ;
        for( int j =0;  j < m; j++)
            count += beams[j];
        printf("%lld\n", count);}}

// *** others ***
