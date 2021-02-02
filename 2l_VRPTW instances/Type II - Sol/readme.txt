Format of an instance:
column 1: the id of a node, 0 is the depot
column 2: the x coordinate
column 3: the y coordinate
column 4: the service duration
column 5: the demand 
column 6: the start time of the associated time window
column 7: the due time of the associated time window
The rest of the columns give the widths and heights of the items.
For instance,
2L-VRPTW-C102-25-PC2.csv, customer 1 has the following information
1,45,68,90,10,0,1127,2,7,12,2,0,0,0,0,0,0
The 8th column is 2, representing the width of the first item and the 9th column is 7, the height of the first item. 
The second item is 12 in width and 2 in height. The rest columns are all zeros,  indicating that there are two items in total associated with the customer.
