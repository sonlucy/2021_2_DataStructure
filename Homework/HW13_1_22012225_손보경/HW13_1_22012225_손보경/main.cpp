/*
* HW13-1 
* [DFS]그래프 깊이 우선 탐색과 미로 탐색 (Maze Traversal) 
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-12-04
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "DepthFirstSearch.h"
//#include "BreadthFirstSearch.h"
#define NUM_NODES 25
#define NUM_EDGES 50
typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;
void main()
{
	/*
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt file !!" << endl;
		exit(1);
	}*/

	/*Vertex v[NUM_NODES] =
	{
		Vertex("v0", 0), Vertex("v1", 1),
		Vertex("v2", 2), Vertex("v3", 3),
		Vertex("v4", 4), Vertex("v5", 5),
		Vertex("v6", 6), Vertex("v7", 7),
		Vertex("v8", 8), Vertex("v9", 9),
		Vertex("v10", 10), Vertex("v11", 11),
		Vertex("v12", 12), Vertex("v13", 13),
		Vertex("v14", 14), Vertex("v15", 15),
		Vertex("v16", 16), Vertex("v17", 17),
		Vertex("v18", 18), Vertex("v19", 19),
		Vertex("v20", 20), Vertex("v21", 21),
		Vertex("v22", 22), Vertex("v23", 23),
		Vertex("v24", 24)

	};*/

	Vertex v[NUM_NODES] =
	{
		Vertex("A", 0), Vertex("B", 1),
		Vertex("C", 2), Vertex("D", 3),
		Vertex("E", 4), Vertex("F", 5),
		Vertex("G", 6), Vertex("H", 7),
		Vertex("I", 8), Vertex("J", 9),
		Vertex("K", 10), Vertex("L", 11),
		Vertex("M", 12), Vertex("N", 13),
		Vertex("O", 14), Vertex("P", 15),
		Vertex("Q", 16), Vertex("R", 17),
		Vertex("S", 18), Vertex("T", 19),
		Vertex("U", 20), Vertex("V", 21),
		Vertex("W", 22), Vertex("X", 23),
		Vertex("Y", 24)

	};

	Edge edges[NUM_EDGES] =  //////////////////////////////////////////////////////////////
	{
		Edge(v[0], v[1], 1), Edge(v[1], v[0], 1),
		Edge(v[0], v[5], 1), Edge(v[5], v[0], 1),
		Edge(v[1], v[2], 1), Edge(v[2], v[1], 1),
		Edge(v[1], v[6], 1), Edge(v[6], v[1], 1),
		Edge(v[6], v[7], 1), Edge(v[7], v[6], 1),
		Edge(v[6], v[11], 1), Edge(v[11], v[6], 1),

		Edge(v[7], v[8], 1), Edge(v[8], v[7], 1),
		Edge(v[8], v[3], 1), Edge(v[3], v[8], 1),
		Edge(v[8], v[13], 1), Edge(v[13], v[8], 1),
		Edge(v[13], v[14], 1), Edge(v[14], v[13], 1),
		Edge(v[14], v[9], 1), Edge(v[9], v[14], 1),
		Edge(v[9], v[4], 1), Edge(v[4], v[9], 1),
		Edge(v[14], v[19], 1), Edge(v[19], v[14], 1),
		
		Edge(v[6], v[11], 1), Edge(v[11], v[6], 1),
		Edge(v[11], v[10], 1), Edge(v[10], v[11], 1),
		Edge(v[10], v[15], 1), Edge(v[15], v[10], 1),
		Edge(v[15], v[20], 1), Edge(v[20], v[15], 1),
		Edge(v[15], v[16], 1), Edge(v[16], v[15], 1),
		Edge(v[16], v[21], 1), Edge(v[21], v[16], 1),
		Edge(v[21], v[22], 1), Edge(v[22], v[21], 1),
		Edge(v[22], v[17], 1), Edge(v[17], v[22], 1),
		Edge(v[17], v[12], 1), Edge(v[12], v[17], 1),
		Edge(v[17], v[18], 1), Edge(v[18], v[17], 1),
		Edge(v[18], v[19], 1), Edge(v[19], v[18], 1),
		Edge(v[18], v[23], 1), Edge(v[23], v[18], 1),

	};


	Graph simpleGraph("GRAPH_SQUARE_25_NODES", NUM_NODES);
	cout << "Inserting vertices .." << endl;
	for (int i = 0; i < NUM_NODES; i++)
	{
		simpleGraph.insertVertex(v[i]);
	}

	VrtxList vrtxLst;
	simpleGraph.vertices(vrtxLst);
	int count = 0;
	cout << "Inserted vertices: ";
	for (VrtxItor vItor = vrtxLst.begin(); vItor != vrtxLst.end(); ++vItor) {
		cout << *vItor << " ";
	}

	cout << endl;
	cout << "Inserting edges .." << endl;
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]);
	}
	cout << "Inserted edges: " << endl;
	count = 0;
	EdgeList egLst;
	simpleGraph.edges(egLst);
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		cout << *p << ", ";
		if (count % 5 == 0)
			cout << endl;
	}


	cout << endl;
	cout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.printGraph();  /////////////////////////////////////////////
	cout << "Testing dfsGraph..." << endl;
	DepthFirstSearch dfsGraph(simpleGraph);
	VrtxList path;
	dfsGraph.showConnectivity();   ///정점간의 간선의 distance를 한눈에 볼 수 있게 표 형태로 출력 

	dfsGraph.findPath(v[0], v[15], path);   //// v[0] -> v[15]로 가는 경로
	cout << "\nPath(" << v[0] << " = > " << v[15] << ") : ";
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		cout << *vItor << " ";
	cout << endl;

	dfsGraph.findPath(v[15], v[0], path);   /// v[15] -> v[0]으로 가는 경로
	cout << "\nPath(" << v[15] << " = > " << v[0] << ") : ";
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		cout << *vItor << " ";
	cout << endl;
}