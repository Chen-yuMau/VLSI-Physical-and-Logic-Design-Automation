# VLSI-Physical-and-Logic-Design-Automation
This repository include some of the most fundamental concepts of VLSI design automation
The files testa-testg are test files.

## 1: Partitioning
This file implements Fiduccia Mattheyses partitioning algorithm. Run file from CMD to pass input filename as a parameter. It will ask for number pf passes. The code is written with placement in mind. This means the node index and the number of nodes are left purposefully free, as apposed to a predefined number. Supports hyperedges
## 2: Placement
This file includes averything from the previous file. The difference is it runs a recursive partitioning function that recursivly partitions the graph and places it onto a 16x16 grid. Supports hyperedgedgs
## 3: Routing
This file includes averything from the previous file. After placing the nodes onto a 16x16 grid, this file puts it onto a 24x24 grid and implements WFS to try to connect all the edges in the file. Does not support hyperedges.

# ----------------------------------------------------------------------------

This is the contents of testa:

> 7 5
> 3 1 0 4 
> 3 3 2 0 
> 3 3 2 1 
> 2 5 2 
> 2 6 3 
> 3 4

The first number of the first line (7) indicates how many nodes or vertices are in the graph of the input.

The second number of the first line (5) indicates how many edges are in the graph of the input.

The subsequent lines are for each of the edges.

The first number of each subsequent line is the number of nodes or vertices are in the edge (since the partitioning and the placement support hyper edges). However, if you want to run the Routing file, make sure all of the edges only contain two nodes or vertices.

The following numbers are the node indexes. They don't need to be in any order or start at any number at all.

The last line is the constraints for the partition file. The first number is the minimum of the smaller partition.
