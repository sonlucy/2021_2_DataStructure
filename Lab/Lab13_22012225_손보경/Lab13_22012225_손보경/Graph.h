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
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {}  //edge�� ������, ���� �����Ϳ� distance ���� 
		Edge(Vertex& v1, Vertex& v2, int d) :distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED) { }
		void endVertices(VrtxList& vrtxLst)
		{
			vrtxLst.push_back(*pVrtx_1);  //������ ���/�������� ��Ÿ���� ���� ���޵ǿ� vrtxLst�� ����� 
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
		Vertex* pVrtx_1;   //vetex�迭�� �ִ� �׸��� �����ͷ� ��������.
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
			pVrtxArray[i] = NULL;  //�ʱ�ȭ
		pAdjLstArray = new EdgeList[num_vertices];
		for (int i = 0; i < num_vertices; i++)
			pAdjLstArray[i].clear();  //�ʱ�ȭ
	}

	string getName() { return name; }
	void vertices(VrtxList& vrtxLst);  //�׷����� ���Ե� ��� �������� ����Ʈ�� ��� ��ȯ
	void edges(EdgeList&);  //�׷����� ���Ե� ��� edge���� ����Ʈ�� ��� ��ȯ
	bool isAdjacentTo(Vertex v, Vertex w);  //���޵ǿ� �� vertex�� ���� �������� �Ǵ�
	
	void insertVertex(Vertex& v);  //�׷����� ������ vertex�߰�
	void insertEdge(Edge& e);    //������ edge �߰�
	void eraseEdge(Edge e);  //�ش��ϴ� edge����
	void eraseVertex(Vertex v);  //�ش��ϴ� vertex(����) ����

	int getNumVertices() { return num_vertices; }  //�׷����� ���Ե� ��ü vertice ����
	void incidentEdges(Vertex v, EdgeList& edges);  //Vertex v�� ����Ǿ��ִ� edge���� ����Ʈ�� ����� �˷���
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }
	void fprintGraph(ofstream& fout);
	bool isValidVrtxID(int vid);  //��ȿ�� ID���� �´���
private:
	string name;
	Vertex* pVrtxArray; //Vertex�� ������. array of pointers of vertex
	EdgeList* pAdjLstArray; //EdgeList�� ������. array of adjacent lists
	int num_vertices;  //��ü ������ ����
};



void Graph::insertVertex(Vertex& v)
{
	int vID;
	vID = v.getID();
	if (pVrtxArray[vID] == NULL) 
	{
		pVrtxArray[vID] = v;  //v�� ����
	}
	//else :������ �̹� �߰����� ����
}

void Graph::vertices(VrtxList& vrtxLst)
{
	vrtxLst.clear();
	for (int i = 0; i < getNumVertices(); i++)
		vrtxLst.push_back(pVrtxArray[i]);  //i��° vertex������������ vrtxLst�� ��� ��ȯ
}  //�׷����� ���Ե� ��� �������� ������ �ľ��� �� ����

void Graph::insertEdge(Edge& e)  //���� �߰�
{
	Vertex vrtx_1, vrtx_2;  //edge�� �����ϰ� �ִ� ���������� ������ ����
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
	e.setpVrtx_1(&pVrtxArray[vID_1]);  //edge�� vertex table�� �ִ� �� �ּҸ� ��������
	e.setpVrtx_2(&pVrtxArray[vID_2]);

	pAdjLstArray[vID_1].push_back(e);  //�� edge�� �����ϴ� ����� ��������Ʈ �ȿ� �� edge�� �߰�
}

void Graph::edges(EdgeList& edges) //�׷����� ���Ե� ��� edge���� ã�Ƽ� ����Ʈ�� �����
{
	EdgeItor eItor;
	Graph::Edge e;

	edges.clear();
	for (int i = 0; i < getNumVertices(); i++)
	{
		eItor = pAdjLstArray[i].begin(); //i��° vertex�� ����Ǿ��ִ� ��� edge���� 
		while (eItor != pAdjLstArray[i].end())  //i��° vertex�� edgelist�� �������� �ƴҶ�����
		{
			e = *eItor;
			edges.push_back(e); //���޵ǿ� ����Ʈ�� �߰�
			eItor++;
		}
	}
}

void Graph::incidentEdges(Vertex v, EdgeList& edgeLst)  //�־��� vertex v�� ����Ǿ��ִ� edge���� list�� �����
{
	Graph::Edge e;
	EdgeItor eItor;
	int vID = v.getID();

	eItor = pAdjLstArray[vID].begin();  //
	while (eItor != pAdjLstArray[vID].end())  //vID��° vertex�� edgelist�� �������� �ƴҶ�����
	{
		e = *eItor;
		edgeLst.push_back(e);   //���޵ǿ� ����Ʈ�� �߰�
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
		numOutgoingEdges = pAdjLstArray[i].size();  //list�� ���ԵǾ��ִ� edge�� ����

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
