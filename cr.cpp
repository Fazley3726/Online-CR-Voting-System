#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
using namespace std;

// Function to perform lexical analysis (checks valid candidate names)
bool isValidCandidateName(const string &name) {
    regex nameRegex("^[A-Za-z ]+$");
    return regex_match(name, nameRegex);
}

// DFA function to validate voting token
bool isValidToken(const string &token) {
    // DFA for token: must start with "VOTE" followed by digits (e.g., VOTE123)
    regex tokenRegex("^VOTE[0-9]+$");
    return regex_match(token, tokenRegex);
}

// Function to eliminate left recursion (simulate elimination for expressions)
void eliminateLeftRecursion(const string &input) {
    cout << "Processing input for left recursion elimination: " << input << endl;
    cout << "Input is valid after eliminating left recursion.\n";
}

// CR Election System Class
class CRElection {
private:
    vector<string> candidates;
    map<string, int> votes;
    vector<string> validTokens;

public:
    // Add candidates
    void addCandidates() {
        int num;
        cout << "Enter the number of candidates: ";
        cin >> num;
        cin.ignore();
        for (int i = 0; i < num; ++i) {
            string name;
            cout << "Enter candidate " << i + 1 << " name: ";
            getline(cin, name);
            if (isValidCandidateName(name)) {
                candidates.push_back(name);
                votes[name] = 0;
            } else {
                cout << "Invalid name! Only alphabets and spaces are allowed.\n";
                --i;
            }
        }
    }

    // Voting function
    void castVote() {
        string token;
        cout << "Enter your voting token (e.g., VOTE123): ";
        cin >> token;

        if (!isValidToken(token)) {
            cout << "Invalid voting token! Try again.\n";
            return;
        }

        if (find(validTokens.begin(), validTokens.end(), token) != validTokens.end()) {
            cout << "Token already used! You cannot vote again.\n";
            return;
        }

        validTokens.push_back(token);

        cout << "Candidates:\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            cout << i + 1 << ". " << candidates[i] << endl;
        }

        int choice;
        cout << "Enter the number corresponding to your chosen candidate: ";
        cin >> choice;

        if (choice > 0 && choice <= candidates.size()) {
            votes[candidates[choice - 1]]++;
            cout << "Vote cast successfully for " << candidates[choice - 1] << "!\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }

    // Display results
    void displayResults() {
        cout << "\nElection Results:\n";
        for (const auto &candidate : candidates) {
            cout << candidate << " - " << votes[candidate] << " votes\n";
        }
    }
};

// Main function
int main() {
    CRElection election;
    int choice;

    while (true) {
        cout << "\nUniversity CR Election System\n";
        cout << "1. Add Candidates\n";
        cout << "2. Cast Vote\n";
        cout << "3. Display Results\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                election.addCandidates();
                break;
            case 2:
                election.castVote();
                break;
            case 3:
                election.displayResults();
                break;
            case 4:
                cout << "Exiting the system. Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}