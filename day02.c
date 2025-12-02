// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day02.md

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
#line 550 "Day02.md"
bool use_sample =FALSE ;

// *** function forward declarations ***


#line 32 "Std.md"
void read_input(const char *day);
#line 77 "Std.md"
char dd(int i, int j);


void pre();
#line 84 "Std.md"
int main(int argc, char *argv[]);
#line 107 "Std.md"
bool is_digit(char c);

num_t parse_number(char **s);
#line 128 "Std.md"
num_t gcd(num_t a, num_t b);
#line 139 "Std.md"
num_t scm(num_t a, num_t b);
num_t num_t_abs(num_t a);
int num_t_sign(num_t a);
#line 148 "Std.md"
char *copy_str(char *s);
#line 560 "Day02.md"
void solve1();
#line 614 "Day02.md"
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
#line 67 "Std.md"
               ;

            s++;}

        if( j > m)
            m = j;
        *s++ = '\0';}}
#line 77 "Std.md"
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
#line 107 "Std.md"
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
#line 128 "Std.md"
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
#line 148 "Std.md"
char *copy_str(char *s)
{
    char *r =( char*)malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;}
#line 560 "Day02.md"
void solve1()
{
    num_t sum =0 ;
    char *s = d[0];
    for(;;)
    {
        char *s2 =s ;
        int l1 =0 ;
        while( is_digit(*s2))
        {
            s2++;
            l1++;}

        s2++;
        int l2 =0 ;
        while( is_digit(*s2))
        {
            s2++;
            l2++;}


        num_t n1 = parse_number(&s);
        s++;
        num_t n2 = parse_number(&s);

        if( l1 % 2 == 0 || l2 % 2 == 0)
        {
            int l = l1 % 2 == 0?  l1:  l2;
            num_t factor = l ==  2?      10:
                           l ==  4 ?    100:
                           l ==  6 ?   1000:
                           l ==  8 ?  10000:
                           l == 10 ? 100000:  0;
            if( l == 0)
            {
                return;}

            num_t h1 = n1/  factor;
            num_t h2 = n2/  factor;
            for( num_t h =h1;  h <= h2; h++)
                if( h * 10 >= factor && h < factor)
                {
                    num_t i = factor * h+  h;
                    if( n1 <= i && i <= n2)
                        sum += i;}}


        if( *s != ',')
            break;
        s++;}

    printf("%lld\n", sum);}


void solve2()
{
    num_t sum =0 ;
    char *s = d[0];
    for(;;)
    {
        char *s2 =s ;
        int l1 =0 ;
        while( is_digit(*s2))
        {
            s2++;
            l1++;}

        s2++;
        int l2 =0 ;
        while( is_digit(*s2))
        {
            s2++;
            l2++;}


        num_t n1 = parse_number(&s);
        s++;
        num_t n2 = parse_number(&s);

        for( num_t n =n1;  n <= n2; n++)
        {
            char buf[20];
            snprintf(buf, 19, "%lld", n);
            int l = strlen(buf);

            bool match =FALSE ;
            for( int m =2;  m <= l; m++)
            {
                if( l % m == 0)
                {
                    match = TRUE;
                    int w = l/  m;
                    for( int i =1;  i < m; i++)
                        for( int j =0;  j < w; j++)
                            if( buf[j] != buf[j + i * w])
                                match = FALSE;}

                if( match)
                    break;}

            if( match)
                sum += n;}


        if( *s != ',')
            break;
        s++;}

    printf("%lld\n", sum);}

// *** others ***
