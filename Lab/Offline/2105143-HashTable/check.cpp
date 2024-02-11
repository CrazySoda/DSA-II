#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cstdlib> // For rand()

using namespace std;

// Function to generate random words
vector<string> generate_words(int n) {
    vector<string> words;
    for (int i = 0; i < n; i++) {
        string word = "";
        int len = 5 + rand() % 6;
        for (int j = 0; j < len; j++) {
            word += 'a' + rand() % 26;
        }
        words.push_back(word);
    }
    return words;
}

// Function to remove duplicates from the vector
void remove_duplicates(vector<string> &words) {
    unordered_set<string> unique_words(words.begin(), words.end());
    words.assign(unique_words.begin(), unique_words.end());
}

vector<string> generate_unique_words(int n) {
    vector<string> words;

    // Fill the vector with random words until it reaches the given number
    while (words.size() < n) {
        int remaining = n - words.size();
        int batch_size = min(remaining, 5); // Generate words in batches of 5
        vector<string> new_words = generate_words(batch_size);
        words.insert(words.end(), new_words.begin(), new_words.end());
        // Remove duplicates
        remove_duplicates(words);
    }
    return words;
}

int main() {
    int n = 100; // Desired number of words

    vector<string> words = generate_unique_words(n);

    // Print the final vector of words
    cout << "Generated array of words:" << endl;
    for (const string &word : words) {
        cout << word << endl;
    }

    return 0;
}
