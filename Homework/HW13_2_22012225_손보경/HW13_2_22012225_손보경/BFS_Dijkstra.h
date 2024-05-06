#ifndef BFS_DIJKSTRA_H 
#define BFS_DIJKSTRA_H
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Graph.h"
#include <fstream>
using namespace std;
typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;
class BreadthFirstSearch
{
protected:
	Graph& graph;  //����� �׷���
	bool done; // flag of search done
	int** ppDistMtrx; // distance matrix ������ ������ �Ÿ��� ��Ÿ���� 2���� ��Ʈ����
protected:
	void initialize();
	bool isValidvID(int vid) { return graph.isValidVrtxID(vid)/*isValidID(vid)*/; }
	int getNumVertices() { return graph.getNumVertices(); }

public:
	BreadthFirstSearch(Graph& g) :graph(g)
	{
		int num_nodes;
		num_nodes = g.getNumVertices();
		// initialize DistMtrx
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes];
		for (int i = 0; i < num_nodes; i++) {
			for (int j = 0; j < num_nodes; j++)
			{
				ppDistMtrx[i][j] = PLUS_INF;
			}
		}
	}
	void initDistMtrx();
	void fprintDistMtrx(ofstream& fout);
	void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);  //������ ���������� ������ ��� ���� ���� �ִܰŸ� ��θ� ã�� ��ȯ
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path);  //������ �Ѱ����κ��� ������ �Ѱ����� ���� �ִܰŸ� ã��
	Graph& getGraph() { return graph; }
	int** getppDistMtrx() { return ppDistMtrx; }
};



void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = getGraph().getpVrtxArray();  //�׷����� vetir array �����ͼ�
	VrtxList vrtxLst;
	graph.vertices(vrtxLst);
	int num_vertices = graph.getNumVertices();

	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED);  //�湮�����������·�

	EdgeList edges;
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED);  //�湮�������� ���·�
}

void BreadthFirstSearch::initDistMtrx()
{
	int** ppDistMtrx;
	int* pLeaseCostMtrx;
	int num_nodes;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVID, vID;

	num_nodes = getNumVertices();
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	ppDistMtrx = getppDistMtrx();

	for (int i = 0; i < num_nodes; i++)  //������ �� ��
	{
		curVID = pVrtxArray[i].getID();  //������� �����̸�
		EdgeItor pe = pAdjLstArray[curVID].begin();
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();  //�������� �����̸�
			ppDistMtrx[curVID][vID] = (*pe).getDistance();
			pe++;
		}
		ppDistMtrx[curVID][curVID] = 0;  //�ڱ��ڽ��� ������ ��߰� ������ 0
	}
}

void BreadthFirstSearch::fprintDistMtrx(ofstream& fout)
{
	int** ppDistMtrx;
	Vertex* pVrtxArray;
	int num_nodes;
	int dist;
	int vID;
	string vName;
	pVrtxArray = graph.getpVrtxArray();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();

	fout << "\nDistance Matrix of Graph (" << graph.getName() << ") :" << endl;
	fout << "       |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "-------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << "-----";
	}
	fout << endl;

	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName << "  |";
		for (int j = 0; j < num_nodes; j++)
		{
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)
				fout << setw(5)<< "+oo";
			else  //
				fout << setw(5) << dist;  //
		}
		fout << endl;
	}
	fout << endl;
}

enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED };
void BreadthFirstSearch::DijkstraShortestPath(ofstream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	int** ppDistMtrx;
	int* pLeastCost;
	int num_nodes, num_selected;
	int minID, minCost;
	BFS_PROCESS_STATUS* pBFS_Process_Stat;
	int* pPrev;

	Vertex* pVrtxArray;
	Vertex vrtx, * pPrevVrtx, v;
	Edge e;
	int start_vID, target_vID, curVID, vID;
	EdgeList* pAdjLstArray;

	pVrtxArray = graph.getpVrtxArray();  //vertex�迭�� �ּ�
	pAdjLstArray = graph.getpAdjLstArray();  //
	start_vID = start.getID();
	target_vID = target.getID();

	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();  //distance matrix�� �ּҸ� ���������Ϳ� ����

	pLeastCost = new int[num_nodes];  //
	pPrev = new int[num_nodes];  //��λ󿡼� �ڱ� �տ� �ִ� ��尡 �������� ����ϱ�����
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes];

	// initialize L(n) = w(start, n);
	for (int i = 0; i < num_nodes; i++)
	{

		pLeastCost[i] = ppDistMtrx[start_vID][i];  //start��忡�� �����ؼ� i��°������ ���� distance table�κ��� �� �о� ����
												//���� �������� ��ΰ� ������ �ʱ���¿��� ���Ѵ�� ������ �Ǿ�����
		pPrev[i] = start_vID;  //��������� �ڱ� �տ� �ִ� previous ���� start_vID
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}
	pBFS_Process_Stat[start_vID] = SELECTED;  //
	num_selected = 1;
	path.clear();

	int round = 0;
	int cost;
	string vName;

	//�Ź� ���尡 ����ɶ����� ������ ���������� ���� ������ ����� ����ؼ� Ȯ���� �� �ְ�
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << "           |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "-----------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	}
	fout << endl;

	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "] |";
		minID = -1;
		minCost = PLUS_INF;
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost 
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED))
			{
				//���ݱ��� �˰��־����ͺ��� �� ���� ���� ������ �ִ� ��尡 ���õǵ���
				minID = i;
				minCost = pLeastCost[i];
			}
		}
		if (minID == -1)  //������ �Ǿ����� �ʴ� vertex�� �ִ� ���
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}
		else
		{
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;

			if (minID == target_vID)  //���������� �����ϸ�
			{
				fout << endl << "reached to the target node ("
					<< pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;
				do {
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];  //��� �� ���� ���� vID ����. (����������)
				} while (vID != start_vID);  //���۳�尡 �ƴ� ������

				vrtx = pVrtxArray[vID];
				path.push_front(vrtx); // start node
				break;
			}
		}

		/* Edge relaxation *//////////////////////
		int pLS, ppDistMtrx_i;
		for (int i = 0; i < num_nodes; i++)
		{
			pLS = pLeastCost[i];
			ppDistMtrx_i = ppDistMtrx[minID][i];  //min_ID�� ���ļ� �����ִ� ������ ���鿡 ���� �κе�

			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))   /////////////////////////
			{  //�� ���� ������ ��θ� ã�� ���
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i]; //
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << setw(5)<< "+oo";
			else
				fout << setw(5) << pLeastCost[i];
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	} // end while()
} // end DijkstraShortestPath()




#endif