#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

// minimum and maximum duration possible for the states
const int minDuration = 1, maxDuration = 20;
// minimum and maximum number of states
const int minStates = 6, maxStates = 20;

class State {
    string name;
    int duration;
public:
    State(string name, int duration) :
            name(std::move(name)), duration(duration) {}

    string getName() const {
        return name;
    }

    static int calculateDuration() {
        return minDuration + (rand() % maxDuration);
    }

    int getDuration() const {
        return duration;
    }

    friend ostream &operator<<(ostream &out, const State &state) {
        out << state.name << "\t==>\t" << state.duration;
        return out;
    }
};

int main() {
    // seed for random number generation.
    srand(time(nullptr));
    // setting all possible states.
    vector<State> states = {
            State{"X", 0},
            State{"Y", 0},
            State{"Z", 0},
            State{"T", 0},
            State{"W", 0},
    };
    // random number of states in the sequence.
    int numberOfStates = (minStates + (rand() % maxStates)) - 2;
    int random;

    vector<State> stateSequence;

    // push the start state (X).
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
    // end the sequence with the same start state.
    stateSequence.emplace_back(
            stateSequence[0].getName(),
            State::calculateDuration()
    );

    vector<string> axisX;
    vector<int> axisY;
    for (int i = 0; i < stateSequence.size(); i++) {
        cout << i << "\t-->\t\t\t" << stateSequence[i] << '\n';
        axisX.emplace_back(stateSequence[i].getName() + " " + to_string(i + 1));
        axisY.emplace_back(stateSequence[i].getDuration());
    }
    plt::figure_size(1000, 640);
    plt::stem(axisX, axisY, "r--");
    plt::show();
}

#pragma clang diagnostic pop
