# Day 8 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	printf("%d %d\n", n, m);
}
```

At 6:12, I established that there are 1000 junction boxes in the input. I think
about creating a list of all the distances between the junction boxes and sort
these. Maybe also a list of the junction boxes.

```c
struct {
	num_t x, y, z;
	int circuit;
} boxes[1000];

struct dist_t {
	int box1, box2;
	num_t dist_sq;
} dists[500*999]; 

void solve1()
{
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		boxes[i].x = parse_number(&s);
		s++;
		boxes[i].y = parse_number(&s);
		s++;
		boxes[i].z = parse_number(&s);
		boxes[i].circuit = i;
	}
	
	// calculate distances
	int nr_dist = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			dists[nr_dist].box1 = i; 
			dists[nr_dist].box2 = j;
			num_t dx = boxes[i].x - boxes[j].x;
			num_t dy = boxes[i].y - boxes[j].y;
			num_t dz = boxes[i].z - boxes[j].z;
			dists[nr_dist].dist_sq = dx * dx + dy * dy + dz * dz;
			nr_dist++;
		} 
 
	printf("%d %d\n", 500 * 999, nr_dist);
}
```

At 6:24, I finished the above code after making several edits.

```c

int compare_dist(const void *a, const void *b)
{
	struct dist_t *a_dist = (struct dist_t *)a;
	struct dist_t *b_dist = (struct dist_t *)b;
	return   b_dist->dist_sq < a_dist->dist_sq ? -1
		   : b_dist->dist_sq > a_dist->dist_sq ? 1
		   : 0;
}

void solve1()
{
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		boxes[i].x = parse_number(&s);
		s++;
		boxes[i].y = parse_number(&s);
		s++;
		boxes[i].z = parse_number(&s);
		boxes[i].circuit = i;
	}
	
	// calculate distances
	int nr_dist = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			dists[nr_dist].box1 = i; 
			dists[nr_dist].box2 = j;
			num_t dx = boxes[i].x - boxes[j].x;
			num_t dy = boxes[i].y - boxes[j].y;
			num_t dz = boxes[i].z - boxes[j].z;
			dists[nr_dist].dist_sq = dx * dx + dy * dy + dz * dz;
			nr_dist++;
		} 

	qsort(dists, nr_dist, sizeof(dists[0]), compare_dist);
	printf("%d %d\n", 500 * 999, nr_dist);
	
	for (int i = 0; i < 10; i++)
		printf("%lld %d %d\n", dists[i].dist_sq, dists[i].box1, dists[i].box2);
}
```

At 6:37, that sorted the list from largest to smallest after making several edits
including an edit to the previous code block, where I added `dist_t`. (I probably
should have done this in the first place.)

```c
int compare_dist(const void *a, const void *b)
{
	struct dist_t *a_dist = (struct dist_t *)a;
	struct dist_t *b_dist = (struct dist_t *)b;
	return   b_dist->dist_sq < a_dist->dist_sq ? 1
		   : b_dist->dist_sq > a_dist->dist_sq ? -1
		   : 0;
}

```

At 6:39, that returned the list in the correct order.

```c

int compare_int(const void* a, const void* b)
{
   return (*(int*)b - *(int*)a);
}

void solve1()
{
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		boxes[i].x = parse_number(&s);
		s++;
		boxes[i].y = parse_number(&s);
		s++;
		boxes[i].z = parse_number(&s);
		boxes[i].circuit = i;
	}
	
	// calculate distances
	int nr_dist = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			dists[nr_dist].box1 = i; 
			dists[nr_dist].box2 = j;
			num_t dx = boxes[i].x - boxes[j].x;
			num_t dy = boxes[i].y - boxes[j].y;
			num_t dz = boxes[i].z - boxes[j].z;
			dists[nr_dist].dist_sq = dx * dx + dy * dy + dz * dz;
			nr_dist++;
		} 

	qsort(dists, nr_dist, sizeof(dists[0]), compare_dist);
	
	for (int i = 0; i < n; i++)
	{
		int circuit1 = boxes[dists[i].box1].circuit;
		int circuit2 = boxes[dists[i].box2].circuit;
		if (circuit2 < circuit1)
		{
			int h = circuit1;
			circuit1 = circuit2;
			circuit2 = h;
		}
		for (int j = 0; j < n; j++)
			if (boxes[j].circuit == circuit2)
				boxes[j].circuit = circuit1;
	}
	
	int circuit_sizes[1000];
	for (int i = 0; i < n; i++)
		circuit_sizes[i] = 0;
	for (int i = 0; i < n; i++)
		circuit_sizes[boxes[i].circuit]++;
	
	qsort(circuit_sizes, n, sizeof(circuit_sizes[0]), compare_int);
	
	num_t answer = 1;
	for (int i = 0; i < 3; i++)
		answer *= circuit_sizes[i];
	printf("%lld\n", answer);
}
```

At 6:50:24, the submitted answer from the above code was correct after I corrected
several syntax errors to make the above code compile.

### Second part of the puzzle.

Most of the work already has been done.

```c
void solve2()
{
	num_t answer = 0;
	for (int i = 0; i < n * (n - 1) / 2; i++)
	{
		int circuit1 = boxes[dists[i].box1].circuit;
		int circuit2 = boxes[dists[i].box2].circuit;
		if (circuit1 != circuit2)
		{
			if (circuit2 < circuit1)
			{
				int h = circuit1;
				circuit1 = circuit2;
				circuit2 = h;
			}
			for (int j = 0; j < n; j++)
				if (boxes[j].circuit == circuit2)
					boxes[j].circuit = circuit1;
			answer = boxes[dists[i].box1].x * boxes[dists[i].box2].x;
		} 
	}
	printf("%lld\n", answer);
}

```

At 6:56:07, the submitted answer from the above code, was correct after I corrected
a syntax error to make the above code compile.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day08.md >day08.c; gcc -g -Wall day08.c -o day08; ./day08 08
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `08` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day08.c](day08.c).



