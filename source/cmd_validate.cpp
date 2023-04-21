//----------------------------------------------------------------------
// cmd_validate.cpp
//
// Demos a console app that validates user commands.
// 
// Exceptions simplify error handling. When you have many
// function calls on the stack, a thrown exception makes
// execution jump to the nearest catch block on the stack.
// This means only one function needs to check for errors.
//
// Exceptions are great when you call a function outside your
// code that throws an exception, like std::stoi()
// 
// When possible, use boolean functions instead of exceptions
// for error handling. Exceptions are slow, and they disrupt
// the call stack.
//----------------------------------------------------------------------
#include <exception>
#include <iostream>
#include <string>

//----------------------------------------------------------------------
// using symbols
//----------------------------------------------------------------------
using std::cin;
using std::cout;
using std::exception;
using std::getline;
using std::string;

// local function prototypes
 string processInput(string& userInput);

// these functions throw exceptions
bool validateString(string& passed);
void validateCommand(string& command);

// exits app
int quitFunction();

//----------------------------------------------------------------------
// InvalidCommandException : thrown on bad command input
//----------------------------------------------------------------------
class InvalidCommandException : public std::exception {
public:
    const char* what() {
        return "Unrecognized command exception: ";
    }
};

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
    cout << "Welcome to the Command Validator!\n\n";

    string input;

    // 'q' or 'Q' quits
    while (true) {
        cout << "P)lay, pA)use, R)ewind, F)ast-forward, S)top, or Q)uit?: ";
        getline(cin, input);

        try {
            if (validateString(input)) {

                // throws InvalidCommandException
                validateCommand(input);
            }
            else {
                cout << "Bad string: " << input << "\n\n";
            }
        }
        // catch specific exception type
        catch (InvalidCommandException& e) {
            cout << e.what() << input << "\n\n";
        }
        // catch any std::exception type
        catch (std::exception& e) {
            cout << e.what() << input << "\n\n";
        }
        // catch any exception type
        catch (...) {
            cout << "Unknown non-std::exception\n\n";
        }
    }
}

//------------------------------------------------------------------------------
// - ensures that passed string contains only alpha characters or dashes
// - returns false on illegal character
//------------------------------------------------------------------------------
bool validateString(string& str) {

    for (auto c : str) {
        if (!isalpha(c) && c != '-') {
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// makes passed string lowercase
//------------------------------------------------------------------------------
string processInput(string& input) {

    string str;
    for (char c : input) {
        str.push_back(tolower(c));
    }

    return str;
}

//------------------------------------------------------------------------------
// - routes user command to appropriate command handler
// - throws InvalidCommandException if passed string is not a valid command
//------------------------------------------------------------------------------
void validateCommand(string& command) {

    //once the string is validated, make it lowercase
    string processed = processInput(command);
    char cmdChar = processed.at(0);

    //If block working as a switch statement, outputs lowercase command, returns true.
    if (cmdChar == 'p' || !processed.compare("play")) {
        cout << "play\n\n";
        return;
    }
    if (cmdChar == 'a' || !processed.compare("pause")) {
        cout << "pause\n\n";
        return;
    }
    if (cmdChar == 'r' || !processed.compare("rewind")) {
        cout << "rewind\n\n";
        return;
    }
    if (cmdChar == 'f' || !processed.compare("fast-forward")) {
        cout << "fast-Forward\n\n";
        return;
    }
    if (cmdChar == 's' || !processed.compare("stop")) {
        cout << "stop\n\n";
        return;
    }
    if (cmdChar == 'q' || !processed.compare("quit")) {
        //prints "quit" and exits the application, no return.
        quitFunction();
    }

    // the input doesn't match any supported command
    throw InvalidCommandException();
}

//------------------------------------------------------------------------------
// exits the program
//------------------------------------------------------------------------------
int quitFunction() {
    cout << "quit\n\nGoodbye!\n\n";

    exit(0);
}