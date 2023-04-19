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
void validateString(string& passed);
void validateCommand(string& command);

// exits app
int quitFunction();

//----------------------------------------------------------------------
// InvalidStringException : throws exception on bad string input
//----------------------------------------------------------------------
class InvalidStringException : public std::exception {
public:
    const char* what() {
        return "Invalid string exception: ";
    }
};

// thrown on bad command input
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

        // handle input errors with validate functions
        // that throw exceptions

        try {
            // throws InvalidStringException
            validateString(input);

            // throws InvalidCommandException
            validateCommand(input);
        }
        // catch specific exception type
        catch (InvalidStringException& e) {
            cout << e.what() << input << "\n\n";
        }
        // catch specific exception type
        catch (InvalidCommandException& e) {
            cout << e.what() << input << "\n\n";
        }
        // catch any std::exception type
        catch (std::exception& e) {
            cout << e.what() << input << "\n\n";
        }
    }
}

//------------------------------------------------------------------------------
// - ensures that passed string contains only alpha characters or dashes
// - throws InvalidStringException if non-alpha character found
//------------------------------------------------------------------------------
void validateString(string& str) {

    for (auto c : str) {
        if (isalpha(c) || c == '-') {
            continue;
        }

        throw(InvalidStringException());
    }
}

//------------------------------------------------------------------------------
// makes passed string lowercase
//------------------------------------------------------------------------------
string processInput(string& userInput) {

    string str;

    for (char c : userInput) {
        str.push_back(tolower(c));
    }

    return str;
}

//------------------------------------------------------------------------------
// - returns true if passed string is a valid command, false otherwise
//------------------------------------------------------------------------------
void validateCommand(string& command) {

    //once the string is validated, make it lowercase
    string processed = processInput(command);

    //If block working as a switch statement, outputs lowercase command, returns true.
    if (!processed.compare("p") || !processed.compare("play")) {
        cout << "play\n\n";
        return;
    }
    if (!processed.compare("a") || !processed.compare("pause")) {
        cout << "pause\n\n";
        return;
    }
    if (!processed.compare("r") || !processed.compare("rewind")) {
        cout << "rewind\n\n";
        return;
    }
    if (!processed.compare("f") || !processed.compare("fast-forward")) {
        cout << "fast-Forward\n\n";
        return;
    }
    if (!processed.compare("s") || !processed.compare("stop")) {
        cout << "stop\n\n";
        return;
    }
    if (!processed.compare("q") || !processed.compare("quit")) {
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
    cout << "any key quits\n\n";
    system("pause");

    cout << "quit\nGoodbye!\n";

    exit(0);
}