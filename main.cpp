#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>
#include <hpx/init.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>
#include <vector>

using namespace std;

void printMatrix(const vector<int>& matrix, int numRows, int numCols) {
    cout << "[\n";
    for (int i = 0; i < numRows; i++) {
        cout << "\t[";
        for (int j = 0; j < numCols; j++) {
            int idx = (i * numCols) + j;
            cout << matrix.at(idx);
            if (j != numCols - 1) {
                cout << ',';
            }
        }

        cout << "]";
        if (i != numRows - 1) {
            cout << ",";
        }

        cout << "\n";
    }
    cout << "]" << endl;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b, int n, int m, int p) {
    vector<int> result(n * p, 0);
    hpx::experimental::for_loop(hpx::execution::par, 0, n, [&](auto i) {
        hpx::experimental::for_loop(hpx::execution::par, 0, p, [&](auto j) {
            int idx = (i * n) + j;
            hpx::experimental::for_loop(hpx::execution::par, 0, m, [&](auto k) {
                int idxa = (i * m) + k;
                int idxb = (k * p) + j;
                result[idx] += a.at(idxa) * b.at(idxb);
            });
        });
    });

    return result;
}

int main() {
    int matrixOneRows;
    int matrixOneCols;
    int matrixTwoRows;
    int matrixTwoCols;

    // Get dimensions of matrix one
    cout << "How many rows will matrix one have?" << endl;
    cin >> matrixOneRows;
    cout << "How many columns will matrix one have?";
    cout << "\n\tThis corresponds to how many rows matrix two has" << endl;
    cin >> matrixOneCols;

    // Get dimensions of matrix two
    matrixTwoRows = matrixOneCols;
    cout << "How many columns will matrix two have?" << endl;
    cin >> matrixTwoCols;

    vector<int> matrixOne(matrixOneRows * matrixOneCols);
    vector<int> matrixTwo(matrixTwoRows * matrixTwoCols);

    // Get values for matrix two
    cout << "Please enter all the values for matrix one newline separated, by column then by row." << endl;
    for (int i = 0; i < matrixOneRows * matrixOneCols; i++) {
        int userInput;
        cin >> userInput;
        matrixOne[i] = userInput;
    }

    printMatrix(matrixOne, matrixOneRows, matrixOneCols);

    // Get values for matrix two
    cout << "Please enter all the values for matrix two newline separated, by column then by row." << endl;
    for (int i = 0; i < matrixTwoCols * matrixTwoRows; i++) {
        int userInput;
        cin >> userInput;
        matrixTwo[i] = userInput;
    }

    printMatrix(matrixTwo, matrixTwoRows, matrixTwoCols);

    // Multiply and print result
    vector<int> result = multiply(matrixOne, matrixTwo, matrixOneRows, matrixTwoRows, matrixTwoCols);
    printMatrix(result, matrixOneRows, matrixTwoCols);
}
