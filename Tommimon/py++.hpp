#ifndef ADVENT_OF_CODE_2022_PY_HPP
#define ADVENT_OF_CODE_2022_PY_HPP

std::vector<std::string> split(std::string const &str, std::string const &delim);
int sum (std::vector<int> const &vec);

template<typename T1, typename T2>
std::vector<T2> map (std::function<T2(const T1)> const &func, std::vector<T1> const &vec)
{
    std::vector<T2> out;
    for (const auto& e: vec)
        out.push_back(func(e));
    return out;
}

template<typename T>
T max (std::vector<T> const &vec, std::function<int(T)> const &key)
{
    T max_elem;
    int max_key;
    bool first = true;
    for (const auto& e: vec) {
        int e_key = key(e);
        if (first || e_key > max_key) {
            first = false;
            max_key = e_key;
            max_elem = e;
        }
    }
    return max_elem;
}

template<typename T>
void remove_elem(std::vector<T> &vec, T const &elem) {
    std::remove_if(vec.begin(), vec.end(), [&](const auto &item) {
        return elem == item;
    });
}

#endif //ADVENT_OF_CODE_2022_PY_HPP
