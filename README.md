# n-puzzle problem
Play the game [here](https://www.artbylogic.com/puzzles/numSlider/numberShuffle.htm)
* **Gameplay**<br/>
The [n-puzzle](https://en.wikipedia.org/wiki/15_puzzle) (most popularly known for the 8-puzzle problem or 15-puzzle problem) problem is a problem where we have at our disposal a k x k board with k*k-1(=n) numerated tiles and an empty spot. A tile adjacent to the empty piece can be moved to this position. The acceptable moves are up, down, left, right. The goal is, starting from a given board to reach a given board where all the titles starting from the top left are sorted in ascending order. <br/>
For example, the puzzle <br/>
<table>
  <tr>
  <td>8</td> <td> </td> <td>6</td>
  </tr>
  <tr>
    <td>5</td> <td>4</td> <td>7</td>
  </tr>
  <tr>
    <td>2</td> <td>3</td> <td>1</td>
  </tr>
</table>
needs to reach the form:<br/>
<table>
  <tr>
  <td>1</td> <td>2</td> <td>3</td>
  </tr>
  <tr>
    <td>4</td> <td>5</td> <td>6</td>
  </tr>
  <tr>
    <td>7</td> <td>8</td> <td>0</td>
  </tr>
</table>

* **Solution** <br/>
This C implementation uses A* search to solve this problem using as heuristic the sum of the manhattan distance of all non-empty pieces from the blocks to their estimated goal positions.

* **Data representation** <br/>
> We represent each puzzle by saving:
1. The puzzle itself<br/>
2. A pointer to the puzzle it was generated by (to print the solution)<br/>
3. The move that caused the generation of the puzzle (u-up, d-down, l-left, r-right)<br/>
4. The coordinates of the empty piece (for instant access when swapping pieces)<br/>

* **How the search works** <br/>
-At first, we find the heuristic calculation of the first given puzzle (using the manhattan distance of every piece). <br/><br/>
-When generating  the possible puzzles of a certain puzzle, we first check if the move that caused the puzzle to come to its current form is the reverse action of the move we are trying to apply. For example, if a puzzle came to its current form by moving down the empty piece (or moving up a numerated piece), moving the empty piece up will cause the generation of the puzzle before moving down the empty piece. So, we ignore it. <br/><br/>
-If the generation of the puzzle is successful, we fix the heuristic calculation of the new puzzle by adding the manhattan distance of the old empty, now occupied, piece and removing the manhattan distance of the now empty piece (once occupied by the old puzzle) to the manhattan distance of the old puzzle.
