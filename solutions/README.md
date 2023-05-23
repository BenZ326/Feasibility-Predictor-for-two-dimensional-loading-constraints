# Feasibility-Predictor-for-two-dimensional-loading-constraints
## Folder - Solution
The folder contains all the detailed solutions of Table 6, Table B1 and Table B2 in the paper.
For example A102, the BP-AD algorithm got the following solution:
320.2  `represents the objective value`<br>
0,12,16 `Route 0` <br>
0,4,13,14,6,16  `Route 1` <br>
0,7,8,1,16 `Route 2` <br>
0,5,15,9,10,16 `Route 3`<br>
0,2,3,11,16 `Route 4`<br>

As for the packing part, check `./BP-AD-packings/A102`.
Note that there might be missing items in the plots of some packing solutions which are due to the preproceessing step of the BLUE algorithm.
One can always find a trivial way to pack the missing items (either place them in either of the sides or at the bottom).
