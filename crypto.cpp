#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct coin {
	long long int num_proc;
	long long int cost;

	coin(long long int _num_proc, long long int _cost)
		: num_proc(_num_proc)
		, cost(_cost) {}
};
long long int n, buget;
vector <struct coin> coins;

void read_input() {
	long long int num_proc, cost;
	ifstream fin("crypto.in");
	fin>> n >> buget;
	for (long long int i = 0; i < n; i++) {
		fin >> num_proc >> cost;
		coins.push_back(coin(num_proc, cost));
	}
	fin.close();
}

void print_output(int result) {
	ofstream fout("crypto.out");
	fout << result;
	fout.close();
}

bool compare(coin c1, coin c2) {
	return (c1.num_proc < c2.num_proc);
}

int main() {
	long long int cost_total = 0, i = 0;
	read_input();

	std::sort(coins.begin(), coins.end(), compare);
	long long int prod_min = coins[0].num_proc;
	for (i = 0; i < n - 1; i++) {
		if (buget <= 0) {
			break;
		}
		cost_total += coins[i].cost;
		if (coins[i].num_proc != coins[i+1].num_proc) {
			if (prod_min + (buget/cost_total) >= coins[i+1].num_proc) {
				buget -= cost_total * (coins[i+1].num_proc - prod_min);
				prod_min = coins[i+1].num_proc;
			} else {
				prod_min += buget /cost_total;
				buget = 0;
				break;
			}
		}
	}
	cost_total += coins[n-1].cost;
	prod_min += buget / cost_total;

	print_output(prod_min);
	return 0;
}
