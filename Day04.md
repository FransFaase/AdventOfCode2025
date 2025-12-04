# Day 4 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	int removable = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (d[i][j] == '@')
			{
				int count = 0;
				for (int i1 = -1; i1 <= 1; i1++)
					for (int j1 = -1; j1 <= 1; j1++)
						if (dd(i + i1, j + j1) == '@')
							count++;
				if (count < 5)
					removable++;
			}
	printf("%ld\n", removable);
}
```

At 6:06:53, the above code returned the correct answer for at a second attempt, after I
realized that it read 'fewer than four' and that it should have been `count < 5`
instead of `count <= 5` as I submitted on the first try.

### Second part of the puzzle.

```c
void solve2()
{
	int removable = 0;
	for (bool go = TRUE; go;)
	{
		go = FALSE;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (d[i][j] == '@')
				{
					int count = 0;
					for (int i1 = -1; i1 <= 1; i1++)
						for (int j1 = -1; j1 <= 1; j1++)
							if (dd(i + i1, j + j1) == '@')
								count++;
					if (count < 5)
					{
						go = TRUE;
						d[i][j] = 'x';
						removable++;
					}
				}
	}
	printf("%ld\n", removable);
}

```

At 6:10:33, the above code returned the correct answer, after I had fixed two
typing errors.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day04.md >day04.c; gcc -g -Wall day04.c -o day04; ./day04 04
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `04` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day01.c](day01.c).



