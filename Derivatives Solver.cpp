#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Term {
    double coefficient;
    int exponent;
};

Term parseTerm(const string& term) {
    Term result = {1, 0};
    size_t xPos = term.find('x');
    if (xPos == string::npos) {
        result.coefficient = stod(term);
    } else {
        if (xPos == 0 || (xPos == 1 && term[0] == '+')) {
            result.coefficient = 1;
        } else if (xPos == 1 && term[0] == '-') {
            result.coefficient = -1;
        } else {
            result.coefficient = stod(term.substr(0, xPos));
        }
        size_t caretPos = term.find('^');
        if (caretPos != string::npos) {
            result.exponent = stoi(term.substr(caretPos + 1));
        } else {
            result.exponent = 1;
        }
    }
    return result;
}

Term derive(const Term& term) {
    Term result = term;
    if (term.exponent == 0) {
        result.coefficient = 0;
        result.exponent = 0;
    } else {
        result.coefficient *= term.exponent;
        result.exponent -= 1;
    }
    return result;
}

string formatTerm(const Term& term) {
    if (term.coefficient == 0) return "";
    string result = to_string(term.coefficient);
    if (term.exponent > 0) {
        result += "x";
        if (term.exponent > 1) {
            result += "^" + to_string(term.exponent);
        }
    }
    return result;
}

string differentiate(const string& polynomial) {
    vector<Term> terms;
    stringstream ss(polynomial);
    string term;
    while (ss >> term) {
        if (term == "+") continue;
        terms.push_back(parseTerm(term));
    }

    string result;
    for (size_t i = 0; i < terms.size(); ++i) {
        Term derivedTerm = derive(terms[i]);
        string formattedTerm = formatTerm(derivedTerm);
        if (!formattedTerm.empty()) {
            if (!result.empty() && derivedTerm.coefficient > 0) {
                result += " + ";
            }
            result += formattedTerm;
        }
    }

    return result.empty() ? "0" : result;
}

int main() {
    string polynomial;
    cout << "Enter a polynomial (3x^3 + 2x^2 - x + 7): ";
    getline(cin, polynomial);
    string derivative = differentiate(polynomial);
    cout << "The derivative is: " << derivative << endl;
    return 0;
}