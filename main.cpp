#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <cassert>

using namespace std;

vector<vector<int>> gen_all_permutations_and_signs(int N) {
    vector<vector<int>> result;
    vector<int> range(N);
    function<vector<int> (int n)> order_sings = [&order_sings] (int n) {
        if (n == 1) {
            vector<int> res = {1};
            return res;
        }
        vector<int> res = order_sings(n-1);
        vector<int> revers;
        for (const  auto &i:res) {
            revers.push_back(i*(-1));
        }
        for (int i = 0; i < n-1; ++i) {
            res.insert(res.end(), revers.begin(), revers.end());
        }
        return res;
    };
    auto signs = order_sings(N);
    iota(range.begin(), range.end(), 0);
    function<void (vector<int> &vec, int l, int r)> permute = [&result, &permute, &signs] (vector<int> &vec, int l, int r) {
        if (l == r) {
            vec.push_back(signs[result.size()]);
            result.emplace_back(vec.begin(), vec.end());
            vec.pop_back();
        } else {
            for (int i = l; i <= r; ++i) {
                swap(vec[l], vec[i]);
                permute(vec, l + 1, r);
                swap(vec[l], vec[i]);
            }
        }
    };
    permute(range, 0, range.size() - 1);
    return result;
}

double Determinant(vector <vector<double>> A, int size){
    double result = 0;
    auto pm = gen_all_permutations_and_signs(size);
//    function<void(const vector<int> &v)> print = [](const vector<int> &v) {
//        for(const  auto &i:v){
//            cout << i << " ";
//        }
//        cout << "\n";
//    };
    for (const auto &i:pm) {
        double item = i[size];
        for (int j = 0; j < size; ++j) {
            item *= A[j][i[j]];
        }
        result += item;
//        print(i);
    }
    return result;
}

int main(int argc, char** argv) {
    int n = 4;


//    assert(pm.size() == 24);


    if (argc == 0) {
        cout << "No arguments!" << endl;
        return 0;
    }
    ifstream inf(argv[1]);
    if (!inf) {
        cerr << "Uh oh, file could not be opened for reading!";
        exit(1);
    }
    vector <double> numbers;
    while (inf) {
        double number;
        inf >> number;
        numbers.push_back(number);
    }
    numbers.pop_back();
    int size_of_matrix = int(sqrt(numbers.size()));

    vector <vector <double>> matrix;

    for (int i = 0; i < size_of_matrix; i++) {
        vector<double> str;
        for (int j = 0; j < size_of_matrix; j++) {
            str.push_back(numbers[i*size_of_matrix+j]);
        }
        matrix.push_back(str);

    }
    cout << Determinant(matrix, size_of_matrix) << endl;
    return 0;
}
