# Day 3 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	long sum = 0;
	for (int i = 0; i < n; i++)
	{
		char ch1 = '0';
		char ch2 = '0';
		int val = 0;
		for (int j1 = 0; j1 + 1 < m; j1++)
			if (d[i][j1] > ch1)
			{
				ch1 = d[i][j1];
				ch2 = '0';
				for (int j2 = j1 + 1; j2 < m; j2++)
					if (d[i][j2] > ch2)
						ch2 = d[i][j2];
			}
		sum += 10 * (ch1 - '0') + (ch2 - '0');
	}
				
	printf("%ld\n", sum);
}
```

At 6:13:16, after I fixed some small bugs (like using 'j' instead of 'j2'), 
the program returned the correct answer.

### Second part of the puzzle.

```c
char max[12];
num_t num = 0;

void search(int left, int i, int j)
{
	if (left == 0)
		return;
	char pos = 12 - left;
	int till = m - left + 1;
	max[pos] = '0';
	for (int j1 = j; j1 < till; j1++)
		if (d[i][j1] > max[pos])
		{
			max[pos] = d[i][j1];
			search(left - 1, i, j1 + 1);
		}
}		

void solve2()
{
	num_t sum = 0;
	for (int i = 0; i < n; i++)
	{
		search(12, i, 0);
		num_t value = 0;
		for (int j = 0; j < 12; j++)
			value = 10 * value + max[j] - '0';
		sum += value;
	}
	printf("%lld", sum);		
}

```

The above solution is basically implementing 12 nested loop with
the recursive function `search`. I had to fix some bug, one being
forgetting the variable `i` to the recursive function.
At 6:29:01, the program returned the correct answer.

### Further improvements

The second part require at bit more than 4 seconds to finish. I think
there is a faster way to find a solution, also one that does not
require recursion.

```c
void solve2()
{
	num_t sum = 0;
	for (int i = 0; i < n; i++)
	{
		num_t value = 0;
		int j = 0;
		for (int p = 0; p < 12; p++)
		{
			int till = m - 11 + p;
			int max_j = j;
			char max = d[i][j];
			for (int j1 = j; j1 < till; j1++)
				if (d[i][j1] > max)
				{
					max = d[i][j1];
					max_j = j1;
				}
			value = 10 * value + max - '0';
			j = max_j + 1;
		}
		sum += value;
	}
	printf("%lld\n", sum);
}
```

At 6:50, this returned the same answer as before.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day03.md >day03.c; gcc -g -Wall day03.c -o day03; ./day03 03
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `03` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day01.c](day01.c).



