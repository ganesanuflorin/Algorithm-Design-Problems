#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct stock {
	int currentValue;
	int minValue;
	int maxValue;

	stock(int _currentValue, int _minValue, int _maxValue)
		:currentValue(_currentValue)
		, minValue(_minValue)
		, maxValue(_maxValue) {}
};

int n, b, l;
vector <struct stock> pocket;


void read_input() {
	int currentValue, minValue, maxValue;
	ifstream fin("stocks.in");
	fin>> n >> b >> l;
	pocket.push_back(stock(0, 0, 0));
	for (int i = 1; i <= n; i++) {
		fin >> currentValue >> minValue >> maxValue;
		pocket.push_back(stock(currentValue, minValue, maxValue));
	}
	fin.close();
}



void print_output(int result) {
	ofstream fout("stocks.out");
	fout << result;
	fout.close();
}

int main() {
	int i, j, k, profit = 0, inves = 0, maxLose = 0, aux;

	read_input();
	vector <vector <vector <int>>> dp
	(n + 1, vector <vector <int>> (b + 1, vector <int> (l + 1)));

	for(j = 0; j <= b; j++) {
		for (k = 0; k <= l; k++) {
			dp[0][j][k] = 0;
		}
	}

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= b; j++) {
			for (k = 1; k <= l; k++) {
				inves = pocket[i].currentValue;
				maxLose = pocket[i].currentValue - pocket[i].minValue;
				profit = pocket[i].maxValue - pocket[i].currentValue;
				dp[i][j][k] = dp[i - 1][j][k];
				if ((j - inves) >= 0 && (k - maxLose) >= 0) {
					aux = dp[i - 1][j - inves][k - maxLose] + profit;
					dp[i][j][k] = max(dp[i][j][k], aux);
				}
			}
		}
	}

	print_output(dp[n][b][l]);
	return 0;
}
