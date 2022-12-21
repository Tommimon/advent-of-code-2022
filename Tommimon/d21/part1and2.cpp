#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "py++.hpp"

using namespace std;
using namespace py;

long int solve(const std::map<string, string>& monkeys, const string& name, bool raise = false) {
    if (raise && name == "humn")
        throw std::invalid_argument( "can't process human expression" );
    string expr = monkeys.find(name)->second;
    if (expr.length() == 11) {
        long int a = solve(monkeys, split(expr, " ")[0], raise);
        long int b = solve(monkeys, split(expr, " ")[2], raise);
        char op = expr[5];
        if (op == '+') return a + b;
        if (op == '-') return a - b;
        if (op == '*') return a * b;
        if (op == '/') return a / b;
    }
    return stoi(expr);
}

long int require(const std::map<string, string>& monkeys, const string& name, long int val) {
    if (name == "humn")
        return val;
    string expr = monkeys.find(name)->second;
    char op = expr[5];
    string missing;
    long int required;
    try {
        long int a = solve(monkeys, split(expr, " ")[0], true);
        missing = split(expr, " ")[2];
        if (op == '+') required = val - a;
        if (op == '-') required = a - val;
        if (op == '*') required = val / a;
        if (op == '/') required = a / val;
    } catch( const std::invalid_argument& e ) {
        long int b = solve(monkeys, split(expr, " ")[2], true);
        missing = split(expr, " ")[0];
        if (op == '+') required = val - b;
        if (op == '-') required = val + b;
        if (op == '*') required = val / b;
        if (op == '/') required = val * b;
    }
    return require(monkeys, missing, required);
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    std::map<string, string> monkeys;

    for (const auto& l : lines) {
        monkeys.insert({split(l, ": ")[0], split(l, ": ")[1]});
    }

    cout << solve(monkeys, "root") << endl;

    monkeys.find("root")->second[5] = '-';

    cout << require(monkeys, "root", 0) << endl;
}
