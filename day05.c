// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day05.md

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
#line 253 "Day05.md"
typedef struct range range_t;

// *** struct declarations ***

struct range{

    num_t from;
    num_t to;
    range_t *next;}
 ;

// *** variable declarations ***

#line 27 "Std.md"
char **d;
int n;
int m;
#line 191 "Day05.md"
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
#line 11 "Day05.md"
void solve1();
#line 197 "Day05.md"
void solve2();
#line 261 "Day05.md"
void ranges_add_range(range_t **ref_ranges, num_t from, num_t to);
#line 289 "Day05.md"
void solve2_ranges();

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
    solve2();
#line 286 "Day05.md"
    solve2_ranges();}
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
#line 11 "Day05.md"
void solve1()
{
    int i =0 ;
    while( d[i][0] != '\0')
        i++;

    int count =0 ;
    for( i++; i < n; i++)
    {
        char *line = d[i];
        num_t id = parse_number(&line);

        for( int i1 =0;  d[i1][0] != '\0'; i1++)
        {
            line = d[i1];
            num_t from = parse_number(&line);
            line++;
            num_t to = parse_number(&line);
            if( from <= id && id <= to)
            {
                count++;
                break;}}}
#line 36 "Day05.md"
    printf("%d\n", count);}
#line 197 "Day05.md"
void solve2()
{
    num_t lowest =- 1;
    num_t highest =- 1;

    num_t count =0 ;
    for(;;)
    {
        num_t min =- 1;
        for( int i =0;  d[i][0] != '\0'; i++)
        {
            char *line = d[i];
            num_t from = parse_number(&line);
            if( from > lowest && (min == -1 || from < min))
                min = from;}

        if( min == -1)
            break;
        lowest = min;
        printf("min = %lld\n", min);
        for( int i =0;  d[i][0] != '\0'; i++)
        {
            char *line = d[i];
            num_t from = parse_number(&line);
            if( from == min)
            {
                printf("from %lld\n", from);
                line++;
                num_t to = parse_number(&line);
                printf("to %lld\n", to);
                if( from <= highest)
                    from = highest + 1;
                if( from <= to)
                {
                    printf("Add range %lld %lld = %lld\n", from, to, to - from + 1);
                    count += to - from + 1;
                    highest = to;}}}
#line 237 "Day05.md"
        printf("lowest %lld highest %lld\n\n", lowest, highest);}

    printf("%lld\n", count);}
#line 261 "Day05.md"
void ranges_add_range(range_t **ref_ranges, num_t from, num_t to)
{
    while( *ref_ranges != 0 && (*ref_ranges)->to < from)
        ref_ranges = &(*ref_ranges)->next;
    if( *ref_ranges == 0 || to < (*ref_ranges)->from)
    {
        range_t *new_range =( range_t*)malloc(sizeof(range_t));
        new_range->from = from;
        new_range->to = to;
        new_range->next = *ref_ranges;
        *ref_ranges = new_range;
        return;}

    if( (*ref_ranges)->from < from)
        from = (*ref_ranges)->from;
    while( (*ref_ranges)->next != 0 && (*ref_ranges)->next->from <= to)
        *ref_ranges = (*ref_ranges)->next;
    (*ref_ranges)->from = from;
    if( (*ref_ranges)->to < to)
        (*ref_ranges)->to = to;}
#line 289 "Day05.md"
void solve2_ranges()
{
    range_t *ranges =0 ;
    for( int i =0;  d[i][0] != '\0'; i++)
    {
        char *line = d[i];
        num_t from = parse_number(&line);
        line++;
        num_t to = parse_number(&line);
        ranges_add_range(&ranges, from, to);}


    num_t count =0 ;
    for( range_t *range =ranges;  range != 0; range = range->next)
        count += range->to - range->from + 1;
    printf("%lld\n", count);}

// *** others ***
