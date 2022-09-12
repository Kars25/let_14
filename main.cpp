#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;

double Determinant(vector <vector<double>> ls, int len){
    if (len == 1) {
        return ls[0][0];
    }
    if (len == 2) {
        return ls[0][0]*ls[1][1] - ls[0][1]*ls[1][0];
    }
    double result = 0;
    for (int i = 0; i < len; i++) {
        double monomial1 = 1;
        double monomial2 = 1;
        for (int j = 0; j < len; j++) {
            monomial1 = monomial1*ls[j][(i+j)%len];
            monomial2 = monomial2*ls[j][(len+i-j)%len];
        }
        result = result + monomial1 - monomial2;
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc == 0) {
        cout << "No arguments!" << endl;
        return 0;
    }
    ifstream inf(argv[1]);
    if (!inf) {
        cerr << "Uh oh, file could not be opened for reading";
        exit(1);
    }
    vector <double> numbers;
    while (inf) {
        double number;
        inf >> number;
        numbers.push_back(number);
    }
    numbers.pop_back();
    int count = numbers.size();
    count = int(sqrt(count));

    vector <vector <double>> matrix;

    for (int i = 0; i < count; i++) {
        vector<double> str;
        for (int j = 0; j < count; j++) {
            str.push_back(numbers[i*count+j]);
        }
        matrix.push_back(str);

    }
    cout << Determinant(matrix, count) << endl;
    return 0;
}
