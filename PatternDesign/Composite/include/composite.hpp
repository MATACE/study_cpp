#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <iostream>
#include <vector>

namespace composite {

class Team {
public:
    Team() = default;
    Team(const std::string& name, int age)
        : name_(name), age_(age) {}
    virtual ~Team() = default;

    std::string name_;
    int age_;
};

class TeamOne : public Team {
public:
    TeamOne() = default;
    TeamOne(const std::string& name, int age)
        : Team(name, age) {}
    virtual ~TeamOne() = default;
};

class TeamTwo : public Team {
public:
    TeamTwo() = default;
    TeamTwo(const std::string& name, int age) 
        : Team(name, age) {}
    virtual ~TeamTwo() = default;
};

class Administrator {
public:
    Administrator() = default;
    virtual ~Administrator() = default;
    void AddTeamMember(Team& team) {
        team_.push_back(team);
    }
    void ShowTeamMember() {
        for (auto iter = team_.begin(); iter != team_.end(); ++iter) {
            std::cout << "Team Member Name: " << iter->name_ << std::endl;
            std::cout << "Team Member Age: " << iter->age_ << std::endl;
        }
    }

private:
    std::vector<Team> team_;
};

}

#endif // COMPOSITE_HPP