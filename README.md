# Hashing Analysis


## Introduction
-------------------------------------------------------------------------------
For this assignment, I decided to implement two different classes of hash tables, both in C++, one a templated version which was used for the open addressing part of the experiment, and one with the C++ list library to complete separate chaining. It was interesting seeing and getting a more significant understanding about the various strengths and weaknesses of each algorithm and collision resolution scheme. Before moving on to the data I present, I will explain the choices I made that affected the results of my data.

### Sizes
-------------------------------------------------------------------------------
I made the choice to use table sizes of 15-20-25 in that order, for each experiment, to keep the results consistent and analyze the efficiency of the algorithms at those sizes respectively.

### Collision Counting
-------------------------------------------------------------------------------
Overall, I added and appended to total collisions to make for better data on the graph, rather than collisions only at each insertion.
Open Addressing: I counted a collision each position that an item had to move until landing in an open space.
Separate Chaining: I counted a collision for each position in the linked list that the item was placed in.
(In hindsight, it may have made for more concise data counting only 1 collision for insertion into the linked list.)
	
## Separate Chaining: Graphs

![Graph 1](https://i.imgur.com/JA7xl9b.png)
![Graph 2](https://i.imgur.com/o0bZ0M4.png)

## Separate Chaining: Discussion

### General
-------------------------------------------------------------------------------
From displaying some of the results of tables I had made, I quickly saw something that the data I presented in the graphs don’t properly illustrate; reaching higher load factors was difficult simply from the sheer number of values that had to be added to the hash table. This is helpful in that hash tables implementing separate chaining will never run out of space, but instead the linked lists in each position will just get unreasonably large (which is bad for computational purposes anyway, but can be better than reallocating space for a table that has run out). It will be obvious soon that the graphs I created showing open addressing have a substantially lower number of collisions when they reach a load factor of 1.

It is clear that separate chaining is very efficient for insertion and removal, but, as can be observed much more clearly in larger table sizes, leaves some empty spaces and takes much longer to fill every key with at least one value.

### Mod Table Size Hashing
-------------------------------------------------------------------------------
For the smaller table sizes that I decided to chose, this hashing algorithm resulted in consistently filling the hash table and without having an exorbitant number of values inserted to do so. It is worth noting also that it easily halved the mid square hashing algorithm’s collision count. As the graph shows, it seems like the table size 15 also provided a substantially lower collision count than the slightly higher tables and a much less exponential growth.

### Mid Square Hashing
-------------------------------------------------------------------------------
I noticed something about the separate chaining using mid square hashing pretty early on which is not a problem for open addressing but certainly affects the collision count; for small table sizes, where the key squared won’t be more than 3 digits (or even 4 I believe), there are certain indices in the hash table which will NEVER be selected by the algorithm, because of a mathematical property of squaring the numbers that I didn’t explore in detail, but I took the modulus for specifically every value for table size 15 as a test (every key between 0 – 60(3 * tableSize)) and the indices 12, 13, and 14 were never a result. This actually means that it is impossible to hit a load factor of 1 with mid square hashing at low table values. I decided then, to cap the load factor at about .8 to get accurate data without infinite loops running. Upon a bit of research I’ve learned that it is actually much better to use mid square hashing for separate chaining on large table sizes (4 digit keys before squaring are more ideal). All things considered, the exponential nature of the collisions is also due to the way I decided to count the collisions, otherwise the largest amount for separate chaining would be around 100.	

## Open Addressing:

![Graph 3](https://i.imgur.com/WYPrKkv.png)
![Graph 4](https://i.imgur.com/nPvk6bU.png)

## Open Addressing: Discussion

### General
-------------------------------------------------------------------------------
Open addressing seems to be much more efficient for low table sizes, and is certainly much more linear until the last value or two are added to the table, since it is at worst O(n) time to reach the only remaining open position. Because of how I have chosen to count collisions, this also means it is at worst ‘n’ collisions for the last insertion itself, meaning relatively exponential growth at the very end of the experiment. Overall, the number of collisions was much smaller when using open addresssing, but it could be close in terms of time of insertion specifically between the two collision schemes while using mod table size hashing (Again, the number of collisions in the separate chaining may have been more accurate if counted less times).

### Mod Table Size Hashing
-------------------------------------------------------------------------------
With the experiment ran at a table size of 15, there were only just under 30 collisions required to completely fill the table. Though the table runs out of space at this point, it is definitely an efficient collision resolution scheme, and it is important to note that table sizes will ALWAYS be intentionally created with much more space than the programmer imagines they will have to use (2 to 3 times the project amount, usually). For small table sizes, as I mentioned in the separate chaining section, it seems like the simple mod table size hashing algorithm is the most efficient and useful. It is also worth noting that the variance of this algorithm seems to be much more stable and always produces relatively low collisions for the general case.

### Mid Square Hashing
-------------------------------------------------------------------------------
The mid square hashing algorithm for open addressing doesn’t create nearly as much of a problem, since the indices which will never initially be selected will eventually receive the values that move after their key was already inhabited by a previous value. Due to this difference, the table was able to easily reach a load factor of 1 without running into any looping problems but did experience a similar exponential growth that of mod table size near the end. It seems also that there was simply more variance with this algorithm, since the table size of 15 had an incredibly low 22 collisions, but the larger sizes of the 3 were near the hundreds mark. 
