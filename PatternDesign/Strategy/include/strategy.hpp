#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>

namespace strategy {

class Team {
public:
    Team() = default;
    virtual ~Team() = default;
    virtual void Sort() = 0;
};

class AscendTeam : public Team {
public:
    AscendTeam() = default;
    virtual ~AscendTeam() = default;
    void Sort() override {
        std::cout << "Sort By Ascend" << std::endl;
    }
};

class DescendTeam : public Team {
public:
    DescendTeam() = default;
    virtual ~DescendTeam() = default;
    void Sort() override {
        std::cout << "Sort By Descend" << std::endl;
    }
};

template <typename T>
class SortTeam {
public:
    SortTeam() = default;
    SortTeam(T& team)
        : team_(team) {}
    virtual ~SortTeam() = default;
    
    void Sort() {
        team_.Sort();
    }

private:
    T& team_;
};

template class SortTeam<AscendTeam>;
template class SortTeam<DescendTeam>;
}

#endif // STRATEGY_HPP