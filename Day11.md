# Day 11 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
typedef struct node_s node_t;
typedef struct out_s out_t;
struct node_s
{
	char name[4];
	out_t *outs;
	num_t paths;	
	node_t *next;
};
node_t *all_nodes = 0;
struct out_s
{
	node_t *node;
	out_t *next;
};

node_t *add_node(const char *s)
{
	for (node_t *node = all_nodes; node != 0; node = node->next)
		if (strncmp(node->name, s, 3) == 0)
			return node;
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	strncpy(new_node->name, s, 3);
	new_node->name[3] = '\0';
	new_node->outs = 0;
	new_node->paths = -1;
	new_node->next = all_nodes;
	all_nodes = new_node;
	return new_node;
}

num_t calc_paths(node_t *node)
{
	if (node->paths >= 0)
		return node->paths;
	if (strcmp(node->name, "out") == 0)
	{
		node->paths = 1;
		return 1;
	}
	if (node->paths == -2)
	{
		printf("Cyclic graph\n");
		exit(1);
	}
	node->paths = -2;
	num_t paths = 0;
	for (out_t *out = node->outs; out != 0; out = out->next)
		paths += calc_paths(out->node);
	node->paths = paths;
	return paths;
}

void solve1()
{
	for (int i = 0; i < n; n++)
	{
		const char *s = d[i];
		node_t *node = add_node(s);
		s += 4;
		while (*s == ' ')
		{
			s++;
			out_t *new_out = (out_t*)malloc(sizeof(out_t));
			new_out->node = add_node(s);
			new_out->next = node->outs;
			node->outs = new_out;
			s += 3;
		}
	}
	num_t answer = calc_paths(add_node("you"));
	printf("%lld\n", answer);
}
```

At 6:27, after fixing some error, this runs to infinitiy.
Lets add some debug print statements.

```c
node_t *add_node(const char *s)
{
	for (node_t *node = all_nodes; node != 0; node = node->next)
		if (strncmp(node->name, s, 3) == 0)
		{
			//printf("Find node %s\n", node->name);
			return node;
		}
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	strncpy(new_node->name, s, 3);
	new_node->name[3] = '\0';
	new_node->outs = 0;
	new_node->paths = -1;
	new_node->next = all_nodes;
	all_nodes = new_node;
	//printf("Added node for %3.3s\n", s);
	return new_node;
}

num_t calc_paths(node_t *node)
{
	//printf("calc_paths %s %lld\n", node->name, node->paths);
	if (node->paths >= 0)
		return node->paths;
	if (strcmp(node->name, "out") == 0)
	{
		node->paths = 1;
		return 1;
	}
	if (node->paths == -2)
	{
		printf("Cyclic graph\n");
		exit(1);
	}
	node->paths = -2;
	num_t paths = 0;
	for (out_t *out = node->outs; out != 0; out = out->next)
		paths += calc_paths(out->node);
	node->paths = paths;
	return paths;
}
```

After seeing that the items on the first line, where repeated, I
noticed that in the for loop in `solve1` the variable `n` was incremented
instead of `i`. How silly.

```c
void solve1()
{
	for (int i = 0; i < n; i++)
	{
		const char *s = d[i];
		node_t *node = add_node(s);
		s += 4;
		while (*s == ' ')
		{
			s++;
			out_t *new_out = (out_t*)malloc(sizeof(out_t));
			new_out->node = add_node(s);
			new_out->next = node->outs;
			node->outs = new_out;
			s += 3;
		}
	}
	num_t answer = calc_paths(add_node("you"));
	printf("%lld\n", answer);
}
```

At 6:36:31, I submitted the correct answer returned from the above version of the code.


### Second part of the puzzle.

This cannot be so hard with the code of part one that I already
implemented. Lets first calculate the total number of paths from
`svr` to `out` and also verify that it does not contain cyclic paths.

```c
void solve2()
{
	num_t answer = calc_paths(add_node("svr"));
	printf("%lld\n", answer);
}

```

At 6:40, indeed a very large amount of paths.

```c
node_t *to_node = 0;

num_t calc_paths(node_t *node)
{
	//printf("calc_paths %s %lld\n", node->name, node->paths);
	if (node->paths >= 0)
		return node->paths;
	if (node == to_node)
	{
		node->paths = 1;
		return 1;
	}
	if (node->paths == -2)
	{
		printf("Cyclic graph\n");
		exit(1);
	}
	node->paths = -2;
	num_t paths = 0;
	for (out_t *out = node->outs; out != 0; out = out->next)
		paths += calc_paths(out->node);
	node->paths = paths;
	return paths;
}

void solve2()
{
	to_node = add_node("out");
	num_t answer = calc_paths(add_node("dac"));
	for (node_t *node = all_nodes; node != 0; node = node->next)
		node->paths = -1;

	to_node = add_node("dac");
	answer *= calc_paths(add_node("fft"));
	for (node_t *node = all_nodes; node != 0; node = node->next)
		node->paths = -1;

	to_node = add_node("fft");
	answer *= calc_paths(add_node("dac"));
	
	printf("%lld\n", answer);
}

```

At 6:47, that returns 0 and 0.

```c
void solve1()
{
	for (int i = 0; i < n; i++)
	{
		const char *s = d[i];
		node_t *node = add_node(s);
		s += 4;
		while (*s == ' ')
		{
			s++;
			out_t *new_out = (out_t*)malloc(sizeof(out_t));
			new_out->node = add_node(s);
			new_out->next = node->outs;
			node->outs = new_out;
			s += 3;
		}
	}
	to_node = add_node("out");
	num_t answer = calc_paths(add_node("you"));
	printf("%lld\n", answer);
}

void solve2()
{
	to_node = add_node("out");
	num_t answer = calc_paths(add_node("dac"));
	for (node_t *node = all_nodes; node != 0; node = node->next)
		node->paths = -1;

	to_node = add_node("dac");
	answer *= calc_paths(add_node("fft"));
	for (node_t *node = all_nodes; node != 0; node = node->next)
		node->paths = -1;

	to_node = add_node("fft");
	answer *= calc_paths(add_node("svr"));
	
	printf("%lld\n", answer);
}
```

At 6:49:03, I submitted the correct answer returned from the above version of the code.


### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day11.md >day11.c; gcc -g -Wall day11.c -o day11; ./day11 11
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `11` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day11.c](day11.c).



