# Day 02 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	long count = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);
		
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			for (num_t h = h1; h <= h2; h++)
			{
				num_t i = factor * h + h;
				if (n1 <= i && i <= n2)
					count++;
			}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%d\n", count);
}
```

At 6:27, after making some edits that returned a 'Segmentation fault'.

```c
void solve1()
{
	long count = 0;
	char *s = d[0];
	for (;;)
	{
		printf("%s\n", s);
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);
		
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			for (num_t h = h1; h <= h2; h++)
			{
				num_t i = factor * h + h;
				if (n1 <= i && i <= n2)
					count++;
			}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%d\n", count);
}
```

At 6:33, it appeared that I had not yet saved my puzzle input. The
program returned the incorrect result. Lets add some more debug code.

```c
void solve1()
{
	long count = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			printf("  %lld - %lld\n", h1, h2);
			for (num_t h = h1; h <= h2; h++)
			{
				num_t i = factor * h + h;
				printf("   - %lld", i);
				if (n1 <= i && i <= n2)
				{
					count++;
					printf(" *");
				}
				printf("\n");
			}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%d\n", count);
}
```

At 6:39, I think, I see the bug. I did include solutions with odd number length;

 
```c
void solve1()
{
	long count = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			printf("  %lld - %lld\n", h1, h2);
			for (num_t h = h1; h <= h2; h++)
				if (h * 10 >= factor)
				{
					num_t i = factor * h + h;
					printf("   - %lld", i);
					if (n1 <= i && i <= n2)
					{
						count++;
						printf(" *");
					}
					printf("\n");
				}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%d\n", count);
}
```

At 6:45, this did still not return the correct answer.
At 6:51, I understood that you have to add up the IDs, instead of counting them.

```c
void solve1()
{
	long sum = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			printf("  %lld - %lld\n", h1, h2);
			for (num_t h = h1; h <= h2; h++)
				if (h * 10 >= factor)
				{
					num_t i = factor * h + h;
					printf("   - %lld", i);
					if (n1 <= i && i <= n2)
					{
						sum += i;
						printf(" *");
					}
					printf("\n");
				}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%d\n", sum);
}
```

At 6:53, that returned a negative number, probably caused by an overflow.

```c
void solve1()
{
	num_t sum = 0;
	char *s = d[0];
	printf("'%s'\n", s);
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			printf("  %lld - %lld\n", h1, h2);
			for (num_t h = h1; h <= h2; h++)
				if (h * 10 >= factor)
				{
					num_t i = factor * h + h;
					printf("   - %lld", i);
					if (n1 <= i && i <= n2)
					{
						sum += i;
						printf(" *");
					}
					printf("\n");
				}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%lld\n", sum);
}
```

At 6:55, that still did not return the correct number. Lets test with the example input.

```c
bool use_sample = TRUE;

```

At 7:07, I noticed that in the first range, it also includes `110`.

```c
void solve1()
{
	num_t sum = 0;
	char *s = d[0];
	printf("'%s'\n", s);
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				printf("Also 12 digit numbers\n");
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			printf("  %lld - %lld: %lld\n", h1, h2, factor);
			for (num_t h = h1; h <= h2; h++)
				if (h * 10 >= factor && h < factor)
				{
					num_t i = factor * h + h;
					printf("   - %lld", i);
					if (n1 <= i && i <= n2)
					{
						sum += i;
						printf(" *");
					}
					printf("\n");
				}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%lld\n", sum);
}
```

At 7:13, this returned the correct answer for the example input.

```c
bool use_sample = FALSE;

```

At 7:14:05, that returned the correct answer.

### Second part of the puzzle.

```c
bool use_sample = TRUE;

void solve2()
{
	num_t sum = 0;
	char *s = d[0];
	printf("'%s'\n", s);
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		printf("%lld-%lld\n", n1, n2);
		for (num_t n = n1; n <= n2; n++)
		{
			char buf[20];
			snprintf(buf, 19, "%lld", n);
			int l = strlen(buf);
			
			bool match = FALSE;
			for (int m = 2; m <= l; m++)
			{
				if (l % m == 0)
				{
					match = TRUE;
					int w = l / m;
					printf("try multiple of %d with width %d:", m, w);
					for (int i = 1; i < m; i++)
						for (int j = 0; j < w; j++)
						{
							printf(" %d-%d", j, j + i * w);
							if (buf[j] != buf[j + i * w])
								match = FALSE;
						}
					printf("\n");
				}
				if (match)
					break;
			}
			if (match)
			{
				printf("- %lld\n", n);
				sum += n;
			}
		}
		
		if (*s != ',')
			break;
		s++;
	}
	printf("%lld\n", sum);
}

```

At 7:42, after several tries, the above code returned the correct answer for the example input;

```c
bool use_sample = FALSE;
```

At 7:44:30, that returned the correct answer for the second part.

### Code clean-up

Belov the code with all debugging statements removed:

```c
void solve1()
{
	num_t sum = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		if (l1 % 2 == 0 || l2 % 2 == 0)
		{
			int l = l1 % 2 == 0 ? l1 : l2;
			num_t factor = l ==  2 ?     10 :
			               l ==  4 ?    100 :
			               l ==  6 ?   1000 :
			               l ==  8 ?  10000 :
			               l == 10 ? 100000 : 0;
			if (l == 0)
			{
				return;
			}
			num_t h1 = n1 / factor;
			num_t h2 = n2 / factor;
			for (num_t h = h1; h <= h2; h++)
				if (h * 10 >= factor && h < factor)
				{
					num_t i = factor * h + h;
					if (n1 <= i && i <= n2)
						sum += i;
				}
		}
		if (*s != ',')
			break;
		s++;
	}
	printf("%lld\n", sum);
}

void solve2()
{
	num_t sum = 0;
	char *s = d[0];
	for (;;)
	{
		char *s2 = s;
		int l1 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l1++;
		}
		s2++;
		int l2 = 0;
		while (is_digit(*s2))
		{
			s2++;
			l2++;
		}
		
		num_t n1 = parse_number(&s);
		s++;
		num_t n2 = parse_number(&s);

		for (num_t n = n1; n <= n2; n++)
		{
			char buf[20];
			snprintf(buf, 19, "%lld", n);
			int l = strlen(buf);
			
			bool match = FALSE;
			for (int m = 2; m <= l; m++)
			{
				if (l % m == 0)
				{
					match = TRUE;
					int w = l / m;
					for (int i = 1; i < m; i++)
						for (int j = 0; j < w; j++)
							if (buf[j] != buf[j + i * w])
								match = FALSE;
				}
				if (match)
					break;
			}
			if (match)
				sum += n;
		}
		
		if (*s != ',')
			break;
		s++;
	}
	printf("%lld\n", sum);
}

```



### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day02.md >day02.c; gcc -g -Wall day02.c -o day02; ./day02 02
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `02` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day02.c](day02.c).



