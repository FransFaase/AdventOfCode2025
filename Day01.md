# Day 1 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	num_t pos = 50;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		char dir = *s++;
		num_t clicks = parse_number(&s);
		if (dir == 'R')
			pos = (pos + clicks) % 100;
		else
		{
			pos -= clicks;
			while (pos < 0)
				pos += 100;
		}
		if (pos == 0)
			count++;
	}
	printf("%d\n", count);
}
```

This gave the correct answer in one try at 6:09:36.

### Second part of the puzzle.

```c
void solve2()
{
	num_t pos = 50;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		char dir = *s++;
		num_t clicks = parse_number(&s);
		if (dir == 'R')
		{
			pos += clicks;
			while (pos >= 100)
			{
				pos -= 100;
				count++;
			}
		}
		else
		{
			pos -= clicks;
			while (pos < 0)
			{
				pos += 100;
				count++;
			}
		}
		if (pos == 0)
			count++;
	}
	printf("%d\n", count);
}

```

At 6:13, this returned an incorrect answer, as I already somewhat
had expected due to counting a 0 click twice. But I decided to
submit it anyways, because my input could not have had such a
situation, I though (which was wrong of course).

```c
void solve2()
{
	num_t pos = 50;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		char dir = *s++;
		num_t clicks = parse_number(&s);
		if (dir == 'R')
		{
			for (int j = 0; j < clicks; j++)
			{
				pos++;
				if (pos == 100)
				{
					pos = 0;
					count++;
				}
			}
		}
		else
		{
			for (int j = 0; j < clicks; j++)
			{
				pos--;
				if (pos == 0)
					count++;
				if (pos < 0)
					pos += 100;
			}
		}
	}
	printf("%d\n", count);
}

```

At 9:17:35, this gave the correct answer. I just went for a kind of
brute force solution, just to avoid another counting error. It is
a bit lame, but as it is often better to go for a solution that is
obviously correct but not most efficient.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day01.md >day01.c; gcc -g -Wall day01.c -o day01; ./day01 01
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `01` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day01.c](day01.c).


