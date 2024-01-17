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

long long totSumVertices;
long long totNumberSubtrees;

vector<long long> sumPerVertex;
vector<long long> totPerVertex;

vector< vector<long long> > sumPerEdge;
vector< vector<long long> > totPerEdge;

vector<int> bagOfVertex;
vector< vector<int> > bags;
vector<int> bagSize;
vector< pair<int, int> > edges;
int nbEdges;
int edgesSelected;

vector< vector<bool> > edgeSelected;

void recursivelyBuildSubtrees(int idx, long long verticesCoveredMask)
{
    if(idx==nbEdges)
    {
        if(edgesSelected==0)
        {
            totNumberSubtrees+=n;
            totSumVertices+=n;
            for(int i=0; i<n; i++)
            {
                sumPerVertex[i]+=1;
                totPerVertex[i]+=1;
            }
        }
        else
        {
            if(edgesSelected+1==count_bits(verticesCoveredMask))
            {
                totNumberSubtrees+=1;
                totSumVertices+=count_bits(verticesCoveredMask);
                traverse_through_neighbors_nest1(verticesCoveredMask,u)
                {
                    //cerr << "count: " << count_bits(verticesCoveredMask) << endl;
                    sumPerVertex[u]+=count_bits(verticesCoveredMask);
                    totPerVertex[u]+=1;
                    traverse_through_neighbors_nest2((adjacencyList[u]&verticesCoveredMask),neigh)
                    {
                        if(edgeSelected[u][neigh])
                        {
                            sumPerEdge[u][neigh]+=count_bits(verticesCoveredMask);
                            totPerEdge[u][neigh]+=1;
                        }
                    }
                }
            }
        }
        return;
    }
    // option 1: do not use current edge
    recursivelyBuildSubtrees(idx+1,verticesCoveredMask);

    // option 2: do use current edge if possible
    int u=edges[idx].first;
    int v=edges[idx].second;
    if(bagOfVertex[u]==bagOfVertex[v]) return;

    // add edge 
    vector<int> bagOfVerticesChanged;
    int oldBag;
    int newBag;
    if(bagSize[u]>bagSize[v]) swap(u,v);
    oldBag=bagOfVertex[u];
    newBag=bagOfVertex[v];
    int oldSize=bagSize[newBag];
    int newSize=bagSize[oldBag]+bagSize[newBag];
    bagSize[newBag]=newSize;
    for(int x : bags[oldBag])
    {
        bagOfVerticesChanged.push_back(x);
        bags[newBag].push_back(x);
        bagOfVertex[x]=newBag;
    }
    long long newVerticesCoveredMask=(verticesCoveredMask|(1LL<<u)|(1LL<<v));
    edgesSelected++;
    edgeSelected[u][v]=edgeSelected[v][u]=true;
    recursivelyBuildSubtrees(idx+1,newVerticesCoveredMask);
    edgeSelected[u][v]=edgeSelected[v][u]=false;
    edgesSelected--;
    // remove edge
    bagSize[newBag]=oldSize;
    for(int x : bagOfVerticesChanged)
    {
        bagOfVertex[x]=oldBag;
        bags[newBag].pop_back();
    }    
}

void calcSubtrees()
{
    totSumVertices=0;
    totNumberSubtrees=0;
    bagOfVertex.assign(n,-1);
    bags.clear();
    bagSize.assign(n,1);
    for(int i=0; i<n; i++)
    {
        bagOfVertex[i]=i;
        vector<int> singleElement;
        singleElement.push_back(i);
        bags.push_back(singleElement);
    }
    edges.clear();
    nbEdges=0;
    for(int i=0; i<n; i++)
    {
        traverse_through_neighbors_nest1(adjacencyList[i],neigh)
        {
            if(neigh<i) continue;
            nbEdges++;
            edges.push_back(make_pair(i,neigh));
        }
    }
    long long verticesCoveredMask=0;
    edgesSelected=0;
    sumPerVertex.assign(n,0);
    totPerVertex.assign(n,0);
    sumPerEdge.assign(n,vector<long long>(n,0));
    totPerEdge.assign(n,vector<long long>(n,0));
    edgeSelected.assign(n,vector<bool>(n,false));
    recursivelyBuildSubtrees(0,verticesCoveredMask);
}

// reads a list of graphs and for each graph, it will output this graph (first line)
// together with the sum of the orders of the subtrees (second line)
// and the number of subtrees (third line)
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long nb_graphs_read_from_input=0;
    string line;
    while(getline(cin,line))
    {
        //line+="\n";
        nb_graphs_read_from_input++;
        n = getNumberOfVertices(line);
        loadGraph(line,n,adjacencyList);
        calcSubtrees();
        long long GSumVertices=totSumVertices;
        long long GNumConnected=totNumberSubtrees;
        for(int i=0; i<n; i++)
        {
            long long VSum=sumPerVertex[i];
            long long VNum=totPerVertex[i];
            if(VSum*GNumConnected<GSumVertices*VNum)
            {
                cout << "mu(G,v) < mu(G) for graph:" << endl;
                cout << line << endl;
                cout << " and vertex v: " << i << endl;
                cout << "GSum and GNum: " << GSumVertices << " " << GNumConnected << endl;
                cout << "VSum and VNum: " << VSum << " " << VNum << endl;
                int numAdjacentEdgesMuGESmaller=0;
                traverse_through_neighbors_nest1(adjacencyList[i],neigh)
                {
                    long long ESum=sumPerEdge[i][neigh];
                    long long ENum=totPerEdge[i][neigh];
                    cout << "ESum and ENum " << ESum << " " << ENum << endl;
                    if(ESum*VNum < VSum*ENum)
                    {
                        numAdjacentEdgesMuGESmaller++;
                    }
                }
                cout << "Additionally we have mu(G,e)<mu(G,v) for " << numAdjacentEdgesMuGESmaller << " out of " << count_bits(adjacencyList[i]) << " edges e that contain v" << endl;
           }
        }
        /*cout << line << endl;
        cout << GSumVertices << endl;
        cout << GNumConnected << endl;*/
    }
    cout << "Computation for average subtree order finished" << endl;
    return 0;
}