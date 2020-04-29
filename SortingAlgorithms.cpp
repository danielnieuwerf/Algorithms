#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std::chrono;
using namespace std;

// function prototypes
void biDirectionalBubbleSort(vector<int>&);
void bubbleSort(vector<int>&);
void combSort(vector<int>&);
void compareAlgorithms();
void selectionSort(vector<int>&);
void write_csv(std::string, long long);
void heapSort(vector<int>&);
void convertHeap(vector<int>&, int, int);
void binaryInsertionSort(vector<int>&);
void introSort(vector<int>&);

// operator overloading
template <typename T>
ostream& operator<<(ostream&, const vector<T>&);

int main()
{
	// Initialise container for random ints
	vector<int> vec{};
	srand(time(0));
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand());
	}
	// Run the test 5000 times
	int x = 5001;
	while (--x) {
		for (int i = 0; i < 10; ++i) {
			vec[i] = rand();
		}
		auto start = high_resolution_clock::now();
		selectionSort(vec);
		auto stop = high_resolution_clock::now();

		// Calculate time in microseconds 
		auto duration = duration_cast<microseconds>(stop - start);

		cout << "\nTime taken by function: "
			<< duration.count() << " microseconds" << endl;

		// append result to textfile
		write_csv("selectionSort.txt", duration.count());
	}
}

/*
*	Utilities
*/
void write_csv(std::string filename, long long x) {
	// Insert vals into csv file or text file
	// seperated by commas

	// Create an output filestream object
	std::ofstream myFile(filename, std::ios_base::app);

	// Send data to the stream
	myFile << x << "," << endl;

	// Close the file
	myFile.close();
}
void compareAlgorithms() {
	cout << "Algorithm" << setw(20) << "Best Time" << setw(20) << "Average Time" <<
		setw(20) << "Worst Time" << setw(20) << "Space" << endl << endl;
	cout << "Bubble Sort" << setw(20) << "O(n)" << setw(20) << "O(n^2)" << setw(20) << "O(n^2)"
		<< setw(20) << "O(1)" << endl;

}

/*
*	Algorithms
*/
void bubbleSort(vector<int>& vec) {

	int n = vec.size();
	for (int i = 1; i < n; ++i) {
		bool swapped = false;

		for (int j = 0; j < n - i; ++j) {

			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
				swapped = true;
			}
		}

		if (!swapped) {
			return;
		}
	}
	return;
}
void biDirectionalBubbleSort(vector<int>& vec) {
	// alternate between bubble sort to the left and right
	// slightly better than bubble sort since it picks up "turtles"
	// "turtles" = small values near the end of the list 
	int n = vec.size();
	for (int i = 1; i < n; ++i) {
		bool swapped = false;

		for (int j = 0; j < n - i; ++j) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
				swapped = true;
			}
		}

		if (!swapped) {
			return;
		}

		swapped = false;
		for (int j = n - i - 1; j >= i; --j) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) {
			return;
		}
	}
	return;
}
void combSort(vector<int>& vec) {

}
void selectionSort(vector<int>& vec) {
	int n = vec.size();
	int f{};
	int l{};
	for (int i = 0; i < n; ++i) {
		int min = INT_MAX;
		for (int j = f; j < n; ++j) {
			if (vec[j] < min) {
				min = vec[j];
				l = j;
			}
		}
		swap(vec[f], vec[l]);
		++f;
	}
	return;
}
void convertHeap(vector<int>& vec, int len, int x)
{
	int largest = x;
	int left = 2 * x + 1;
	int right = 2 * x + 2;

	if (left < len && vec[left] > vec[largest]) {
		largest = left;
	}

	if (right < len && vec[right] > vec[largest]) {
		largest = right;
	}

	if (largest != x)
	{
		swap(vec[x], vec[largest]);
		convertHeap(vec, len, largest);
	}

	return;

}
void heapSort(vector<int>& vec)
{
	int len = vec.size();	// try figure out a way where this is not necessary to speed it up
	for (int i = len / 2 - 1; i >= 0; --i) {
		convertHeap(vec, len, i);
	}

	for (int i = len - 1; i >= 0; --i)
	{
		swap(vec[0], vec[i]);
		convertHeap(vec, i, 0);
	}
	return;
}
void introSort(vector<int>& vec) {
	sort(vec.begin(), vec.end());
}

void binaryInsertionSort(vector<int>& vec) {
	int n = vec.size();
	if (n == 0)
		return;
	vector<int> ans{};
	ans.push_back(vec[0]);
	ans.reserve(n);	// ans will be size n

	for (int i = 1; i < n; ++i) {
		// find where to insert num into ans
		int left = 0;
		int right = i - 1;
		int mid = 0;
		int x = vec[i];
		// binary search to find where to insert into ans
		while (left <= right) {
			mid = (left + right) / 2;
			if (x > ans[mid]) {
				left = mid + 1;
				mid = left;
			}
			else if (x < ans[mid]) {
				right = mid - 1;
				mid = right + 1;
			}
			else {
				break;
			}
		}
		// insert x into ans
		ans.insert(ans.begin() + mid, x);
	}

	//set vec
	vec = ans;
}

/*
*	Operator overloading
*/
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	int n = v.size();
	os << "[";
	for (int i = 0; i < n; ++i) {
		os << v[i];
		if (i != n - 1)
			os << ", ";
	}
	os << "]\n";
	return os;
}