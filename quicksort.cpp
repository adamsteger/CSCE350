// Copyright 2022 Adam Steger
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


int partition(vector<float> &v, int start, int end) {
    int pivot = start;
    int j = end;
    for (int i = end; i >= start; --i) {
        if (v[i] >= v[pivot]) {
            swap(v[i], v[j]);
            --j;
        }
    }
    swap(v[j], v[pivot]);
    return j;
}

void quicksort(vector<float> &v, int start, int end) {
    if (start < end) {
        int s = partition(v, start, end);
        quicksort(v, start, s-1);
        quicksort(v, s+1, end);
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
    quicksort(v, 0, v.size()-1);
    printVector(v);
}
