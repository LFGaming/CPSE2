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

    // Read the file into a string using std::istreambuf_iterator
    std::vector<char> text(std::istreambuf_iterator<char>{file}, {});
    // Count the number of lines
    int numLines = std::count(text.begin(), text.end(), '\n');

    if (!text.empty() && text.back() != '\n') {
        ++numLines; // Increment if last line doesn't end with a newline
    }

    // Print the total number of characters and lines
    std::cout << "Total number of characters: " << text.size() << std::endl;
    std::cout << "Total number of lines: " << numLines << std::endl;
    int countalpha = std::count_if(text.begin(), text.end(), [](char ch){ return isalpha(ch)!=0; });
    std::cout<< "Total number of lines: "<<countalpha <<std::endl;

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

    std::cout << "10 most common words:" << std::endl;

    // Transform the wordFrequency map into a vector of pairs
    // This makes it easier to sort and print the words by frequency
    std::vector<std::pair<int, std::string>> sortedWordFrequency;
    std::transform(wordFrequency.begin(), wordFrequency.end(), std::back_inserter(sortedWordFrequency),
                [](const std::pair<std::string, int>& pair) {
                    // Swap the key and value when adding to the vector
                    return std::make_pair(pair.second, pair.first);
                });

    // Sort the vector in descending order
    // std::partial_sort is used to sort only the first 10 elements, which improves performance
    std::partial_sort(sortedWordFrequency.begin(), sortedWordFrequency.begin() + 10, sortedWordFrequency.end(), std::greater<>());

    // Print the 10 most common words
    // std::for_each is used to iterate over the first 10 elements of the vector
    std::for_each(sortedWordFrequency.begin(), sortedWordFrequency.begin() + 10,
                [](const std::pair<int, std::string>& pair) {
                    // Print the word and its frequency
                    std::cout << pair.second << ": " << pair.first << std::endl;
                });

    return 0;
}