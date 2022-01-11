#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;

auto boxlut = vi{ 0, 0, 0, 3, 3, 3, 6, 6, 6 };

auto q = vvi{};
auto toCheck = vii{};

void presolve() {
	auto nosolve = vii{};

	auto count = int{ 0 };
	auto sum = int{ 0 };

	while (!toCheck.empty()) {
		auto f = toCheck.back();
		toCheck.pop_back();

		// row
		count = 0;
		sum = 0;
		for (int i = 0; i < 9; ++i) {
			if (0 != q[f.first][i]) {
				count += 1;
				sum += q[f.first][i];
			}
		}

		if (8 == count) {
			q[f.first][f.second] = 45 - sum;
			continue;
		}

		// col
		count = 0;
		sum = 0;
		for (int i = 0; i < 9; ++i) {
			if (0 != q[i][f.second]) {
				count += 1;
				sum += q[i][f.second];
			}
		}

		if (8 == count) {
			q[f.first][f.second] = 45 - sum;
			continue;
		}

		// box
		count = 0;
		sum = 0;
		const auto& t = boxlut[f.first];
		const auto& l = boxlut[f.second];
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (0 != q[t + i][l + j]) {
					count += 1;
					sum += q[t + i][l + j];
				}
			}
		}

		if (8 == count) {
			q[f.first][f.second] = 45 - sum;
			continue;
		}

		// no solve
		nosolve.push_back(f);
	}

	toCheck = nosolve;
}

bool check(int r, int c, int x) {
	// 행/열 체크
	for (int i = 0; i < 9; ++i) {
		if (q[r][i] == x || q[i][c] == x) {
			return false;
		}
	}

	// 박스 체크
	const auto& t = boxlut[r];
	const auto& l = boxlut[c];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (q[t + i][l + j] == x) {
				return false;
			}
		}
	}

	return true;
}

bool solve(int begin) {
	if (begin == toCheck.size()) {
		return true;
	}

	const auto& now = toCheck[begin];

	for (int x = 1; x <= 9; ++x) {
		if (!check(now.first, now.second, x)) {
			continue;
		}

		q[now.first][now.second] = x;

		if (solve(begin + 1))
		{
			return true;
		}

		q[now.first][now.second] = 0;
	}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	q = vvi(9, vi(9));
	toCheck = vii{};
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			int x;
			cin >> x;

			if (0 == x) {
				toCheck.push_back({ r, c });
			}

			q[r][c] = x;
		}
	}

	presolve();

	if (0 < toCheck.size()) {
		solve(0);
	}

	for (const auto& vec : q) {
		for (const auto& x : vec) {
			cout << x << ' ';
		}
		cout << '\n';
	}

	return 0;
}