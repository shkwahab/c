// Copyright 2012 Mikhail Mozolin

//    This file is part of FindAllSpanningTrees.
//
//    FindAllSpanningTrees is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    FindAllSpanningTrees is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with  FindAllSpanningTrees.  If not, see <http://www.gnu.org/licenses/>.

// ABSTRACT:
// Enumerates all spanning trees in a directed graph
//
// REFERENCES:
// Gabow, Harold N. and Myers, Eugene W. Finding all spanning trees of directed and undirected graphs.
// SIAM J. of Comput., Vol. 7, No. 3, August 78, pp. 280-287
// Cormen, Thomas H. et.al. Introduction to algorithms. The MIT Press, Cambridge, 1990

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

// number of vertices in a graph
const int V = 4;

// represents an edge of a graph
class edge
{
public:
    int from_node; // id of the from node
    int to_node;   // id of the to node
    int operator!=(const edge &e)
    {
        // This function overloads the "not equal to" operator for objects of the 'edge' class.
        // It compares the 'from_node' and 'to_node' members of the current object and the input object 'e',
        // and returns 'true' if they are not equal, 'false' otherwise.
        return (this->from_node != e.from_node || this->to_node != e.to_node);
    }

    int operator==(const edge &e)
    {
        // This function overloads the "equal to" operator for objects of the 'edge' class.
        // It compares the 'from_node' and 'to_node' members of the current object and the input object 'e',
        // and returns 'true' if they are equal, 'false' otherwise.
        return (this->from_node == e.from_node && this->to_node == e.to_node);
    }

    edge()
    {
        // This is the default constructor for the 'edge' class.
        // It initializes the 'from_node' and 'to_node' members to 0.
        from_node = 0;
        to_node = 0;
    }

    edge(int from_node, int to_node) : from_node(from_node), to_node(to_node){};
    // This is a constructor for the 'edge' class that takes two integer arguments, 'from_node' and 'to_node'.
    // It initializes the 'from_node' and 'to_node' members of the new object to the input values.

    edge(const edge &e) : from_node(e.from_node), to_node(e.to_node){};
    // This is the copy constructor for the 'edge' class.
    // It initializes the 'from_node' and 'to_node' members of the new object to the values of the input object 'e'.
};

const int NIL = -1;

enum COLOR
{
    WHITE,
    GRAY,
    BLACK
};

// represents a vertex in a graph
class Vertex
{
public:
    int d;
    int f;
    int parent;
    COLOR color;
};

// represents a graph
class graph
{

public:
    // members
    int nverteces_originally_connected; // number of vertices that have edges in graph upon construction
    int root_vertex;
    vector<vector<int>> edge;
    int time;
    Vertex *vertex;

    // constructors
    graph(const int nverteces) { edge.assign(nverteces, vector<int>()); }

    // operators
    graph operator=(const graph &gr);

    // member functions
    int ownsvertex(const int ind);
    void removeedge(const int from, const int to);
    void addedge(const int from, const int to);
    void print();
    // traverses a tree in depth first order
    void DFS_Visit(int u);
    int getNconnectedverteces();
};

graph graph::operator=(const graph &gr)
{

    nverteces_originally_connected = gr.nverteces_originally_connected;
    // This line assigns the value of the member variable 'nverteces_originally_connected' of the input object 'gr' to the same member variable in the current object.

    root_vertex = gr.root_vertex;
    // This line assigns the value of the member variable 'root_vertex' of the input object 'gr' to the same member variable in the current object.

    time = gr.time;
    // This line assigns the value of the member variable 'time' of the input object 'gr' to the same member variable in the current object.

    edge = gr.edge;
    // This line assigns the value of the member variable 'edge' of the input object 'gr' to the same member variable in the current object.

    return gr;
}

void graph::DFS_Visit(int u)
{
    vertex[u].color = GRAY;
    // This line sets the 'color' member of the 'vertex' object at index 'u' to the value 'GRAY'.
    // 'color' is a variable that is used to keep track of the state of each vertex during the DFS algorithm.
    // The value 'GRAY' indicates that the vertex has been discovered but not yet finished being processed.

    time++;
    // This line increments the value of the 'time' variable.
    // 'time' is likely used to keep track of the order in which vertices are discovered and finished being processed.

    vertex[u].d = time;
    // This line sets the 'd' member of the 'vertex' object at index 'u' to the current value of 'time'.
    // 'd' is likely used to store the "discovery time" of the vertex, or the time at which it was first encountered during the DFS.

    for (int i = 0; i < (int)edge[u].size(); i++)
    // This line starts a for loop that iterates through all the edges that connect to the current vertex 'u'.
    // 'edge[u]' is a vector of integers that represent the indices of the vertices that are connected to 'u'.
    // The loop variable 'i' is used as an index for the vector.

    {
        // This brace starts the body of the for loop.

        if (vertex[edge[u][i]].color == WHITE)
        // This line checks if the 'color' member of the vertex at index 'edge[u][i]' is 'WHITE', indicating that it has not yet been encountered during the DFS.

        {
            vertex[edge[u][i]].parent = u;
            // This line sets the 'parent' member of the 'vertex' object at index 'edge[u][i]' to the current vertex 'u'.
            // 'parent' is likely used to keep track of the predecessor vertex in the DFS tree.

            DFS_Visit(edge[u][i]);
            // This line recursively calls the 'DFS_Visit' function on the next vertex 'edge[u][i]' that has not yet been encountered.
        }
    }

    vertex[u].color = BLACK;
    // This line sets the 'color' member of the 'vertex' object at index 'u' to the value 'BLACK', indicating that the vertex has been finished being processed.

    time++;
    // This line increments the value of the 'time' variable.

    vertex[u].f = time;
    // This line sets the 'f' member of the 'vertex' object at index 'u' to the current value of 'time'.
    // 'f' is likely used to store the "finishing time" of the vertex, or the time at which it was finished being processed during the DFS.
}

// does this vertex have inbound or outbound connections? // there is at least one outbound connection
int graph::ownsvertex(const int ind)
{
if (edge[ind].size() > 0)
{
return 1;
}
// This line checks if the given vertex 'ind' has at least one outbound connection,
// by checking the size of the vector at index 'ind' in the 'edge' vector of vectors.
// If it has at least one outbound connection, the function returns 1.

for (int i = 0; i < (int)edge.size(); i++)
// This line starts a for loop that iterates through all the edges in the 'edge' vector of vectors.
// The loop variable 'i' is used as an index for the vector.

{
vector<int>::iterator it;
it = find(edge[i].begin(), edge[i].end(), ind);
    // This line uses the 'find' algorithm to search for the vertex 'ind' in the vector at index 'i' in the 'edge' vector of vectors.
    // 'it' is an iterator that points to the first occurrence of 'ind' in the vector, or 'edge[i].end()' if 'ind' is not found.

if (it != edge[i].end())
{
    return 1;
}
// This line checks if the iterator 'it' points to a valid position in the vector, indicating that 'ind' was found.
// If 'ind' was found, the function returns 1.
}

return 0;
// If the vertex 'ind' was not found in any of the vectors in the 'edge' vector of vectors,
// the function returns 0, indicating that the vertex is not present in the graph.
}

void graph::removeedge(const int from, const int to)
{

    vector<int>::iterator it;

    it = find(edge[from].begin(), edge[from].end(), to);

    edge[from].erase(it);
}

void graph::addedge(const int from, const int to)
{

    edge[from].insert(edge[from].begin(), to);
}

void graph::print()
{

    cout << "\n";
    for (int i = 0; i < (int)edge.size(); i++)
    {
        cout << i << "\t";

        for (int j = 0; j < (int)edge[i].size(); j++)
        {
            if (j != 0)
            {
                cout << ",";
            }
            cout << edge[i][j];
        }

        cout << "\n";
    }
    cout << "\n";
}

// gets number of connected vertices in the graph, if a vertex does not
// have an incoming or an outgoing edge
// then it is not counted towards the result
int graph::getNconnectedverteces()
{
    vector<int> tally(V, 0);

    // increase tallies of vertices that have an outgoing edge
    for (int i = 0; i < (int)edge.size(); i++)
    {
        if (edge[i].size() > 0)
        {
            tally[i]++;
        }
    }

    // increase tallies of vertices that have an incoming edge
    for (int i = 0; i < (int)edge.size(); i++)
    {
        for (int j = 0; j < (int)edge[i].size(); j++)
        {
            tally[edge[i][j]]++;
        }
    }

    int Nconnected = 0;
    for (int i = 0; i < (int)tally.size(); i++)
    {
        if (tally[i] > 0)
        {
            Nconnected++;
        }
    }

    return Nconnected;
}

graph G(V);

graph T(V);

graph L(V);

list<edge> F;

// number of spanning trees found in G
int nspanningtrees = 0;

void GROW()
{

    int TnSpannedVertices = T.getNconnectedverteces();

    if (TnSpannedVertices == V)
    {
        L = T;
        nspanningtrees++;
        cout << "---------spanning tree " << nspanningtrees << "----------\n";
        L.print();
        cout << "----------------------------------\n";

        if (L.vertex != 0)
        {
            delete[] L.vertex;
        }

        L.vertex = new Vertex[V];

        for (int i = 0; i < V; i++)
        {
            L.vertex[i].color = WHITE;
            L.vertex[i].parent = NIL;
            L.vertex[i].f = NIL;
            L.vertex[i].d = NIL;
        }

        L.time = 0;

        L.DFS_Visit(L.root_vertex);
    }
    else
    {
        list<edge> FF;

        int b = 1;
        int iterations = 0;
        do

        {

            int size = F.size();

            edge e = F.front();

            F.pop_front();

            // let e go from T to vertex v, v does not belong to T
            int v = e.to_node;

            // add e to T
            T.addedge(e.from_node, v);

            // Debug
            // T.print();

            // make a temp copy of F before changing it;
            list<edge> Fcopy(F);

            // push each edge (v, w) in G, where w does not belong to T, onto F
            // Note: this means each edge coming out of v
            for (int i = 0; i < (int)G.edge[v].size(); i++)
            {
                int w = G.edge[v][i];
                if (!T.ownsvertex(w))
                {
                    // got an edge
                    F.push_front(edge(v, w));
                }
            }

            // remove each edge (w,v) (that is, each edge that is incident to v) where w belongs to T, from F
            for (int w = 0; w < (int)G.edge.size(); w++)
            {
                if (T.ownsvertex(w))
                {
                    vector<int>::iterator it;
                    it = find(G.edge[w].begin(), G.edge[w].end(), v);
                    if (it != G.edge[w].end())
                    {
                        // an edge incident from w and incident to v has been found
                        F.remove(edge(w, v));
                    }
                }
            }

            GROW();

            // restore F
            F = Fcopy;

            // remove e from T and from G; add e to FF
            T.removeedge(e.from_node, e.to_node);

            G.removeedge(e.from_node, e.to_node);

            FF.push_front(e);

            // bridge test
            b = 1;

            // go over all edges in G coming into v
            for (int w = 0; w < (int)G.edge.size(); w++)
            {
                vector<int>::iterator it;
                it = find(G.edge[w].begin(), G.edge[w].end(), v);
                if (it != G.edge[w].end())
                {
                    // an edge incident to v is found

                    if (!(L.vertex[v].d < L.vertex[w].d && L.vertex[w].d < L.vertex[w].f && L.vertex[w].f < L.vertex[v].f))
                    {
                        // w is NOT a descendant of v
                        b = 0;
                        break; // for
                    }
                }
            }

        }

        // we want to stop when b is true; this for bridge test
        while (!b);

        // reconstruct G:
        // pop each edge e from FF, push e onto F, and add e to G

        while (!FF.empty())
        {
            edge e = FF.front();
            FF.pop_front();
            F.push_front(e);
            G.addedge(e.from_node, e.to_node);

        } // end while
    }     // end else
}

// S finds all spanning trees rooted at r in a directed graph G rooted at r
void S()
{

    G.root_vertex = 0;
    G.addedge(0, 1); // edge 1
    G.addedge(0, 2); // edge 2
    G.addedge(1, 3); // edge 3
    G.addedge(3, 2); // edge 4
    G.addedge(1, 2); // edge 5
    G.addedge(2, 1); // edge 6

    cout << "---------Example graph------------\n";
    G.print();
    cout << "----------------------------------\n";

    // discover all descendants of the root vertex in G
    // and initialize list F with them

    for (int i = 0; i < (int)G.edge[G.root_vertex].size(); i++)
    {

        F.push_front(edge(G.root_vertex, G.edge[G.root_vertex][i]));
    }

    T.root_vertex = 0;

    L.root_vertex = 0;

    nspanningtrees = 0;

    GROW();

    cout << nspanningtrees << " spanning trees found.\n\n";
}

int main()
{

    S();

    // user should hit Return to continue
    // useful during debugging out of Visual Studio.
    system("pause");
}