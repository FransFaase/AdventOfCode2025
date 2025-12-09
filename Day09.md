# Day $ of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

At 6:04, I am going to steal some code from the previous day.

```c
typedef struct redtile_s redtile_t;
struct redtile_s {
	num_t x, y;
};
redtile_t redtiles[1000];

typedef struct area_s area_t;
struct area_s {
	int redtile1, redtile2;
	num_t area;
};
area_t areas[500*999]; 

void solve1()
{
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		redtiles[i].x = parse_number(&s);
		s++;
		redtiles[i].y = parse_number(&s);
	}
	
	// calculate areas
	int nr_area = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			areas[nr_area].redtile1 = i; 
			areas[nr_area].redtile2 = j;
			num_t dx = redtiles[i].x - redtiles[j].x;
			num_t dy = redtiles[i].y - redtiles[j].y;
			areas[nr_area].area = (dx + 1) * (dy + 1);
			nr_area++;
		} 

	qsort(areas, nr_area, sizeof(areas[0]), compare_area);
	printf("%lld\n", areas[0].area);
}

int compare_area(const void *a, const void *b)
{
	area_t *a_area = (area_t *)a;
	area_t *b_area = (area_t *)b;
	return   b_area->area < a_area->area ? -1
		   : b_area->area > a_area->area ? 1
		   : 0;
}
```

At 6:15, the above did not return the correct answer. Lets try on the example input.

```c
bool use_sample = TRUE;
```

At 6:17, that returned 1. (Later, I noticed, I had used the visualization as
input, not the list of coordinates.)

```c
bool use_sample = FALSE;
int compare_area(const void *a, const void *b)
{
	area_t *a_area = (area_t *)a;
	area_t *b_area = (area_t *)b;
	return   b_area->area < a_area->area ? 1
		   : b_area->area > a_area->area ? -1
		   : 0;
}
```

At 6:18, that returns a negative number.

```c
void solve1()
{
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		redtiles[i].x = parse_number(&s);
		s++;
		redtiles[i].y = parse_number(&s);
	}
	
	// calculate areas
	int nr_area = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			areas[nr_area].redtile1 = i; 
			areas[nr_area].redtile2 = j;
			num_t dx = redtiles[i].x - redtiles[j].x;
			if (dx < 0) dx = -dx;
			num_t dy = redtiles[i].y - redtiles[j].y;
			if (dy < 0) dy = -dy;
			areas[nr_area].area = (dx + 1) * (dy + 1);
			nr_area++;
		} 

	qsort(areas, nr_area, sizeof(areas[0]), compare_area);
	printf("%lld\n", areas[0].area);
}

int compare_area(const void *a, const void *b)
{
	area_t *a_area = (area_t *)a;
	area_t *b_area = (area_t *)b;
	return   b_area->area < a_area->area ? -1
		   : b_area->area > a_area->area ? 1
		   : 0;
}

```

At 6:20:27, I submitted the correct answer returned by the above code.

### Second part of the puzzle.

Had to think some time about how to approach this.

```
bool coloured_tiles(num_t y, num_t x1, num_t x2)
{
	num_t ups[250];
	int nr_ups = 0;
	num_t downs[250];
	int nr_downs = 0;
	for (int i = 0; i < n; i++)
	{
		int i2 = (i + 1) % n;
		if (redtiles[i].x == redtiles[i2].x)
		{
			num_t x = redtiles[i].x;
			if (redtiles[i].y > redtiles[i2])
			{
				for (int j = 0; j < nr_downs; j++)
					if (x < downs[j])
					{
						num_t h = downs[j];
						downs[j] = x;
						x = h;
					}
				downs[nr_downs++] = x;
			}
			else
			if (redtiles[i].y > redtiles[i2])
			{
				for (int j = 0; j < nr_ups; j++)
					if (x < ups[j])
					{
						num_t h = ups[j];
						ups[j] = x;
						x = h;
					}
				ups[nr_ups++] = x;
			}
		}
	}
	
	for (int x = x1; x <= x2; x++)
```

At 6:57, I abonded the above code and decided to write an inside function:

```c
bool use_sample = TRUE;

bool inside(num_t x, num_t y)
{
	int inside_score = 0;
	for (int i1 = 0; i1 < n; i1++)
	{
		int i2 = (i1 + 1) % n;
		num_t x1 = redtiles[i1].x;
		num_t x2 = redtiles[i2].x;
		num_t y1 = redtiles[i1].y;
		num_t y2 = redtiles[i2].y;
		if (y1 == y2 && (x1 < x2 ? x1 <= x && x <= x2 : x2 <= x && x <= x1))
			return TRUE;
		if (x1 == x2)
		{
			// going down;
			if (y1 <= y && y <= y2)
			{
				if (x == x1)
					return TRUE;
				if (y < y2)
				{
					if (x < x1)
						inside_score++;
					if (x > x1)
						inside_score--;
				}
			}
			// going up;
			if (y2 <= y && y <= y1)
			{
				if (x == x1)
					return TRUE;
				if (y < y1)
				{
					if (x < x1)
						inside_score--;
					if (x > x1)
						inside_score++;
				}
			}
		}
	}
	return inside_score > 0;
}

void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		if (inside(x1, y2) && inside(x2, y1))
		{
			if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
			if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
			bool go = TRUE;
			for (int x = x1; x <= x2 && go; x++)
				for (int y = y1; y <= y2 && go; y++)
					 go = inside(x, y);
			if (go)
			{
				printf("%lld\n", areas[a].area);
				return;
			}
		}
	}
}

```

At 7:36, the above code return 50 for the example input, which is wrong.

```c
bool inside(num_t x, num_t y)
{
	printf("inside %lld, %lld: ", x, y);
	int inside_score = 0;
	for (int i1 = 0; i1 < n; i1++)
	{
		int i2 = (i1 + 1) % n;
		num_t x1 = redtiles[i1].x;
		num_t x2 = redtiles[i2].x;
		num_t y1 = redtiles[i1].y;
		num_t y2 = redtiles[i2].y;
		if (y == y1 && y1 == y2 && (x1 < x2 ? x1 <= x && x <= x2 : x2 <= x && x <= x1))
		{
			printf("on horizontal %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
			return TRUE;
		}
		if (x1 == x2)
		{
			// going down;
			if (y1 <= y && y <= y2)
			{
				if (x == x1)
				{
					printf("on down %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
					return TRUE;
				}
				if (y < y2)
				{
					if (x < x1)
						inside_score++;
					if (x > x1)
						inside_score--;
				}
			}
			// going up;
			if (y2 <= y && y <= y1)
			{
				if (x == x1)
				{
					printf("on up %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
					return TRUE;
				}
				if (y < y1)
				{
					if (x < x1)
						inside_score--;
					if (x > x1)
						inside_score++;
				}
			}
		}
	}
	printf("inside_score = %d\n", inside_score); 
	return inside_score > 0;
}

void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		printf("Testing area %lld from %lld,%lld to %lld, %lld:\n",
			areas[a].area, x1, y1, x2, y2);
		if (inside(x1, y2) && inside(x2, y1))
		{
			if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
			if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
			bool go = TRUE;
			for (int x = x1; x <= x2 && go; x++)
				for (int y = y1; y <= y2 && go; y++)
					 go = inside(x, y);
			if (go)
			{
				printf("%lld\n", areas[a].area);
				return;
			}
		}
	}
}
```

At 7:43, it looks like I made a little mistake. I added `y == y1` in the first
if-statement in the `inside` function to fix the mistake.

```c
bool use_sample = FALSE;

bool inside(num_t x, num_t y)
{
	//printf("inside %lld, %lld: ", x, y);
	int inside_score = 0;
	for (int i1 = 0; i1 < n; i1++)
	{
		int i2 = (i1 + 1) % n;
		num_t x1 = redtiles[i1].x;
		num_t x2 = redtiles[i2].x;
		num_t y1 = redtiles[i1].y;
		num_t y2 = redtiles[i2].y;
		if (y == y1 && y1 == y2 && (x1 < x2 ? x1 <= x && x <= x2 : x2 <= x && x <= x1))
		{
			//printf("on horizontal %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
			return TRUE;
		}
		if (x1 == x2)
		{
			// going down;
			if (y1 <= y && y <= y2)
			{
				if (x == x1)
				{
					//printf("on down %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
					return TRUE;
				}
				if (y < y2)
				{
					if (x < x1)
						inside_score++;
					if (x > x1)
						inside_score--;
				}
			}
			// going up;
			if (y2 <= y && y <= y1)
			{
				if (x == x1)
				{
					//printf("on up %lld,%lld to %lld,%lld\n", x1, y1, x2, y2);
					return TRUE;
				}
				if (y < y1)
				{
					if (x < x1)
						inside_score--;
					if (x > x1)
						inside_score++;
				}
			}
		}
	}
	//printf("inside_score = %d\n", inside_score); 
	return inside_score > 0;
}

void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		//printf("Testing area %lld from %lld,%lld to %lld, %lld:\n",
		//	areas[a].area, x1, y1, x2, y2);
		if (inside(x1, y2) && inside(x2, y1))
		{
			if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
			if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
			bool go = TRUE;
			for (int x = x1; x <= x2 && go; x++)
				for (int y = y1; y <= y2 && go; y++)
					 go = inside(x, y);
			if (go)
			{
				printf("%lld\n", areas[a].area);
				return;
			}
		}
	}
}
```

At 7:52, that is really taking a long time, as expected.

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		if (t1 == (t2 + 1) % n || t2 == (t1 + 1) % n)
		{
			printf("Testing area %d %d %lld from %lld,%lld to %lld, %lld:\n",
				   t1, t2, areas[a].area, x1, y1, x2, y2);
		
			if (inside(x1, y2) && inside(x2, y1))
			{
				if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
				if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
				bool go = TRUE;
				for (int x = x1; x <= x2 && go; x++)
					for (int y = y1; y <= y2 && go; y++)
						 go = inside(x, y);
				if (go)
				{
					printf("%lld\n", areas[a].area);
					return;
				}
			}
		}
	}
}
```

At 7:57, that did not return the correct answer.

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		printf("Testing area %d %d %lld from %lld,%lld to %lld, %lld:\n",
			   t1, t2, areas[a].area, x1, y1, x2, y2);
		
		if (inside(x1, y2) && inside(x2, y1))
		{
			if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
			if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
			bool go = TRUE;
			for (int x = x1; x <= x2 && go; x++)
				for (int y = y1; y <= y2 && go; y++)
					 go = inside(x, y);
			if (go)
			{
				printf("%lld\n", areas[a].area);
				return;
			}
		}
	}
}
```

At 7:59, I realize that it is maybe enough to test if the lines are on the inside:

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		printf("Testing area %d %d %lld from %lld,%lld to %lld, %lld:\n",
			   t1, t2, areas[a].area, x1, y1, x2, y2);
		
		if (inside(x1, y2) && inside(x2, y1))
		{
			if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
			if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
			bool go = TRUE;
			for (int x = x1; x <= x2 && go; x++)
				go = inside(x, y1) && inside(x, y2);
			for (int y = y1; y <= y2 && go; y++)
				go = inside(x1, y) && inside(x2, y);
			if (go)
			{
				printf("%lld\n", areas[a].area);
				return;
			}
		}
	}
}
```
At 8:02, okay, that runs a bit faster, but still rather slow.

At 8:04:15, I submitted the correct answer from the above code, which took about 121 second the print the solution. 

### After thoughs

After reading [Day 9 solution on reddit](https://www.reddit.com/r/adventofcode/comments/1phywvn/2025_day_9_solutions/),
I realized that maybe it is enough to test if there are no red tiles inside the
area between two points.

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
		if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
		bool go = TRUE;
		for (int i = 0; i < n; i++)
			if (   x1 < redtiles[i].x && redtiles[i].x < x2
				&& y1 < redtiles[i].y && redtiles[i].y < y2)
			{
				go = FALSE;
				break;
			}
		if (go)
		{
			printf("%lld\n", areas[a].area);
			return;
		}
	}
}
```

No, that is not enough. You also have to test that no line crosses the area.

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
		if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
		bool go = TRUE;
		for (int i = 0; i < n && go; i++)
			if (   x1 < redtiles[i].x && redtiles[i].x < x2
				&& y1 < redtiles[i].y && redtiles[i].y < y2)
				go = FALSE;
		for (int i1 = 0; i1 < n && go; i1++)
		{
			int i2 = (i1 + 1) % n;
			num_t xl1 = redtiles[i1].x;
			num_t yl1 = redtiles[i1].y; 
			num_t xl2 = redtiles[i2].x;
			num_t yl2 = redtiles[i2].y;
			if (xl1 == xl2)
			{
				if (yl1 > yl2) { num_t h = yl1; yl1 = yl2; yl2 = h; }
				if (yl1 <= y1 && y2 <= yl2)
					go = FALSE;
			}
			if (yl1 == yl2)
			{		
				if (xl1 > xl2) { num_t h = xl1; xl1 = xl2; xl2 = h; } 
				if (xl1 <= x1 && x2 <= xl2)
					go = FALSE;
			}
		}
		if (go)
		{
			printf("%lld\n", areas[a].area);
			return;
		}
	}
}
```

That too did not return the correct answer.

```c
void solve2()
{
	int nr_areas = n * (n - 1) / 2;
	for (int a = 0; a < nr_areas; a++)
	{
		int t1 = areas[a].redtile1;
		num_t x1 = redtiles[t1].x;
		num_t y1 = redtiles[t1].y; 
		int t2 = areas[a].redtile2;
		num_t x2 = redtiles[t2].x;
		num_t y2 = redtiles[t2].y;
		if (x1 > x2) { num_t h = x1; x1 = x2; x2 = h; } 
		if (y1 > y2) { num_t h = y1; y1 = y2; y2 = h; }
		bool go = TRUE;
		for (int i = 0; i < n && go; i++)
			if (   x1 < redtiles[i].x && redtiles[i].x < x2
				&& y1 < redtiles[i].y && redtiles[i].y < y2)
				go = FALSE;
		for (int i1 = 0; i1 < n && go; i1++)
		{
			int i2 = (i1 + 1) % n;
			num_t xl1 = redtiles[i1].x;
			num_t yl1 = redtiles[i1].y; 
			num_t xl2 = redtiles[i2].x;
			num_t yl2 = redtiles[i2].y;
			if (yl1 > yl2) { num_t h = yl1; yl1 = yl2; yl2 = h; }
			if (xl1 > xl2) { num_t h = xl1; xl1 = xl2; xl2 = h; } 
			if (xl1 == xl2 && x1 < xl1 && xl1 < x2)
			{
				if (yl1 <= y1 && y2 <= yl2)
					go = FALSE;
			}
			if (yl1 == yl2 && y1 < yl1 && yl1 < y2)
			{		
				if (xl1 <= x1 && x2 <= xl2)
					go = FALSE;
			}
		}
		if (go)
		{
			printf("%lld\n", areas[a].area);
			return;
		}
	}
}
```

At 8:46, that did return the correct answer with a total runtime for both parts of 0.038 seconds.


### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day$.md >day$.c; gcc -g -Wall day$.c -o day$; ./day$ $
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `$` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day$.c](day$.c).



