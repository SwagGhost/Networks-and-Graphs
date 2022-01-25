#include <iostream>
#include <vector>

using namespace std;

/* We will use a struct to identify the properties of each edge: */
struct Edge {
    /* We will use this property to determine whether an edge is contained in the Euler tour: */
    bool cycle;
    int u;
    int v;
};

/* We will use a struct to identify the properties of each vertex: */
struct Vertex {
    int vertex;
    int degree;
};

int main() {
    bool foundA, foundB = false;
    vector <Vertex> vertices;
    Vertex v;
    /* We will store the edges in a vector of type Edge: */
    vector <Edge> edges;
    Edge e;
    int A, B, N = 0;
    cin >> N;
    int M = N;
    bool simple = true;
    while (N > 0)  {
        cin >> A >> B;
        /* We set the property "cycle" of each edge (object e) to false, because it has not yet been contained in the Euler tour: */
        e.cycle = false;
        /* The edge connects vertex u = A and v = B: */
        e.u = A;
        e.v = B;
        /* We store the edge: */
        edges.push_back(e);
        /* If there are vertices stored in the vector with vertices, then we will update their degrees. */
        /* If a A == B, then we do not need a specific case, because this method will update the degree properly. */
        if (vertices.size() > 0) {
            for (int i = 0; i < vertices.size(); i++) {
                v = vertices[i];
                /* When we find vertex A in the vector, then we increment its degree: */
                if (v.vertex == A) {
                    foundA = true;
                    v.degree++;
                    vertices[i] = v;
                }
                /* When we find vertex A in the vector, then we increment its degree: */
                if (v.vertex == B) {
                    foundB = true;
                    v.degree++;
                    vertices[i] = v;
                }
                /* We stop if we have found both: */
                if (foundA == true && foundB == true) {
                    i = vertices.size();
                }
            }
            /* If A != B and we could not find them, then we they are new: */
            if (A != B) {
                if (foundA == false) {
                    v.vertex = A;
                    v.degree = 1;
                    vertices.push_back(v);
                }
                if (foundB == false) {
                    v.vertex = B;
                    v.degree = 1;
                    vertices.push_back(v);
                }
            }
        }
        /* This is for the first line of the input, where vertices.size() == 0 holds: */
        else {
            if (A == B) {
                v.vertex = A;
                v.degree = 2;
                vertices.push_back(v);
            }
            else {
                v.vertex = A;
                v.degree = 1;
                vertices.push_back(v);
                v.vertex = B;
                vertices.push_back(v);
            }
        }
        /* We will automically detect whether the graph is simple (to determine whether it is a tree): */
        if (A == B) {
            simple = false;
            if (foundA == false) {
                v.vertex = A;
                v.degree = 1;
                vertices.push_back(v);
            }
        }
        foundA = false;
        foundB = false;
        N--;
    }
    /* We use this boolean to determine whether we already know the output ("Yes" or "No") to stop when we know there is no Euler tour possible: */
    bool no = false;
    /* If we have a large number of vertices, then it is better to first check the degrees (they have to be even for an Euler tour): */
    if (vertices.size() > 49) {
        for (int j = 0; j < vertices.size(); j++) {
            v = vertices[j];
            /* We know that a vertex cannot be disconnected and it must have an even degree: */
            if (v.degree == 0 || v.degree % 2 != 0) {
                /* If it is not the case, we stop: */
                cout << "No";
                j = vertices.size();
                no = true;
            }
        }
        /* In case it is not connected: */
        if (no == false && vertices.size() == M + 1 && simple == true) {
            cout << "No";
            no = true;
        }
        /* In case it is connected, we know for sure we are going to find an Euler tour: */
        if (no == false && vertices.size() < M + 1 && simple == true) {
            cout << "Yes";
            no = true;
        }
    }
    
    if (no == false) {
        /* We start at vertex w, the last vertex from the input: */
        int w = B;
        bool construct_cycle = true;
        bool iterate_again = true;
        int x = edges.size();
        int cycle_found = edges.size();
        /* While it is true that we are constructing the Euler tour: */
        while (construct_cycle) {
            /* We will keep iterating to find the next edge: */
            while (iterate_again) {
                for (unsigned int i = 0; i < edges.size(); i++) {
                    e = edges[i];
                    /* If we find an edge incident to w and it is not yet contained in the Euler tour: */
                    if (e.u == w && e.cycle == false) {
                        /* We "traverse" it and the next current vertex will be the neighbour of w: */
                        w = e.v;
                        /* We make sure to mark that is contained in the Eyler tour now: */
                        e.cycle = true;
                        /* We update the edge: */
                        edges[i] = e;
                        /* We incement cycle_found to keep track of how many vertices we still have to add to the cycle to make it an Euler tour: */
                        cycle_found--;
                        /* We stop with this iteration: */
                        iterate_again = false;
                        i = edges.size();
                    }
                    /* Same goes for this case: */
                    if (e.v == w && e.cycle == false) {
                        w = e.u;
                        e.cycle = true;
                        edges[i] = e;
                        cycle_found--;
                        iterate_again = false;
                        i = edges.size();
                    }
                    /* We keep track of the iterations, after x iterations (where x is the intial value, edges.size(), we know for sure that we will not find a another edge for the Euler tour: */
                    x--;
                    if (x == 0 && e.cycle == true) {
                        construct_cycle = false;
                    }
                }
            }
            /* If all the edges have been contained in the Euler tour: */
            if (cycle_found == 0) {
                construct_cycle = false;
            }
            x = edges.size();
            iterate_again = true;
        }

        if (cycle_found == 0) {
            cout << "Yes";
        }
        else {
            cout << "No";
        }
    }
    
    return 0;
}

