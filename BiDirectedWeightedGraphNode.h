#include <vector>
using namespace std;

class BiDirectedWeightedGraphNode
{
private:
	int index;
	vector<pair<int, int>> neighbours;	// pair.first is index of destination node, pair.second is weight

public:
	// constructors
	BiDirectedWeightedGraphNode(int index1) {
		index = index1;
		neighbours.clear();
	}
	BiDirectedWeightedGraphNode(int index1, int index2, int weight) {
		index = index1;
		pair<int, int> p;
		p.first = index2;
		p.second = weight;
		neighbours.push_back(p);
	}

	// getters and setters
	int getIndex() {
		return index;
	}
	void setIndex(int i) {
		index = i;
	}
	vector<pair<int, int>> getNeighbours() {
		return neighbours;
	}
	void setNeighbours(vector<pair<int, int>> p) {
		neighbours = p;
	}

	// add a pair to neighbours
	void addneighbour(int i, int w) {
		// i is index, w is weight
		pair <int, int> p;
		p.first = i;
		p.second = w;
		// what if p is already in neighbours?
		neighbours.push_back(p);
	}

};




