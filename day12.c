// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day12.md

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
#line 385 "Day12.md"
bool use_sample =TRUE ;
#line 16 "Day12.md"
int nr_variants[6];
char pieces[6][8][3][3];
int piece_size[6];
#line 449 "Day12.md"
int pieces_j[6][8];
#line 526 "Day12.md"
int nr_per_piece[6];

int h   ;int    w;
char region[100][100];

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
#line 451 "Day12.md"
void solve1();
#line 531 "Day12.md"
bool solve_line(int i);
#line 369 "Day12.md"
void solve2();
#line 568 "Day12.md"
bool find(int i, int j, int left_pieces, int empty);

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
#line 451 "Day12.md"
void solve1()
{
    for( int p =0;  p < 6; p++)
    {
        char piece[3][3];
        for( int i =0;  i < 3; i++)
            for( int j =0;  j < 3; j++)
                piece[i][j] = pieces[p][0][i][j] = d[1 + 5 * p + i][j];

        nr_variants[p] = 1;
        for( int f =0;  f < 2; f++)
        {
#line 466 "Day12.md"
            for( int r =0;  r < 4; r++)
            {
                char h      = piece[0][0];
                piece[0][0] = piece[0][2];
                piece[0][2] = piece[2][2];
                piece[2][2] = piece[2][0];
                piece[2][0] = h;
                h           = piece[0][1];
                piece[0][1] = piece[1][2];
                piece[1][2] = piece[2][1];
                piece[2][1] = piece[1][0];
                piece[1][0] = h;

                bool equal =FALSE ;
                for( int v =0;  v < nr_variants[p] && !equal; v++)
                {
                    equal = TRUE;
                    for( int i =0;  i < 3 && equal; i++)
                        for( int j =0;  j < 3 && equal; j++)
                            equal = pieces[p][v][i][j] == piece[i][j];}

                if( !equal)
                {
                    int v = nr_variants[p];
                    for( int i =0;  i < 3; i++)
                        for( int j =0;  j < 3; j++)
                            pieces[p][v][i][j] = piece[i][j];
                    nr_variants[p]++;}}


            for( int i =0;  i < 3; i++)
            {
                int h = piece[i][0];
                piece[i][0] = piece[i][2];
                piece[i][2] = h;}

            piece_size[p] = 0;
            for( int i =0;  i < 3; i++)
                for( int j =0;  j < 3; j++)
                    if( piece[i][j] == '#')
                        piece_size[p]++;}

        for( int v =0;  v < nr_variants[p]; v++)
        {
            for( int j =0;  j < 3; j++)
                if( pieces[p][v][0][j] == '#')
                {
                    pieces_j[p][v] = j;
                    break;}}}
#line 519 "Day12.md"
    int nr_fit =0 ;
    for( int i =30;  i < n; i++)
        if( solve_line(i))
            nr_fit++;
    printf("%d\n", nr_fit);}
#line 531 "Day12.md"
bool solve_line(int i)
{
    char *s = d[i];
    w = parse_number(&s);
    s++;
    h = parse_number(&s);
    s += 2;
    int sum =0 ;
    int nr_pieces =0 ;
    for( int p =0;  p < 6; p++)
    {
        nr_per_piece[p] = parse_number(&s);
        s++;
        nr_pieces += nr_per_piece[p];
        sum += piece_size[p] * nr_per_piece[p];}

    int area = w*  h;
    int empty = area-  sum;
    if( empty < 0)
    {

        return FALSE;}

    if( nr_pieces <= (w / 3) * (h / 3))
    {


        return TRUE;}


    printf("%3d: '%s' %d %d %d, %dx%d=%d %d\n", i + 1, d[i], area, sum, empty, w / 3, h / 3, (w / 3) * (h / 3), (w / 3) * (h / 3) - nr_pieces);
    for( int i =0;  i < h; i++)
        for( int j =0;  j < w; j++)
            region[i][j] = '.';
    return find(0, 0, nr_pieces, empty);}
#line 369 "Day12.md"
void solve2()
{}
#line 568 "Day12.md"
bool find(int i, int j, int left_pieces, int empty)
{
    if( left_pieces == 0)
    {
        for( int i1 =0;  i1 < h; i1++)
        {
            for( int j1 =0;  j1 < w; j1++)
                printf("%c", region[i1][j1]);
            printf("\n");}

        return TRUE;}
#line 582 "Day12.md"
    for(;;)
    {
        if( region[i][j] == '.')
            break;
        if( ++j >= w)
        {
            j = 0;
            if( ++i >= h)
                return FALSE;}}
#line 594 "Day12.md"
    for( int p =0;  p < 6; p++)
        if( nr_per_piece[p] > 0)
        {
            for( int v =0;  v < nr_variants[p]; v++)
            {
                int i1 =i ;
                int j1 = j-  pieces_j[p][v];
                if( 0 <= i1 && i1 + 2 < h && 0 <= j1 && j1 + 2 < w)
                {
                    bool fits =TRUE ;
                    for( int i2 =0;  i2 < 3 && fits; i2++)
                        for( int j2 =0;  j2 < 3 && fits; j2++)
                            fits = pieces[p][v][i2][j2] == '.' || region[i1 + i2][j1 + j2] == '.';
                    if( fits)
                    {
                        nr_per_piece[p]--;
                        for( int i2 =0;  i2 < 3; i2++)
                            for( int j2 =0;  j2 < 3; j2++)
                                if( pieces[p][v][i2][j2] == '#')
                                    region[i1 + i2][j1 + j2] = 'a' + left_pieces % 26;
                        if( find(i, j, left_pieces - 1, empty))
                            return TRUE;
                        nr_per_piece[p]++;
                        for( int i2 =0;  i2 < 3; i2++)
                            for( int j2 =0;  j2 < 3; j2++)
                                if( pieces[p][v][i2][j2] == '#')
                                    region[i1 + i2][j1 + j2] = '.';}}}}
#line 625 "Day12.md"
    if( empty > 0)
        return find(i + 1, j, left_pieces, empty - 1);
    return FALSE;}

// *** others ***
