#include "Hashtable.h"
#include "avlbst.h"
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    clock_t start;
    double duration;

    if (argc < 6) {
        cout << "Not Enough Command Line Arguments" << endl;
        return -1;
    }

    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    int x = atoi(argv[3]);
    int d = atoi(argv[4]);
    int r = atoi(argv[5]);

    vector<string> words;

    // Parsing and Storing
    string temp;
    while (ifile >> temp) {
        string cur = "";
        for (unsigned int i = 0; i < temp.size(); i++) {
            if (temp[i] >= 'a' && temp[i] <= 'z') {
                cur += temp[i];
            } else if (temp[i] >= 'A' && temp[i] <= 'Z') {
                cur += (temp[i] - 'A' + 'a');
            } else {
                continue;
            }
        }
        if (!cur.empty() && cur.size() <= 28) {
            words.push_back(cur);
        }
    }
    // clock starts
    start = clock();

    // initialize data strutures
    for (int i = r; i > 0; i--) {
        if (x != 3) {
            Hashtable temp(d, x);
            for (string i : words) {
                temp.add(i);
            }
        } else {
            AVLTree<string, int> avl;
            for (string i : words) {
                auto it = avl.find(i);
                if (it == avl.end()) {
                    avl.insert(make_pair(i, 1));
                } else {
                    (*it).second++;
                }
            }
        }
    }
    // clock ends
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    // output data
    if (x != 3) {
        Hashtable hash(d, x);
        for (string i : words) {
            hash.add(i);
        }
        hash.reportAll(ofile);
    } else {
        AVLTree<string, int> avl;
        for (string i : words) {
            auto it = avl.find(i);
            if (it == avl.end()) {
                avl.insert(make_pair(i, 1));
            } else {
                (*it).second++;
            }
        }
        for (auto it : avl) {
            ofile << it.first << " " << it.second << endl;
        }
    }
    // cout duration
    std::cout << duration / r << endl;
}
