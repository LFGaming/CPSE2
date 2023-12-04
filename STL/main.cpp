#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    // Open the file
    std::ifstream file("KingJamesBible.txt");
    if (!file) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    // Read the file character by character and count the number of lines
    std::vector<char> characters;
    char ch;
    int numLines = 0;
    while (file.get(ch)) {
        characters.push_back(ch);
        if (ch == '\n') {
            numLines++;
        }
    }

    // Print the total number of characters and lines
    std::cout << "Total number of characters: " << characters.size() << std::endl;
    std::cout << "Total number of lines: " << numLines + 1 << std::endl;

    // Count the number of alphabets
    int numAlphabets = 0;
    for (char ch : characters) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            numAlphabets++;
        }
    }
    std::cout << "Total number of alphabets: " << numAlphabets << std::endl;

    // Convert all uppercase characters to lowercase
    for (char &ch : characters) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
    }

    // Count the frequency of each character
    std::map<char, int> frequency;
    for (char ch : characters) {
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch]++;
        }
    }

    // Print the frequency of each character
    std::cout << "Frequency of characters (sorted by character):" << std::endl;
    for (auto pair : frequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Count the frequency of each word
    std::map<std::string, int> wordFrequency;
    std::string word;
    for (char ch : characters) {
        if (ch >= 'a' && ch <= 'z') {
            word += ch;
        } else if (!word.empty()) {
            wordFrequency[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        wordFrequency[word]++;
    }

    // Sort the words by frequency and print the 10 most common words
    // Print a message indicating the 10 most common words will be displayed
    std::cout << "10 most common words:" << std::endl;

    // Create a vector to hold pairs of word frequency and the word itself
    std::vector<std::pair<int, std::string>> sortedWordFrequency;

    // Iterate over each word in the wordFrequency map
    for (auto pair : wordFrequency) {
        // For each word, create a pair with the frequency as the first element and the word as the second
        // Add this pair to the sortedWordFrequency vector
        sortedWordFrequency.push_back({pair.second, pair.first});
    }

    // Sort the sortedWordFrequency vector in descending order of frequency
    // std::greater<>() is a comparison function that sorts in descending order
    std::sort(sortedWordFrequency.begin(), sortedWordFrequency.end(), std::greater<>());

    // Print the 10 most common words and their frequencies
    // Iterate over the first 10 elements of the sortedWordFrequency vector (or fewer if the vector has less than 10 elements)
    for (size_t i = 0; i < 10 && i < sortedWordFrequency.size(); i++) {
        // For each element, print the word (the second element of the pair) and the frequency (the first element of the pair)
        std::cout << sortedWordFrequency[i].second << ": " << sortedWordFrequency[i].first << std::endl;
    }

    // End of main function, return 0 to indicate successful execution
    return 0;
}