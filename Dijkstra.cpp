#include <iostream>
#include <climits>
#include "BiDirectedWeightedGraphNode.h"
#include <algorithm>
using namespace std;

// declaration of methods
int minimumDistance(vector<int>, vector<bool>, int);
vector<int> dijkstra(vector<BiDirectedWeightedGraphNode>, int, int);
void printPath(vector<int>);

int main()
{
	BiDirectedWeightedGraphNode node0 = BiDirectedWeightedGraphNode(0, 1, 2);
	node0.addneighbour(2, 6);
	node0.addneighbour(3, 4);
	BiDirectedWeightedGraphNode node1 = BiDirectedWeightedGraphNode(1, 3, 3);
	node1.addneighbour(4, 2);
	BiDirectedWeightedGraphNode node2 = BiDirectedWeightedGraphNode(2, 3, 6);
	node2.addneighbour(6, 3);
	BiDirectedWeightedGraphNode node3 = BiDirectedWeightedGraphNode(3, 2, 4);
	node3.addneighbour(5, 3);
	BiDirectedWeightedGraphNode node4 = BiDirectedWeightedGraphNode(4, 5, 7);
	BiDirectedWeightedGraphNode node5 = BiDirectedWeightedGraphNode(5);
	BiDirectedWeightedGraphNode node6 = BiDirectedWeightedGraphNode(6, 5, 1);
	node6.addneighbour(0, 2332);
	BiDirectedWeightedGraphNode node7 = BiDirectedWeightedGraphNode(7, 5, 1);
	node7.setNeighbours(node0.getNeighbours());

	vector<BiDirectedWeightedGraphNode> graph{node0, node1, node2, node3, node4, node5, node6, node7};
	
	int startingNode{};
	int destinationNode{};
	int ln = graph.size();	// graph length
	// choose the starting node and destination node
	cout << "Enter the starting node: ";
	cin >> startingNode;
	while (startingNode < 0 || startingNode >= ln) {
		cin.clear();
		system("cls");
		cout << "Enter the starting node: ";
		cin >> startingNode;
	}

	cout << "Enter the destination node: ";
	cin >> destinationNode;
	while (destinationNode < 0 || destinationNode >= ln) {
		cin.clear();
		system("cls");
		cout << "Enter the destination node: ";
		cin >> destinationNode;
	}


	// d is the shortest path from starting node to destination node
	vector<int> d = dijkstra(graph, startingNode, destinationNode);

	// print shortest path
	printPath(d);
}


int minimumDistance(vector<int> dist, vector<bool> s, int len)
{
	// returns index with minimum distance with s[i] false
	// if no such index exists return -1
	
	int min = INT_MAX, index = -1;
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == false && dist[i] <= min)
		{
			min = dist[i];
			index = i;
		}
	}

	return index;
}
vector<int> dijkstra(vector<BiDirectedWeightedGraphNode> graph, int sourceNode, int destinationNode)
{
	// deal with trivial case sourceNode == destinationNode
	if (sourceNode == destinationNode) {
		return { sourceNode };
	}

	// distances[i] is distance from node i to sourceNode
	// set[i] is true if the minimum distances[i] has been set

	vector<int> distances{};
	vector<bool> set{};
	int len = graph.size();

	// initialise the distance from sourceNode to each vertex to int max
	for (int i = 0; i < len; i++)
	{
		distances.push_back(INT_MAX);
		set.push_back(false);
	}
	// set distance from sourceNode to sourceNode to 0
	distances[sourceNode] = 0;

	// update distances until we are done
	bool done = false;
	while (!done) {
		int u = minimumDistance(distances, set, len);
		// if u is -1 we are done 
		if (u == -1) {
			break;
		}
		set[u] = true;
		// update distances considering paths through u
		int j = graph[u].getIndex();
		for (pair<int,int> neigh:graph[u].getNeighbours()) {
			if (set[neigh.first] == false &&  distances[u] != INT_MAX && distances[u] + neigh.second < distances[neigh.first])
				distances[neigh.first] = distances[u] + neigh.second;
		}
	}

	// if no path exists return {-1}
	if (distances[destinationNode] == INT_MAX) {
		return { -1 };
	}

	// working backwards from the destination to find a shortest path
	vector<int> path{};
	path.push_back(destinationNode);
	done = false;
	int j = destinationNode;
	while (!done) {
		// check node i goes to j
		for (int i = 0; i < len; ++i) {
			for (pair<int,int> neigh: graph[i].getNeighbours()) {
				if (neigh.first == j && neigh.second + distances[i] == distances[j]) {
					path.push_back(i);
					j = i;
					if (j == sourceNode) {
						// we are done
						done = true;
						break;
					}
				}
			}
		}
	}

	// reverse path vector to display path in the correct order
	reverse(path.begin(), path.end());

	return path;
}
void printPath(vector<int> d) {
	// if no path exists
	if (d[0] == -1) {
		cout << "No path exists";
	}
	else {
		int n = d.size();
		cout << "\nShortest Path [";
		for (int i = 0; i < n; ++i)
			i == n - 1 ? cout << d[i] : cout << d[i] << " ";
		cout << "]";
	}
}


/*
EXTENSION:
starting node must go through middle node
then to destination
dijk(sn,mn)
dijk(mn, d)
add these together and print
*/