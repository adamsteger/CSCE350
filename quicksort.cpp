// Copyright 2022 Adam Steger
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


int partition(vector<float> &v, int start, int end) {
    int pivot = start;
    int j = end;
    int i = start;
    while (i <= j) {
        while (v[i] < v[pivot]) {
            i++;
        }
        while (v[j] > v[pivot]) {
            j--;
        }
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(vector<float> &v, int start, int end) {
    if (start < end) {
        int s = partition(v, start, end);
        quicksort(v, start, s-1);
        quicksort(v, s, end);
    }
}

void printVector(vector<float> &v) {
    ofstream out;
    out.open("output.txt");
    for (float i : v) {
        out << i << " ";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    fstream in(argv[1]);
    vector<float> v;
    if (in.is_open()) {
        string line;
        while (getline(in, line, ' ')) {
            float num = stof(line);
            v.push_back(num);
        }
    }
    in.close();
    auto start = high_resolution_clock::now();
    quicksort(v, 0, v.size()-1);
    auto finish = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(finish - start);
    cout << "Execution time: " << time.count() << " microseconds" << "\n";
    printVector(v);
}
