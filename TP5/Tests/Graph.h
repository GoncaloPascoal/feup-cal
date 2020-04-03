/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    
	void dijkstraShortestPath(const T &s);      
	void bellmanFordShortestPath(const T &s);   
	vector<T> getPathTo(const T &dest) const;   

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    queue<Vertex<T>*> queue;

    for (Vertex<T>* vertex : vertexSet) {
        vertex->path = NULL;

        if (vertex->info == orig) {
            vertex->dist = 0;
            queue.push(vertex);
        }
        else {
            vertex->dist = numeric_limits<double>::max();
        }
    }

    while (!queue.empty()) {
        Vertex<T>* vert = queue.front(); queue.pop();

        for (const Edge<T>& edge : vert->adj) {
            if (edge.dest->dist == numeric_limits<double>::max()) {
                queue.push(edge.dest);

                edge.dest->dist = vert->dist + 1;
                edge.dest->path = vert;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	MutablePriorityQueue<Vertex<T>> queue;

	for (Vertex<T>* vertex : vertexSet) {
	    vertex->path = NULL;

	    if (vertex->info == origin) {
	        vertex->dist = 0;
	        vertex->queueIndex = 0;
	        queue.insert(vertex);
	    }
	    else {
	        vertex->dist = numeric_limits<double>::max();
	    }
	}

    while (!queue.empty()) {
        Vertex<T>* vertex = queue.extractMin();

        for (const Edge<T>& edge : vertex->adj) {
            bool notInQueue = edge.dest->dist == numeric_limits<double>::max();

            if (edge.dest->dist > vertex->dist + edge.weight) {
                edge.dest->dist = vertex->dist + edge.weight;
                edge.dest->path = vertex;

                if (notInQueue) {
                    edge.dest->queueIndex = edge.dest->dist;
                    queue.insert(edge.dest);
                }
                else {
                    queue.decreaseKey(edge.dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	for (Vertex<T>* vertex : vertexSet) {
		vertex->path = NULL;
		
		if (vertex->info == orig) {
			vertex->dist = 0;
		}
		else {
			vertex->dist = numeric_limits<double>::max();
		}
	}

	for (size_t i = 1; i < vertexSet.size(); ++i) { // |V| - 1 iterations
		for (Vertex<T>* vertex : vertexSet) {
			for (Edge<T>& edge : vertex->adj) {
				if (edge.dest->dist > vertex->dist + edge.weight) {
					edge.dest->dist = vertex->dist + edge.weight;
					edge.dest->path = vertex;
				}
			}
		}
	}
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;

	const Vertex<T>* destPtr = findVertex(dest);
	const Vertex<T>* pathPtr = destPtr->path;

	res.push_back(destPtr->info);

	while (pathPtr != NULL) {
	    res.push_back(pathPtr->info);
	    pathPtr = pathPtr->path;
	}

	std::reverse(res.begin(), res.end());

	return res;
}



/**************** All Pairs Shortest Path  ***************/


static vector<vector<double>> distances;
static vector<vector<int>> previous;

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	distances = vector<vector<double>>(vertexSet.size(), vector<double>(vertexSet.size(), numeric_limits<double>::max()));
	previous = vector<vector<int>>(vertexSet.size(), vector<int>(vertexSet.size(), -1));

	for (size_t i = 0; i < vertexSet.size(); ++i) {
		distances[i][i] = 0.0;

		for (const Edge<T>& edge : vertexSet[i]->adj) {
			auto it = find(vertexSet.begin(), vertexSet.end(), edge.dest);

			if (it != vertexSet.end()) {
				distances[i][distance(vertexSet.begin(), it)] = edge.weight;
				previous[i][distance(vertexSet.begin(), it)] = i;
			}
		}
	}

	for (size_t k = 0; k < vertexSet.size(); ++k) {
		for (size_t i = 0; i < vertexSet.size(); ++i) {
			for (size_t j = 0; j < vertexSet.size(); ++j) {
				if (distances[i][j] > distances[i][k] + distances[k][j]) {
					distances[i][j] = distances[i][k] + distances[k][j];
					previous[i][j] = previous[k][j];
				}
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	
	int origIdx = -1, destIdx = -1;

	for (size_t i = 0; i < vertexSet.size(); ++i) {
		if (vertexSet[i]->info == orig) {
			origIdx = i;
		}
		else if (vertexSet[i]->info == dest) {
			destIdx = i;
		}
	}

	if (origIdx != -1 && destIdx != -1) {
		res.push_back(dest);

		int prevIdx = previous[origIdx][destIdx];

		while (prevIdx >= 0) {
			res.push_back(vertexSet[prevIdx]->info);
			prevIdx = previous[origIdx][prevIdx];
		}
	}

	reverse(res.begin(), res.end());

	return res;
}


#endif /* GRAPH_H_ */
