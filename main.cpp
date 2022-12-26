#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <iostream>
#include <utility>
#include <vector>
#include <ctime>

#include "matplotlibcpp.h"

using namespace std;

const int a = 1, b = 20;
const int minStates = 6, maxStates = 20;

class State {
    string name;
    int duration;
public:
    explicit State(string name, int duration = 0) :
            name(std::move(name)), duration(duration) {}

    string getName() const {
        return name;
    }

    static int calculateDuration() {
        return a + rand() % b;
    }

    int getDuration() const {
        return duration;
    }

    friend ostream &operator<<(ostream &out, const State &state) {
        out << state.name << " = " << state.duration;
        return out;
    }
};

void plotDiagram(const vector<State> &);

int main() {
    srand(time(nullptr));
    vector<State> states = {
            State{"X"},
            State{"Y"},
            State{"Z"},
            State{"T"},
            State{"W"},
    };
    int numberOfStates = (minStates + rand() % maxStates) - 2;
    unsigned int random;
    vector<State> stateSequence;
    stateSequence.emplace_back(
            states[0].getName(),
            State::calculateDuration()
    );
    for (int i = 0; i < numberOfStates; i++) {
        random = rand() % states.size();
        stateSequence.emplace_back(
                states[random].getName(),
                State::calculateDuration()
        );
    }
    stateSequence.emplace_back(
            states[0].getName(),
            State::calculateDuration()
    );
    for (const State &state: stateSequence) {
        cout << state << '\n';
    }
    cout << '\n';
    plotDiagram(stateSequence);
}

void plotDiagram(const vector<State> &states) {
    int maximumY = states.front().getDuration();
    for (auto &item: states) {
        if (item.getDuration() > maximumY)
            maximumY = item.getDuration();
    }
    int i, j;
    int count;
    for (i = 0; i < states.size(); i++) {
        cout << states[i].getName() << ' ';
        count = states[i].getDuration();
        for (j = 0; j < count; j++)
            cout << "-|";
        cout << '\n';
    }
}

#pragma clang diagnostic pop
