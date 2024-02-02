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

void createWords(string& curWord, string str, vector<string>& words){
    for(char& x : str){
        if(isalpha(x)){
            curWord += x;
        } else if(!curWord.empty()){
            for(char& x : curWord){
                x = toupper(x);
            }
            words.push_back(curWord);
            curWord.clear();
        }
    }

    if(!curWord.empty()){
        for(char& x : curWord){
            x = toupper(x);
        }
        words.push_back(curWord);
    }
}

string fromCaesarCipher(ifstream& inputFile){
    cout << "Enter the text to Caesar-cipher decrypt:" << endl;
    string str;
    getline(cin,str);

    vector<string> words;
    string curWord;
    createWords(curWord,str,words);


    string result;

    for(int shift = 0; shift < 26; shift++){
        int correctWords = 0;

        for(string& s : words){
            string decryptedWord;
            for(char& x : s){
                x = rot(x, -shift);
                decryptedWord += x;
            }
            s = decryptedWord;

            string line;
            while(getline(inputFile,line)){
                if(line.find(decryptedWord) != string::npos){
                    correctWords++;
                    break;
                }
            }
        }

        if(correctWords > words.size()/2){
            for(string x : words){
                result += x;
                result += " ";
            }
        } else{
            result = "No good decryptions found";
        }
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
        cout << endl
             << "Enter a command (case does not matter): ";

        // Use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;
        // TODO_STUDENT: Execute non-exit commands.
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
    int shiftChar = findIndexInAlphabet(c);
    shiftChar = (shiftChar + amount) % 26;
    c = ALPHABET[shiftChar];
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