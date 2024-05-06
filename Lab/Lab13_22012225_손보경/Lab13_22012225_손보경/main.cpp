/*
* Lab13
* BFS- Dijkstra
* 
* 정보통신공학과 22012225 손보경
* 2021-12-03-(금)
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_Dijkstra.h"
using namespace std;
#define GRAPH_SIMPLE_USA_7_NODES

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Failed to open output.txt file !!" << endl;
		exit;
	}

#define NUM_NODES 7 
#define NUM_EDGES 26 
	Vertex v[NUM_NODES] = // 7 nodes
	{
		Vertex("SF", 0), Vertex("LA", 1), Vertex("DLS", 2),
		Vertex("CHG", 3), Vertex("MIA", 4), Vertex("NY", 5),
		Vertex("BOS", 6)
	};
	/*Graph::*/Edge edges[NUM_EDGES] = // 70 edges
	{
		Edge(v[0], v[1], 337), Edge(v[1], v[0], 337), Edge(v[0], v[2], 1464), Edge(v[2], v[0], 1464),
		Edge(v[0], v[3], 1846), Edge(v[3], v[0], 1846), Edge(v[0], v[6], 2704), Edge(v[6], v[0], 2704),
		Edge(v[1], v[2], 1235), Edge(v[2], v[1], 1235), Edge(v[1], v[4], 2342), Edge(v[4], v[1], 2342),
		Edge(v[2], v[3], 802), Edge(v[3], v[2], 802), Edge(v[2], v[4], 1121), Edge(v[4], v[2], 1121),
		Edge(v[3], v[5], 740), Edge(v[5], v[3], 740), Edge(v[3], v[6], 867), Edge(v[6], v[3], 867),
		Edge(v[5], v[4], 1090), Edge(v[4], v[5], 1090), Edge(v[5], v[6], 187), Edge(v[6], v[5], 187),
		Edge(v[4], v[6], 1258), Edge(v[6], v[4], 1258),
	};

	int test_start = 1;
	int test_end = 6;
	Graph simpleGraph("GRAPH_SIMPLE_USA_7_NODES", NUM_NODES);

	fout << "Inserting vertices .." << endl;
	for (int i = 0; i < NUM_NODES; i++) 
	{
		simpleGraph.insertVertex(v[i]);
	}

	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst);
	int count = 0;
	fout << "Inserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor)
	{
		fout << *vItor << ", ";
	}
	fout << endl;
	fout << "Inserting edges .." << endl;
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]);
	}
	fout << "Inserted edges: " << endl;
	count = 0;
	EdgeList egLst;
	simpleGraph.edges(egLst);
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		fout << *p << ", ";
		if (count % 5 == 0)
			fout << endl;
	}


	fout << endl << endl;
	fout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.fprintGraph(fout);
	/* ==========================================*/
	VrtxList path;
	BreadthFirstSearch bfsGraph(simpleGraph);

	fout << "\nTesting Breadth First Search with Dijkstra Algorithm" ;
	bfsGraph.initDistMtrx();
	//fout << "Distance matrix of BFS for Graph:" << endl;
	bfsGraph.fprintDistMtrx(fout);   ///정점간의 간선의 가중치를 한눈에 볼 수 있게 표 형태로 출력 
	path.clear();

	fout << "\nDijkstra Shortest Path Finding from " << v[test_start].getName() << " to "<< v[test_end].getName() << " .... " << endl;
	bfsGraph.DijkstraShortestPath(fout, v[test_start], v[test_end], path);  ///////////v[test_start]에서 v[test_end]로 가는 최단거리 찾기
	fout << "Path found by DijkstraShortestPath from " << v[test_end] << " to " << v[test_start] << " : ";
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
	{
		fout << *vItor;
		if (*vItor != v[test_end])                    //도착지로가는최단경로 츌력
			fout << " -> ";
	}
	fout << endl;
	fout.close();
}
