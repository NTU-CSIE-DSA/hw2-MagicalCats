# DSA 2023 HW2 - Magical Cats
# Tutorial
Keywords: `sorting`, `binary search`, `circular array`, `linked list`
## Preprocessing
1. For each color, push all cats with that color into a deque and sort the deque. Let's call them **color deques**. This can be done efficiently by sorting with the key (color, appetite) first.
3. Sort all deques by color. Given a color, we can find the corresponding **color deque** in $O(log N)$ with binary search.
4. Sort all cats by appetite. Create a linked list with appetite in sorted order. Let's call this **appetite linked lists**.
5. Implement **appetite linked lists** in a way that we can find the node by appetite in $O(log N)$.

All preprocessing can be done in $O(NlogN)$ time.
## Questioning step

1. For each query $(c_i,l_i,r_i)$, apply binary search to find the lower bound and upper bound in the according **color deque**. The answer is the number of elements within two bounds.

This step can be done in $O(logN)$ time.

## Swapping step
1. Notice that all cats have unique appetite values and the two swapping cats have "adjacent" appetites.
2. By 1. we can directly swap two cats' appetites while keeping the sorted order of **color arrays** and **appetite linked lists**. 
3. Be careful that if two cats have the same color, we cannot swap the appetites directly because the sorted order would be invalid. We can swap indices instead.

Finding the swapping target cost $O(logN)$ time, and swapping can be done in $O(1)$ time.
## Magic step

For each magic step,
1. Find the max/min appetite in all cats by the sorted appetite linked list to compute the value after magic.
2. Find the **color deque**, pop the cat from front/back, and push the cat with new appetite value to front/back.
3. Find the cat in appetite in **appetite linked list**, remove it, and insert it to the head/tail of **appetite linked list**.

Finding the magic target cost $O(logN)$ time and manipulating deque/linked list cost $O(1)$ time.
## Coding Tips
1. We can encapsulate the deque data structure and access it with indices [0...n-1]. Otherwise, the binary search would be difficult to implement.
2. Implement lower bound and upper bound binary search separately.
3. For a relatively concise implementation, please refer to the solution.


## Testdata
Generated by [TPS](https://github.com/ioi-2017/tps)
```
# generate testdata
tps gen
```