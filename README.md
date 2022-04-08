# n-puzzle

* **Gameplay**<br/>
The [n-puzzle](https://en.wikipedia.org/wiki/15_puzzle) (most popularly known for the 8-puzzle or 15-puzzle) is a problem where we have at our disposal a kxk board with k*k-1(=n) numbered tiles and an empty spot. A tile adjacent to the empty spot can be moved to this position. The acceptable moves are up, down, left, right. The goal is, starting from a given board to reach a given board where all the titles starting from the top left are sorted in ascending order. <br/>
For example, the puzzle <br/>
8 0 6<br/>
5 4 7<br/>
2 3 1<br/>
needs to reach the form:<br/>
1 2 3<br/>
4 5 6<br/>
7 8 0<br/>

* **Solution** <br/>
This C implementation uses A* search to solve this problem using as heuristic the sum of the manhattan distance of all non-empty pieces from the blocks to their estimated goal positions.
