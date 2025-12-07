# Advent Of Code 2025

My effort for the [Advent of Code 2025](https://adventofcode.com/2025) contest.
All times are for Central European Timezone (CET).

I am going to use [MarkDownC](https://github.com/FransFaase/IParse/?tab=readme-ov-file#markdownc)
again, like I did in the past years. MarkDownC is a tool for
performing literatie programming with MarkDown files. It parses one
or more MarkDown files and outputs all the fragments of C code found
in those files, rearranging them such that all the definitions are placed
in an order that can be compiled. When a certain function or variable
declaration is repeated, the last version is put in the output.

### Monday, December 1, 2025

I woke up around 4:15 and did not fall asleep again. Around 5:45, I was sitting
behind my laptop waiting for the puzzle to appear. I had forgotten to open the
file for the input to be pasted into and also gave it the wrong name when I saved
it the first time. My answer for the first part was correct in one go. For the
second part, I required two tries. I had already somewhat expected that the first
try was going to be wrong due to a combination not shown in the example input.

See further [Day 1](Day01.md) and [day01.c](day01.c).

### Tuesday, December 2, 2025

I started at 6:00. I struggled a lot with the first part, probably because I
decided to go with a smart numeric method, instead of the more brute force
approach of printing all the numbers as string and check if they are repeated.
By the fact that at the time, I finished, far more people had solved the second
part than those only having solved the first part, I conclude that many went
with the brute force string method, which I used for the second part.

See further [Day 2](Day02.md) and [day02.c](day02.c).

### Wednesday, December 3, 2025

I started at 6:00 and found the answers to both puzzles without many problems,
except for some small bug related to incorrect or missing variables. Then I
also spend some time finding a non-recursive, much more efficient solution for
the second part.

See further [Day 3](Day03.md) and [day03.c](day03.c).

### Thursday, December 4, 2025

I started at 6:00 and finished both puzzles at 6:10:33. With the first puzzle,
I made one mistake: I first implemented 'four or less' instead of 'less than four'.
For the second part, I had to fix two small typing errors.

See further [Day 4](Day04.md) and [day04.c](day04.c).

### Friday, December 5, 2025

I started at 6:00 and finished both puzzles at 6:52:45. For the second part,
I decided not to use the code that I had written during an earlier year for
combining ranges, but to write some new code. After I found the answer for the
second part, I spend less than 10 minutes to find the answer with the code
I wrote earlier.

See further [Day 5](Day05.md) and [day05.c](day05.c).

### Saturday, December 6, 2025

I started at 6:00. This was not a very particular difficult puzzle with respect
to the algorithm to use, nevertheless it took me quite some time, first not
noticing a warning that was actual an error, making my decide to adapt my
run script to report all warnings and treat them as errors. And with the second
part, I struggled a bit to parse the digits in the correct direction.

See further [Day 6](Day06.md) and [day06.c](day06.c).

### Sunday, December 7, 2025

I started a bit after 6:00. When solving the first part, I already got the
idea what the second part was going to be and that idea was correct. Still
took me some time to solve the second part, due to some mistakes.

See further [Day 7](Day07.md) and [day07.c](day07.c).

### Personal stats

The columns 'Gold' and 'Silver' contain the numbers from the [Stats](https://adventofcode.com/2025/stats)
page after I finished both parts. This gives some idea of my global ranking.

```
Day   -Part 1-   -Part 2-   -Gold-  -Silver-
  1   00:09:36   00:17:35      869      2484
  2   01:14:05   01:44:30     8344      2698
  3   00:13:16   00:29:01     2371      3649
  4   00:06:53   00:10:33      874      1069  
  5   00:08:17   00:52:45     4903      3931
  6   00:28:07   00:42:29     2522      3988
  7   00:17:28   00:34:48     2305      2486
```
 
