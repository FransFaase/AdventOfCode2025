# Day 10 of Advent of Code 2025

The code below makes use of [a standard library](Std.md), which
also contains the `main` function that reads the input in the global variable `d`
where `n` contains the number of lines and `m` the length of the longest line,
and than calls the function `solve1` and `solve2`.

```c
void solve1()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		int pattern = 0;
		s++;
		for (int i = 1; *s != ']'; i *= 2)
			if (*s == '#')
				pattern |= i;
		s += 2;
		int buttons[100];
		int nr_buttons = 0;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		int min = nr_buttons;
		long max = 1 << nr_buttons;
		for (int m = 0; m < max; m++)
		{
			int nr_switched = 0;
			int state = 0;
			for (int b = 0; b < nr_buttons; b++)
				if (((1 << b) & m) != 0)
				{
					nr_switched++;
					state ^= buttons[b];
				}
			if (state == pattern && nr_switched < min)
				min = nr_switched;
		}
		count += min;
	}
	printf("%lld\n", count);	
}
```

At 6:16, the above seems to get into an infinite loop.

```c
void solve1()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		int pattern = 0;
		s++;
		for (int i = 1; *s != ']'; i *= 2)
			if (*s++ == '#')
				pattern |= i;
		s += 2;
		int buttons[100];
		int nr_buttons = 0;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		int min = nr_buttons;
		long max = 1 << nr_buttons;
		for (int m = 0; m < max; m++)
		{
			int nr_switched = 0;
			int state = 0;
			for (int b = 0; b < nr_buttons; b++)
				if (((1 << b) & m) != 0)
				{
					nr_switched++;
					state ^= buttons[b];
				}
			if (state == pattern && nr_switched < min)
				min = nr_switched;
		}
		count += min;
	}
	printf("%lld\n", count);	
}
```

### Second part of the puzzle.

```c

int nr_pos;
int buttons[100];
int nr_buttons;
num_t jolting[100];
num_t state[100];
int min;


void search_min(int jolts)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
		if (state[p] > jolting[p])
			return;
		else if (state[p] < jolting[p])
			equal = FALSE;
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	for (int b = 0; b < nr_buttons; b++)
	{
		num_t old_state[100];		
		for (int p = 0; p < nr_pos; p++)
		{
			old_state[p] = state[p];
			if (((1 << p) & buttons[b]) != 0)
				state[p]++;
		}
		search_min(jolts);
		for (int p = 0; p < nr_pos; p++)
			state[p] = old_state[p];
	}
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0);
		count += min;
	}
	printf("%lld\n", count);	
}

```

At 6:47, that runs rather slow.

```c
void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		while (*s != '(')
			s++;
		printf("A\n");
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		printf("C\n");
		
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		printf("D\n");
		
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0);
		count += min;
		printf("B\n");
	}
	printf("%lld\n", count);	
}
```

At 6:49, there is a problem with the recursive call.

```c
void search_min(int jolts)
{
	printf("%d:", jolts);
	for (int p = 0; p < nr_pos; p++)
		printf(" %lld,%lld", state[p], jolting[p]);
	printf("\n");
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
		if (state[p] > jolting[p])
			return;
		else if (state[p] < jolting[p])
			equal = FALSE;
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	for (int b = 0; b < nr_buttons; b++)
	{
		num_t old_state[100];		
		for (int p = 0; p < nr_pos; p++)
		{
			old_state[p] = state[p];
			if (((1 << p) & buttons[b]) != 0)
				state[p]++;
		}
		search_min(jolts);
		for (int p = 0; p < nr_pos; p++)
			state[p] = old_state[p];
	}
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0);
		count += min;
	}
	printf("%lld\n", count);	
}

```

At 6:58, it looks the algorithm is too slow.

```c
bool use_sample = TRUE;
```

At 6:58, it even is too slow for the example input.

```c
void search_min(int jolts, int min_b)
{
	//printf("%d:", jolts);
	//for (int p = 0; p < nr_pos; p++)
	//	printf(" %lld,%lld", state[p], jolting[p]);
	//printf("\n");
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
		if (state[p] > jolting[p])
			return;
		else if (state[p] < jolting[p])
			equal = FALSE;
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	for (int b = min_b; b < nr_buttons; b++)
	{
		num_t old_state[100];		
		for (int p = 0; p < nr_pos; p++)
		{
			old_state[p] = state[p];
			if (((1 << p) & buttons[b]) != 0)
				state[p]++;
		}
		search_min(jolts, b);
		for (int p = 0; p < nr_pos; p++)
			state[p] = old_state[p];
	}
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0, 0);
		count += min;
	}
	printf("%lld\n", count);	
}

```

At 7:04, it returns the correct answer for the example input.

```c
bool use_sample = FALSE;
```

But it looks like it is still too slow for the input.

```c
void search_min(int jolts, int min_b)
{
	//printf("%d:", jolts);
	//for (int p = 0; p < nr_pos; p++)
	//	printf(" %lld,%lld", state[p], jolting[p]);
	//printf("\n");
	if (jolts >= min)
		return;
	bool equal = TRUE;
	int search_p = 0;
	int lowest_left = 1000;
	for (int p = 0; p < nr_pos; p++)
	{
		int diff = jolting[p] - state[p];
		if (diff < 0)
			return;
		else if (diff > 0)
		{
			equal = FALSE;
			if (diff < lowest_left)
			{
				search_p = p;
				lowest_left = diff;
			}
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	for (int b = 0; b < nr_buttons; b++)
		if (((1 << search_p) & buttons[b]) != 0)
		{
			num_t old_state[100];		
			for (int p = 0; p < nr_pos; p++)
			{
				old_state[p] = state[p];
				if (((1 << p) & buttons[b]) != 0)
					state[p]++;
			}
			search_min(jolts, b);
			for (int p = 0; p < nr_pos; p++)
				state[p] = old_state[p];
		}
}

```

At 7:29, works for sample input, but still too slow.

```c
void search_min(int jolts, int cur_p, int min_b)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	int min_p = 0;
	int lowest_left = 1000;
	for (int p = 0; p < nr_pos; p++)
	{
		int diff = jolting[p] - state[p];
		if (diff < 0)
			return;
		else if (diff > 0)
		{
			equal = FALSE;
			if (diff < lowest_left)
			{
				min_p = p;
				lowest_left = diff;
			}
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	if (cur_p == -1 || state[cur_p] == 0)
	{
		min_b = 0;
		cur_p = min_p;
	}
	for (int b = min_b; b < nr_buttons; b++)
		if (((1 << cur_p) & buttons[b]) != 0)
		{
			num_t old_state[100];
			for (int p = 0; p < nr_pos; p++)
			{
				old_state[p] = state[p];
				if (((1 << p) & buttons[b]) != 0)
					state[p]++;
			}
			search_min(jolts, cur_p, b);
			for (int p = 0; p < nr_pos; p++)
				state[p] = old_state[p];
		}
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0, -1, 0);
		count += min;
	}
	printf("%lld\n", count);	
}
```

At 7:38, it is a bit faster, but still far too slow.

```c
void search_min(int jolts, int cur_p, int min_b)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	int min_p = 0;
	int lowest_left = 1000;
	for (int p = 0; p < nr_pos; p++)
	{
		int diff = jolting[p] - state[p];
		if (diff < 0)
			return;
		else if (diff > 0)
		{
			equal = FALSE;
			if (diff < lowest_left)
			{
				min_p = p;
				lowest_left = diff;
			}
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}
	if (++jolts >= min)
		return;
	if (cur_p == -1 || state[cur_p] == 0)
	{
		min_b = 0;
		cur_p = min_p;
	}
	for (int b = min_b; b < nr_buttons; b++)
		if (((1 << cur_p) & buttons[b]) != 0)
		{
			num_t old_state[100];
			for (int steps = jolting[cur_p] - state[cur_p]; steps > 0; steps--)
			{
				for (int p = 0; p < nr_pos; p++)
				{
					old_state[p] = state[p];
					if (((1 << p) & buttons[b]) != 0)
						state[p] += steps;
				}
				search_min(jolts, cur_p, b + 1);
				for (int p = 0; p < nr_pos; p++)
					state[p] = old_state[p];
			}
		}
}
```

At 7:51, I fear, I have to use a smarter approach, and start with the position
that is involved into the least number of buttons.

```c
bool use_sample = TRUE;
```

At 7:58, that returns the incorrect value for the example input.

```c
void search_min(int jolts, int cur_p, int min_b, int mult)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] < 0)
			return;
		if (jolting[p] > 0)
		{
			equal = FALSE;
			if (jolts + jolting[p] >= min)
				return;
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}
	
	if (cur_p == -1)
	{
		int min_comb;
		int max_jolting = 0;
		// find the next one with the least number of combinations.
		for (int p = 0; p < nr_pos; p++)
		{
			if (jolting[p] > 0)
			{
				int up = jolting[p];
				int i = 0;
				int nr_comb = 1;
				for (int b = 0; b < nr_buttons; b++)
					if (((1 << p) & buttons[b]) != 0)
					{
						i++;
						if (i > 1)
						{
							nr_comb = nr_comb * up;
							up--;
						}
					}
				if (cur_p == -1 || i < mult || (i == 1 && jolting[p] > max_jolting))
				{
					min_comb = nr_comb;
					cur_p = p;
					mult = i;
					max_jolting = jolting[p];
				}
			}
		}

		min_b = 0;
		printf(" jolts %d: cur_p = %d, mul = %d, min_comb = %d\n", jolts, cur_p, mult, min_comb);
	}
	num_t old_jolting[100];
	if (mult == 1)
	{
		jolts += jolting[cur_p];
		//if (jolts >= min)
		//	return;
		for (int b = min_b; b < nr_buttons; b++)
			if (((1 << cur_p) & buttons[b]) != 0)
			{
				for (int p = 0; p < nr_pos; p++)
				{
					old_jolting[p] = jolting[p];
					if (((1 << p) & buttons[b]) != 0)
						jolting[p] -= jolting[cur_p];
				}
				search_min(jolts + jolting[cur_p], -1, -1, -1);
				for (int p = 0; p < nr_pos; p++)
					jolting[p] = old_jolting[p];
				break;
			}
	}
	else
	{
		jolts++;
		for (int b = min_b; b < nr_buttons; b++)
			if (((1 << cur_p) & buttons[b]) != 0)
			{
				for (int p = 0; p < nr_pos; p++)
				{
					old_jolting[p] = jolting[p];
					if (((1 << p) & buttons[b]) != 0)
						jolting[p]--;
				}
				search_min(jolts, cur_p, b, mult - 1);
				for (int p = 0; p < nr_pos; p++)
					jolting[p] = old_jolting[p];
			}
	}
}


void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int j = 0; j < nr_buttons; j++)
			state[j] = 0;
		search_min(0, -1, 0, -1);
		printf(" = %d\n", min);
		count += min;
	}
	printf("%lld\n", count);	
}
```

A took a break and continued at 11:56.

```c

bool use_sample = FALSE;

num_t max_per_button[100];

void search_min(int jolts, int cur_p, int b, int mult)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] < 0)
			return;
		if (jolting[p] > 0)
		{
			equal = FALSE;
			if (jolts + jolting[p] >= min)
				return;
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}

	bool select_p = cur_p == -1 || jolting[cur_p] == 0 || mult == 0;
	num_t old_max_per_button[100];
	if (select_p)
	{
		// find the next one with the least number of combinations.
		cur_p = -1;
		num_t best_comb;
		int best_m;
		for (int p = 0; p < nr_pos; p++)
		{
			if (jolting[p] > 0)
			{
				m = 0;
				num_t sum = 0;
				for (int b = 0; b < nr_buttons; b++)
					if (((1 << p) & buttons[b]) != 0)
					{
						num_t max = 1000;
						for (int p2 = 0; p2 < nr_pos; p2++)
							if ((((1 << p2) & buttons[b]) != 0) && jolting[p2] < max)
								max = jolting[p2];
						if (max > 0)
							m++;
						sum += max;
					}
				if (sum < jolting[p])
					return;
				if (   cur_p == -1
					|| (  m == 1
					    ? (best_m > 1 || jolting[p] > best_comb)
					    : jolting[p] < best_comb))
				{
					cur_p = p;
					best_m = m;
					best_comb = jolting[p];
				}
			}
		}
		mult = 0;
		for (int b = 0; b < nr_buttons; b++)
			old_max_per_button[b] = max_per_button[b];
		for (int b = 0; b < nr_buttons; b++)
			if (((1 << cur_p) & buttons[b]) != 0)
			{
				num_t max = 1000;
				for (int p = 0; p < nr_pos; p++)
					if ((((1 << p) & buttons[b]) != 0) && jolting[p] < max)
						max = jolting[p];
				max_per_button[b] = max;
				if (max > 0)
					mult++;
			}

		b = 0;
	}
	if (mult > 0)
	{
		for (; b < nr_buttons; b++)
			if (max_per_button[b] > 0 && ((1 << cur_p) & buttons[b]) != 0)
				break;

		num_t r = jolting[cur_p];
		if (max_per_button[b] < r)
			r = max_per_button[b];
		num_t r_till = mult == 1 ? r : 0;

		for (; r >= r_till; r--)
		{
			num_t old_jolting[100];
			for (int p = 0; p < nr_pos; p++)
			{
				old_jolting[p] = jolting[p];
				if (((1 << p) & buttons[b]) != 0)
					jolting[p] -= r;
			}
			search_min(jolts + r, cur_p, b + 1, mult - 1);
			for (int p = 0; p < nr_pos; p++)
				jolting[p] = old_jolting[p];
		}
	}

	if (select_p)
	{
		for (int b = 0; b < nr_buttons; b++)
			max_per_button[b] = old_max_per_button[b];
	}
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		num_t nr_pos_per_button[100];
		nr_buttons = 0;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			int nr_pos = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				nr_pos++;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_pos_per_button[nr_buttons] = nr_pos;
			for (int i = nr_buttons; i > 0 && nr_pos_per_button[i-1] < nr_pos_per_button[i]; i--)
			{
				int nr = nr_pos_per_button[i-1]; 
				nr_pos_per_button[i-1] = nr_pos_per_button[i];
				nr_pos_per_button[i] = nr;
				num_t value = buttons[i-1];
				buttons[i-1] = buttons[i];
				buttons[i] = value;
			}
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min= 1000;
		search_min(0, -1, -1, 0);
		printf(" = %d\n", min);
		count += min;
	}
	printf("%lld\n", count);	
}
```

At 16:29, lets try a slightly different approach:

```c
void search_min(int jolts, int cur_p, int b, int mult)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] < 0)
			return;
		if (jolting[p] > 0)
		{
			equal = FALSE;
			if (jolts + jolting[p] >= min)
				return;
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}

	bool select_p = cur_p == -1 || jolting[cur_p] == 0 || mult == 0;
	num_t old_max_per_button[100];
	if (select_p)
	{
		// find the next one with the least number of combinations.
		cur_p = -1;
		num_t best_comb;
		int best_m;
		for (int p = 0; p < nr_pos; p++)
		{
			if (jolting[p] > 0)
			{
				m = 0;
				num_t sum = 0;
				for (int b = 0; b < nr_buttons; b++)
					if (((1 << p) & buttons[b]) != 0)
					{
						num_t max = 1000;
						for (int p2 = 0; p2 < nr_pos; p2++)
							if ((((1 << p2) & buttons[b]) != 0) && jolting[p2] < max)
								max = jolting[p2];
						if (max > 0)
							m++;
						sum += max;
					}
				if (sum < jolting[p])
					return;
				if (   cur_p == -1
					|| (  m == 1
					    ? (best_m > 1 || jolting[p] > best_comb)
					    : m == 2
					    ? (best_m > 2|| (best_m == 2 && jolting[p] < best_comb))
					    : jolting[p] < best_comb))
				{
					cur_p = p;
					best_m = m;
					best_comb = jolting[p];
				}
			}
		}
		mult = 0;
		for (int b = 0; b < nr_buttons; b++)
			old_max_per_button[b] = max_per_button[b];
		for (int b = 0; b < nr_buttons; b++)
			if (((1 << cur_p) & buttons[b]) != 0)
			{
				num_t max = 1000;
				for (int p = 0; p < nr_pos; p++)
					if ((((1 << p) & buttons[b]) != 0) && jolting[p] < max)
						max = jolting[p];
				max_per_button[b] = max;
				if (max > 0)
					mult++;
			}

		b = 0;
	}
	if (mult > 0)
	{
		for (; b < nr_buttons; b++)
			if (max_per_button[b] > 0 && ((1 << cur_p) & buttons[b]) != 0)
				break;

		num_t r_max = jolting[cur_p];
		if (max_per_button[b] < r_max)
			r_max = max_per_button[b];

		for (int r = mult == 1 ? r_max : 0; r <= r_max; r++)
		{
			num_t old_jolting[100];
			for (int p = 0; p < nr_pos; p++)
			{
				old_jolting[p] = jolting[p];
				if (((1 << p) & buttons[b]) != 0)
					jolting[p] -= r;
			}
			search_min(jolts + r, cur_p, b + 1, mult - 1);
			for (int p = 0; p < nr_pos; p++)
				jolting[p] = old_jolting[p];
		}
	}

	if (select_p)
	{
		for (int b = 0; b < nr_buttons; b++)
			max_per_button[b] = old_max_per_button[b];
	}
}
```

May try a completely different approach where a button is selected in stead of a position.

```

bool use_sample = TRUE;

bool proc_buttons[100];

void search_min(int jolts)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] < 0)
			return;
		if (jolting[p] > 0)
		{
			equal = FALSE;
			if (jolts + jolting[p] >= min)
				return;
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}

	int sel_b = -1;
	num_t min = 1000;
	for (int b = 0; b < sel_b; b++)
	{
		if (!proc_buttons[b])
		{
			num_t max = 1000;
			for (int p = 0; p < nr_pos; p++)
				if ((((1 << p) & buttons[b]) != 0) && jolting[p] < max)
					max = jolting[p];
			if (sel_b == -1 || max < min)
			{
				sel_b = b;
				min = max;
			}
		}
	}
	
	if (sel_b == -1)
		return;
	
	proc_buttons[sel_b] = TRUE;
	jolts += min;
	for (int p = 0; p < nr_pos; p++)
		if (((1 << p) & buttons[sel_b]) != 0)
			jolting[p] -= min;
	for (int r = min; ; r--)
	{
		search_min(jolts);
		if (r == 0)
			break;

		for (int p = 0; p < nr_pos; p++)
			if (((1 << p) & buttons[sel_b]) != 0)
				jolting[p] -= r;
		}
		search_min(jolts + r);
		for (int p = 0; p < nr_pos; p++)
			jolting[p] = old_jolting[p];
	}
	
	proc_buttons[sel_b] = FALSE;
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		num_t nr_pos_per_button[100];
		nr_buttons = 0;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			int nr_pos = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				nr_pos++;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_pos_per_button[nr_buttons] = nr_pos;
			for (int i = nr_buttons; i > 0 && nr_pos_per_button[i-1] < nr_pos_per_button[i]; i--)
			{
				int nr = nr_pos_per_button[i-1]; 
				nr_pos_per_button[i-1] = nr_pos_per_button[i];
				nr_pos_per_button[i] = nr;
				num_t value = buttons[i-1];
				buttons[i-1] = buttons[i];
				buttons[i] = value;
			}
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int b = 0; b < nr_buttons; b++)
			proc_buttons[b] = FALSE;
		search_min(0);
		printf(" = %d\n", min);
		count += min;
	}
	printf("%lld\n", count);	
}

```

At 20:56, I now think that I know what I did wrong. I will combine the above
approach with what I wrote before.

```c
//bool use_sample = TRUE;

bool proc_buttons[100];

int depth;

void search_min_b(int jolts)
{
	if (jolts >= min)
		return;
	bool equal = TRUE;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] < 0)
			return;
		if (jolting[p] > 0)
		{
			equal = FALSE;
			if (jolts + jolting[p] >= min)
				return;
		}
	}
	if (equal)
	{
		min = jolts;
		return;
	}
	
	// Check if there is a position that has no button anymore
	num_t max_single;
	int single_p = -1;
	for (int p = 0; p < nr_pos; p++)
	{
		if (jolting[p] > 0)
		{
			m = 0;
			
			for (int b = 0; b < nr_buttons; b++)
				if (!proc_buttons[b] && ((1 << p) & buttons[b]) != 0)
					m++;
			if (m == 0)
				return;
			if (m == 1 && single_p == -1)
			{
				single_p = p;
				max_single = jolting[p];
			}
		}
	}
	if (single_p != -1)
	{
		if (jolts + max_single >= min)
			return;
		
		int b = 0;
		while(b < nr_buttons && (proc_buttons[b] || ((1 << single_p) & buttons[b]) == 0))
			b++;

		//printf("%*.*sSingle %d\n", depth, depth, "", b);
		proc_buttons[b] = TRUE;
		depth++;
				
		num_t old_jolting[100];
		for (int p = 0; p < nr_pos; p++)
		{
			old_jolting[p] = jolting[p];
			if (((1 << p) & buttons[b]) != 0)
				jolting[p] -= max_single;
		}
		search_min_b(jolts + max_single);
		for (int p = 0; p < nr_pos; p++)
			jolting[p] = old_jolting[p];
		
		depth--;
		proc_buttons[b] = FALSE;
		
		return;
	}
	
	int sel_b = -1;
	num_t sel_min = 1000;
	for (int b = 0; b < nr_buttons; b++)
	{
		if (!proc_buttons[b])
		{
			for (int p = 0; p < nr_pos; p++)
				if ((((1 << p) & buttons[b]) != 0) && jolting[p] < sel_min)
				{
					sel_b = b;
					sel_min = jolting[p];
				}
		}
	}
	
	if (sel_b == -1)
		return;
	
	//printf("%*.*sAll %lld of %d\n", depth, depth, "", sel_min, sel_b);
	proc_buttons[sel_b] = TRUE;
	depth++;

	//jolts += min;
	//for (int p = 0; p < nr_pos; p++)
	//	if (((1 << p) & buttons[sel_b]) != 0)
	//		jolting[p] -= min;
	for (num_t r = sel_min; r >= 0; r--)
		if (jolts + r < min)
		{
			num_t old_jolting[100];
			for (int p = 0; p < nr_pos; p++)
			{
				old_jolting[p] = jolting[p];
				if (((1 << p) & buttons[sel_b]) != 0)
					jolting[p] -= r;
			}
			search_min_b(jolts + r);
			for (int p = 0; p < nr_pos; p++)
				jolting[p] = old_jolting[p];
			//search_min_b(jolts);
			//if (r == 0)
			//	break;
	
			//for (int p = 0; p < nr_pos; p++)
			//	if (((1 << p) & buttons[sel_b]) != 0)
			//		jolting[p]++;
		}
	
	depth--;
	proc_buttons[sel_b] = FALSE;
}

void solve2()
{
	num_t count = 0;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		char *s = d[i];
		while (*s != '(')
			s++;
		nr_pos = (s - d[i]) - 3;
		num_t nr_pos_per_button[100];
		nr_buttons = 0;
		while (*s == '(')
		{
			s++;
			buttons[nr_buttons] = 0;
			int nr_pos = 0;
			for (;;)
			{
				num_t num = parse_number(&s);
				buttons[nr_buttons] |= 1 << num;
				nr_pos++;
				if (*s++ == ')')
					break;
			}
			s++;
			nr_pos_per_button[nr_buttons] = nr_pos;
			for (int i = nr_buttons; i > 0 && nr_pos_per_button[i-1] < nr_pos_per_button[i]; i--)
			{
				int nr = nr_pos_per_button[i-1]; 
				nr_pos_per_button[i-1] = nr_pos_per_button[i];
				nr_pos_per_button[i] = nr;
				num_t value = buttons[i-1];
				buttons[i-1] = buttons[i];
				buttons[i] = value;
			}
			nr_buttons++;
		}
		for (int j = 0; *s != '}'; j++)
		{
			s++;
			jolting[j] = parse_number(&s);
		}
		min = 1000;
		for (int b = 0; b < nr_buttons; b++)
			proc_buttons[b] = FALSE;
		search_min_b(0);
		printf(" = %d\n", min);
		count += min;
	}
	printf("%lld\n", count);	
}
```

At 21:39, it appears to be still as slow as before.


```
 0 1 2 3 4 5 6 7 8 9

(  1,2,3,4,    7,  9) = 6 
(0,          6      ) 
(  1,2,3,4,5,6,  8,9) 
(0,1,2,  4,5,6,7,8  ) 
(0,1,2,  4,    7    ) 
(  1,  3,4,5,6,7,8,9) 
(0,1,2,3,4,6,  7,  9) 
(    2,3,4,5,6,7    ) 
(0,        5,6,7,  9) 
(0,  2,3,4,5,6,7,8  ) 
(  1,          7    ) 
(  1,2,3,    6,7,8,9) 
(    2,3,      7,8  )
 6 8 9

{73,231,221,196,225,191,212,127,168,195}
```

### Executing this page

The command to process this markdown file, is:
```
../IParse/software/MarkDownC Std.md Day10.md >day10.c; gcc -g -Wall day10.c -o day10; ./day10 10
```
I run the bash file [`runOnSave.sh`](runOnSave.sh) with `10` as the argument,
which everytime when I save this file, runs the above command and shows the
result or the first compile errors, if there are any.

The C file that is compiled is [day10.c](day10.c).



