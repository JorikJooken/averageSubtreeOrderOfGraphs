# Average subtree order
This repository contains code and data related to the average subtree order of a graph.

Below, we briefly describe how the different programs can be invoked and what their input and output is.
We will assume that Linux is being used and that nauty is installed. The details on how to install nauty can be found on [this link](https://pallini.di.uniroma1.it/).

The graphs that we are dealing with will either be in adjacency matrix format or graph6 format. We will use nauty to convert the adjacency matrix format to graph6 format (using "amtog"), filtering out pairwise non-isomorphic graphs (using "shortg") and adding an edge to a graph in all possible ways (using "addedgeg").

The programs related to the average subtree order can be compiled by the following command:
```bash
make
```


## CODE
### dumbbellGenerator.cpp
This program expects three parameters as input (K, L, P) and it will output a dumbbell consisting of a clique of order K and a clique of order L for which a vertex of each is connected by a path such that the path contains P vertices.
For example, the dumbbell with parameters (6,6,4) has order 6+6+4-2=14.

Invoking the command

```bash
./dumbbellGeneratorExecutable 3 3 2
```

will result in the following output:
```
n=6
011100
101000
110000
100011
000101
000110
```

### addAllMaximalMatchings.cpp
This program reads a graph in graph6 format and outputs this graph together with all graphs obtained from adding a maximal matching to this graph.

Invoking the command

```bash
./dumbbellGeneratorExecutable 3 3 2 | ./nauty/nauty27r3/amtog | ./addAllMaximalMatchingsExecutable
```

will result in the following output:
```
n=6
011100
101000
110000
100011
000101
000110
n=6
011100
101010
110001
100011
010101
001110
n=6
011100
101001
110010
100011
001101
010110
n=6
011110
101100
110001
110011
100101
001110
n=6
011110
101001
110100
101011
100101
010110
n=6
011101
101100
110010
110011
001101
100110
n=6
011101
101010
110100
101011
010101
100110
```
### computeAverageSubtreeOrder.cpp
This program reads a list of graphs in graph6 format and for each graph, it will output this graph (first line) together with the sum of the orders of the subtrees (second line) and the number of subtrees (third line).

Invoking the command
```bash
./dumbbellGeneratorExecutable 3 3 2 | ./nauty/nauty27r3/amtog | ./addAllMaximalMatchingsExecutable | ./nauty/nauty27r3/amtog | ./nauty/nauty27r3/shortg | ./computeAverageSubtreeOrderExecutable 
```
will result in the following output:
```
E`ow
204
54
Eqlw
1666
339
E{Sw
1002
210
```

### allDecreaseOrNot.cpp.cpp
This program is a small helper program that reads triples of lines that represent a graph, the sum of the orders of the subtrees and the number of subtrees. The program will find the graph G with the least number of subtrees and will check for how many graphs the average subtree order is at most equal to the average subtree order of G.

Invoking the command
```bash
./dumbbellGeneratorExecutable 3 3 2 | ./nauty/nauty27r3/amtog | ./addAllMaximalMatchingsExecutable | ./nauty/nauty27r3/amtog | ./nauty/nauty27r3/shortg | ./computeAverageSubtreeOrderExecutable | ./allDecreaseOrNotExecutable
```
will result in the following output:
```
Average order non-strictly decreased 1 times out of 3 pairwise non-isomorphic graphs
Average order strictly decreased 0 times out of 3 pairwise non-isomorphic graphs
```

## DATA
### resultsForDumbbell_6_6_4
These are the results that show that the dumbbell with parameters (6,6,4) has the property that adding any maximal matching or any edge, except for one edge, strictly decreases its average subtree order.

This folder contains the output of invoking the following command:
```bash
./dumbbellGeneratorExecutable 6 6 4 | ./nauty/nauty27r3/amtog | ./addAllMaximalMatchingsExecutable | ./nauty/nauty27r3/amtog | ./nauty/nauty27r3/shortg | ./computeAverageSubtreeOrderExecutable 
```
(i.e. the file addMaximalMatchingToDumbbell_6_6_4.txt contains the average subtree order for the dumbbell with parameters (6,6,4) as well as the subtree orders of all graphs that are obtained by adding a maximal matching to it). It took quite some time for this program to finish running, so this file is given for the sake of convenience.

Invoking the command
```bash
./allDecreaseOrNotExecutable < resultsForDumbbell_6_6_4/addMaximalMatchingToDumbbell_6_6_4.txt
```

will result in the following output:

```
Average order non-strictly decreased 15 times out of 15 pairwise non-isomorphic graphs
Average order strictly decreased 14 times out of 15 pairwise non-isomorphic graphs
```

This folder also contains the file addOneEdgeToDumbbell_6_6_4.txt, which contains the average subtree order for the dumbbell with parameters (6,6,4) as well as the subtree orders of all graphs that are obtained by adding an edge to that dumbbell. It took quite some time for this program to finish running, so this file is given for the sake of convenience.

This file could also be reconstructed manually by invoking the command:

```bash
./dumbbellGeneratorExecutable 6 6 4 | ./nauty/nauty27r3/amtog | ./nauty/nauty27r3/addedgeg | ./nauty/nauty27r3/shortg | ./computeAverageSubtreeOrderExecutable
```

and then pasting the output in a file that already contains the average subtree order of the dumbbell with parameters (6,6,4).

Finally, invoking the command
```bash
./allDecreaseOrNotExecutable < resultsForDumbbell_6_6_4/addOneEdgeToDumbbell_6_6_4.txt
```

will result in the following output:

```
Average order non-strictly decreased 6 times out of 7 pairwise non-isomorphic graphs
Average order strictly decreased 5 times out of 7 pairwise non-isomorphic graphs
```

Note that for both files, the dumbbell with parameters (6,6,4) is also included (e.g. the file addOneEdgeToDumbbell_6_6_4.txt contains 7 graphs and their average subtree order: the dumbbell itself and also the 6 pairwise non-isomorphic graphs obtained by adding an edge to that dumbbell).
