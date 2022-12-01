#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> packs(split(input, "\n\n"));
    vector<int> pack_values;
    for (const auto& p: packs) {
        vector<string> elfs(split(p, "\n"));
        vector<int> numbers(map<string, int>([](const string& e) {return e.empty() ? 0 : stoi(e);}, elfs));
        pack_values.emplace_back(sum(numbers));
    }

    int largest = max<int>(pack_values, [](const int e) {return e;});
    int tot = largest;
    std::cout << largest << std::endl;
    remove_elem<int>(pack_values, largest);

    largest = max<int>(pack_values, [](const int e) {return e;});
    tot += largest;
    remove_elem<int>(pack_values, largest);

    largest = max<int>(pack_values, [](const int e) {return e;});
    tot += largest;
    std::cout << tot << std::endl;
}
