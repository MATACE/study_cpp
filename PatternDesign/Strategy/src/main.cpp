#include <iostream>

#include "strategy.hpp"

using namespace std;
using namespace strategy;

extern template class SortTeam<AscendTeam>;
extern template class SortTeam<DescendTeam>;

int main(int argc, char const *argv[])
{

    SortTeam<AscendTeam> ascend_team(*(new AscendTeam));
    SortTeam<DescendTeam> descend_team(*(new DescendTeam));

    ascend_team.Sort();
    descend_team.Sort();

    return 0;
}
