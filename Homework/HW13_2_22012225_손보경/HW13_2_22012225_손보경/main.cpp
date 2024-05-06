/*
* HW13-2
*  [BFS] Dijkstra 알고리즘을 사용한 최단거리 경로 탐색
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-12-04
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

#define NUM_NODES 11
#define NUM_EDGES 34
	Vertex v[NUM_NODES] = // 14 nodes
	{
		Vertex("SL", 0), Vertex("CC", 1), Vertex("SC", 2),
		Vertex("SW", 3), Vertex("WJ", 4), Vertex("GR", 5),
		Vertex("DJ", 6), Vertex("DG", 7), Vertex("PH", 8),
		Vertex("GJ", 9), Vertex("BS", 10),
	};
	/*Graph::*/Edge edges[NUM_EDGES] = // 70 edges
	{
		Edge(v[0], v[1], 71), Edge(v[1], v[0], 71), 
		Edge(v[1], v[2], 79), Edge(v[2], v[1], 79),
		Edge(v[0], v[3], 34), Edge(v[3], v[0], 34), 
		Edge(v[3], v[4], 84), Edge(v[4], v[3], 84),
		Edge(v[4], v[1], 47), Edge(v[1], v[4], 47), 
		Edge(v[4], v[5], 91), Edge(v[5], v[4], 91),
		Edge(v[5], v[2], 42), Edge(v[2], v[5], 42), 
		
		Edge(v[3], v[6], 109), Edge(v[6], v[3], 109),
		Edge(v[4], v[7], 174), Edge(v[7], v[4], 174), 
		Edge(v[5], v[8], 200), Edge(v[8], v[5], 200),

		Edge(v[6], v[7], 120), Edge(v[7], v[6], 120), 
		Edge(v[7], v[8], 66), Edge(v[8], v[7], 66),
		
		Edge(v[6], v[9], 138), Edge(v[9], v[6], 138),
		Edge(v[9], v[7], 170), Edge(v[7], v[9], 170),
		Edge(v[9], v[10], 202), Edge(v[10], v[9], 202),
		Edge(v[10], v[7], 87), Edge(v[7], v[10], 87),
		Edge(v[10], v[8], 93), Edge(v[8], v[10], 93),


	};

	int test_start = 1;
	int test_end = 6;
	Graph simpleGraph("GRAPH_SIMPLE_USA_11_NODES", NUM_NODES);

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
	bfsGraph.fprintDistMtrx(fout);  /////정점간의 간선의 가중치를 한눈에 볼 수 있게 표 형태로 출력 
	path.clear();

	fout << "\nDijkstra Shortest Path Finding from " << v[test_start].getName() << " to " << v[test_end].getName() << " .... " << endl;
	bfsGraph.DijkstraShortestPath(fout, v[test_start], v[test_end], path);  ///////////////////v[test_start]에서 v[test_end]로 가는 최단거리 찾기
	fout << "Path found by DijkstraShortestPath from " << v[test_start] << " to " << v[test_end] << " : ";  //////////
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
	{
		fout << *vItor;
		if (*vItor != v[test_end])                    //도착지로가는최단경로 츌력
			fout << " -> ";
	}
	fout << endl;
	fout.close();
}
