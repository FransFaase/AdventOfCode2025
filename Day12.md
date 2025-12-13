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

### Extra 

The reddit post [Page two of the list](https://www.reddit.com/r/adventofcode/comments/1pkl4gb/2025_day_12_part_3_page_two_of_the_list/)
made me decide to continue working on the algorithm that I had
initial in mind to solve the original puzzle.

```c
bool use_sample = TRUE;

bool solve_line(int i)
{
	char *s = d[i];
	int w = parse_number(&s);
	s++;
	int h = parse_number(&s);
	s += 2;
	int sum = 0;
	int nr_pieces = 0;
	int nr_per_piece[6];
	for (int p = 0; p < 6; p++)
	{
		nr_per_piece[p] = parse_number(&s);
		s++;
		nr_pieces += nr_per_piece[p];
		sum += piece_size[p] * nr_per_piece[p];
	}
	int area = w * h;
	int empty = area - sum;
	if (empty < 0)
	{
		//printf("%2d: rectangle are smaller than area of pieces\n", i);
		return FALSE;
	}
	if (nr_pieces <= (w / 3) * (h / 3))
	{
		//printf("%d: The %d by %d rectangle can be filled with %d 3x3 squares, which is more than %d pieces\n",
		//	i, w, i, (w / 3) * (h / 3), nr_pieces);
		return TRUE;
	}
	// We do not know
	printf("%3d: '%s' %d %d %d, %dx%d=%d %d\n", i + 1, d[i], area, sum, empty, w / 3, h / 3, (w / 3) * (h / 3), (w / 3) * (h / 3) - nr_pieces);
	return FALSE;
}
```

The above code outputs the following three lines (in 0.001 seconds):

```
686: '28x18: 0 72 0 0 0 0' 504 504 0, 9x6=54 -18
717: '18x12: 6 4 4 4 6 4' 216 178 38, 6x4=24 -4
437
```

It seems, that there is only one hard region. Many have to many shapes to
fit in the region and there are also many where the shapes fit in the region
if they are placed (randomly) on a 3x3 grip. The only two cases that are
left are regions on line 686 and 717. It seems rather obvious that the
region on line 686 cannot be filled with 72 copies of second shape. That
only leaves the region on line 717 to be determined. 

At 15:30, I reloaded the input. Now it return three hard regions:
```
 58: '18x12: 6 4 4 4 6 4' 216 178 38, 6x4=24 -4
317: '20x21: 0 0 0 0 70 0' 420 420 0, 6x7=42 -28
418: '28x18: 0 72 0 0 0 0' 504 504 0, 9x6=54 -18
436
```

I continued developing the code.

```c
int pieces_j[6][8];

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
		for (int v = 0; v < nr_variants[p]; v++)
		{
			for (int j = 0; j < 3; j++)
				if (pieces[p][v][0][j] == '#')
				{
					pieces_j[p][v] = j;
					break;
				}
		}
	}
	
	int nr_fit = 0;
	for (int i = 30; i < n; i++)
		if (solve_line(i))
			nr_fit++;
	printf("%d\n", nr_fit);
}

int nr_per_piece[6];

int h, w;
char region[100][100];

bool solve_line(int i)
{
	char *s = d[i];
	w = parse_number(&s);
	s++;
	h = parse_number(&s);
	s += 2;
	int sum = 0;
	int nr_pieces = 0;
	for (int p = 0; p < 6; p++)
	{
		nr_per_piece[p] = parse_number(&s);
		s++;
		nr_pieces += nr_per_piece[p];
		sum += piece_size[p] * nr_per_piece[p];
	}
	int area = w * h;
	int empty = area - sum;
	if (empty < 0)
	{
		//printf("%2d: rectangle are smaller than area of pieces\n", i);
		return FALSE;
	}
	if (nr_pieces <= (w / 3) * (h / 3))
	{
		//printf("%d: The %d by %d rectangle can be filled with %d 3x3 squares, which is more than %d pieces\n",
		//	i, w, i, (w / 3) * (h / 3), nr_pieces);
		return TRUE;
	}
	// We do not know
	printf("%3d: '%s' %d %d %d, %dx%d=%d %d\n", i + 1, d[i], area, sum, empty, w / 3, h / 3, (w / 3) * (h / 3), (w / 3) * (h / 3) - nr_pieces);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			region[i][j] = '.';
	return find(0, 0, nr_pieces, empty);
}

bool find(int i, int j, int left_pieces, int empty)
{
	if (left_pieces == 0)
	{
		for (int i1 = 0; i1 < h; i1++)
		{
			for (int j1 = 0; j1 < w; j1++)
				printf("%c", region[i1][j1]);
			printf("\n");
		}
		return TRUE;
	}
		
	// search for the next unfilled spot in the region.
	for (;;)
	{
		if (region[i][j] == '.')
			break;
		if (++j >= w)
		{
			j = 0;
			if (++i >= h)
				return FALSE;
		}
	}
	
	for (int p = 0; p < 6; p++)
		if (nr_per_piece[p] > 0)
		{
			for (int v = 0; v < nr_variants[p]; v++)
			{
				int i1 = i;
				int j1 = j - pieces_j[p][v];
				if (0 <= i1 && i1 + 2 < h && 0 <= j1 && j1 + 2 < w)
				{
					bool fits = TRUE;
					for (int i2 = 0; i2 < 3 && fits; i2++)
						for (int j2 = 0; j2 < 3 && fits; j2++)
							fits = pieces[p][v][i2][j2] == '.' || region[i1 + i2][j1 + j2] == '.';
					if (fits)
					{
						nr_per_piece[p]--;
						for (int i2 = 0; i2 < 3; i2++)
							for (int j2 = 0; j2 < 3; j2++)
								if (pieces[p][v][i2][j2] == '#')
									region[i1 + i2][j1 + j2] = 'a' + left_pieces % 26;
						if (find(i, j, left_pieces - 1, empty))
							return TRUE;
						nr_per_piece[p]++;
						for (int i2 = 0; i2 < 3; i2++)
							for (int j2 = 0; j2 < 3; j2++)
								if (pieces[p][v][i2][j2] == '#')
									region[i1 + i2][j1 + j2] = '.';
					}
				}
			}
		}
	if (empty > 0)
		return find(i + 1, j, left_pieces, empty - 1);
	return FALSE;
}

```

The above code can process the second list and return the correct answer.
The program takes less than 1 second to complete.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day12.md >day12.c; gcc -g -Wall day12.c -o day12; ./day12 12
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `12` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day12.c](day12.c).



