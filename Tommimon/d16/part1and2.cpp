#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "py++.hpp"

using namespace std;
using namespace py;

class Valve {
    public:
    string name;
    vector<string> connected;
    int pressure;

    explicit Valve(const string &s) {
        name = s.substr(6, 2);
        pressure = stoi(split(split(s, "rate=")[1], ";")[0]);
        string a = split(s, "tunnel lead to valve ")[1];
        connected = split(a, ", ");
    }
};

std::map<string, Valve> toOpen;
vector<string> names;
std::map<string, int> indexes;
int distances[100][100];

void explore(string current, int rate, int release, string opened, int time_left, int &best_release) {
    int drawable = 0;
    for (const auto& v: toOpen) {
        drawable += v.second.pressure*(time_left);
    }

    if (drawable+release < best_release)
        return;

    bool available = false;
    for (const auto& v: toOpen) {
        if (distances[indexes.find(current)->second][indexes.find(v.second.name)->second] + 1 <= time_left && !opened.contains("," + v.second.name)) {
            available = true;
            string chosenName = v.second.name;
            explore(
                    chosenName,
                    rate + toOpen.find(chosenName)->second.pressure,
                    release + (distances[indexes.find(current)->second][indexes.find(chosenName)->second] + 1) * rate,
                    opened + "," + chosenName,
                    time_left - distances[indexes.find(current)->second][indexes.find(chosenName)->second] - 1,
                    best_release);
        }
    }

    if (!available) {
        release += rate * time_left;
        if (release > best_release)
            best_release = release;
        return;
    }
}

void explore_elephant(string current_me, string current_elephant, int rate_me, int rate_elephant, int release, string opened, int my_time_left, int elephant_time_left, int &best_release) {
    int drawable = 0;
    int time_left = my_time_left > elephant_time_left ? my_time_left : elephant_time_left;
    for (const auto& v: toOpen) {
        drawable += v.second.pressure*(time_left);
    }

    if (drawable+release < best_release)
        return;

    bool elephant_turn = my_time_left <= elephant_time_left;
    string &current = elephant_turn ? current_elephant : current_me;
    int &rate = elephant_turn ? rate_elephant : rate_me;

    bool available = false;
    for (const auto& v: toOpen) {
        if (distances[indexes.find(current)->second][indexes.find(v.second.name)->second] + 1 <= my_time_left && !opened.contains("," + v.second.name)) {
            available = true;
            string chosenName = v.second.name;
            if (elephant_turn)
                explore_elephant(
                        current_me,
                        chosenName,
                        rate_me,
                        rate + toOpen.find(chosenName)->second.pressure,
                        release +
                        (distances[indexes.find(current)->second][indexes.find(chosenName)->second] + 1) * rate,
                        opened + "," + chosenName,
                        my_time_left,
                        time_left - distances[indexes.find(current)->second][indexes.find(chosenName)->second] - 1,
                        best_release);
            else
                explore_elephant(
                        chosenName,
                        current_elephant,
                        rate + toOpen.find(chosenName)->second.pressure,
                        rate_elephant,
                        release +
                        (distances[indexes.find(current)->second][indexes.find(chosenName)->second] + 1) * rate,
                        opened + "," + chosenName,
                        time_left - distances[indexes.find(current)->second][indexes.find(chosenName)->second] - 1,
                        elephant_time_left,
                        best_release);
        }
    }

    if (!available) {
        release += rate_me * my_time_left + rate_elephant * elephant_time_left;
        if (release > best_release)
            best_release = release;
        return;
    }
}


int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    input = replace(replace(replace(input, "tunnels", "tunnel"), "valves", "valve"), "leads", "lead");

    vector<string> lines(split(input, "\n"));
    vector<Valve> valves_vector(py::map<string, Valve>([](const string& s){return Valve(s);}, lines));
    std::map<string, Valve> valves;
    for (const auto& v: valves_vector) {
        valves.insert({v.name, v});
    }

    for (int i = 0; i < valves.size(); ++i) {
        for (int j = 0; j < valves.size(); ++j)
            distances[i][j] = INT32_MAX;
        distances[i][i] = 0;
    }

    for (const auto& v: valves) {
        indexes.insert({v.first, names.size()});
        names.push_back(v.first);
    }

    bool run = true;
    while (run) {
        run = false;
        auto iteratorI = valves.begin();
        for (int i = 0; i < valves.size(); ++i) {
            auto iteratorJ = valves.begin();
            for (int j = 0; j < valves.size(); ++j) {
                if (distances[i][j] == INT32_MAX)
                    run = true;
                if (count_if(iteratorI->second.connected.begin(), iteratorI->second.connected.end(), [&](string s){return s == iteratorJ->second.name;}) > 0)
                    for (int k = 0; k < valves.size(); ++k) {
                        if (distances[i][k] + 1 < distances[j][k] && distances[i][k] != INT32_MAX)
                            distances[j][k] = distances[i][k] + 1;
                        if (distances[j][k] + 1 < distances[i][k] && distances[i][k] != INT32_MAX)
                            distances[i][k] = distances[j][k] + 1;
                    }
                iteratorJ++;
            }
            iteratorI++;
        }
    }

    int time_left = 30;
    string opened;
    string current = "AA";
    int best_release = 0;
    int rate = 0;
    while (time_left > 0) {
        int max = -1;
        string maxName;
        for (const auto& v: valves) {
            if (distances[indexes.find(current)->second][indexes.find(v.second.name)->second] + 1 <= time_left && v.second.pressure > max && !opened.contains("," + v.second.name)) {
                max = v.second.pressure;
                maxName = v.second.name;
            }
        }

        if (max == -1) {
            best_release += time_left * rate;
            break;
        }

        opened += "," + maxName;
        time_left -= distances[indexes.find(current)->second][indexes.find(maxName)->second] + 1;
        best_release += (distances[indexes.find(current)->second][indexes.find(maxName)->second] + 1) * rate;
        rate += max;
        current = maxName;
    }

    for (const auto& v: valves) {
        if (v.second.pressure != 0)
            toOpen.insert(v);
    }

    opened = "";
    explore("AA", 0, 0, opened, 30, best_release);

    cout << best_release << endl;

    opened = "";
    explore_elephant("AA", "AA", 0, 0, 0, opened, 26, 26, best_release);

    cout << best_release << endl;
}
