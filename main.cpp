#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

bool isFloat(string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f;
	return iss.eof() && !iss.fail();
}

float vectorDistance(vector<string> a, vector<string> b) {
	float distance = 0;
	int l = a.size() - 1;
	for (int i = 0; i < l; i++) {
		distance += pow(stof(b[i]) - stof(a[i]), 2);
	}
	distance = sqrt(distance);
	return distance;
}

int main(int argc, char* argv[]) {
	string filename;
	int k;
	if (argc < 2) {
		cout << "HELP:\n";
		cout << "<csv file path> <k>\n";
		filename = "iris.csv";
		k = 3;
		//return 0;
	}
	else {
		filename = argv[1];
		k = atoi(argv[2]);
	}
    vector< vector<string> > data;
    ifstream myfile("C:\\Users\\root\\source\\repos\\knn\\iris.csv");
    string buffer;
    vector<string> label;
    while (myfile.peek() != EOF) {
        getline(myfile, buffer);
        int l = buffer.size();
        int idx = -1;
        vector <string> temp;
        for (int i = 0; i < l; i++) {
            if (buffer[i] == ',' || buffer[i] == '\n') {
                temp.push_back(buffer.substr(idx + 1, i - idx - 1));
                idx = i;
            }
        }
        temp.push_back(buffer.substr(idx + 1, l));
            data.push_back(temp);
    }
    vector<string> t = data[0];
    int l = data.size()-1;
    int yidx = data[0].size()-1;
    vector<pair<float, string>> v;
    for (int i = 0; i < l; i++) {
        float distance = vectorDistance(data[i], data[0]);
        v.push_back(pair<float, string>(distance, data[i][yidx]));
    }
    vector<pair<float, string> >::iterator iter;
    sort(v.begin(), v.end());
    map<string, int> counters;
    for (int i = 0; i < k; i++) {
        if (counters.find(v[i].second) == counters.end()) {
            counters.insert(pair<string,int>(v[i].second,0));
        }
        else {
            counters[v[i].second] += 1;
        }
    }
    //sort(counters.begin(), counters.end());
    map<string, int>::iterator it = counters.begin();
    for (map<string, int>::iterator it2 = counters.begin(); it2 != counters.end(); ++it2)
    {
        if (it2->second > it->second)
            it = it2;
    }
    cout << it->first << endl;
	getchar();
}