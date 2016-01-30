# gchq-2015-christmas-challenge
My own attempt at cracking GCHQ's Christmas Challenge

## Method:

1. For each row and column, iterate over all possible combinations of black and white squares. Store those that are valid according to that row's or column's key. (*This took 6m 43s on my machine.*)

2. For every square in the grid, find all the combinations of valid row combinations and column combinations (found in the previous step) which set the same value for this square. Store all of these sets for each square.

3. Finally, iterate over all the possible combinations (found in the previous step) among all the squares in a row, with those of the other rows.
