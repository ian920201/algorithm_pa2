#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

void MaximumPlanarSubset(int* points, int** M,  int n) {
    for (int i = 0; i < n; i++) {
        M[i][i] = 0;
    }
    for (int l = 1; l < n; l++) {
        for (int i = 0; i < n - l; i++) {
            int j = i + l;
            int k = points[j];
            if (!(i <= k && k <= j)) {
                M[i][j] = M[i][j - 1];
            }
            else if (k != i) {
                if (M[i][j - 1] > M[k + 1][j - 1] + 1 + M[i][k - 1]) {
                    M[i][j] = M[i][j - 1];
                }
                else {
                    M[i][j] = M[k + 1][j - 1] + 1 + M[i][k - 1];
                }
            }
            else {
                M[i][j] = M[i + 1][j - 1] + 1;
            }
        }
    }
}

void getChords(int* points, int** M, int i, int j, vector<int>& result) {
    if (i >= j) {
        return;
    }
    int k = points[j];
    if (M[i][j] == M[i][j - 1]) {
        getChords(points, M, i, j - 1, result);
    }
    else if (k != i && M[i][j] == M[k + 1][j - 1] + 1 + M[i][k - 1]) {
        result.push_back(points[j]);
        getChords(points, M, k + 1, j - 1, result);
        getChords(points, M, i, k - 1, result);
    }
    else {
        result.push_back(points[j]);
        getChords(points, M, i + 1, j - 1, result);
    }
}

void Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    vector<int> left(data.begin() + low, data.begin() + middle1 + 1);
    vector<int> right(data.begin() + middle2, data.begin() + high + 1);
    int i = 0;
    int j = 0;
    for (int k = low; k <= high; k++) {
        if (i < left.size() && (j >= right.size() || left[i] <= right[j])) {
            data[k] = left[i];
            i++;
        } 
        else {
            data[k] = right[j];
            j++;
        }
    }
}

void MergeSortSubVector(vector<int>& data, int low, int high) {
    if ((high - low) >= 1) {
        int middle1 = (high + low) / 2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

void MergeSort(vector<int>& data) {
    MergeSortSubVector(data, 0, data.size() - 1);
}

int main(int argc, char* argv[]) {
    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");
    int n;
    (void)!fscanf(in, "%d", &n);
    int* points = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < (n / 2); i++) {
        int start, end;
        (void)!fscanf(in, "%d", &start);
        (void)!fscanf(in, "%d", &end);
        points[start] = end;
        points[end] = start;
    }
    int** M = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        M[i] = (int*)malloc(sizeof(int) * n);
    }
    vector<int> result;
    MaximumPlanarSubset(points, M, n);
    fprintf(out, "%d\n", M[0][n - 1]);
    getChords(points, M, 0, n - 1, result);
    MergeSort(result);
    for (int i = 0; i < result.size(); i++) {
        fprintf(out, "%d %d", result[i], points[result[i]]);
        if (i != result.size() - 1) {
            fprintf(out, "\n");
        }
    }

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
    free(points);
    fclose(in);
    fclose(out);
    return 0;
}
