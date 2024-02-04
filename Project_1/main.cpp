#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function prototypes at the top of the file for function decomposition

/**
 * Print instructions for using the program.
 */
void printMenu();
/**
 * Returns the 0-based index in the English alphabet where `c` appears,
 * or -1 if `c` is not an uppercase letter in the alphabet.
 *
 * For example:
 *  - `findIndexInAlphabet('A')` returns 0
 *  - `findIndexInAlphabet('D')` returns 3
 *  - `findIndexInAlphabet('+')` returns -1
 *  - `findIndexInAlphabet('a')` returns -1
 */
int findIndexInAlphabet(char c);
/**
 * Returns `c` rotated by `amount` many characters forward. If we run out
 * of letters in the alphabet, wrap around back to 'A'. This method
 * assumes that `c` is an uppercase letter.
 * For example:
 *  - `rot('A', 0)` returns 'A'
 *  - `rot('A', 1)` returns 'B'
 *  - `rot('Z', 1)` returns 'A'
 *  - `rot('A', 10)` returns 'K'
 *  - `rot('J', 25)` returns 'I'
 */
char rot(char c, int amount);
/**
 * Returns a new string in which every character has been rotated by `amount`
 * letters. Lowercase letters are converted to uppercase and rotated.
 * Non-alphabetic characters are left alone.
 * For example:
 *  `rot("A", 0)` returns "A"
 *  `rot("AA", 3)` returns "DD"
 *  `rot("HELLO", 0)` returns "HELLO"
 *  `rot("HELLO", 1)` returns "IFMMP"
 *  `rot("oh HEL-LO!", 1)` returns "PI IFM-MP!"
 */
string rot(string line, int amount);
/**
 * Shifts a provided string by going character by character
 * and rotating each one by an indicated amount
 * @return Encrypted string
 */
string toCaesarCipher();
/**
 * Takes a string and separates into entries based on spaces
 * @param str String provided by user
 * @param words Vector of separate words
 */
void createWords(string str, vector<string>& words);
/**
 * Goes through dictionary vector, checking if there is an entry
 * that matches the word being checked
 * @param word Word being checked
 * @param dictionary Vector containing the dictionary
 * @return True if match, false otherwise
 */
bool searchDictionary(string& word, vector<string>& dictionary);
/**
 * Decrypts a passed in string by brute force method
 * @param inputFile Dictionary
 * @return Decrypted text
 */
string fromCaesarCipher(ifstream& inputFile);
/**
 * Encrypts an inputted string using a specified key
 * @return Encrypted text
 */
string toVigenere();


string toCaesarCipher(){
    cout << "Enter the text to encrypt:" << endl;
    string str;
    getline(cin,str);

    cout << "Enter the number of characters to rotate by:" << endl;
    string shift;
    getline(cin,shift);
    int numShift = stoi(shift);

    string encryptedTxt = rot(str,numShift);

    return encryptedTxt;
}

void createWords(string str, vector<string>& words){
    // creates substring until it runs into a space,
    // then feeds the substring into the vector
    for (int i = 0; i < str.size(); i++) {
        if(str.at(i) == ' '){
            words.push_back(str.substr(0, i));
            str = str.substr(i + 1);
            i = 0;
        }
    }
    // feeds in last word because there are no more spaces
    words.push_back(str);
}

bool searchDictionary(string& word, vector<string>& dictionary){
    // goes through each word in the dictionary file until it
    // runs into a word that matches the word being checked
    for(string& x : dictionary){
        if(x == word){
            return true;
        }
    }
    return false;
}

string fromCaesarCipher(ifstream& inputFile){
    vector<string> dictionary;
    string entry;

    // feeds each line as an entry into the dictionary vector
    while(!inputFile.eof()){
        getline(inputFile,entry);
        dictionary.push_back(entry);
    }

    cout << "Enter the text to Caesar-cipher decrypt:" << endl;
    string str;
    getline(cin,str);

    string holdStr = str;

    // cleans up the inputted string, changing lowercase to uppercase,
    // and removes spaces and other characters
    for(int i = 0; i< str.size(); i++){
        if(!isalpha(str.at(i)) && str.at(i) != ' '){
            str.erase(str.begin()+i);
            i--;
        }
        if(islower(str.at(i))){
            str.at(i) = toupper(str.at(i));
        }
        while(i > 0 && str.at(i) == ' ' && str.at(i-1) == ' '){
            str.erase(str.begin()+i);
            i--;
        }
    }

    vector<string> words;

    createWords(str,words);

    string result;

    if(words.size() == 1){ // if the input is 1 word long
        string temp;
        for(int i = 26; i > 0; i--){
            temp = rot(words.at(0), 26 - i);
            if(searchDictionary(temp,dictionary)){
                result += temp + "\n";

            }
        }
    } else{ // if the input is more than 1 word long
        for(int shift = 26; shift > 0; shift--){
            string temp;
            double correctWords = 0;

            // goes through vector of words, decrypting the word and
            // checking it against the dictionary
            for (string x : words){
                temp = rot(x, 26-shift);
                if(searchDictionary(temp, dictionary)){
                    correctWords++;
                }
            }

            // checks if more than half the words in the vector appear
            // in the dictionary
            if(correctWords/words.size() > 0.5){
                int k = 0;
                for(char & x : holdStr){
                    if(x != ' '){
                        x = rot(x, 26 - shift);
                    }
                    k++;
                }
                result = holdStr;
            }
        }
    }
    if(result == ""){
        result = "No good decryptions found";
    }
    return result;
}

string toVigenere(){
    cout << "Enter text to encrypt:" << endl;
    string str;
    getline(cin,str);

    cout << "Enter the Vigenère key:" << endl;
    string key;
    getline(cin,key);

    // key to uppercase
    string fixedKey;
    for(char& x : key){
        if(isalpha(x)){
            x = toupper(x);
            fixedKey += x;
        }
    }

    int k = 0;
    for(char & x : str){
        if(isalpha(x)){
            x = toupper(x);

            if(k == fixedKey.size()){
                k = 0;
            }

            x = rot(x, findIndexInAlphabet(fixedKey[k]));
            k++;
        }
    }
    return str;
}

int main() {
    string command;

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    do {
        ifstream inputFile("dictionary.txt");
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        getline(cin, command);
        cout << endl;

        if(command == "C" || command == "c"){
            string result;
            result = toCaesarCipher();
            cout << result << endl;
        } else if(command == "D" || command == "d"){
            string result;
            result = fromCaesarCipher(inputFile);
            cout << result << endl;
        } else if(command == "V"|| command == "v"){
            string result;
            result = toVigenere();
            cout << result << endl;
        }

        cout << endl;

        inputFile.close();

    } while (!(command == "x" || command == "X"));

    return 0;
}

void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    // Caesar Ciphers
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    // Vigenere
    cout << "V - Encrypt with Vigenère" << endl;
    // Utility
    cout << "X - Exit Program" << endl;
}

int findIndexInAlphabet(char c) {
    size_t found = ALPHABET.find(c);
    if(found != string::npos){
        return found;
    }
    return -1;
}

char rot(char c, int amount) {
    c = toupper(c);
    int shiftChar;
    if(isalpha(c)){
        shiftChar = findIndexInAlphabet(c);
        shiftChar = (shiftChar + amount) % 26;
        c = ALPHABET[shiftChar];
    }

    return c;
}

string rot(string line, int amount){

    for(char& x : line){
        if(isalpha(x)){
            x = toupper(x);
            x = rot(x,amount);
        }
    }
    return line;
}