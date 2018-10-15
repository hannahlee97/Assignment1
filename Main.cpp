// 다른건 다 못한다고 쳐도 그 2번 아웃풋하는거 에드 해야함 ㅠㅠㅠㅠㅠㅠ 이거라도 안하면 안됨
// 그리고 앞으로는 그냥 조온나 코드바꾸기!
// overload operator 왠만하면 넣고 싶은데ㅠㅠㅠㅠㅠㅠ
// 순서바꾸기, 하나씩 지워보

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
    ifstream f1;
    string filename;

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
    else {cout << "Cannot Open the File, Try Again." << endl;}

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
    cout << "Printing Matrix Q : \n" << Q << endl;
    Q.randomWalk((1-p));
    cout << "Printing new Matrix Q after multiplication : \n" << Q << endl;

    Matrix M = S + Q;
    cout << "Printing Matrix M : \n"<< M << endl;

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
