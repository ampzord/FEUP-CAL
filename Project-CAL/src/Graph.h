/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>

#include "matcher.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

const double SPEED_TRUCK = 50;
const double CLIENT_TIME = 1.0 / 12.0;

/**
 * \brief Struct to hold a Networks sorted Market set.
 */
template<class T>
struct SortSet {

	SortSet(int & supermarket, Graph<T>* graph) {
		this->supermarket = supermarket;
		this->graph = graph;
	}
	bool operator ()(int i, int j) {
		return graph->W[supermarket][i] < graph->W[supermarket][j];
	}

	int supermarket;
	Graph<T>* graph;
};

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

/** \brief Standard Class to hold Network's Vertexs.*/
template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
	bool processing;
	int indegree;
	double dist;
	string type;
	int clients;
	vector<int> clientsPossible;
	unsigned long long id;
	double time;
	double weight;
	bool served;
	string name;

public:

	Vertex(T in, string typ, unsigned long long nodeId, string nam);
	friend class Graph<T> ;

	void addEdge(Vertex<T> *dest, double w, string nam);
	bool removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	bool operator<(const Vertex<T> vertex);

	Vertex* path;
};

/** \brief Struct to hold Distance information for the Vertexes. */
template<class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}

template<class T>
bool Vertex<T>::operator<(const Vertex<T> vertex) {
	return clients > vertex.clients;
}

//atualizado pelo exercício 5
template<class T>
Vertex<T>::Vertex(T in, string typ, unsigned long long nodeId, string nam) :
		info(in), visited(false), processing(false), indegree(0), dist(0), type(
				typ), clients(0), id(nodeId), served(false), name("") {
	path = NULL;
	time = 0;
	weight = 0;
	if (typ == "User") {
		time = CLIENT_TIME;
		weight = rand() % 10 + 1;
	}

	if (typ == "Market") {
		weight = rand() % 20 + 11;
		name = nam;
	}
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, string nam) {
	Edge<T> edgeD(dest, w, nam);
	adj.push_back(edgeD);
}

//--
template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template<class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

/** \brief Standard Class to hold Netork's Edges.*/
template<class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	double speed;
	double time;
	string name;
	string district;
public:
	Edge(Vertex<T> *d, double w, string nam);
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, string nam) :
		dest(d), weight(w), speed(SPEED_TRUCK), name(nam) {
	time = weight / speed;
}

/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

/** \brief Standard Class to hold the Network's Graph.*/
template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

	friend struct SortSet<T> ;

public:
	bool addVertex(const T &in, string type, unsigned long long nodeId, string nam);
	bool addEdge(const T &sourc, const T &dest, double w, string nam);
	bool addEdge(const int src, const int dst, double w, string nam);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	unsigned long long getVertexId(const int index) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	map<int, vector<int> > sortPaths(bool normal);
	vector<pair<int, vector<int> > > sortPathsSingle(bool normal);
	vector<int> getPossiblePath(vector<int> clients);
	vector<int> getPossiblePath(int supermarket, vector<int> clients);
	Edge<T> getEdge(int src, int dst);
	double pathTime(vector<int> clients, double & weight, int noClients);
	vector<int> getFullPath(int suprmarket, vector<int> nodes);
	vector<int> getfloydWarshallPathInt(int origin, int destination);
	void getfloydWarshallPathIntAux(int index1, int index2, vector<int> & res);
	void clearClientsServed(vector<int> clients);
	void removeMostDistantClient(int supermarket, vector<int> & clients,
			typename vector<pair<Vertex<T>*, int> >::iterator it,
			typename vector<pair<Vertex<T>*, int> >::iterator ite);
	int removeMostDistantClient2(int supermarket, vector<int> & clients);
	bool rearrangeMap(vector<pair<Vertex<T>*, int> > supermarkets,
			typename vector<pair<Vertex<T>*, int> >::iterator it);
	bool firstShortDist(int supermarket1, vector<int>::iterator it,
			vector<int>::iterator ite, int supermarket2,
			vector<int>::iterator it2, vector<int>::iterator ite2);
	void clearServed(vector<int> nodes);
	void cutNodes(GraphViewer* gv);
	bool exactSearch(vector<string> roads, string market);
	void approximateSearch(vector<string> roads, string market);
};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template<class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template<class T>
bool Graph<T>::addVertex(const T &in, string type, unsigned long long nodeId, string nam) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in, type, nodeId, nam);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj = v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, string nam) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vD->indegree++;
	vS->addEdge(vD, w, nam);

	return true;
}

template<class T>
bool Graph<T>::addEdge(const int src, const int dst, double w, string nam) {

	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->id == src) {
			vS = *it;
			found++;
		}
		if ((*it)->id == dst) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vD->indegree++;
	vS->addEdge(vD, w, nam);

	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template<class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			//cout << "ok ";
			dfs(it->dest, res);
		}
}

template<class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop();
		l++;
		int nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T>
unsigned long long Graph<T>::getVertexId(const int index) const {

	if (index >= vertexSet.size() || index < 0) {
		return -1;
	}

	return vertexSet[index]->id;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}

template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector<Vertex<T>*> buffer;
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->indegree == 0)
			buffer.push_back(vertexSet[i]);
	}
	return buffer;
}

template<class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true)
			numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if (getNumCycles() > 0) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!q.empty()) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if (v->adj[i].dest->indegree == 0)
				q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexSet.size()) {
		while (!res.empty())
			res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) {

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while (v->path != NULL && v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if (v->path != NULL)
		buffer.push_front(v->path->info);

	vector<T> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest) {

	int originIndex = -1, destinationIndex = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == origin)
			originIndex = i;
		if (vertexSet[i]->info == dest)
			destinationIndex = i;

		if (originIndex != -1 && destinationIndex != -1)
			break;
	}

	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1) {
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);

	return res;
}

template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2,
		vector<T> & res) {
	if (P[index1][index2] != -1) {
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2], index2, res);
	}
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue<Vertex<T>*> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (w->dist == INT_INFINITY) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue<Vertex<T>*> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector<Vertex<T>*> pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());

	while (!pq.empty()) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex) {
	if (vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for (unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++) {
		if (vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

/*void printSquareArray(int ** arr, unsigned int size)
 {
 for(unsigned int k = 0; k < size; k++)
 {
 if(k == 0)
 {
 cout <<  "   ";
 for(unsigned int i = 0; i < size; i++)
 cout <<  " " << i+1 << " ";
 cout << endl;
 }

 for(unsigned int i = 0; i < size; i++)
 {
 if(i == 0)
 cout <<  " " << k+1 << " ";

 if(arr[k][i] == INT_INFINITY)
 cout << " - ";
 else
 cout <<  " " << arr[k][i] << " ";
 }

 cout << endl;
 }
 }*/

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int *[vertexSet.size()];
	P = new int *[vertexSet.size()];
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for (unsigned int j = 0; j < vertexSet.size(); j++) {
			W[i][j] = edgeCost(i, j);
			P[i][j] = -1;
		}
	}

	for (unsigned int k = 0; k < vertexSet.size(); k++)
		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int j = 0; j < vertexSet.size(); j++) {
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if (W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min(W[i][j], W[i][k] + W[k][j]);
				if (val != W[i][j]) {
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}

template<class T>
bool sortFunc(pair<Vertex<T>*, int> a, pair<Vertex<T>*, int> b) {
	return *(a.first) < *(b.first);
}

template<class T>
vector<pair<int, vector<int> > > Graph<T>::sortPathsSingle(bool normal) {

	vector<pair<Vertex<T>*, int> > supermarkets;
	map<Vertex<T>*, int> clients;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->type == "Market") {
			supermarkets.push_back(pair<Vertex<T>*, int>(vertexSet[i], i));
		} else if (vertexSet[i]->type == "User") {
			clients.insert(
					typename std::map<Vertex<T>*, int>::value_type(vertexSet[i],
							i));
		}
	}

	map<int, vector<int> > clientMarkets;

	for (typename map<Vertex<T>*, int>::iterator it = clients.begin();
			it != clients.end(); it++) {
		vector<int> tmp;

		int i = it->second;

		for (typename vector<pair<Vertex<T>*, int> >::iterator it2 =
				supermarkets.begin(); it2 != supermarkets.end(); it2++) {
			int j = it2->second;

			if (W[j][i] != INT_INFINITY && W[j][i] != INT_INFINITY) {
				it2->first->clients++;
				it2->first->clientsPossible.push_back(i);
				tmp.push_back(it2->second);
			}
		}

		if (tmp.size() != 0) {
			clientMarkets.insert(
					typename std::map<int, vector<int> >::value_type(i, tmp));
		}
	}

	vector<pair<int, vector<int> > > res;

	if (supermarkets.size() == 0) {
		return res;
	}

	bool finish = false;

	sort(supermarkets.begin(), supermarkets.end(), sortFunc<T>);

	typename vector<pair<Vertex<T>*, int> >::iterator it = supermarkets.begin();

	while (it->first->clientsPossible.size() > 0 && !finish) {
		double time = 24;

		double weight = it->first->weight + 1;

		vector<int> removed;

		while ((time >= 24 || weight > it->first->weight)
				&& it->first->clientsPossible.size() > 0) {
			vector<int> tmp = it->first->clientsPossible;

			vector<int> full;

			if (normal) {
				vector<int> asd = getPossiblePath(it->first->clientsPossible);

				full = getFullPath(it->second, asd);
			} else {
				full = getPossiblePath(it->second, it->first->clientsPossible);
			}

			time = pathTime(full, weight, it->first->clientsPossible.size());

			if ((time >= 24 || weight > it->first->weight)
					&& it->first->clientsPossible.size() > 0) {
				removed.push_back(
						removeMostDistantClient2(it->second,
								it->first->clientsPossible));
			} else {
				res.push_back(pair<int, vector<int> >(it->second, full));
			}
		}

		if (it->first->clientsPossible.size() == 0) {
			finish = true;
		}

		clearClientsServed(it->first->clientsPossible);

		for (unsigned int i = 0; i < removed.size(); i++) {
			it->first->clientsPossible.push_back(removed[i]);
		}
	}

	return res;
}

template<class T>
map<int, vector<int> > Graph<T>::sortPaths(bool normal) {

	vector<pair<Vertex<T>*, int> > supermarkets;
	map<Vertex<T>*, int> clients;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->type == "Market") {
			supermarkets.push_back(pair<Vertex<T>*, int>(vertexSet[i], i));
		} else if (vertexSet[i]->type == "User") {
			clients.insert(
					typename std::map<Vertex<T>*, int>::value_type(vertexSet[i],
							i));
		}
	}

	map<int, vector<int> > clientMarkets;

	for (typename map<Vertex<T>*, int>::iterator it = clients.begin();
			it != clients.end(); it++) {
		vector<int> tmp;

		int i = it->second;

		for (typename vector<pair<Vertex<T>*, int> >::iterator it2 =
				supermarkets.begin(); it2 != supermarkets.end(); it2++) {
			int j = it2->second;

			if (W[j][i] != INT_INFINITY && W[j][i] != INT_INFINITY) {
				it2->first->clients++;
				it2->first->clientsPossible.push_back(i);
				tmp.push_back(it2->second);
			}
		}

		if (tmp.size() != 0) {
			clientMarkets.insert(
					typename std::map<int, vector<int> >::value_type(i, tmp));
		}
	}

	sort(supermarkets.begin(), supermarkets.end(), sortFunc<T>);

	map<int, vector<int> > res;

	for (typename vector<pair<Vertex<T>*, int> >::iterator it =
			supermarkets.begin(); it != supermarkets.end(); it++) {
		bool tried = false;

		double time = 24;

		double weight = it->first->weight + 1;

		while ((time >= 24 || weight > it->first->weight)
				&& it->first->clientsPossible.size() > 0) {
			vector<int> tmp = it->first->clientsPossible;

			vector<int> full;

			if (normal) {
				vector<int> asd = getPossiblePath(it->first->clientsPossible);

				full = getFullPath(it->second, asd);
			} else {
				full = getPossiblePath(it->second, it->first->clientsPossible);
			}

			time = pathTime(full, weight, it->first->clientsPossible.size());

			if ((time >= 24 || weight > it->first->weight)
					&& it->first->clientsPossible.size() > 0) {
				clearServed(full);
				if (tried) {
					typename vector<pair<Vertex<T>*, int> >::iterator it2 = it;
					it2++;
					removeMostDistantClient(it->second,
							it->first->clientsPossible, it2,
							supermarkets.end());
				} else {
					tried = rearrangeMap(supermarkets, it);
				}
			} else {
				res.insert(
						typename std::map<int, vector<int> >::value_type(
								it->second, full));
			}
		}

		clearClientsServed(it->first->clientsPossible);
	}

	return res;
}

template<class T>
bool Graph<T>::rearrangeMap(vector<pair<Vertex<T>*, int> > supermarkets,
		typename vector<pair<Vertex<T>*, int> >::iterator it) {
	typename vector<pair<Vertex<T>*, int> >::iterator it2 = it++;

	typename vector<pair<Vertex<T>*, int> >::iterator ite = supermarkets.end();

	if (it == ite) {
		return false;
	}

	vector<int> clients;
	vector<int> clients2;

	vector<int> client1;
	vector<int> client2;

	int min1 = INT_INFINITY;
	int min2 = INT_INFINITY;

	int count = 0;

	for (unsigned int i = 0; i < it2->first->clientsPossible.size(); i++) {
		clients.push_back(it2->first->clientsPossible[i]);
	}

	sort(clients.begin(), clients.end(), SortSet<T>(it2->second, this));

	for (unsigned int i = 0; i < it->first->clientsPossible.size(); i++) {
		clients2.push_back(it->first->clientsPossible[i]);
	}

	sort(clients2.begin(), clients2.end(), SortSet<T>(it->second, this));

	int size = clients.size() + clients2.size();

	while (count < size) {
		if (clients.size() == 0) {
			for (unsigned int i = 0; i < clients2.size(); i++) {
				client2.push_back(clients2[i]);
			}

			break;
		}

		if (clients2.size() == 0) {
			for (unsigned int i = 0; i < clients.size(); i++) {
				client1.push_back(clients[i]);
			}

			break;
		}

		min1 = W[it2->second][*(clients.begin())];
		min2 = W[it->second][*(clients2.begin())];

		if (min1 < min2) {
			client1.push_back(*clients.begin());
			clients2.erase(
					find(clients2.begin(), clients2.end(), *clients.begin()));
			clients.erase(clients.begin());
		} else if (min2 < min1) {
			client2.push_back(*clients2.begin());
			clients.erase(
					find(clients.begin(), clients.end(), *clients2.begin()));
			clients2.erase(clients2.begin());
		} else {
			vector<int>::iterator start = clients.begin();
			vector<int>::iterator start2 = clients2.begin();
			start++;
			start2++;
			if (firstShortDist(it2->second, start, clients.end(), it->second,
					start2, clients2.end())) {
				client1.push_back(*clients.begin());
				clients2.erase(
						find(clients2.begin(), clients2.end(),
								*clients.begin()));
				clients.erase(clients.begin());
			} else {
				client2.push_back(*clients2.begin());
				clients.erase(
						find(clients.begin(), clients.end(),
								*clients2.begin()));
				clients2.erase(clients2.begin());
			}
		}

		count++;
	}

	it2->first->clientsPossible.empty();
	it->first->clientsPossible.empty();

	it2->first->clientsPossible = client1;
	it->first->clientsPossible = client2;

	it = it2;

	return true;
}

template<class T>
bool Graph<T>::firstShortDist(int supermarket1, vector<int>::iterator it,
		vector<int>::iterator ite, int supermarket2, vector<int>::iterator it2,
		vector<int>::iterator ite2) {
	if (it == ite) {
		return false;
	}

	if (it2 == ite2) {
		return true;
	}

	int min1 = W[supermarket1][*it];
	int min2 = W[supermarket2][*it2];

	if (min1 > min2) {
		return true;
	} else if (min1 < min2) {
		return false;
	} else {
		firstShortDist(supermarket1, ++it, ite, supermarket2, ++it2, ite2);
	}
}

template<class T>
void Graph<T>::removeMostDistantClient(int supermarket, vector<int> & clients,
		typename vector<pair<Vertex<T>*, int> >::iterator it,
		typename vector<pair<Vertex<T>*, int> >::iterator ite) {
	int maximum = 0;

	int index = -1;

	for (unsigned int i = 0; i < clients.size(); i++) {
		if (W[supermarket][clients[i]] != INT_INFINITY
				&& W[supermarket][clients[i]] > maximum) {
			maximum = W[supermarket][clients[i]];
			index = i;
		}
	}

	if (index == -1) {
		return;
	}

	if (it != ite) {
		if (W[it->second][*(clients.begin() + index)] != INT_INFINITY) {
			it->first->clientsPossible.push_back(*(clients.begin() + index));
		}
	}

	clients.erase(clients.begin() + index);
}

template<class T>
int Graph<T>::removeMostDistantClient2(int supermarket, vector<int> & clients) {
	int maximum = 0;

	int index = -1;

	for (unsigned int i = 0; i < clients.size(); i++) {
		vertexSet[clients[i]]->served = false;
		if (W[supermarket][clients[i]] != INT_INFINITY
				&& W[supermarket][clients[i]] > maximum) {
			maximum = W[supermarket][clients[i]];
			index = i;
		}
	}

	if (index == -1) {
		return -1;
	}

	int res = *(clients.begin() + index);

	clients.erase(clients.begin() + index);

	return res;
}

template<class T>
vector<int> Graph<T>::getPossiblePath(vector<int> clients) {

	int maximum = 0;
	int src = -1;
	int dst = -1;

	vector<int> res;

	if (clients.size() == 1) {
		res.push_back(clients[0]);
		return res;
	}

	for (unsigned int i = 0; i < clients.size(); i++) {
		int x = clients[i];

		for (unsigned int j = 0; j < clients.size(); j++) {
			int y = clients[j];

			if (W[x][y] > maximum) {
				maximum = W[x][y];
				src = i;
				dst = j;
			} else if (W[y][x] > maximum) {
				maximum = W[y][x];
				src = j;
				dst = i;
			}
		}
	}

	if (src == -1 || dst == -1) {
		return res;
	}

	res.push_back(clients[src]);

	clients.erase(clients.begin() + src);
	clients.erase(clients.begin() + dst - 1);

	vector<int> tmp = getPossiblePath(clients);

	for (unsigned int i = 0; i < tmp.size(); i++) {
		res.push_back(tmp[i]);
	}

	res.push_back(clients[dst]);

	return res;
}

template<class T>
vector<int> Graph<T>::getPossiblePath(int supermarket, vector<int> clients) {

	int minimum = INT_MAX;
	int dst = -1;
	int source = -1;

	for (unsigned int i = 0; i < clients.size(); i++) {
		if (W[supermarket][clients[i]] < minimum) {
			minimum = W[supermarket][clients[i]];
			dst = i;
			source = clients[i];
		}
	}

	vector<int> res;

	minimum = INT_MAX;

	while (clients.size() > 1) {
		res.push_back(source);

		for (unsigned int i = 0; i < clients.size(); i++) {
			if (W[source][clients[i]] > 0 && W[source][clients[i]] < minimum) {
				minimum = W[dst][clients[i]];
				dst = i;
				source = clients[i];
			}
		}

		minimum = INT_MAX;

		clients.erase(clients.begin() + dst);
	}

	res.push_back(*clients.begin());

	return getFullPath(supermarket, res);
}

template<class T>
double Graph<T>::pathTime(vector<int> nodes, double & weight, int noClients) {

	double time = 0;

	weight = 0;

	int noC = 0;

	for (unsigned int i = 1; i < nodes.size(); i++) {
		if (noC >= noClients) {
			break;
		}

		Edge<T> adj = getEdge(nodes[i - 1], nodes[i]);
		time += vertexSet[nodes[i - 1]]->time + adj.time;
		if (vertexSet[nodes[i]]->type == "User"
				&& !(vertexSet[nodes[i]]->served)) {
			noC++;
			weight += vertexSet[nodes[i]]->weight;
			vertexSet[nodes[i]]->served = true;
		}
	}

	return time;
}

template<class T>
void Graph<T>::clearServed(vector<int> nodes) {

	for (unsigned int i = 0; i < nodes.size(); i++) {
		vertexSet[nodes[i]]->served = false;
	}
}

template<class T>
Edge<T> Graph<T>::getEdge(int src, int dst) {
	for (unsigned int i = 0; i < vertexSet[src]->adj.size(); i++) {
		if (vertexSet[src]->adj[i].dest->id == vertexSet[dst]->id) {
			return vertexSet[src]->adj[i];
		}
	}

	return Edge<T>(NULL, 0, "");
}

template<class T>
vector<int> Graph<T>::getFullPath(int supermarket, vector<int> nodes) {
	vector<int> res;

	vector<int> temp = getfloydWarshallPathInt(supermarket, nodes[0]);

	for (unsigned int i = 0; i < temp.size(); i++) {
		res.push_back(temp[i]);
	}

	for (unsigned int i = 1; i < nodes.size(); i++) {
		vector<int> temp2 = getfloydWarshallPathInt(nodes[i - 1], nodes[i]);

		for (unsigned int i = 1; i < temp2.size(); i++) {
			res.push_back(temp2[i]);
		}
	}

	vector<int> temp3 = getfloydWarshallPathInt(nodes[nodes.size() - 1],
			supermarket);

	for (unsigned int i = 1; i < temp3.size(); i++) {
		res.push_back(temp3[i]);
	}

	return res;
}

template<class T>
vector<int> Graph<T>::getfloydWarshallPathInt(int origin, int destination) {

	vector<int> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[origin][destination] == INT_INFINITY)
		return res;

	res.push_back(origin);

	//se houver pontos intermedios...
	if (P[origin][destination] != -1) {
		int intermedIndex = P[origin][destination];

		getfloydWarshallPathIntAux(origin, intermedIndex, res);

		res.push_back(intermedIndex);

		getfloydWarshallPathIntAux(intermedIndex, destination, res);
	}

	res.push_back(destination);

	return res;
}

template<class T>
void Graph<T>::getfloydWarshallPathIntAux(int index1, int index2,
		vector<int> & res) {
	if (P[index1][index2] != -1) {
		getfloydWarshallPathIntAux(index1, P[index1][index2], res);

		res.push_back(P[index1][index2]);

		getfloydWarshallPathIntAux(P[index1][index2], index2, res);
	}
}

template<class T>
void Graph<T>::clearClientsServed(vector<int> clients) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		for (unsigned int i = 0; i < (*it)->clientsPossible.size(); i++) {
			for (unsigned int j = 0; j < clients.size(); j++) {
				if ((*it)->clientsPossible[i] == clients[j]) {
					(*it)->clientsPossible.erase(
							(*it)->clientsPossible.begin() + i);
					i--;
				}
			}
		}
	}
}

template<class T>
void Graph<T>::cutNodes(GraphViewer* gv) {
	bool changed = true;
	while (changed) {
		changed = false;
		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			//cout << vertexSet[i]->indegree << endl;
			//cout << vertexSet[i]->adj.size() << endl;
			if (vertexSet[i]->indegree == 2 && vertexSet[i]->adj.size() == 2) {
				//cout << "D1" << endl;
				gv->removeNode(vertexSet[i]->id);
				addEdge(vertexSet[i]->adj[0].dest->info,
						vertexSet[i]->adj[1].dest->info,
						vertexSet[i]->adj[0].weight
								+ vertexSet[i]->adj[1].weight);
				removeVertex(vertexSet[i]->info);
				i--;
				changed = true;
				continue;
			}
		}

		cout << "ENDL" << endl;
	}
}

template<class T>
bool Graph<T>::exactSearch(vector<string> roads, string market) {

	if(roads.size() == 1)
	{
		return false;
	}

	typename vector<Vertex<T>*>::iterator its = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();

	map<Vertex<T>*, int> m;

	for (; its != ite; its++) {
		for(int i = 0; i < (*its)->adj.size(); i++)
		{
			for(int j = 0; j < roads.size(); j++)
			{
				if(kmp((*its)->adj[i].name, roads[j]))
				{
					m.insert(typename std::map<Vertex<T>*, int>::value_type(*its,i));
				}
			}
		}
	}

	Vertex<T>* tmp = NULL;

	if(m.size() == 0)
	{
		return false;
	}

	typename map<Vertex<T>*, int>::iterator it = m.begin();
	typename map<Vertex<T>*, int>::iterator it2 = m.begin();

	it2++;

	while(it2 != m.end()) {

		if(it->first->adj[it->second].name == it2->first->adj[it2->second].name)
		{
			it++;
			it2++;
			continue;
		}

		if(tmp == NULL)
		{
			if(it->first->id == it2->first->id)
			{
				tmp = it->first;
			}

			if(it->first->id == it2->first->adj[it2->second].dest->id)
			{
				tmp = it->first;
			}

			if(it2->first->id == it->first->adj[it->second].dest->id)
			{
				tmp = it2->first;
			}

			if(it->first->adj[it->second].dest->id == it2->first->adj[it2->second].dest->id)
			{
				tmp = it->first->adj[it->second].dest;
			}

			if(tmp == NULL)
			{
				return false;
			}
		}
		else
		{
			if(it->first->id == it2->first->id && it->first->id == tmp->id)
			{
				tmp = it->first;
				it++;
				it2++;
				continue;
			}

			if(it->first->id == it2->first->adj[it2->second].dest->id && it->first->id == tmp->id)
			{
				tmp = it->first;
				it++;
				it2++;
				continue;
			}

			if(it2->first->id == it->first->adj[it->second].dest->id && it2->first->id == tmp->id)
			{
				tmp = it2->first;
				it++;
				it2++;
				continue;
			}

			if(it->first->adj[it->second].dest->id == it2->first->adj[it2->second].dest->id && it->first->adj[it->second].dest->id == tmp->id)
			{
				tmp = it->first->adj[it->second].dest;
				it++;
				it2++;
				continue;
			}

			return false;
		}

		it++;
		it2++;
	}

	if(tmp != NULL && tmp->type == "Market" && kmp(tmp->name, market))
	{
		return true;
	}

	return false;
}

template<class T>
void Graph<T>::approximateSearch(vector<string> roads, string market) {


}

#endif /* GRAPH_H_ */
