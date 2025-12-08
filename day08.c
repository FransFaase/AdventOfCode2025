// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day08.md

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

#line 25 "Day08.md"
struct dist_t{
    int box1, box2;
    num_t dist_sq;}
  dists[500*999];

// *** variable declarations ***

#line 27 "Std.md"
char **d;
int n;
int m;
bool use_sample =FALSE ;
#line 20 "Day08.md"
struct{
    num_t x, y, z;
    int circuit;}
  boxes[1000];

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
#line 134 "Day08.md"
void solve1();
#line 114 "Day08.md"
int compare_dist(const void *a, const void *b);
#line 129 "Day08.md"
int compare_int(const void* a, const void* b);
#line 201 "Day08.md"
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
#line 134 "Day08.md"
void solve1()
{
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        boxes[i].x = parse_number(&s);
        s++;
        boxes[i].y = parse_number(&s);
        s++;
        boxes[i].z = parse_number(&s);
        boxes[i].circuit = i;}
#line 148 "Day08.md"
    int nr_dist =0 ;
    for( int i =1;  i < n; i++)
        for( int j =0;  j < i; j++)
        {
            dists[nr_dist].box1 = i;
            dists[nr_dist].box2 = j;
            num_t dx = boxes[i].x-  boxes[j].x;
            num_t dy = boxes[i].y-  boxes[j].y;
            num_t dz = boxes[i].z-  boxes[j].z;
            dists[nr_dist].dist_sq = dx * dx + dy * dy + dz * dz;
            nr_dist++;}


    qsort(dists, nr_dist, sizeof(dists[0]), compare_dist);

    for( int i =0;  i < n; i++)
    {
        int circuit1 = boxes[dists[i].box1].circuit;
        int circuit2 = boxes[dists[i].box2].circuit;
        if( circuit2 < circuit1)
        {
            int h =circuit1 ;
            circuit1 = circuit2;
            circuit2 = h;}

        for( int j =0;  j < n; j++)
            if( boxes[j].circuit == circuit2)
                boxes[j].circuit = circuit1;}


    int circuit_sizes[1000];
    for( int i =0;  i < n; i++)
        circuit_sizes[i] = 0;
    for( int i =0;  i < n; i++)
        circuit_sizes[boxes[i].circuit]++;

    qsort(circuit_sizes, n, sizeof(circuit_sizes[0]), compare_int);

    num_t answer =1 ;
    for( int i =0;  i < 3; i++)
        answer *= circuit_sizes[i];
    printf("%lld\n", answer);}
#line 114 "Day08.md"
int compare_dist(const void *a, const void *b)
{
    struct dist_t *a_dist =( struct dist_t *)a;
    struct dist_t *b_dist =( struct dist_t *)b;
    return   b_dist->dist_sq < a_dist->dist_sq ? 1:
             b_dist->dist_sq > a_dist->dist_sq ? -1:
             0;}
#line 129 "Day08.md"
int compare_int(const void* a, const void* b)
{
   return (*(int*)b - *(int*)a);}
#line 201 "Day08.md"
void solve2()
{
    num_t answer =0 ;
    for( int i =0;  i < n * (n - 1) / 2; i++)
    {
        int circuit1 = boxes[dists[i].box1].circuit;
        int circuit2 = boxes[dists[i].box2].circuit;
        if( circuit1 != circuit2)
        {
            if( circuit2 < circuit1)
            {
                int h =circuit1 ;
                circuit1 = circuit2;
                circuit2 = h;}

            for( int j =0;  j < n; j++)
                if( boxes[j].circuit == circuit2)
                    boxes[j].circuit = circuit1;
            answer = boxes[dists[i].box1].x * boxes[dists[i].box2].x;}}


    printf("%lld\n", answer);}

// *** others ***
