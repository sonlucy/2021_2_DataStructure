#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
//typedef std::list<Graph::Vertex> vrtxLst;
//typedef std::list<Graph::Edge> EdgeList;
//typedef std::list<Graph::Vertex>::iterator VrtxItor;
//typedef std::list<Graph::Edge>::iterator EdgeItor;
using namespace std;
#define PLUS_INF INT_MAX/2 
enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED, EDGE_NOT_FOUND };

class Graph // Graph based on Adjacency Matrix
{
public:
	class Vertex;
	class Edge;
	typedef std::list<Graph::Vertex> VrtxList;
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Vertex>::iterator VrtxItor;
	typedef std::list<Edge>::iterator EdgeItor;

public:
	class Vertex // Graph::Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex v)
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex() : name(), ID(-1) {}
		Vertex(string n, int id) : name(n), ID(id) { }
		Vertex(int id) : ID(id) {}
		string getName() { return name; }
		void setName(string c_name) { name = c_name; }
		int getID() { return ID; }
		void setID(int id) { ID = id; }
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; }
		VrtxStatus getvrtxStatus() { return vrtxStatus; }
		bool operator==(Vertex v) { return ((ID == v.getID()) && (name == v.getName())); }
		bool operator!=(Vertex v) { return ((ID != v.getID()) || (name != v.getName())); }
	private:
		string name;
		int ID;
		VrtxStatus vrtxStatus;
	}; // end class Vertex

public:
	class Edge // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e)
		{
			fout << "Edge(" << setw(2) << *e.getpVrtx_1() << ", " << setw(2)
				<< *e.getpVrtx_2() << ", " << setw(4) << e.getDistance() << ")";
			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {}  //edge의 시작점, 끝점 포인터와 distance 설정 
		Edge(Vertex& v1, Vertex& v2, int d) :distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED) { }
		void endVertices(VrtxList& vrtxLst)
		{
			vrtxLst.push_back(*pVrtx_1);  //간선의 출발/도착지를 나타내는 값을 전달되온 vrtxLst에 담아줌 
			vrtxLst.push_back(*pVrtx_2);
		}
		Vertex opposite(Vertex v)
		{
			if (v == *pVrtx_1)
				return *pVrtx_2;
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			else {
				//cout << "Error in opposite()" << endl;
				return Vertex(NULL);
			}
		}

		Vertex* getpVrtx_1() { return pVrtx_1; }
		Vertex* getpVrtx_2() { return pVrtx_2; }
		int getDistance() { return distance; }
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; }
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; }
		void setDistance(int d) { distance = d; }

		bool operator!=(Edge e)
		{
			return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 != e.getpVrtx_2()));
		}
		bool operator==(Edge e) 
		{
			return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 == e.getpVrtx_2()));
		}

		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; }
		EdgeStatus getEdgeStatus() { return edgeStatus; }

	private:
		Vertex* pVrtx_1;   //vetex배열에 있는 항목을 포인터로 가지도록.
		Vertex* pVrtx_2;
		int distance;
		EdgeStatus edgeStatus;
	}; // end class Edge
public:
	Graph() : name(""), pVrtxArray(NULL), pAdjLstArray(NULL) {} // default constructor
	Graph(string nm, int num_nodes) : name(nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		num_vertices = num_nodes;
		pVrtxArray = new Graph::Vertex[num_vertices];
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;  //초기화
		pAdjLstArray = new EdgeList[num_vertices];
		for (int i = 0; i < num_vertices; i++)
			pAdjLstArray[i].clear();  //초기화
	}

	string getName() { return name; }
	void vertices(VrtxList& vrtxLst);  //그래프에 포함된 모든 정점들을 리스트에 담아 반환
	void edges(EdgeList&);  //그래프에 포함된 모든 edge들을 리스트에 담아 반환
	bool isAdjacentTo(Vertex v, Vertex w);  //전달되온 두 vertex가 서로 인접한지 판단
	
	void insertVertex(Vertex& v);  //그래프에 지정된 vertex추가
	void insertEdge(Edge& e);    //지정된 edge 추가
	void eraseEdge(Edge e);  //해당하는 edge삭제
	void eraseVertex(Vertex v);  //해당하는 vertex(정점) 삭제

	int getNumVertices() { return num_vertices; }  //그래프에 포함된 전체 vertice 개수
	void incidentEdges(Vertex v, EdgeList& edges);  //Vertex v에 연결되어있는 edge들을 리스트로 만들어 알려줌
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }
	void fprintGraph(ofstream& fout);
	bool isValidVrtxID(int vid);  //유효한 ID값이 맞는지
private:
	string name;
	Vertex* pVrtxArray; //Vertex의 포인터. array of pointers of vertex
	EdgeList* pAdjLstArray; //EdgeList의 포인터. array of adjacent lists
	int num_vertices;  //전체 정점의 개수
};



void Graph::insertVertex(Vertex& v)
{
	int vID;
	vID = v.getID();
	if (pVrtxArray[vID] == NULL) 
	{
		pVrtxArray[vID] = v;  //v를 설정
	}
	//else :이전에 이미 추가된적 있음
}

void Graph::vertices(VrtxList& vrtxLst)
{
	vrtxLst.clear();
	for (int i = 0; i < getNumVertices(); i++)
		vrtxLst.push_back(pVrtxArray[i]);  //i번째 vertex에대한정보를 vrtxLst에 담아 반환
}  //그래프에 포함된 모든 정점들의 정보를 파악할 수 있음

void Graph::insertEdge(Edge& e)  //간선 추가
{
	Vertex vrtx_1, vrtx_2;  //edge가 연결하고 있는 시작정점과 끝나는 정점
	Vertex* pVtx;
	int vID_1, vID_2;

	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();

	if (pVrtxArray[vID_1] == NULL) {
		pVrtxArray[vID_1] = vrtx_1;
	}
	if (pVrtxArray[vID_2] == NULL) {
		pVrtxArray[vID_2] = vrtx_2;
	}
	e.setpVrtx_1(&pVrtxArray[vID_1]);  //edge가 vertex table에 있는 그 주소를 가지도록
	e.setpVrtx_2(&pVrtxArray[vID_2]);

	pAdjLstArray[vID_1].push_back(e);  //그 edge의 시작하는 노드의 인접리스트 안에 그 edge를 추가
}

void Graph::edges(EdgeList& edges) //그래프에 포함된 모든 edge들을 찾아서 리스트에 담아줌
{
	EdgeItor eItor;
	Graph::Edge e;

	edges.clear();
	for (int i = 0; i < getNumVertices(); i++)
	{
		eItor = pAdjLstArray[i].begin(); //i번째 vertex에 연결되어있는 모든 edge들이 
		while (eItor != pAdjLstArray[i].end())  //i번째 vertex의 edgelist의 마지막이 아닐때까지
		{
			e = *eItor;
			edges.push_back(e); //전달되온 리스트에 추가
			eItor++;
		}
	}
}

void Graph::incidentEdges(Vertex v, EdgeList& edgeLst)  //주어진 vertex v에 연결되어있는 edge들을 list에 담아줌
{
	Graph::Edge e;
	EdgeItor eItor;
	int vID = v.getID();

	eItor = pAdjLstArray[vID].begin();  //
	while (eItor != pAdjLstArray[vID].end())  //vID번째 vertex의 edgelist의 마지막이 아닐때까지
	{
		e = *eItor;
		edgeLst.push_back(e);   //전달되온 리스트에 추가
		eItor++;
	}
}

bool Graph::isValidVrtxID(int vid)
{
	if ((vid >= 0) && (vid < num_vertices))
		return true;
	else
	{
		cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName()
			<< ") with num_vertices (" << num_vertices << ")" << endl;
	}
}

void Graph::fprintGraph(ofstream& fout)
{
	int i, j;
	EdgeItor eItor;
	Graph::Edge e;
	int numOutgoingEdges;

	fout << this->getName() << " with " << this->getNumVertices()
		<< " vertices has following connectivity :" << endl;
	for (i = 0; i < num_vertices; i++)
	{
		fout << " vertex (" << setw(3) << pVrtxArray[i].getName() << ") : ";
		numOutgoingEdges = pAdjLstArray[i].size();  //list에 포함되어있는 edge의 개수

		eItor = pAdjLstArray[i].begin();
		while (eItor != pAdjLstArray[i].end())
		{
			e = *eItor;
			fout << e << " ";
			eItor++;
		}
		fout << endl;
	}
}





#endif
