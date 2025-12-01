# Some standard definition and generic code

First some standard includes:

```c
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "unistd.h"
```

Some standard type definitions:
```c
typedef long long num_t;
typedef int bool;
#define FALSE 0
#define TRUE 1

```

A function to read the input into a array of lines:

```c
typedef char *char_p;

char **d;
int n;
int m;
bool use_sample = FALSE;

void read_input(const char *day)
{
    n = 0;
    m = 0;
    char filename[50];
    sprintf(filename, use_sample ? "day%s.txt" : "input/day%s.txt", day);
    FILE *f = fopen(filename, "r");
    if (f == 0)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }
    int fh = fileno(f);
    size_t length = lseek(fh, 0L, SEEK_END);
    lseek(fh, 0L, SEEK_SET);
    char *data = (char*)malloc(length);
    length = read(fh, data, length);
    fclose(f);
    
    // count the number of lines in the file
    for (int i = 0; i < length; i++)
        if (data[i] == '\n')
            n++;
    
    d = (char**)malloc(n * sizeof(char_p));
    char *s = data;
    for (int i = 0; i < n; i++)
    {
        d[i] = s;
        
        int j =  0;
        while (*s != '\n')
        {
            if (*s == '\r)
                *s = '\0';
               else
                   j++;
            s++;
        }
        if (j > m)
            m = j;
        *s++ = '\0';
    }
}

char dd(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m ? d[i][j] : ' '; }


void pre()
{
}

int main(int argc, char *argv[])
{
    int len = strlen(argv[0]);
    if (len <= 2)
    {
        printf("Program name should be longer than two.\n");
        return 0;
    }
    
    pre();
    
    read_input(argv[0] + len - 2);
    
    solve1();
    solve2();
}

```

A function to parse a number from a string.

```c

bool is_digit(char c) { return '0' <= c && c <= '9'; }

num_t parse_number(char **s)
{
    int sign = 1;
    if (**s == '-')
    {
        sign = -1;
        (*s)++;
    }
    num_t value = 0;
    for (;is_digit(**s); (*s)++)
        value = 10 * value + **s - '0';
    return sign * value;
}
```


### Greatest Common Divisor and Smallest Commoon Multiplier

```c
num_t gcd(num_t a, num_t b)
{
    while (a != 0)
    {
        num_t c = b % a;
        b = a;
        a = c;
    }
    return b;
}

num_t scm(num_t a, num_t b) { return a * (b / gcd(a, b)); }
num_t num_t_abs(num_t a) { return a < 0 ? -a : a; }
int num_t_sign(num_t a) { return a < 0 ? -1 : a > 0 ? 1 : 0; }

```

### Basic string function

```c
char *copy_str(char *s)
{
    char *r = (char*)malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}
```
 