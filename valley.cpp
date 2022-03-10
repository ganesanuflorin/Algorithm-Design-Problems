#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

std::vector<long long int> valley;
long long int n;

void read_input() {
	long long int num;
	ifstream fin("valley.in");
	fin >> n;
	for (long long int i = 0; i < n; i++) {
		fin >> num;
		valley.push_back(num);
	}
	fin.close();
}

void print_output(long long int result) {
	ofstream fout("valley.out");
	fout << result;
	fout.close();
}
int main() {
	long long int i = 0, count = 0;
	read_input();
	long long int index = 0;
	long long int min = valley[0];

	for (i = 0; i < n; i++) {
		if (valley[i] < min) {
			min = valley[i];
			index = i;
		}
	}
	for (i = 0; i < index; i++) {
		if (valley[i] < valley[i+1]) {
			count += (valley[i+1] - valley[i]);
			valley[i+1] = valley[i];
		}
	}
	for (i = n-1 ; i > index; i--) {
		if (valley[i-1] > valley[i]) {
			count += (valley[i-1] - valley[i]);
			valley[i-1] = valley[i];
		}
	}

	if (min == valley[n-1]) {
		count += (valley[n-2] - valley[n-1]);
	}

	if (min == valley[0]) {
		count += (valley[1] - valley[0]);
	}
	print_output(count);
	return 0;
}
