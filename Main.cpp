
/*
 *  C++ Assignment01 Main.cpp
 */


#include "Matrix.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const double p{ 0.85 };

int main()
{
    string filename;
    ifstream f1;

    cout << "Please write the filename that you want to open: " << endl;

    getline(cin, filename);
    f1.open(filename);

    string checking;
    int range = 0;

    if (f1.is_open()) {
        while (getline(f1, checking)) {
            range++;
        }
        f1.close();
    }
    else {cout << "Cannot Open the File, Please Try Again." << endl;}

    Matrix G(range);
    cout << "Printing Initial Matrix :  \n" << G << endl;
    f1.open(filename);
    cout << "Printing Matrix checking data import : \n" << G << endl;

    Matrix S = G.outDegree();
    cout << "Printing OutDegree to check if Sum is Zero : \n\n" << S << endl;
    S.randomWalk(p);
    cout << "Printing Connectivity Matrix after the randomwalk : \n\n" << S << endl;

    Matrix Q(range);
    Q.everyOne();
    cout << "Printing Matrix Q : \n\n" << Q << endl;
    Q.randomWalk((1-p));
    cout << "Printing new Matrix Q after multiplication : \n\n" << Q << endl;

    Matrix M = S + Q;
    cout << "Printing Matrix M : \n\n"<< M << endl;

    Matrix rank(2);
    rank.fillOne();
    Matrix oldRank = rank;

    cout << "Printing Matrix rank : " << endl;
    oldRank.print();

    Matrix newRank = rank.multiplication(M);
    cout << "Printing new rank :" << endl;
    newRank.print();
    cout << endl;

    while(oldRank != newRank) {
        oldRank = newRank;
        newRank = newRank.multiplication(M);
    }

    rank = newRank;
    rank.print();

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
