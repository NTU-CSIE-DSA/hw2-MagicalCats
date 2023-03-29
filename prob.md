## Description
DSA is a passionate cat lover who shares zir home with hundreds of thousands of furry felines. These adorable creatures consume tons of food every day, so DSA wants to obtain some statistics to make zir future feeding plan.

There are $N$ cats in the house, and each cat living in the $i^{th}$ room has a **unique** appetite $a_i$. This appetite value represents the weight of food distributed to that cat every day. Additionally, each cat is associated with a color denoted by an integer value $b_i$.

DSA wants to determine the relationship between a cat's color and its appetite. Specifically, ze wants to know how many cats have an appetite within $[l_j,r_j]$ and share the color $x_j$. 

However, some greedy cats in the house are seeking more food and secretly swap their bowls with some other unsuspecting victims. To avoid getting caught by DSA, a greedy cat always chooses a victim whose appetite is closest to its own among the cats with larger appetites. Whenever two cats' bowls are swapped, their appetites are also swapped forever, given that DSA distributes food based on the size of the bowls. Note that the cat with the largest appetite currently cannot be greedy.

Recently, a magical fairy visited DSA's house and came 
up with an interesting idea. The fairy will select a specific 
color $x_j$ and then choose the cat with the highest or lowest 
appetite among all the cats with that color. The fairy granted 
magical powers to the chosen cat, which could cast a spell to 
change its appetite to the highest appetite of all cats plus one,
denoted as $\max_{0\le i < N}(a_i)+1$. However, sometimes the 
magic could fail and cause the reverse effect, changing the cat's 
appetite to the smallest appetite of all cats minus one, 
denoted as $\min_{0\le i < N}(a_i)-1$. 
The selection of the cat with the highest or lowest appetite to grant magic is denoted by 
$s_j \in  \\{1,0 \\}$, 
and the success or failure of the magic is denoted by 
$t_j \in \\{1,0 \\}$. Note that a cat's appetite can become negative here because of magic.

DSA begins to ask some questions, but greedy cats may swap bowls, and magic spells may be cast during the question-answering process. The total number of events, including questions, swaps, and magic, is $M$. Despite the disturbances caused by these troublemakers, can you help DSA answer zir questions?
## Input
The first line contains two integers $N,M$, the number of cats and the number of events.

The second line contains $N$ integers $a_0 ... a_{N-1}$ , and $a_i$ is the appetite of $i^{th}$ cat.

The third line contains $N$ integers $b_0 ... b_{N-1}$ , and $b_i$ is the color of $i^{th}$ cat

Each of the following $M$ lines is one of the formats:
* $1$ $x_j$  $l_j$  $r_j$ : An integer $1$ for questioning event followed by three integers $x_j$ $l_j$ $r_j$ ,the color, the lower bound and the upper bound of a question.
A cat with color $x_j$ may not exist for a questioning event.
* $2$ $k_j$ : An integer $2$ for swapping event followed by another integer $k_j$ ,the index of greedy cat.
* $3$ $x_j$ $s_j$ $t_j$ : An integer $3$ for magic event followed by three integers $x_j$ $s_j$ $t_j$, the color, the magic target, the magic result.
A cat with color $x_j$ always exists for a magic event.

Note that the cats are 0-indexed.

## Output
For each questioning event, output the answer in a newline.


## Constraint
* $2 \le N \le 3\times10^{5}$
* $1 \le M \le 3\times10^{5}$
* $1 \le a_{i},b_{i},x_{j} \le 10^{9}$
* $0 \le k_{j} < N$
* $s_j , t_j \in \\{0,1\\}$
* $-2 \times 10^{9} \le l_j \le r_j \le  2 \times 10^{9}$

## Subtasks

### subtask 1 (5pts)
* $1 \le M \le 10^3$

### subtask 2 (10pts)
* Only questioning event.

### subtask 3 (35pts)
* Only questioning and swapping event.

### subtask 4 (50pts)
* No other constraints.

## Sample Cases
### Sample Input 1
```
6 5
2 1 6 4 5 3
2 1 3 2 3 3
1 2 1 4
1 4 3 6
2 3
1 2 2 3
1 3 4 6

```
### Sample Output 1
```
2
0
1
2
```
### Sample Input 2
```
10 7
6 3 2 4 10 5 9 8 7 1
5 8 1 6 7 7 4 9 1 9
2 8
3 1 0 1
1 1 9 11
1 1 8 10
1 1 5 11
2 8
1 1 5 9
```

### Sample Output 2
```
1
1
2
1
```
## Hint
* We recommend you consider only the first two events (subtasks 2~3) first.