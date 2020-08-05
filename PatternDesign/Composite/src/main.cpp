#include <iostream>

#include "composite.hpp"

using namespace std;
using namespace composite;

int main(int argc, char const *argv[])
{
    TeamOne team_one("xiao hong", 42);
    TeamTwo team_two("xiao ming", 43);

    Administrator administers;
    administers.AddTeamMember(team_one);
    administers.AddTeamMember(team_two);
    
    administers.ShowTeamMember();

    return 0;
}
