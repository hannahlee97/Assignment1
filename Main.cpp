
/*
 *  C++ Assignment01 Main.cpp
 */


#include "Matrix.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const double p{0.85};

int main() {
    string filename;
    fstream f1;

    cout << "Please write the filename that you want to open: " << endl;

    getline(cin, filename);
    f1.open(filename);

    string checking;
    int range = 0;

    if (f1.is_open()) {
        while (getline(f1, checking)) {
            range++;
        }
    } else {
        cout << "Cannot Open the File, Please Try Again." << endl;
    }
    f1.close();

    Matrix G(range);
    f1.open(filename);

    if (f1.is_open()) {
        int r = 0;
        int c = 0;
        int max_c = range;
        double v;

        if (c == max_c) {
            c = 0;
            r++;
        }
        while (f1 >> v) {
            G.set_value(r, c, v);
            c++;
        }
        f1.close();
    } else {
        cout << "Cannot Open the File, Please Try Again." << endl;
    }
    f1.close();

    Matrix S = G.outDegree();

    S.randomWalk(p);

    Matrix Q(range);
    Q.everyOne();
    Q.randomWalk((1 - p));

    Matrix M = S + Q;

    Matrix rank(2);
    rank.fillOne();
    Matrix oldRank = rank;

    Matrix newRank = rank.multiplication(M);

    while (oldRank != newRank) {
        oldRank = newRank;
        newRank = newRank.multiplication(M);
    }

    rank = newRank;

    rank.scaleRank();
    rank.print();


    ofstream f2;
    f2.open("Connectivity.txt");

    if (f2.is_open()) {
        int range = rank.get_dimension() * rank.get_dimension();
        for (int i = 0; i < range; ++i) {
            f2 << rank.get_value(i) << endl;
        }
    }

    f2.close();

    system("STOP");
    return 0;
}
