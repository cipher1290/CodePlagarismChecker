#include "tokenizer.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <regex>
using namespace std;

// Helper to filter common boilerplate tokens
vector<string> filterCommonTokens(const vector<string>& tokens) {
    unordered_set<string> ignore = {
        "#", "include", "iostream", "using", "namespace", "std",
        "main", "int", "void", "cin", "cout", "return",
        "0", "1", "2", "3", "4", "5", ";", "{", "}", "(", ")", ",", "="
    };

    vector<string> filtered;
    for (const string& t : tokens) {
        // Remove all numbers, brackets, semicolons, and common C++ headers/types
        if (ignore.count(t)) continue;
        if (regex_match(t, regex(R"(\d+)"))) continue; // numbers
        if (regex_match(t, regex(R"([;{}\(\)])"))) continue; // basic punctuations
        filtered.push_back(t);
    }
    return filtered;
}


// Standard LCS logic
int LCSLength(const vector<string>& A, const vector<string>& B) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (A[i - 1] == B[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    return dp[n][m];
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./plagcheck file1.cpp file2.cpp" << endl;
        return 1;
    }

    string file1 = argv[1];
    string file2 = argv[2];

    // Process and tokenize files
    vector<string> tokens1 = filterCommonTokens(processFile(file1));
    vector<string> tokens2 = filterCommonTokens(processFile(file2));

    // LCS similarity
    int lcs = LCSLength(tokens1, tokens2);
    double similarity = (2.0 * lcs) / (tokens1.size() + tokens2.size()) * 100;

    cout << "{\n";
    cout << "  \"tokens_file1\": " << tokens1.size() << ",\n";
    cout << "  \"tokens_file2\": " << tokens2.size() << ",\n";
    cout << "  \"LCS_length\": " << lcs << ",\n";
    cout << "  \"similarity\": " << similarity << ",\n";
    cout << "  \"plagiarized\": " << (similarity > 70 ? "true" : "false") << "\n";
    cout << "}" << endl;

    return 0;
}
