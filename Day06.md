# Day 6 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	num_t sum = 0;
	char *s = d[n - 1];
	for (int j = 0; s[j] != '\0';)
	{
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (int i = 0; i < n - 1; i++)
		{
			char *v = d[i][j];
			num_t value = parse_number(&v);
			if (mode == '+')
				result += value;
			else
				result *= value;
		} 
		sum += result;
		while (s[j] == ' ') j++;
	}
	printf("%lld\n", sum);
}
```

At 6:10, this returned a segmentation error.

```c
void solve1()
{
	num_t sum = 0;
	char *s = d[n - 1];
	for (int j = 0; s[j] == '+' || s[j] == '*';)
	{
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (int i = 0; i < n - 1; i++)
		{
			char *v = d[i][j];
			num_t value = parse_number(&v);
			if (mode == '+')
				result += value;
			else
				result *= value;
		} 
		sum += result;
		while (s[j] == ' ') j++;
	}
	printf("%lld\n", sum);
}
```

At 6:12, the above code gets into an infinite loop.

```c
void solve1()
{
	num_t sum = 0;
	printf("%d\n", n);
	char *s = d[n - 1];
	for (int j = 0; s[j] == '+' || s[j] == '*';)
	{
		printf("%d\n", j);
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (int i = 0; i < n - 1; i++)
		{
			char *v = &d[i][j];
			num_t value = parse_number(&v);
			if (mode == '+')
				result += value;
			else
				result *= value;
		} 
		sum += result;
		j++;
		while (s[j] == ' ') j++;
		printf("%d\n", j);
	}
	printf("%lld\n", sum);
}
```

At 6:20, saving my input file (something I have forgotten in previous days as well),
after fixing some problems in the above code, and adding the `-Wall -Werror` to
the `gcc` compiler, the above program did return some result but it was not the correct
result. Let try it on the example input.

```c
bool use_sample = TRUE;
void solve1()
{
	num_t sum = 0;
	char *s = d[n - 1];
	for (int j = 0; s[j] == '+' || s[j] == '*';)
	{
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (int i = 0; i < n - 1; i++)
		{
			char *v = &d[i][j];
			while (*v == ' ') v++;
			num_t value = parse_number(&v);
			printf("%c %lld %lld\n", mode, result, value);
			if (mode == '+')
				result += value;
			else
				result *= value;
		}
		printf("%lld\n", result); 
		sum += result;
		j++;
		while (s[j] == ' ') j++;
	}
	printf("%lld\n", sum);
}
```

At 6:27, that returned the correct answer for the example input after I added
a statement to skip spaces at the start. I had assumed that all numbers lined
up with the '+' or '*' in the last line.

```c
bool use_sample = FALSE;
```

At 6:28:07, that returned the correct answer for my input.


### Second part of the puzzle.

```c
void solve2()
{
	num_t sum = 0;
	char *s = d[n - 1];
	for (int j = 0; s[j] == '+' || s[j] == '*';)
	{
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (int i = 0; i < n - 1; i++)
		{
			num_t value = 0;
			bool digits = FALSE;
			for (int i = n - 2; i >= 0; i--)
				if ('0' <= d[i][j] && d[i][j] <= '9')
				{
					digits = TRUE;
					value = 10 * value + d[i][j] - '0';
				}
			if (!digits)
				break;
			printf("%c %lld %lld\n", mode, result, value);
			if (mode == '+')
				result += value;
			else
				result *= value;
		}
		printf("%lld\n", result); 
		sum += result;
		j++;
		while (s[j] == ' ') j++;
	}
	printf("%lld\n", sum);
}

```

At 6:35, that did not return the correct answer. Lets try with example input.


```c
bool use_sample = TRUE;
void solve2()
{
	num_t sum = 0;
	char *s = d[n - 1];
	for (int j = 0; s[j] == '+' || s[j] == '*';)
	{
		char mode = s[j];
		num_t result = mode == '+' ? 0 : 1;
		for (;;)
		{
			num_t value = 0;
			bool digits = FALSE;
			for (int i = 0; i < n - 1; i++)
				if ('0' <= d[i][j] && d[i][j] <= '9')
				{
					digits = TRUE;
					value = 10 * value + d[i][j] - '0';
				}
			if (!digits)
				break;
			printf("%c %lld %lld\n", mode, result, value);
			if (mode == '+')
				result += value;
			else
				result *= value;
			j++;
		}
		printf("%lld\n", result); 
		sum += result;
		j++;
		while (s[j] == ' ') j++;
	}
	printf("%lld\n", sum);
}

```

At 6:41, that returned the correct answer for the sample input after
I ran it several times and made some modifications. I was reading the
digits in the wrong direction.


```c
bool use_sample = FALSE;
```

At 6:42:29, that returned the correct answer for my puzzle input.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day06.md >day06.c; gcc -g -Wall day06.c -o day06; ./day06 06
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `06` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day06.c](day06.c).



