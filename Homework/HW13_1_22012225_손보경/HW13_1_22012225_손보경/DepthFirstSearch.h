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

	void setEdgeStatus(Edge& e, EdgeStatus es);  //지정된 간선에 지정된 상태를 설정하는 기능
	EdgeStatus getEdgeStatus(Edge& e);  //지정된 간선의 상태를 읽어 반환해주는 함수

public:
	DepthFirstSearch(Graph& g);
	void findPath(Vertex& s, Vertex& t, VrtxList& path);
	Graph& getGraph() { return graph; }
	void showConnectivity();
	void showConnectivity(ofstream& fout);

private:
	VrtxStatus* pVrtxStatus;
	EdgeStatus** ppEdgeStatus;
	int** ppConnectivity; // two dimensional array; table of distance[v1][v2]
}; // end of class DepthFirstSearch

DepthFirstSearch::DepthFirstSearch(Graph& g) :graph(g)  //그래프 객체 전달
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
		ppConnectivity[i] = new int[num_nodes];    //2차원 동적 배열 (행렬형태)로 

	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppConnectivity[i][j] = PLUS_INF;  //일단 모든 노드 간의 distance를 무한대로 초기화

	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	EdgeList edges;
	edges.clear();
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
	{
		vrtx_1 = *(*pe).getpVrtx_1(); 
		vID_1 = vrtx_1.getID();
		
		vrtx_2 = *(*pe).getpVrtx_2(); 
		vID_2 = vrtx_2.getID();
		
		ppConnectivity[vID_1][vID_2] = (*pe).getDistance();  //
	}
	for (int i = 0; i < num_nodes; i++)
		ppConnectivity[i][i] = 0; // 두 노드가 같으면 distance는 0
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
		pVrtxStatus[i] = UN_VISITED;  //VrtxStatus[] 를 초기상태로 설정
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED;  //EdgeStatus[][] 를 초기상태로 설정
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
				fout << setw(5) << dist;  //
		} //end inner for
		fout << endl;
	} // end outer for
}


void DepthFirstSearch::showConnectivity()
{
	int num_nodes = graph.getNumVertices();
	int dist;
	Graph g = getGraph();
	Vertex* pVrtxArray = g.getpVrtxArray();
	cout << "Connectivity of graph: " << endl;
	cout << "     |";
	for (int i = 0; i < num_nodes; i++)
		cout << setw(5) << pVrtxArray[i].getName();
	cout << endl;
	cout << "-----+";
	for (int i = 0; i < num_nodes; i++)
		cout << "-----";
	cout << endl;
	for (int i = 0; i < num_nodes; i++) {
		cout << "   " << pVrtxArray[i].getName() << " | ";
		for (int j = 0; j < num_nodes; j++) {
			dist = ppConnectivity[i][j];
			if (dist == PLUS_INF)
				cout << "  +oo";
			else
				cout << setw(5) << dist;  //
		} //end inner for
		cout << endl;
	} // end outer for
}


void DepthFirstSearch::dfsTraversal(Vertex& v, Vertex& target, VrtxList& path)
{
	//startVisit(v);
	visit(v);  //맨처음에 v를 visited로 설정.
	if (v == target)  //현재 방문하고 있는 노드가 목적지노드라면
	{
		done = true;
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
		if (eStat == EDGE_UN_VISITED)  //방문하지않은 초기화상태
		{
			visit(e);
			Vertex w = e.opposite(v);  //그 edge에 연결되어있는 vertex 중 v반대편에 있는 vertex
			if (!isVisited(w))  //w가 아직 방문한 적이 없다면
			{
				//traverseDiscovery(e, v);
				path.push_back(w);
				setEdgeStatus(e, DISCOVERY);  //
				if (!isDone())
				{
					dfsTraversal(w, target, path);  //recursive call(재귀함수 호출). w부터 시작해서 다시 찾아가게끔.

					if (!isDone()) {
						//traverseBack(e, v);
						// check whether node w is already in path as a cycle
						Vertex last_pushed = path.back(); // for debugging
						path.pop_back();  //path에 삽입하였던 마지막 정점을 pop_back()함수를 사용해 제거
					}
				}
			}
			else // w is VISITED
			{
				setEdgeStatus(e, BACK);  //w가 이미 이전에 방문한적 있었다
			}
		} // end if (eStat == EDGE_UN_VISITED)
	} // end of while - processing of all incedent edges
}

void DepthFirstSearch::findPath(Vertex& start, Vertex& target, VrtxList& path)
{
	initialize();
	path.clear();

	path.push_back(start);
	dfsTraversal(start, target, path);  //출발지로부터 목적지까지의 경로를 탐색하고, 그 결과를 path(VrtxList객체)에 담아준다.

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
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))  //지정된 간선이 정상적인범위의 정점 식별자를 가지면
	{
		ppEdgeStatus[vID_1][vID_2] = es;  //간선의 상태를 변경
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
	if (graph.isValidVrtxID(vID_1) && graph.isValidVrtxID(vID_2))//지정된 간선이 정상적인범위의 정점 식별자를 가지면
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		return eStat;  //상태 읽어 반환
	}
	else {
		cout << "Edge (" << e << ") was not found from AdjacencyList" << endl;
		return EDGE_NOT_FOUND;
	}
}





#endif
