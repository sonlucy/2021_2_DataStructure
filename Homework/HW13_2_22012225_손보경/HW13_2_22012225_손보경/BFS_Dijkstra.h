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
	Graph& graph;  //사용할 그래프
	bool done; // flag of search done
	int** ppDistMtrx; // distance matrix 정점들 사이의 거리를 나타내는 2차원 매트릭스
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
	void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);  //지정된 시작점에서 나머지 모든 노드로 가는 최단거리 경로를 찾아 반환
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path);  //지정된 한곳으로부터 지정된 한곳으로 가는 최단거리 찾기
	Graph& getGraph() { return graph; }
	int** getppDistMtrx() { return ppDistMtrx; }
};



void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = getGraph().getpVrtxArray();  //그래프의 vetir array 가져와서
	VrtxList vrtxLst;
	graph.vertices(vrtxLst);
	int num_vertices = graph.getNumVertices();

	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED);  //방문하지않은상태로

	EdgeList edges;
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED);  //방문하지않은 상태로
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

	for (int i = 0; i < num_nodes; i++)  //정점의 총 수
	{
		curVID = pVrtxArray[i].getID();  //출발지의 정점이름
		EdgeItor pe = pAdjLstArray[curVID].begin();
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();  //도착지의 정점이름
			ppDistMtrx[curVID][vID] = (*pe).getDistance();
			pe++;
		}
		ppDistMtrx[curVID][curVID] = 0;  //자기자신의 정점의 출발과 도착은 0
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

	pVrtxArray = graph.getpVrtxArray();  //vertex배열의 주소
	pAdjLstArray = graph.getpAdjLstArray();  //
	start_vID = start.getID();
	target_vID = target.getID();

	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();  //distance matrix의 주소를 이중포인터에 설정

	pLeastCost = new int[num_nodes];  //
	pPrev = new int[num_nodes];  //경로상에서 자기 앞에 있는 노드가 누구인지 기록하기위해
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes];

	// initialize L(n) = w(start, n);
	for (int i = 0; i < num_nodes; i++)
	{

		pLeastCost[i] = ppDistMtrx[start_vID][i];  //start노드에서 시작해서 i번째노드까지 가는 distance table로부터 값 읽어 저장
												//만약 직접가는 경로가 없으면 초기상태에선 무한대로 설정이 되어있음
		pPrev[i] = start_vID;  //현재까지의 자기 앞에 있는 previous 노드는 start_vID
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}
	pBFS_Process_Stat[start_vID] = SELECTED;  //
	num_selected = 1;
	path.clear();

	int round = 0;
	int cost;
	string vName;

	//매번 라운드가 진행될때마다 각각의 목적지노드로 가는 누적된 비용을 출력해서 확인할 수 있게
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
				//지금까지 알고있었던것보다 더 작은 값을 가지고 있는 노드가 선택되도록
				minID = i;
				minCost = pLeastCost[i];
			}
		}
		if (minID == -1)  //연결이 되어있지 않는 vertex가 있는 경우
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}
		else
		{
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;

			if (minID == target_vID)  //목적지까지 도착하면
			{
				fout << endl << "reached to the target node ("
					<< pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;
				do {
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];  //계속 그 앞의 노드로 vID 설정. (역추적위해)
				} while (vID != start_vID);  //시작노드가 아닐 때까지

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
			ppDistMtrx_i = ppDistMtrx[minID][i];  //min_ID를 거쳐서 갈수있는 나머지 노드들에 대한 부분들

			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))   /////////////////////////
			{  //더 좋은 조건의 경로를 찾은 경우
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