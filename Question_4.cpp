#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Check if a character is a vowel (a, e, i, o, u) in either case
bool isVowel(char ch) {
    char c = ch;
    if (c >= 'A' && c <= 'Z') c = char(c - 'A' + 'a'); // manual tolower
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main() {
    // (a) Concatenate one string to another
    cout << "\n(a) Concatenate two strings\n";
    cout << "Enter first string: ";
    string s1; getline(cin, s1);
    cout << "Enter second string: ";
    string s2; getline(cin, s2);
    string concatenated = s1 + s2; // simplest way
    cout << "Concatenated: " << concatenated << "\n";

    // (b) Reverse a string
    cout << "\n(b) Reverse a string\n";
    cout << "Enter a string to reverse: ";
    string toReverse; getline(cin, toReverse);
    // Basic reverse using two pointers
    int i = 0, j = (int)toReverse.size() - 1;
    while (i < j) {
        char tmp = toReverse[i];
        toReverse[i] = toReverse[j];
        toReverse[j] = tmp;
        i++; j--;
    }
    cout << "Reversed: " << toReverse << "\n";

    // (c) Delete all vowels from the string
    cout << "\n(c) Delete all vowels from a string\n";
    cout << "Enter a string: ";
    string withVowels; getline(cin, withVowels);
    string noVowels = "";
    for (char ch : withVowels) {
        if (!isVowel(ch)) noVowels += ch; // keep non-vowels
    }
    cout << "Without vowels: " << noVowels << "\n";

    // (d) Sort strings in alphabetical order
    cout << "\n(d) Sort multiple strings alphabetically\n";
    cout << "How many strings? ";
    int n; 
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline
    vector<string> arr(n);
    for (int k = 0; k < n; ++k) {
        cout << "Enter string " << (k + 1) << ": ";
        getline(cin, arr[k]);
    }
    // Simple sort using standard lexicographical order
    sort(arr.begin(), arr.end());
    cout << "Sorted order:\n";
    for (const auto& s : arr) cout << s << "\n";

    // (e) Convert a character from uppercase to lowercase
    cout << "\n(e) Convert a character from uppercase to lowercase\n";
    cout << "Enter a single character: ";
    char ch;
    cin >> ch;
    // Manual lowercase conversion (only affects A-Z)
    if (ch >= 'A' && ch <= 'Z') {
        ch = char(ch - 'A' + 'a');
    }
    cout << "Lowercase: " << ch << "\n";

    return 0;
}
