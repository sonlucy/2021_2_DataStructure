#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H
#include <iostream>
#include <list>
#include <algorithm>
#include "Graph.h"
//#include "BFS_Dijkstra.h"
using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Vertex>::iterator VertexItor;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class DepthFirstSearch
{
protected:
	Graph& graph;
	Vertex start;
	bool done; // flag of search done
protected:
	void initialize();
	void dfsTraversal(Vertex& v, Vertex& target, VrtxList& path);
	virtual void traverseDiscovery(const Edge& e, const Vertex& from) { }
	virtual void traverseBack(const Edge& e, const Vertex& from) { }
	virtual void finishVisit(const Vertex& v) {}
	virtual bool isDone() const { return done; }
	// marking utilities
	void visit(Vertex& v);
	void visit(Edge& e);
	void unvisit(Vertex& v);
	void unvisit(Edge& e);
	bool isVisited(Vertex& v);
	bool isVisited(Edge& e);
	void setEdgeStatus(Edge& e, EdgeStatus es);
	EdgeStatus getEdgeStatus(Edge& e);
public:
	DepthFirstSearch(Graph& g);
	void findPath(Vertex& s, Vertex& t, VrtxList& path);
	Graph& getGraph() { return graph; }
	//void showConnectivity();
	void showConnectivity(ofstream &fout);

private:
	VrtxStatus* pVrtxStatus;
	EdgeStatus** ppEdgeStatus;
	int** ppConnectivity; // two dimensional array; table of distance[v1][v2]
}; // end of class DepthFirstSearch

DepthFirstSearch::DepthFirstSearch(Graph& g) :graph(g)
{
	int num_nodes = graph.getNumVertices();
	pVrtxStatus = new VrtxStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;

	ppEdgeStatus = new EdgeStatus * [num_nodes];
	for (int i = 0; i < num_nodes; i++)
		ppEdgeStatus[i] = new EdgeStatus[num_nodes];

	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;

	ppConnectivity = new int* [num_nodes];
	for (int i = 0; i < num_nodes; i++)
		ppConnectivity[i] = new int[num_nodes];

	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppConnectivity[i][j] = PLUS_INF;

	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	EdgeList edges;
	edges.clear();
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
	{
		vrtx_1 = *(*pe).getpVrtx_1(); vID_1 = vrtx_1.getID();
		vrtx_2 = *(*pe).getpVrtx_2(); vID_2 = vrtx_2.getID();
		ppConnectivity[vID_1][vID_2] = (*pe).getDistance();
	}
	for (int i = 0; i < num_nodes; i++)
		ppConnectivity[i][i] = 0; // distance of same node 
}

void DepthFirstSearch::initialize()
{
	int num_nodes = graph.getNumVertices();
	VrtxList verts;
	graph.vertices(verts);
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	done = false;
	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED;
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;
}

void DepthFirstSearch::showConnectivity(ofstream& fout)
{
	int num_nodes = graph.getNumVertices();
	int dist;
	Graph g = getGraph();
	Vertex* pVrtxArray = g.getpVrtxArray();
	fout << "Connectivity of graph: " << endl;
	fout << " |";
	for (int i = 0; i < num_nodes; i++)
		fout << setw(5) << pVrtxArray[i].getName();
	fout << endl;
	fout << "-----+";
	for (int i = 0; i < num_nodes; i++)
		fout << "-----";
	fout << endl;
	for (int i = 0; i < num_nodes; i++) {
		fout << " " << pVrtxArray[i].getName() << " | ";
		for (int j = 0; j < num_nodes; j++) {
			dist = ppConnectivity[i][j];
			if (dist == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << dist;
		} //end inner for
			fout << endl;
	} // end outer for
}


// 현재 단계에서의 탐색 기준 노드의 상태를 visited상태로 변환하며, 만약 현재 방문하고 있는 노드가 목적지 노드라면 done 플래그를 true로 설정하고 함수를 종료하고 반환. 
void DepthFirstSearch::dfsTraversal(Vertex& v, Vertex& target, VrtxList& path)  //함수인수로 dfs 기준노드, 목적지노드, 탐색경로를 저장할 정점 리스트
{
	//startVisit(v);
	visit(v);  //맨처음에 v를 visited로 설정.

	if (v == target)  //현재 방문하고 있는 노드가 목적지노드라면
	{
		done = true;   //done 플래그를 true로 설정한 후 반환
		return;
	}

	EdgeList incidentEdges;
	incidentEdges.clear();
	graph.incidentEdges(v, incidentEdges);
	EdgeItor pe = incidentEdges.begin();
	while (!isDone() && pe != incidentEdges.end())  //지금 현재 방문하고있는 v의 edge들에 대해??
	{
		Edge e = *pe++;
		EdgeStatus eStat = getEdgeStatus(e);
		if (eStat == EDGE_UN_VISITED)  //방문하지않은 초기화상태이면
		{
			visit(e);
			Vertex w = e.opposite(v);  //그 edge에 연결되어있는 vertex 중 v반대편에 있는 vertex를 w로 설정
			if (!isVisited(w))  //w가 아직 방문한 적이 없다면
			{
				//traverseDiscovery(e, v);
				path.push_back(w);
				setEdgeStatus(e, DISCOVERY);  //그 edge는 discovery 상태로.
				if (!isDone()) 
				{
					dfsTraversal(w, target, path);  //recursive call. w부터 시작해서 다시 찾아가게끔.
		
					if (!isDone()) {
						//traverseBack(e, v);
						// check whether node w is already in path as a cycle
						Vertex last_pushed = path.back(); // for debugging
						path.pop_back();
					}
				}
			}
			else // w is VISITED
			{
				setEdgeStatus(e, BACK);  //그 edge는 back상태로. (w가 이미 이전에 방문한적 있었다)
			}
		} // end if (eStat == EDGE_UN_VISITED)
	} // end of while - processing of all incedent edges
}
void DepthFirstSearch::findPath(Vertex& start, Vertex& target, VrtxList& path)
{
	initialize();
	path.clear();

	path.push_back(start);
	dfsTraversal(start, target, path);

}

void DepthFirstSearch::visit(Vertex& v)
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices();
	int vID = v.getID();
	if (graph.isValidVrtxID(vID))
	{
		pVrtxStatus[vID] = VISITED;
	}
}
void DepthFirstSearch::visit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))
	{
		ppEdgeStatus[vID_1][vID_2] = EDGE_VISITED;
	}
}

void DepthFirstSearch::unvisit(Vertex& v)
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices();
	int vID = v.getID();
	if (graph.isValidVrtxID(vID))
	{
		pVrtxStatus[vID] = UN_VISITED;
	}
}
void DepthFirstSearch::unvisit(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))
	{
		ppEdgeStatus[vID_1][vID_2] = EDGE_UN_VISITED;
	}
}

bool DepthFirstSearch::isVisited(Vertex& v)
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices();
	int vID = v.getID();
	if (graph.isValidVrtxID(vID))
	{
		return (pVrtxStatus[vID] == VISITED);
	}
}
bool DepthFirstSearch::isVisited(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	EdgeStatus eStat;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		if ((eStat == EDGE_VISITED) || (eStat == DISCOVERY) || (eStat == BACK))
			return true;
		else
			return false;
	}
	return false;
}

void DepthFirstSearch::setEdgeStatus(Edge& e, EdgeStatus es)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))
	{
		ppEdgeStatus[vID_1][vID_2] = es;
	}
}
EdgeStatus DepthFirstSearch::getEdgeStatus(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	EdgeStatus eStat;
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		return eStat;
	}
	else {
		cout << "Edge (" << e << ") was not found from AdjacencyList" << endl;
		return EDGE_NOT_FOUND;
	}
}





#endif
