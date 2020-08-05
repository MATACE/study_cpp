#include <iostream>

#include "bridge.hpp"

using namespace std;
using namespace bridge;

int main(int argc, char const *argv[])
{
    // Poor Man
    PoorDay poor_day;
    Man poor_man(poor_day);

    poor_man.ShowDay();

    // Rich Man
    RichDay rich_day;
    Man rich_man(rich_day);
    
    rich_man.ShowDay();

    return 0;
}
