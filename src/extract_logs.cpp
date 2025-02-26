#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>

using namespace std;

string parseLineDate(const string &line) {
    if (line.size() >= 10)
        return line.substr(0, 10);
    return "";
}

streampos binarySearch(ifstream &file, const string &target_date, streampos fileSize) {
    streampos low = 0, high = fileSize, result_offset = -1;

    while (low <= high) {
        streampos mid = (low + high) / 2;
        file.seekg(mid);

        if (mid != 0) {
            string dummy;
            getline(file, dummy);  
        }

        streampos pos = file.tellg();
        string line;
        if (!getline(file, line)) {
            high = mid - 1;
            continue;
        }

        string current_date = parseLineDate(line);

        if (current_date < target_date) {
            low = file.tellg();
        } else {
            result_offset = pos;
            high = mid - 1;
        }
    }

    return result_offset;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./extract_logs <YYYY-MM-DD>" << endl;
        return 1;
    }

    string target_date = argv[1];

    if (target_date.size() != 10 || target_date[4] != '-' || target_date[7] != '-') {
        cerr << "Error: Invalid date format. Use YYYY-MM-DD." << endl;
        return 1;
    }

    string inputFile = "logs_2024.log";  
    string outputFile = "../output/output_" + target_date + ".txt";


    ifstream inFile(inputFile, ios::in | ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open log file " << inputFile << endl;
        return 1;
    }

    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error: Unable to create output file " << outputFile << endl;
        return 1;
    }

    inFile.seekg(0, ios::end);
    streampos fileSize = inFile.tellg();

    streampos start_offset = binarySearch(inFile, target_date, fileSize);
    if (start_offset == -1) {
        cerr << "No logs found for " << target_date << endl;
        return 0;
    }

    inFile.clear();
    inFile.seekg(start_offset);

    string line;
    while (getline(inFile, line)) {
        if (parseLineDate(line) != target_date)
            break;
        outFile << line << "\n";
    }

    cout << "Log entries for " << target_date << " written to " << outputFile << endl;
    return 0;
}
