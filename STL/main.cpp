#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// Function to print character frequencies sorted by amount
void printCharFrequencyByAmount(const std::vector<int>& frequency) {
    std::vector<std::pair<int, char>> freqChar;
    for (int i = 0; i < 26; i++) {
        freqChar.push_back({frequency[i], static_cast<char>('a' + i)});
    }
    std::sort(freqChar.begin(), freqChar.end(), std::greater<>());
    std::cout << "Frequency of characters (sorted by amount):" << std::endl;
    for (const auto& pair : freqChar) {
        std::cout << pair.second << ": " << pair.first << std::endl;
    }
}



int main() {
    // Open the file
    std::ifstream file("KingJamesBible.txt");
    if (!file) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    // Read the file into a string
    std::string text;
    std::string line;
    while (std::getline(file, line)) {
        text += line + '\n';
    }
    // Count the number of lines
    int numLines = std::count(text.begin(), text.end(), '\n') + 1;

    // Print the total number of characters and lines
    std::cout << "Total number of characters: " << text.size() << std::endl;
    std::cout << "Total number of lines: " << numLines << std::endl;

    // Convert all uppercase characters to lowercase
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return std::tolower(c); });

    // Count the frequency of each character
    std::vector<int> frequency(26, 0);
    for (char ch : text) {
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }

    // Print the frequency of each character sorted by character
    std::cout << "Frequency of characters (sorted by character):" << std::endl;
    for (int i = 0; i < 26; i++) {
        std::cout << static_cast<char>('a' + i) << ": " << frequency[i] << std::endl;
    }

    // Print the frequency of each character sorted by amount
    printCharFrequencyByAmount(frequency);

    // Count the frequency of each word
    std::map<std::string, int> wordFrequency;
    std::string word;
    for (char ch : text) {
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
    std::cout<< "10 most common words:" << std::endl;
    std::vector<std::pair<int, std::string>> sortedWordFrequency;
    for (auto pair : wordFrequency) {
        sortedWordFrequency.push_back({pair.second, pair.first});
    }
    std::sort(sortedWordFrequency.begin(), sortedWordFrequency.end(), std::greater<>());
    for (size_t i = 0; i < 10 && i < sortedWordFrequency.size(); i++) {
        std::cout << sortedWordFrequency[i].second << ": " << sortedWordFrequency[i].first << std::endl;
    }

    return 0;
}