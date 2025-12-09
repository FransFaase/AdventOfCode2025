// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day09.md

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
#line 11 "Day09.md"
typedef struct redtile_s redtile_t;
#line 17 "Day09.md"
typedef struct area_s area_t;

// *** struct declarations ***

#line 12 "Day09.md"
struct redtile_s{
    num_t x, y;}
 ;
#line 18 "Day09.md"
struct area_s{
    int redtile1, redtile2;
    num_t area;}
 ;

// *** variable declarations ***

#line 27 "Std.md"
char **d;
int n;
int m;
#line 347 "Day09.md"
bool use_sample =FALSE ;
#line 15 "Day09.md"
redtile_t redtiles[1000];
#line 22 "Day09.md"
area_t areas[500*999];

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
#line 85 "Day09.md"
void solve1();
#line 114 "Day09.md"
int compare_area(const void *a, const void *b);
#line 349 "Day09.md"
bool inside(num_t x, num_t y);
#line 512 "Day09.md"
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
#line 85 "Day09.md"
void solve1()
{
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        redtiles[i].x = parse_number(&s);
        s++;
        redtiles[i].y = parse_number(&s);}
#line 96 "Day09.md"
    int nr_area =0 ;
    for( int i =1;  i < n; i++)
        for( int j =0;  j < i; j++)
        {
            areas[nr_area].redtile1 = i;
            areas[nr_area].redtile2 = j;
            num_t dx = redtiles[i].x-  redtiles[j].x;
            if( dx < 0) dx = -dx;
            num_t dy = redtiles[i].y-  redtiles[j].y;
            if( dy < 0) dy = -dy;
            areas[nr_area].area = (dx + 1) * (dy + 1);
            nr_area++;}


    qsort(areas, nr_area, sizeof(areas[0]), compare_area);
    printf("%lld\n", areas[0].area);}


int compare_area(const void *a, const void *b)
{
    area_t *a_area =( area_t *)a;
    area_t *b_area =( area_t *)b;
    return   b_area->area < a_area->area ? -1:
             b_area->area > a_area->area ? 1:
             0;}
#line 349 "Day09.md"
bool inside(num_t x, num_t y)
{

    int inside_score =0 ;
    for( int i1 =0;  i1 < n; i1++)
    {
        int i2 = (i1 + 1)%  n;
        num_t x1 = redtiles[i1].x;
        num_t x2 = redtiles[i2].x;
        num_t y1 = redtiles[i1].y;
        num_t y2 = redtiles[i2].y;
        if( y == y1 && y1 == y2 && (x1 < x2 ? x1 <= x && x <= x2:  x2 <= x && x <= x1))
        {

            return TRUE;}

        if( x1 == x2)
        {

            if( y1 <= y && y <= y2)
            {
                if( x == x1)
                {

                    return TRUE;}

                if( y < y2)
                {
                    if( x < x1)
                        inside_score++;
                    if( x > x1)
                        inside_score--;}}
#line 384 "Day09.md"
            if( y2 <= y && y <= y1)
            {
                if( x == x1)
                {

                    return TRUE;}

                if( y < y1)
                {
                    if( x < x1)
                        inside_score--;
                    if( x > x1)
                        inside_score++;}}}}
#line 402 "Day09.md"
    return inside_score > 0;}
#line 512 "Day09.md"
void solve2()
{
    int nr_areas = n * (n - 1)/  2;
    for( int a =0;  a < nr_areas; a++)
    {
        int t1 = areas[a].redtile1;
        num_t x1 = redtiles[t1].x;
        num_t y1 = redtiles[t1].y;
        int t2 = areas[a].redtile2;
        num_t x2 = redtiles[t2].x;
        num_t y2 = redtiles[t2].y;
        printf("Testing area %d %d %lld from %lld,%lld to %lld, %lld:\n", 
               t1, t2, areas[a].area, x1, y1, x2, y2)
#line 523 "Day09.md"
        ;


        if( inside(x1, y2) && inside(x2, y1))
        {
            if( x1 > x2) { num_t h =x1 ; x1 = x2; x2 = h;}
            if( y1 > y2) { num_t h =y1 ; y1 = y2; y2 = h;}
            bool go =TRUE ;
            for( int x =x1;  x <= x2 && go; x++)
                go = inside(x, y1) && inside(x, y2);
            for( int y =y1;  y <= y2 && go; y++)
                go = inside(x1, y) && inside(x2, y);
            if( go)
            {
                printf("%lld\n", areas[a].area);
                return;}}}}

// *** others ***
