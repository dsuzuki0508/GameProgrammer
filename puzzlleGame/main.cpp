#include<iostream>
#include<vector>
#include<string>
#include <assert.h>
using namespace std;

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first + r.first,l.second + r.second };
}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first - r.first,l.second - r.second };
}

vector<string> dist = {
   "        ",
   "  ..    ",
   "        ",
   "        ",
   "        ",
   "        ",
   "        ",
   "        "
};
vector<string>  map = {
	"########",
	"#      #",
	"# oo   #",
	"#      #",
	"#      #",
	"########"
};
pair<int, int> pos = make_pair(1,5);

void draw(){
	for (int i= 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (dist[i][j] == '.') {
				if (pos == make_pair(i, j))cout << 'P';
				else if (map[i][j] == 'o') cout << 'O';
				else cout << '.';
			}
			else {
				if (pos == make_pair(i, j))cout << 'p';
				else cout << map[i][j];
			}
		}
		cout << endl;
	}
}

pair<int,int> getInput() {
	char c;
	cout << "a:left s:right w:up z:down. command?" << endl;
	cin >> c;
	auto tmp = pos;
	switch (c)
	{
	case 'a':
		tmp.second -= 1;
		break;
	case 's':
		tmp.second += 1;
		break;
	case 'w':
		tmp.first -= 1;
		break;
	case 'z':
		tmp.first += 1;
		break;

	default:
		break;
	}
	if (map[tmp.first][tmp.second] == '#') {
		tmp = pos;
	}
	if (map[tmp.first][tmp.second] == 'o') {
		auto tmp2 = tmp + tmp - pos;
		if (map[tmp2.first][tmp2.second] != ' ') {
			tmp = pos;
		}
	}
	return tmp;
}

void updateGame(pair<int, int> next) {
	if (map[next.first][next.second] == 'o') {
		auto tmp = next + next - pos;
		assert(map[tmp.first][tmp.first] == ' ');
		if (map[tmp.first][tmp.second] != ' ') {
			next = pos;
			return;
		}
		map[tmp.first][tmp.second] = 'o';
		map[next.first][next.second] = ' ';
	}

	assert(map[next.first][next.second] == ' ');
	pos = next;
}

bool isClearedState() {
	for (int i = 0; i < dist.size(); i++) {
		for (int j = 0; j < dist[i].size(); j++) {
			if (dist[i][j] == '.' && map[i][j] != 'o') {
				return false;
			}
		}
	}
	return true;
}

int main() {
	draw();
	while (true) {
		auto next = getInput();
		updateGame(next);
		draw();
		if (isClearedState()) break;
	}
	cout << "Congratulation's! you won." << endl;

	return 0;
}