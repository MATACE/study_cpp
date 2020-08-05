#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace iterator_api {

class RadioStation {
public:
    RadioStation() = default;
    RadioStation(float frequency)
        : frequency_(frequency) {}
    virtual ~RadioStation() = default;
    float GetFrequency() const {
        return frequency_;
    }

    friend bool operator==(const RadioStation& lhs, const RadioStation& rhs) { };

private:
    float frequency_;

};

class StationList {
    using iter = std::vector<RadioStation>::iterator;
public:
    StationList() = default;
    virtual ~StationList() = default;
    void AddStation(const RadioStation& station) {
        station_.push_back(station);
    };
    void RemoveStation(const RadioStation& to_remove) {
        auto found = std::find(station_.begin(), station_.end(), to_remove);
        if (found != station_.end()) {
            station_.erase(found);
        }
    }

    iter begin() {
        return station_.begin();
    }

    iter end() {
        return station_.end();
    }

private:
    std::vector<RadioStation> station_;
};

}

#endif // ITERATOR_HPP