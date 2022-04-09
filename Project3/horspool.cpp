// Copyright 2022 Adam Steger
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int* shiftTable(string pattern) {
    int table[27];
    int m = pattern.length();
    for (int i = 0; i < 27; i++) {
        table[i] = m;
    }
    for (int i = 0; i <= m - 2; i++) {
        table[pattern[i]] = m - 1 - i;
    }
    return table;
}

int horspool(string pattern, string text, int m) {
    int *table = shiftTable(pattern);
    int i = m - 1;
    int n = text.length();
    while (i <= n - 1) {
        int k = 0;
        while (k <= m-1 && pattern[m-1-k] == text[i-k]) {
            k++;
        }
        if (k == m) {
            return i - m + 1;
        } else {
            int num = static_cast<int>(text[i]);
            i = i + table[text[i]];
        }
    }
    return -1;
}


int main(int argc, char *argv[]) {
    int output = -1;
    if (argc != 2) {  // Check to ensure file was run correctly
        return 1;
    }
    fstream in(argv[1]);
    if (in.is_open()) {
        string line;
        getline(in, line);
        string pattern = line;
        getline(in, line);
        string text = line;
        // Start timer before algorithm is called
        auto start = high_resolution_clock::now();
        int m = pattern.length();
        output = horspool(pattern, text, m);
        // End timer directly after algorithm finishes
        auto finish = high_resolution_clock::now();
        // Calculate duration by subtracting start from finish
        auto time = duration_cast<nanoseconds>(finish - start);
        // Output execution time
        cout << time.count() << " nanoseconds" << "\n";
    }
    in.close();  // Close input stream

    ofstream out;
    out.open("output.txt");  // Create output file
    out << output;
    out.close();  // Close stream to output file
}
