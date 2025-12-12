# Day 12 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

At 6:05, I am afraid this is going to be the hardest puzzle of all puzzles.
I do not know if there is a second part, but the first part already looks very
hard. This is a cover problem, not an exact cover problem, but similar. The number
of pieces to be fitted in are huge. Now, lets first try to write some code to
parse the input.

```c

int nr_variants[6];
char pieces[6][8][3][3];
int piece_size[6];

void solve1()
{
	for (int p = 0; p < 6; p++)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				pieces[p][0][i][j] = d[1 + 5 * p + i][j];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%c", pieces[p][0][i][j]);
			printf("\n");
		}
		printf("\n");
	}
}
```

At 6:15, lets add code to calculate the variants;

```c
void solve1()
{
	for (int p = 0; p < 6; p++)
	{
		char piece[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				piece[i][j] = pieces[p][0][i][j] = d[1 + 5 * p + i][j];

		nr_variants[p] = 1;
		for (int f = 0; f < 2; f++)
		{
			// 0,0 0,1 0,2
			// 1,0     1,2
			// 2,0 2,1 2,2
			for (int r = 0; r < 4; r++)
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
				
				bool equal = FALSE;
				for (int v = 0; v < nr_variants[p]; v++)
				{
					equal = TRUE;
					for (int i = 0; i < 3 && equal; i++)
						for (int j = 0; j < 3 && equal; j++)
							equal = pieces[p][v][i][j] == piece[i][j];
				}
				if (!equal)
				{
					int v = nr_variants[p];
					for (int i = 0; i < 3; i++)
						for (int j = 0; j < 3; j++)
							pieces[p][v][i][j] = piece[i][j];
					nr_variants[p]++;
				}
			}
			for (int i = 0; i < 3; i++)
			{
				int h = piece[i][0];
				piece[i][0] = piece[i][2];
				piece[i][2] = h;
			}
		}
		printf("Variants = %d\n", nr_variants[p]);
		for (int v = 0; v < nr_variants[p]; v++)
		{				
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					printf("%c", pieces[p][v][i][j]);
				printf("\n");
			}
			printf("\n");
		}
	}
}
```

At 6:34, that returns 9 variants per piece, which is impossible.

```c
void solve1()
{
	for (int p = 0; p < 6; p++)
	{
		char piece[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				piece[i][j] = pieces[p][0][i][j] = d[1 + 5 * p + i][j];

		nr_variants[p] = 1;
		for (int f = 0; f < 2; f++)
		{
			// 0,0 0,1 0,2
			// 1,0     1,2
			// 2,0 2,1 2,2
			for (int r = 0; r < 4; r++)
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
				
				bool equal = FALSE;
				for (int v = 0; v < nr_variants[p] && !equal; v++)
				{
					equal = TRUE;
					for (int i = 0; i < 3 && equal; i++)
						for (int j = 0; j < 3 && equal; j++)
							equal = pieces[p][v][i][j] == piece[i][j];
				}
				if (!equal)
				{
					int v = nr_variants[p];
					for (int i = 0; i < 3; i++)
						for (int j = 0; j < 3; j++)
							pieces[p][v][i][j] = piece[i][j];
					nr_variants[p]++;
				}
			}
			for (int i = 0; i < 3; i++)
			{
				int h = piece[i][0];
				piece[i][0] = piece[i][2];
				piece[i][2] = h;
			}
		}
		printf("Variants = %d\n", nr_variants[p]);
		for (int v = 0; v < nr_variants[p]; v++)
		{				
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					printf("%c", pieces[p][v][i][j]);
				printf("\n");
			}
			printf("\n");
		}
	}
}
```

At 6:36, fixed the problem by add `&& !equal` to condition of the for loop over `v`.
Lets remove all the print statements and parse the rest of the lines to get some
idea about how tight the conditions are.

```c
void solve1()
{
	for (int p = 0; p < 6; p++)
	{
		char piece[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				piece[i][j] = pieces[p][0][i][j] = d[1 + 5 * p + i][j];

		nr_variants[p] = 1;
		for (int f = 0; f < 2; f++)
		{
			// 0,0 0,1 0,2
			// 1,0     1,2
			// 2,0 2,1 2,2
			for (int r = 0; r < 4; r++)
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
				
				bool equal = FALSE;
				for (int v = 0; v < nr_variants[p] && !equal; v++)
				{
					equal = TRUE;
					for (int i = 0; i < 3 && equal; i++)
						for (int j = 0; j < 3 && equal; j++)
							equal = pieces[p][v][i][j] == piece[i][j];
				}
				if (!equal)
				{
					int v = nr_variants[p];
					for (int i = 0; i < 3; i++)
						for (int j = 0; j < 3; j++)
							pieces[p][v][i][j] = piece[i][j];
					nr_variants[p]++;
				}
			}
			for (int i = 0; i < 3; i++)
			{
				int h = piece[i][0];
				piece[i][0] = piece[i][2];
				piece[i][2] = h;
			}
			piece_size[p] = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (piece[i][j] == '#')
						piece_size[p]++;
		}
	}
	
	for (int i = 30; i < n; i++)
		solve_line(i);
}

void solve_line(int i)
{
	char *s = d[i];
	int w = parse_number(&s);
	s++;
	int h = parse_number(&s);
	s += 2;
	int sum = 0;
	int nr_per_piece[6];
	for (int p = 0; p < 6; p++)
	{
		nr_per_piece[p] = parse_number(&s);
		s++;
		sum += piece_size[p] * nr_per_piece[p];
	}
	int area = w * h;
	int empty = area - sum;
	printf("%d %d %d\n", area, sum, empty);			
}

```

At 6:52, it looks like there is either just not enough space or a lot left.
Lets asume that if there is a lot of space left, it will work.
(I corrected the number of number of pieces from 5 to 6 in all of the above code
fragments)

```c
void solve1()
{
	for (int p = 0; p < 6; p++)
	{
		char piece[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				piece[i][j] = pieces[p][0][i][j] = d[1 + 5 * p + i][j];

		nr_variants[p] = 1;
		for (int f = 0; f < 2; f++)
		{
			// 0,0 0,1 0,2
			// 1,0     1,2
			// 2,0 2,1 2,2
			for (int r = 0; r < 4; r++)
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
				
				bool equal = FALSE;
				for (int v = 0; v < nr_variants[p] && !equal; v++)
				{
					equal = TRUE;
					for (int i = 0; i < 3 && equal; i++)
						for (int j = 0; j < 3 && equal; j++)
							equal = pieces[p][v][i][j] == piece[i][j];
				}
				if (!equal)
				{
					int v = nr_variants[p];
					for (int i = 0; i < 3; i++)
						for (int j = 0; j < 3; j++)
							pieces[p][v][i][j] = piece[i][j];
					nr_variants[p]++;
				}
			}
			for (int i = 0; i < 3; i++)
			{
				int h = piece[i][0];
				piece[i][0] = piece[i][2];
				piece[i][2] = h;
			}
			piece_size[p] = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (piece[i][j] == '#')
						piece_size[p]++;
		}
	}
	
	int nr_fit = 0;
	for (int i = 30; i < n; i++)
		if (solve_line(i))
			nr_fit++;
	printf("%d\n", nr_fit);
}

bool solve_line(int i)
{
	char *s = d[i];
	int w = parse_number(&s);
	s++;
	int h = parse_number(&s);
	s += 2;
	int sum = 0;
	int nr_per_piece[6];
	for (int p = 0; p < 6; p++)
	{
		nr_per_piece[p] = parse_number(&s);
		s++;
		sum += piece_size[p] * nr_per_piece[p];
	}
	int area = w * h;
	int empty = area - sum;
	printf("%d %d %d\n", area, sum, empty);
	return empty > 0;
}

```

At 6:56:39, I submitted the correct answer from the above code.


### Second part of the puzzle.

```c
void solve2()
{
}

```

The second part was just having solved the first part and
all parts of the earlier days.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day12.md >day12.c; gcc -g -Wall day12.c -o day12; ./day12 12
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `12` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day12.c](day12.c).



