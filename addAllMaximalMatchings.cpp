// This program reads a graph and outputs this graph together with all graphs obtained from adding a maximal matching to this graph

#include <bits/stdc++.h>

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32 bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)

using namespace std;

const int nb_bits=32;
#define MAXVERTICES 32

int getNumberOfVertices(string graphString) 
{
	if(graphString.size() == 0){
        printf("Error: String is empty.\n");
        abort();
    }
    else if((graphString[0] < 63 || graphString[0] > 126) && graphString[0] != '>') {
    	printf("Error: Invalid start of graphstring.\n");
    	abort();
    }

	int index = 0;
	if (graphString[index] == '>') { // Skip >>graph6<< header.
		index += 10;
	}

	if(graphString[index] < 126) { // 0 <= n <= 62
		return (int) graphString[index] - 63;
	}

	else if(graphString[++index] < 126) { 
		int number = 0;
		for(int i = 2; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else if (graphString[++index] < 126) {
		int number = 0;
		for (int i = 5; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else {
		printf("Error: Format only works for graphs up to 68719476735 vertices.\n");
		abort();
	}
}

void loadGraph(string graphString, int numberOfVertices, long long adjacencyList[]) {
	int startIndex = 0;
	if (graphString[startIndex] == '>') { // Skip >>graph6<< header.
		startIndex += 10;
	}
	if (numberOfVertices <= 62) {
		startIndex += 1;
	}
	else if (numberOfVertices <= MAXVERTICES) {
		startIndex += 4;
	}
	else {
		printf("Error: Program can only handle graphs with %d vertices or fewer.\n",MAXVERTICES);
		abort();
	}

	for (int vertex = 0; vertex < numberOfVertices; vertex++) { //Initialize adjacencyList.
		adjacencyList[vertex] = 0;
	}

	int currentVertex = 1;
	int sum = 0; 
	for (int index = startIndex; index<graphString.size(); index++) {
		int i;
		for (i = prev(graphString[index] - 63, 6); i != -1; i = prev(graphString[index] - 63, i)) {
			while(5-i+(index-startIndex)*6 - sum >= 0) {
				sum += currentVertex;
				currentVertex++;
			}
			sum -= --currentVertex;
			int neighbour = 5-i+(index - startIndex)*6 - sum;
            adjacencyList[currentVertex]|=(1LL<<neighbour);
            adjacencyList[neighbour]|=(1LL<<currentVertex);
		}
	}
}

#define left_shifted(n,x) ((n)<<(x))
#define set_bit(n,i) ((n)|=left_shifted(1LL,i))
#define count_bits(n) (__builtin_popcountll((n)))
//#define index_rightmost_bit(n) (count_bits((n)^(n-1))-1)
#define index_rightmost_bit(n) (__builtin_ctzll(n))
#define rightmost_bit_removed(n) ((n)&((n)-1))
#define traverse_through_neighbors_nest1(x,neighbor) for(long long (neighbor)=index_rightmost_bit((x)),DESTROYED_MASK1=(x); (DESTROYED_MASK1)!=0; (DESTROYED_MASK1)=rightmost_bit_removed((DESTROYED_MASK1)),(neighbor)=index_rightmost_bit((DESTROYED_MASK1)))
#define traverse_through_neighbors_nest2(x,neighbor) for(long long (neighbor)=index_rightmost_bit((x)),DESTROYED_MASK2=(x); (DESTROYED_MASK2)!=0; (DESTROYED_MASK2)=rightmost_bit_removed((DESTROYED_MASK2)),(neighbor)=index_rightmost_bit((DESTROYED_MASK2)))

int n;
long long adjacencyList[MAXVERTICES];

vector< pair<int, int> > matching;
void recursivelyBuildMaximalMatching(int idx, long long matchingMask)
{
    if(matchingMask&(1LL<<idx)) return recursivelyBuildMaximalMatching(idx+1,matchingMask);
    if(idx==n)
    {
        bool maximal=true;
        for(int i=0; i<n && maximal; i++)
        {
            if(matchingMask&(1LL<<i)) continue;
            traverse_through_neighbors_nest1((~adjacencyList[i])&(~matchingMask)&((1LL<<(n))-1),neigh)
            {
                if(i==neigh) continue;
                maximal=false;
                break;
            }
        }
        if(!maximal) return;
        // add the matching
        for(pair<int, int> p : matching)
        {
            int u=p.first;
            int v=p.second;
            adjacencyList[u]=(adjacencyList[u]^(1LL<<v));
            adjacencyList[v]=(adjacencyList[v]^(1LL<<u));
        }
        cout << "n=" << n << endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(adjacencyList[i]&(1LL<<j)) cout << "1";
                else cout << "0";
            }
            cout << endl;
        }
        // remove the matching
        for(pair<int, int> p : matching)
        {
            int u=p.first;
            int v=p.second;
            adjacencyList[u]=(adjacencyList[u]^(1LL<<v));
            adjacencyList[v]=(adjacencyList[v]^(1LL<<u));
        }
        return;
    }
    // option 1: do not use current idx
    recursivelyBuildMaximalMatching(idx+1,matchingMask);
    
    // option 2: use current idx if both ends are not taken
    long long maskBitsAfterIdx=((1LL<<(n-idx-1))-1)<<(idx+1);
    // option 2: use current idx
    traverse_through_neighbors_nest1((~adjacencyList[idx])&(~matchingMask)&(maskBitsAfterIdx),neigh)
    {
        matchingMask=(matchingMask^(1LL<<idx));
        matchingMask=(matchingMask^(1LL<<neigh));
        matching.push_back(make_pair(idx,neigh));
        recursivelyBuildMaximalMatching(idx+1,matchingMask);
        matching.pop_back();
        matchingMask=(matchingMask^(1LL<<idx));
        matchingMask=(matchingMask^(1LL<<neigh));
    }
    return;
}

void addMaximalMatchings()
{
    long long matchingMask=0LL;
    matching.clear();
    recursivelyBuildMaximalMatching(0,matchingMask);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long nb_graphs_read_from_input=0;
    string line;
    // reads a graph, outputs this graph together with all graphs obtained from adding a maximal matching to this graph
    while(getline(cin,line))
    {
        //line+="\n";
        nb_graphs_read_from_input++;
        n = getNumberOfVertices(line);
        loadGraph(line,n,adjacencyList);
        // output current graph
        cout << "n=" << n << endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(adjacencyList[i]&(1LL<<j)) cout << "1";
                else cout << "0";
            }
            cout << endl;
        }
        // output all graphs obtained from adding a maximal matching to G
        addMaximalMatchings();
    }
    //cerr << nb_graphs_read_from_input << " graphs were read from input" << endl;
    return 0;
}
