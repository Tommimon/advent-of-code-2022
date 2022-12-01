#include <iostream>
#include <vector>

std::vector<std::string> split(std::string const &str, std::string const &delim)
{
    std::vector<std::string> out;
    std::string remaining(str);
    size_t cut = 0;
    while (!remaining.empty() && cut != std::string::npos)
    {
        cut = remaining.find(delim);
        if (cut == std::string::npos)
            out.push_back(remaining.substr(0, remaining.size()));
        else if (cut == 0) {
            remaining = remaining.substr(delim.size(), remaining.size());
        }
        else {
            out.push_back(remaining.substr(0, cut));
            remaining = remaining.substr(cut, remaining.size());
        }
    }
    return out;
}

int sum (std::vector<int> const &vec) {
    int tot = 0;
    for (auto e: vec)
        tot += e;
    return tot;
}
