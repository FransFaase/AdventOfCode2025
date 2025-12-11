// This is generated with MarkDownC 0.1 of December 1, 2025.
// from the files:
// - Std.md
// - Day10.md

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
#line 764 "Day10.md"
bool use_sample =FALSE ;
#line 114 "Day10.md"
int nr_pos;
int buttons[100];
int nr_buttons;
num_t jolting[100];
num_t state[100];
int min;
#line 766 "Day10.md"
num_t max_per_button[100];
#line 1180 "Day10.md"
bool proc_buttons[100];

int depth;
#line 1529 "Day10.md"
num_t matrix[50][50];
int reduced_on_pos[50];
num_t button_presses[50];

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
#line 61 "Day10.md"
void solve1();
#line 933 "Day10.md"
void search_min(int jolts, int cur_p, int b, int mult);
#line 1696 "Day10.md"
void solve2();
#line 1184 "Day10.md"
void search_min_b(int jolts);
#line 1793 "Day10.md"
void solve_equations(int jolt, int button);

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
#line 61 "Day10.md"
void solve1()
{
    num_t count =0 ;
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        int pattern =0 ;
        s++;
        for( int i =1;  *s != ']'; i *= 2)
            if( *s++ == '#')
                pattern |= i;
        s += 2;
        int buttons[100];
        int nr_buttons =0 ;
        while( *s == '(')
        {
            s++;
            buttons[nr_buttons] = 0;
            for(;;)
            {
                num_t num = parse_number(&s);
                buttons[nr_buttons] |= 1 << num;
                if( *s++ == ')')
                    break;}

            s++;
            nr_buttons++;}

        int min =nr_buttons ;
        long max = 1<<  nr_buttons;
        for( int m =0;  m < max; m++)
        {
            int nr_switched =0 ;
            int state =0 ;
            for( int b =0;  b < nr_buttons; b++)
                if( ((1 << b) & m) != 0)
                {
                    nr_switched++;
                    state ^= buttons[b];}

            if( state == pattern && nr_switched < min)
                min = nr_switched;}

        count += min;}

    printf("%lld\n", count);}
#line 933 "Day10.md"
void search_min(int jolts, int cur_p, int b, int mult)
{
    if( jolts >= min)
        return;
    bool equal =TRUE ;
    for( int p =0;  p < nr_pos; p++)
    {
        if( jolting[p] < 0)
            return;
        if( jolting[p] > 0)
        {
            equal = FALSE;
            if( jolts + jolting[p] >= min)
                return;}}


    if( equal)
    {
        min = jolts;
        return;}


    bool select_p = cur_p == -1 || jolting[cur_p] == 0||  mult == 0;
    num_t old_max_per_button[100];
    if( select_p)
    {

        cur_p = -1;
        num_t best_comb;
        int best_m;
        for( int p =0;  p < nr_pos; p++)
        {
            if( jolting[p] > 0)
            {
                m = 0;
                num_t sum =0 ;
                for( int b =0;  b < nr_buttons; b++)
                    if( ((1 << p) & buttons[b]) != 0)
                    {
                        num_t max =1000 ;
                        for( int p2 =0;  p2 < nr_pos; p2++)
                            if( (((1 << p2) & buttons[b]) != 0) && jolting[p2] < max)
                                max = jolting[p2];
                        if( max > 0)
                            m++;
                        sum += max;}

                if( sum < jolting[p])
                    return;
                if(    cur_p == -1
                    || (  m == 1
                        ? (best_m > 1 || jolting[p] > best_comb):
                          m == 2
                        ? (best_m > 2|| (best_m == 2 && jolting[p] < best_comb)):
                          jolting[p] < best_comb))
                {
                    cur_p = p;
                    best_m = m;
                    best_comb = jolting[p];}}}
#line 995 "Day10.md"
        mult = 0;
        for( int b =0;  b < nr_buttons; b++)
            old_max_per_button[b] = max_per_button[b];
        for( int b =0;  b < nr_buttons; b++)
            if( ((1 << cur_p) & buttons[b]) != 0)
            {
                num_t max =1000 ;
                for( int p =0;  p < nr_pos; p++)
                    if( (((1 << p) & buttons[b]) != 0) && jolting[p] < max)
                        max = jolting[p];
                max_per_button[b] = max;
                if( max > 0)
                    mult++;}


        b = 0;}

    if( mult > 0)
    {
        for(;  b < nr_buttons; b++)
            if( max_per_button[b] > 0 && ((1 << cur_p) & buttons[b]) != 0)
                break;

        num_t r_max = jolting[cur_p];
        if( max_per_button[b] < r_max)
            r_max = max_per_button[b];

        for( int r = mult == 1?  r_max:  0; r <= r_max; r++)
        {
            num_t old_jolting[100];
            for( int p =0;  p < nr_pos; p++)
            {
                old_jolting[p] = jolting[p];
                if( ((1 << p) & buttons[b]) != 0)
                    jolting[p] -= r;}

            search_min(jolts + r, cur_p, b + 1, mult - 1);
            for( int p =0;  p < nr_pos; p++)
                jolting[p] = old_jolting[p];}}
#line 1037 "Day10.md"
    if( select_p)
    {
        for( int b =0;  b < nr_buttons; b++)
            max_per_button[b] = old_max_per_button[b];}}
#line 1696 "Day10.md"
void solve2()
{
    num_t count =0 ;
    for( int i =0;  i < n; i++)
    {
        char *s = d[i];
        while( *s != '(')
            s++;
        nr_pos = (s - d[i]) - 3;

        nr_buttons = 0;
        while( *s == '(')
        {
            for( int p =0;  p < nr_pos; p++)
                matrix[p][nr_buttons] = 0;
            s++;
            buttons[nr_buttons] = 0;
            for(;;)
            {
                num_t num = parse_number(&s);
                matrix[num][nr_buttons] = 1;
                if( *s++ == ')')
                    break;}

            s++;
            nr_buttons++;}

        for( int j =0;  *s != '}'; j++)
        {
            s++;
            jolting[j] = parse_number(&s);}


        for( int p =0;  p < nr_pos; p++)
        {
            for( int b =0;  b < nr_buttons; b++)
                if( matrix[p][b] == 0)
                    printf("    ");
                else
                    printf("%4lld", matrix[p][b])
#line 1734 "Day10.md"
                ;

            printf(" = %lld\n", jolting[p]);}

        printf("\n");


        bool reduced_rows[50];
        for( int p =0;  p < nr_pos; p++)
            reduced_rows[p] = FALSE;

        for( int b =0;  b < nr_buttons; b++)
        {

            int p =0 ;
            for( p = 0; p < nr_pos; p++)
                if( !reduced_rows[p] && matrix[p][b] != 0)
                    break;
            if( p < nr_pos)
            {
                reduced_on_pos[b] = p;
                reduced_rows[p] = TRUE;

                num_t factor = matrix[p][b];
                printf("%d: %lld\n", p, factor);

                for( int o_p =0;  o_p < nr_pos; o_p++)
                    if( !reduced_rows[o_p] && matrix[o_p][b] != 0)
                    {
                        num_t o_factor = matrix[o_p][b];
                        matrix[o_p][b] = 0;
                        for( int b2 = b+  1; b2 < nr_buttons; b2++)
                            matrix[o_p][b2] = factor * matrix[o_p][b2] - o_factor * matrix[p][b2];
                        jolting[o_p] = factor * jolting[o_p] - o_factor * jolting[p];}
#line 1771 "Day10.md"
                for( int p =0;  p < nr_pos; p++)
                {
                    for( int b =0;  b < nr_buttons; b++)
                        if( matrix[p][b] == 0)
                            printf("    ");
                        else
                            printf("%4lld", matrix[p][b])
#line 1776 "Day10.md"
                        ;

                    printf(" = %lld\n", jolting[p]);}

                printf("\n");}

            else
                reduced_on_pos[b] = -1
#line 1782 "Day10.md"
            ;}


        min = 1000;
        solve_equations(0, nr_buttons - 1);
        printf("min = %d\n", min);
        count += min;}

    printf("%lld\n", count);}
#line 1184 "Day10.md"
void search_min_b(int jolts)
{
    if( jolts >= min)
        return;
    bool equal =TRUE ;
    for( int p =0;  p < nr_pos; p++)
    {
        if( jolting[p] < 0)
            return;
        if( jolting[p] > 0)
        {
            equal = FALSE;
            if( jolts + jolting[p] >= min)
                return;}}


    if( equal)
    {
        min = jolts;
        return;}
#line 1207 "Day10.md"
    num_t max_single;
    int single_p =- 1;
    for( int p =0;  p < nr_pos; p++)
    {
        if( jolting[p] > 0)
        {
            m = 0;

            for( int b =0;  b < nr_buttons; b++)
                if( !proc_buttons[b] && ((1 << p) & buttons[b]) != 0)
                    m++;
            if( m == 0)
                return;
            if( m == 1 && single_p == -1)
            {
                single_p = p;
                max_single = jolting[p];}}}
#line 1227 "Day10.md"
    if( single_p != -1)
    {
        if( jolts + max_single >= min)
            return;

        int b =0 ;
        while(b < nr_buttons && (proc_buttons[b] || ((1 << single_p) & buttons[b]) == 0))
            b++;


        proc_buttons[b] = TRUE;
        depth++;

        num_t old_jolting[100];
        for( int p =0;  p < nr_pos; p++)
        {
            old_jolting[p] = jolting[p];
            if( ((1 << p) & buttons[b]) != 0)
                jolting[p] -= max_single;}

        search_min_b(jolts + max_single);
        for( int p =0;  p < nr_pos; p++)
            jolting[p] = old_jolting[p];

        depth--;
        proc_buttons[b] = FALSE;

        return;}


    int sel_b =- 1;
    num_t sel_min =1000 ;
    for( int b =0;  b < nr_buttons; b++)
    {
        if( !proc_buttons[b])
        {
            for( int p =0;  p < nr_pos; p++)
                if( (((1 << p) & buttons[b]) != 0) && jolting[p] < sel_min)
                {
                    sel_b = b;
                    sel_min = jolting[p];}}}
#line 1272 "Day10.md"
    if( sel_b == -1)
        return;


    proc_buttons[sel_b] = TRUE;
    depth++;
#line 1283 "Day10.md"
    for( num_t r =sel_min;  r >= 0; r--)
        if( jolts + r < min)
        {
            num_t old_jolting[100];
            for( int p =0;  p < nr_pos; p++)
            {
                old_jolting[p] = jolting[p];
                if( ((1 << p) & buttons[sel_b]) != 0)
                    jolting[p] -= r;}

            search_min_b(jolts + r);
            for( int p =0;  p < nr_pos; p++)
                jolting[p] = old_jolting[p];}
#line 1305 "Day10.md"
    depth--;
    proc_buttons[sel_b] = FALSE;}
#line 1793 "Day10.md"
void solve_equations(int jolt, int button)
{
    if( button < 0)
    {
        if( jolt < min)
        {
            min = jolt;}

        return;}

    if( jolt >= min)
        return;

    int pos = reduced_on_pos[button];
    if( pos >= 0)
    {
        num_t value = jolting[pos];
        for( int b = button+  1; b < nr_buttons; b++)
            value -= matrix[pos][b] * button_presses[b];
        num_t factor = matrix[pos][button];

        if( factor < 0)
        {
            factor = -factor;
            value = -value;}

        if( value < 0)
            return;
        if( factor > 1)
        {
            if( value % factor != 0)
                return;
            value /= factor;}

        jolt += value;
        if( jolt < min)
        {
            button_presses[button] = value;

            depth++;
            solve_equations(jolt, button - 1);
            depth--;}}


    else{

        button_presses[button] = 0;
        while( jolt < min)
        {

            depth++;
            solve_equations(jolt, button - 1);
            depth--;
            button_presses[button]++;
            jolt++;}}}

// *** others ***
