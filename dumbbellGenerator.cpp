#include <bits/stdc++.h>

using namespace std;

// expects three parameters as input (K, L, P) and 
// it will output a dumbbell consisting of a clique of order K and a clique of order L for which a vertex of each is connected by a path
// such that the path contains P vertices
// e.g. the dumbbell with parameters (6,6,4) has order 6+6+4-2=14
int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        cerr << "Wrong number of arguments." << endl;
    }
    int K=atoi(argv[1]);
    int L=atoi(argv[2]);
    int P=atoi(argv[3]);
    int n=K+L+P-2;
    vector< vector<int> > adjMatrix(n,vector<int>(n,0));
    for(int i=0; i<K; i++)
    {
        for(int j=0; j<K; j++)
        {
            if(i!=j) adjMatrix[i][j]=1;
        }
    }
    for(int i=0; i<L; i++)
    {
        for(int j=0; j<L; j++)
        {
            if(i!=j) adjMatrix[K+P-2+i][K+P-2+j]=1;
        }
    }
    if(P==2)
    {
        adjMatrix[0][K]=adjMatrix[K][0]=1;
    }
    else
    {
        for(int i=K; i<K+P-2; i++)
        {
            adjMatrix[i][i-1]=adjMatrix[i-1][i]=1;
            adjMatrix[i][i+1]=adjMatrix[i+1][i]=1;
        }
    }

    cout << "n=" << n << endl;
    for(int i=0; i<n; i++)
    {
        int deg=0;
        for(int j=0; j<n; j++)
        {
            deg+=adjMatrix[i][j];
            cout << adjMatrix[i][j];
        }
        /*if(deg != 3)
        {
            cout << "Degree of vertex " << i << " was different from 3! I exit." << endl;
            exit(1);
        }*/
        cout << endl;
    }
    return 0;
}
