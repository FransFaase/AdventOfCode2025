// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day11.md

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
#line 9 "Day11.md"
typedef struct node_s node_t;
typedef struct out_s out_t;

// *** struct declarations ***

struct node_s{

    char name[4];
    out_t *outs;
    num_t paths;
    node_t *next;}
 ;

struct out_s{

    node_t *node;
    out_t *next;}
 ;

// *** variable declarations ***

#line 27 "Std.md"
char **d;
int n;
int m;
bool use_sample =FALSE ;
#line 18 "Day11.md"
node_t *all_nodes =0 ;
#line 179 "Day11.md"
node_t *to_node =0 ;

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
#line 88 "Day11.md"
node_t *add_node(const char *s);
#line 181 "Day11.md"
num_t calc_paths(node_t *node);
#line 227 "Day11.md"
void solve1();
#line 249 "Day11.md"
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
#line 88 "Day11.md"
node_t *add_node(const char *s)
{
    for( node_t *node =all_nodes;  node != 0; node = node->next)
        if( strncmp(node->name, s, 3) == 0)
        {

            return node;}

    node_t *new_node =( node_t*)malloc(sizeof(node_t));
    strncpy(new_node->name, s, 3);
    new_node->name[3] = '\0';
    new_node->outs = 0;
    new_node->paths = -1;
    new_node->next = all_nodes;
    all_nodes = new_node;

    return new_node;}
#line 181 "Day11.md"
num_t calc_paths(node_t *node)
{

    if( node->paths >= 0)
        return node->paths;
    if( node == to_node)
    {
        node->paths = 1;
        return 1;}

    if( node->paths == -2)
    {
        printf("Cyclic graph\n");
        exit(1);}

    node->paths = -2;
    num_t paths =0 ;
    for( out_t *out = node->outs; out != 0; out = out->next)
        paths += calc_paths(out->node);
    node->paths = paths;
    return paths;}
#line 227 "Day11.md"
void solve1()
{
    for( int i =0;  i < n; i++)
    {
        const char *s = d[i];
        node_t *node = add_node(s);
        s += 4;
        while( *s == ' ')
        {
            s++;
            out_t *new_out =( out_t*)malloc(sizeof(out_t));
            new_out->node = add_node(s);
            new_out->next = node->outs;
            node->outs = new_out;
            s += 3;}}


    to_node = add_node("out");
    num_t answer = calc_paths(add_node("you"));
    printf("%lld\n", answer);}


void solve2()
{
    to_node = add_node("out");
    num_t answer = calc_paths(add_node("dac"));
    for( node_t *node =all_nodes;  node != 0; node = node->next)
        node->paths = -1;

    to_node = add_node("dac");
    answer *= calc_paths(add_node("fft"));
    for( node_t *node =all_nodes;  node != 0; node = node->next)
        node->paths = -1;

    to_node = add_node("fft");
    answer *= calc_paths(add_node("svr"));

    printf("%lld\n", answer);}

// *** others ***
