#ifndef MINIMUM_SPANNING_TREE_H
#define MINIMUM_SPANNING_TREE_H
#include <iostream>
#include <list>
#include <algorithm>
#include "Graph.h"
#include <ctime>
#include <vector>

#include "WeightedEdge.h"
//#include "BFS_Dijkstra.h"  ///
using namespace std;


typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Vertex>::iterator VertexItor;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class MinimumSpanningTree
{
public:
	MinimumSpanningTree(Graph& g, ostream& ostr)
		:graph(g), fout(ostr)
	{
		int num_nodes;
		num_nodes = g.getNumVertices();
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				ppDistMtrx[i][j] = PLUS_INF;
			}
		}
		initDistMtrx();
		fout << "Distance Matrix initialisation :" << endl;
		fprintDistMtrx(fout);
	}

	void initialize();
	void initDistMtrx();
	void fprintDistMtrx(ostream& fout);
	void KruskalMST();
	void PrimJarnikMST(int s);
	Graph& getGraph() { return graph; }
	int** getppDistMtrx() { return ppDistMtrx; }




private:
	Graph& graph;
	ostream& fout;
	int** ppDistMtrx;
};

void MinimumSpanningTree::KruskalMST()
{
	int num_nodes, num_edges;
	Vertex* pVrtxArray;
	EdgeList* pAdjListArray;
	int curVrtx_ID, vrtxID;
	weightedEdge wtEdge, minWtEdge;
	std::vector<weightedEdge> wtEdges;
	std::list<int>* pCluster;
	std::list<int>::iterator clusterItor;
	int* pClusterNo;
	int org, end_ID, dist;



}


void MinimumSpanningTree::PrimJarnikMST()
{
	int num_nodes, num_edges;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVrtx_ID, vrtxID;
	int** ppDistMtrx;
	int* pDist;
	int start, min_id, dist, min_dist, min_dist_org, min_dist_end, end_ID;
	VertexStatus* pVrtxStatus;
	Graph::Edge* pParentEdge, edge, min_edge; // edge that connects this node to the cloud
	std::list<Graph::Edge> selectedEdgeLst;
	std::list<Graph::Edge>::iterator edgeItor;
	num_nodes = graph.getNumVertices();
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();

	initDistMtrx();
	ppDistMtrx = getppDistMtrx();

	pDist = new int[num_nodes];
	pVrtxStatus = new VertexStatus[num_nodes];
	pEdge = new Graph::Edge[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		pDist[i] = PLUS_INF;
		pVrtxStatus[i] = NOT_SELECTED;
		pParentEdge[i] = Graph::Edge(NULL, NULL, PLUS_INF);
	}
	srand(time(0));
	start = rand() % num_nodes; // randomly select start node
	cout << "Start node : " << start << endl;
	pDist[start] = 0;
	selectedEdgeLst.clear();

	for (int round = 0; round < num_nodes; round++) {
		min_dist = PLUS_INF;
		min_id = -1;
		for (int n = 0; n < num_nodes; n++)
		{
			if ((pVrtxStatus[n] == NOT_SELECTED) && (pDist[n] < min_dist)) {
				min_dist = pDist[n];
				min_id = n;
			} // end if
		} // end for
		if (min_id == -1)
		{
			cout << "Error in finding Prim-Jarnik's algorithm !!";
			break;
		}
		pVrtxStatus[min_id] = SELECTED;

		EdgeItor pe = pAdjLstArray[min_id].begin();
		while (pe != pAdjLstArray[min_id].end())
		{
			end_ID = ((*pe).getVertex_2()).getID();
			dist = (*pe).getDistance();
			if ((pVrtxStatus[end_ID] == NOT_SELECTED) && (dist <= pDist[end_ID])) {
				pDist[end_ID] = dist;
				pParentEdge[end_ID] = *pe;
			}
			pe++;
		} // end while
		if (min_id != start) {
			min_edge = pParentEdge[min_id];
			selectedEdgeLst.push_back(min_edge);
		}
		cout << "Dist after round [" << setw(2) << round << "] : ";
		for (int i = 0; i < num_nodes; i++) {
			if (pDist[i] == PLUS_INF)
				cout << " +oo ";
			else
				cout << setw(4) << pDist[i] << " ";
		}
		cout << endl;
	} // end for

	cout << "\nEnd of finding Minimum Spanning Tree by Prim-Jarnik's Algorithm;";
	cout << "selectedEdgeLst.size = " << selectedEdgeLst.size() << endl;
	cout << "Selected edges: " << endl;
	edgeItor = selectedEdgeLst.begin();
	int cnt = 0;
	while (edgeItor != selectedEdgeLst.end())
	{
		cout << *edgeItor << ", ";
		edgeItor++;
		if ((++cnt % 5) == 0)
			cout << endl;
	}
	cout << endl;
}

#endif