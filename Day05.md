# Day 5 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

At 6:02, lets try it without creating list of ranges.

```c
void solve1()
{
	int i = 0;
	while (d[i][0] != '\0')
		i++;
	
	int count = 0;
	for (i++; i < n; i++)
	{
		char *line = d[i];
		num_t id = parse_number(&line);
		
		for (int i1 = 0; d[i1][0] != '\0'; i1++)
		{
			line = d[i1];
			num_t from = parse_number(&line);
			line++;
			num_t to = parse_number(&line);
			if (from <= id && id <= to)
			{
				count++;
				break;
			}
		}
	}
	printf("%d\n", count);
}
```

At 6:08:17, the answer from the above program was accepted as the correct answer.

### Second part of the puzzle.

Lets try this without some code that I wrote during an earlier year for
combining overlapping ranges.

```c
void solve2()
{
	num_t lowest = -1;
	num_t highest = -1;
	
	num_t count = 0;
	for (bool go = TRUE; go;)
	{
		go = FALSE;
		num_t min = -1;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from > lowest && (min == -1 || from < min))
				min = from;
		}
		if (min == -1)
			break;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			line++;
			num_t to = parse_number(&line);
			if (from <= highest)
				from = highest + 1;
			if (to <= from)
			{
				count = from - to + 1;
				highest = to;
				go = TRUE;
			}
		}
	}
	printf("%lld\n", count);
}

```

At 6:26, the program seems to be in an endless loop.


```c
void solve2()
{
	num_t lowest = -1;
	num_t highest = -1;
	
	num_t count = 0;
	for (bool go = TRUE; go;)
	{
		go = FALSE;
		num_t min = -1;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from > lowest && (min == -1 || from < min))
				min = from;
		}
		if (min == -1)
			break;
		lowest = min;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			line++;
			num_t to = parse_number(&line);
			if (from <= highest)
				from = highest + 1;
			if (to <= from)
			{
				count = from - to + 1;
				highest = to;
				go = TRUE;
			}
		}
	}
	printf("%lld\n", count);
}

```

At 6:32 that did not return the correct answer. The reason that the earlier version
was caught into an endless loop, was because `lowest` was not updated after the next
minimum was found. Lets try with the example input.

```c
bool use_sample = TRUE;
void solve2()
{
	num_t lowest = -1;
	num_t highest = -1;
	
	num_t count = 0;
	for (bool go = TRUE; go;)
	{
		go = FALSE;
		num_t min = -1;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from > lowest && (min == -1 || from < min))
				min = from;
		}
		if (min == -1)
			break;
		lowest = min;
		printf("min = %lld\n", min);
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from == min)
			{
				printf("from %lld\n", from);
				line++;
				num_t to = parse_number(&line);
				printf("to %lld\n", to);
				if (from <= highest)
					from = highest + 1;
				if (from <= to)
				{
					printf("Add range %lld %lld = %lld\n", from, to, to - from + 1);
					count += to - from + 1;
					highest = to;
					go = TRUE;
				}
			}
		}
		printf("lowest %lld highest %lld\n\n", lowest, highest);
	}
	printf("%lld\n", count);
}
```

At 6:45, after several attempts, this returns the correct value for the example input.
It seems, I mixed up `from` and `to` several times.

```c
bool use_sample = FALSE;
```

It still does not return the correct answer on my input.

```c
void solve2()
{
	num_t lowest = -1;
	num_t highest = -1;
	
	num_t count = 0;
	for (;;)
	{
		num_t min = -1;
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from > lowest && (min == -1 || from < min))
				min = from;
		}
		if (min == -1)
			break;
		lowest = min;
		printf("min = %lld\n", min);
		for (int i = 0; d[i][0] != '\0'; i++)
		{
			char *line = d[i];
			num_t from = parse_number(&line);
			if (from == min)
			{
				printf("from %lld\n", from);
				line++;
				num_t to = parse_number(&line);
				printf("to %lld\n", to);
				if (from <= highest)
					from = highest + 1;
				if (from <= to)
				{
					printf("Add range %lld %lld = %lld\n", from, to, to - from + 1);
					count += to - from + 1;
					highest = to;
				}
			}
		}
		printf("lowest %lld highest %lld\n\n", lowest, highest);
	}
	printf("%lld\n", count);
}
```

At 6:52:45, I submitted the correct answer from the above code. I removed the logic
on the `go` variable, because all starting values should be searched no matter if
the `highest` value is increased or not.

### Range functions

See, if my previous implementation with ranges would have solved the second
part faster.

```c
typedef struct range range_t;
struct range
{
    num_t from;
    num_t to;
    range_t *next;
};

void ranges_add_range(range_t **ref_ranges, num_t from, num_t to)
{
    while (*ref_ranges != 0 && (*ref_ranges)->to < from)
        ref_ranges = &(*ref_ranges)->next;
    if (*ref_ranges == 0 || to < (*ref_ranges)->from)
    {
        range_t *new_range = (range_t*)malloc(sizeof(range_t));
        new_range->from = from;
        new_range->to = to;
        new_range->next = *ref_ranges;
        *ref_ranges = new_range;
        return;
    }
    if ((*ref_ranges)->from < from)
        from = (*ref_ranges)->from;
    while ((*ref_ranges)->next != 0 && (*ref_ranges)->next->from <= to)
        *ref_ranges = (*ref_ranges)->next;
    (*ref_ranges)->from = from;
    if ((*ref_ranges)->to < to)
        (*ref_ranges)->to = to;
}

int main(int argc, char *argv[])
{
	...
    solve2_ranges();
}

void solve2_ranges()
{
	range_t *ranges = 0;
	for (int i = 0; d[i][0] != '\0'; i++)
	{
		char *line = d[i];
		num_t from = parse_number(&line);
		line++;
		num_t to = parse_number(&line);
		ranges_add_range(&ranges, from, to);
	}
	
	num_t count = 0;
	for (range_t *range = ranges; range != 0; range = range->next)
		count += range->to - range->from + 1;
	printf("%lld\n", count);
}

```

That would indeed have returned the correct answer in less than 10 minutes
coding.

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day05.md >day05.c; gcc -g -Wall day05.c -o day05; ./day05 05
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `05` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day05.c](day05.c).



