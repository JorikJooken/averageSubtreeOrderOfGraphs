#include <bits/stdc++.h>

using namespace std;

// expects three parameters as input (K, L, P) and 
// it will output the following graph:
// take a clique of order K, a clique of order L and a cycle of order P. Let u and v be two vertices at distance 2 in the clique.
// Now identify one vertex of the fist clique with u and one vertex of the second clique with v.
// the order of the whole graph is thus K+L+P-2
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
    for(int i=0; i<P; i++)
    {
        adjMatrix[i][(i+1)%P]=adjMatrix[(i+1)%P][i]=1;
    }

    for(int i=0; i<K; i++)
    {
        for(int j=0; j<K; j++)
        {
            if(i==j) continue;
            int u=P+i-1;
            if(i==0) u=0;
            int v=P+j-1;
            if(j==0) v=0;
            if(i==0 || j==0) adjMatrix[u][v]=1;
        }
    }
    for(int i=0; i<L; i++)
    {
        for(int j=0; j<L; j++)
        {
            if(i==j) continue;
            int u=P+K-1+i-1;
            if(i==0) u=2;
            int v=P+K-1+j-1;
            if(j==0) v=2;
            if(i==0 || j==0) adjMatrix[u][v]=1;
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
