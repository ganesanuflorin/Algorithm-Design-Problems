#include <algorithm>
#include <fstream>
#include <vector>

#define MAX 9223372036854775807;

using namespace std;

struct moutain {
	long long height;
	long long cost;

	moutain(long long _height, long long _cost)
		: height(_height)
		, cost(_cost) {}
};
long long n;
vector <struct moutain> mountains;

void read_input() {
	long long height, cost;
	ifstream fin("ridge.in");
	fin>> n;
	mountains.push_back(moutain(0, 0));
	for (long long i = 0; i < n; i++) {
		fin >> height >> cost;
		mountains.push_back(moutain(height, cost));
	}
	fin.close();
}

void print_output(long long result) {
	ofstream fout("ridge.out");
	fout << result;
	fout.close();
}

long long minWith3(long long min1, long long min2, long long min3) {
	return ((min1 < min2) && (min1 < min3)) ? min1
	: min2 < min3 ? min2
	: min3;
}
long long minWith2(long long min1, long long min2) {
	return (min1 < min2) ? min1
	: min2;
}

int main() {
    long long i, aux;
    read_input();
	vector <vector <long long>> dp(n + 1, vector <long long> (3, 0));

	for (i = 1; i <= n; i++) {
		dp[i][0] = minWith3(dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]);
		dp[i][1] = mountains[i].cost + minWith3(dp[i - 1][0],
											   dp[i - 1][1],
											   dp[i - 1][2]);
		dp[i][2] = 2 * mountains[i].cost + minWith3(dp[i - 1][0],
													dp[i - 1][1],
													dp[i - 1][2]);

		if ((mountains[i - 1].height - mountains[i].height) == -2) {
			dp[i][0] = minWith3(dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]);
			dp[i][1] = mountains[i].cost + minWith3(dp[i - 1][0],
											       dp[i - 1][1],
											       dp[i - 1][2]);

			dp[i][2] = 2 * mountains[i].cost + minWith2(dp[i - 1][1],
										   		   		dp[i - 1][2]);
		 }

		if ((mountains[i - 1].height - mountains[i].height) == -1) {
			dp[i][0] = minWith3(dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]);
			dp[i][1] = mountains[i].cost + minWith2(dp[i - 1][1], dp[i - 1][2]);
			dp[i][2] = 2 * mountains[i].cost + minWith2(dp[i - 1][0], dp[i - 1][2]);
		}

		if ((mountains[i - 1].height - mountains[i].height) == 1) {
			dp[i][0] = minWith2(dp[i - 1][0], dp[i - 1][2]);
			dp[i][1] = mountains[i].cost + minWith2(dp[i - 1][0], dp[i - 1][1]);
			dp[i][2] = 2 * mountains[i].cost + minWith3(dp[i - 1][0],
											       		dp[i - 1][1],
											       		dp[i - 1][2]);
		}

		if ((mountains[i - 1].height - mountains[i].height) == 2) {
			dp[i][0] = minWith2(dp[i - 1][0], dp[i - 1][1]);
			dp[i][1] = mountains[i].cost + minWith3(dp[i - 1][0],
											        dp[i - 1][1],
											        dp[i - 1][2]);
			dp[i][2] = 2 * mountains[i].cost + minWith3(dp[i - 1][0],
														dp[i - 1][1],
														dp[i - 1][2]);
		}

		if ((mountains[i - 1].height - mountains[i].height) == 0) {
			dp[i][0] = minWith2(dp[i - 1][1], dp[i - 1][2]);
			dp[i][1] = mountains[i].cost + minWith2(dp[i - 1][0], dp[i - 1][2]);
			dp[i][2] = 2 * mountains[i].cost + minWith2(dp[i - 1][0], dp[i - 1][1]);
		}

		if (mountains[i].height < 2) {
			if (mountains[i].height == 1) {
				dp[i][2] = MAX;
			} else {
				dp[i][2] = MAX;
				dp[i][1] = MAX;
			}
		}
	}
	aux = minWith3(dp[n][0], dp[n][1], dp[n][2]);
	print_output(aux);
    return 0;
}
