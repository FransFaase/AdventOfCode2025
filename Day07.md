# Day 7 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

At 6:03, lets just count the number of '^' characters :-).

```c
void solve1()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (d[i][j] == '^')
				count++;
	printf("%lld\n", count);
}
```

At 6:05, that does not the right answer, as I had somehow expected, but nevertheless
it could have been a lucky guess.

```c
void solve1()
{
	num_t count = 0;
	// Search for the S character;
	for (int j = 0; j < 0; j++)
		if (d[0][j] == 'S')
		{
			d[1][j] = '|';
			break;
		}
	for (int i = 1; i + 1 < n; i++)
		for (int j = 1; j + 1 < m; j++)
			if (d[i][j] == '|')
			{
				if (d[i+1][j] == '^')
				{
					count++;
					d[i+1][j-1] = '|';
					d[i+1][j+1] = '|';
				}
				else
					d[i+1][j] = '|';
			}
	printf("%lld\n", count);
}
```

At 6:13, this return 0, due to a small mistake in the first 'for' statement where
`j < 0` is used.

```c
void solve1()
{
	num_t count = 0;
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			d[1][j] = '|';
			break;
		}
	for (int i = 1; i + 1 < n; i++)
		for (int j = 1; j + 1 < m; j++)
			if (d[i][j] == '|')
			{
				if (d[i+1][j] == '^')
				{
					count++;
					d[i+1][j-1] = '|';
					d[i+1][j+1] = '|';
				}
				else
					d[i+1][j] = '|';
			}
	printf("%lld\n", count);
}
```

At 6:17:28, I submitted the correct answer from the above code.

### Second part of the puzzle.

```c
void solve2()
{
	num_t beams[100];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[100];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < 100; j++)
			if (beams[j] > 0 && d[i][j] == '^')
			{
				next_beams[j-1]++;
				next_beams[j+1]++;
			}
		for (int j = 0; j < 100; j++)
			beams[j] = next_beams[j];
	}
	num_t count = 0;
	for (int j = 0; j < 100; j++)
		count += beams[j];
	printf("%lld\n", count);
}

```

At 6:25, this returned 0 and a message that the stack was
crashed due to the value 100 being to low. Lets add a define
for this.

```c
#define M 200
void solve2()
{
	num_t beams[M];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[M];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < m; j++)
			if (beams[j] > 0 && d[i][j] == '^')
			{
				next_beams[j-1]++;
				next_beams[j+1]++;
			}
		for (int j = 0; j < M; j++)
			beams[j] = next_beams[j];
	}
	num_t count = 0;
	for (int j = 0; j < M; j++)
		count += beams[j];
	printf("%lld\n", count);
}

```

At 6:26, that returns a negative number, which was due to
some mixup of 'M' and 'm' causing unassigned array locations
being mixed in the answer.


```c
#define M 200
void solve2()
{
	num_t beams[M];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[M];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < m; j++)
			if (beams[j] > 0 && d[i][j] == '^')
			{
				next_beams[j-1]++;
				next_beams[j+1]++;
			}
		for (int j = 0; j < m; j++)
			beams[j] = next_beams[j];
		num_t count = 0;
		for (int j = 0; j < m; j++)
			count += beams[j];
		printf("%lld\n", count);
	}
}

```

At 6:29, that did return the number of beams at the end because I was
just adding one to when a beam is split, instead the number of beams that
came from above.

```c
#define M 200
void solve2()
{
	num_t beams[M];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[M];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < m; j++)
			if (beams[j] > 0 && d[i][j] == '^')
			{
				next_beams[j-1] += beams[j];
				next_beams[j+1] += beams[j];
			}
		for (int j = 0; j < m; j++)
			beams[j] = next_beams[j];
		num_t count = 0;
		for (int j = 0; j < m; j++)
			count += beams[j];
		printf("%lld\n", count);
	}
}

```

At 6:30 that did not return the correct answer. Let try the example input.

```c
bool use_sample = TRUE;
void solve2()
{
	num_t beams[M];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[M];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < m; j++)
			if (beams[j] > 0)
			{
				if (d[i][j] == '^')
				{
					next_beams[j-1] += beams[j];
					next_beams[j+1] += beams[j];
				}
				else
					next_beams[j] += beams[j];
			}
		for (int j = 0; j < m; j++)
			beams[j] = next_beams[j];
		num_t count = 0;
		for (int j = 0; j < m; j++)
			count += beams[j];
		printf("%lld\n", count);
	}
}
```

At 6.34, that return the correct answer for the example input.
I had forgotten to deal with the case that the beam is not split.

```c
bool use_sample = FALSE;
```

At 6:34:48, I submitted the correct answer from the above code.

### Extra

I wondered if it would be possible to get an answer just one lower
than the one found for the second part by adding/removing some of the
`^` in the puzzle input. After some programming, it looked it was
not that hard.

```c
int main(int argc, char *argv[])
{
	...
	solve3();
}

num_t count = 0;

void solve2()
{
	num_t beams[M];
	for (int j = 0; j < m; j++)
		beams[j] = 0;
	
	// Search for the S character;
	for (int j = 0; j < m; j++)
		if (d[0][j] == 'S')
		{
			beams[j] = 1;
			break;
		}
	for (int i = 2; i < n; i += 2)
	{
		num_t next_beams[M];
		for (int j = 0; j < m; j++)
			next_beams[j] = 0;
		for (int j = 0; j < m; j++)
			if (beams[j] > 0)
			{
				if (d[i][j] == '^')
				{
					next_beams[j-1] += beams[j];
					next_beams[j+1] += beams[j];
				}
				else
					next_beams[j] += beams[j];
			}
		for (int j = 0; j < m; j++)
			beams[j] = next_beams[j];
	}
	for (int j = 0; j < m; j++)
		count += beams[j];
	printf("%lld\n", count);
}

void solve3()
{
	int nr_changed = 1;
	num_t smallest_diff = -1;
	num_t largest_diff = 0;
	num_t nr_the_same = 0;
	num_t nr_one_less = 0;
	for (int level = 1; level < 5; level++)
	{
		nr_changed += level + 1;
		printf("%d\n", nr_changed);
		int i1 = 140 - 2 * level;
		int j1 = 3 + level;
		//for (int i = 0; i <= level; i++)
		//{
		//	for (int j = 0; j <= i; j++)
		//		printf("%c", d[i1 + 2 * i][j1 - i + 2*j]);
		//	printf("\n");
		//}
		//printf("\n");
		num_t max = 1 << nr_changed;
		for (num_t l = 0; l < max; l++)
		{
			num_t k = 1;
			for (int i = 0; i <= level; i++)
				for (int j = 0; j <= i; j++)
				{
					d[i1 + 2 * i][j1 - i + 2*j] = (k & l) == 0 ? '.' : '^';
					k *= 2;
				}
			
			num_t beams[M];
			for (int j = 0; j < m; j++)
				beams[j] = 0;
			
			// Search for the S character;
			for (int j = 0; j < m; j++)
				if (d[0][j] == 'S')
				{
					beams[j] = 1;
					break;
				}
			for (int i = 2; i < n; i += 2)
			{
				num_t next_beams[M];
				for (int j = 0; j < m; j++)
					next_beams[j] = 0;
				for (int j = 0; j < m; j++)
					if (beams[j] > 0)
					{
						if (d[i][j] == '^')
						{
							next_beams[j-1] += beams[j];
							next_beams[j+1] += beams[j];
						}
						else
							next_beams[j] += beams[j];
					}
				for (int j = 0; j < m; j++)
					beams[j] = next_beams[j];
			}
			num_t count2 = 0;
			for (int j = 0; j < m; j++)
				count2 += beams[j];
			num_t diff = count2 < count ? count - count2 : count2 - count;
			if (diff == 0)
				nr_the_same++;
			else if (smallest_diff == -1 || diff < smallest_diff)
			{
				smallest_diff = diff;
				printf("diff: %lld %lld\n", smallest_diff, count2);
			}
			if (diff > largest_diff && diff > smallest_diff)
			{
				largest_diff = diff;
				printf("diff: %lld %lld\n", largest_diff, count2);
			}				
			if (count2 + 1 == count)
			{
				nr_one_less++;
				printf("found %lld for: ", count2);
				num_t k = 1;
				for (int i = 0; i <= level; i++)
				{
					if (i > 0) printf("|");
					for (int j = 0; j <= i; j++)
					{
						printf("%c", (k & l) == 0 ? '.' : '^');
						k *= 2;
					}
				}
				printf("\n");
			}
		}
		printf("nr the same: %lld\n", nr_the_same);
		printf("nr one less: %lld\n", nr_one_less);
	}
}

```
### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day07.md >day07.c; gcc -g -Wall day07.c -o day07; ./day07 07
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `07` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day07.c](day07.c).



