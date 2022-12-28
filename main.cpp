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

// class for holding the State properties.
class State {
    // state symbol.
    string name;
    // state duration
    int duration;
public:
    // constructor for setting the name & duration.
    State(string name, int duration) :
            name(std::move(name)), duration(duration) {}

    string getName() const {
        return name;
    }

    int getDuration() const {
        return duration;
    }

    // returns a random number from [minDuration] to [maxDuration] as duration for the state.
    static int calculateDuration() {
        return minDuration + (rand() % maxDuration);
    }
    // short to print the properties in a formatted way.
    friend ostream &operator<<(ostream &out, const State &state) {
        out << state.name << "\t==>\t" << state.duration;
        return out;
    }
};

int main() {
    // seed for random number generation.
    srand(time(nullptr));
    // setting all possible states with duration set to 0.
    vector<State> states = {
            State{"X", 0},
            State{"Y", 0},
            State{"Z", 0},
            State{"T", 0},
            State{"W", 0},
    };
    // random number of states in the sequence.
    int numberOfStates = (minStates + (rand() % maxStates)) - 2;
    unsigned int random;

    // holds a state sequence of length [numberOfStates].
    vector<State> stateSequence;

    // push the start state [X].
    stateSequence.emplace_back(
            states[0].getName(),
            State::calculateDuration()
    );
    // push a random state to the state sequence with random duration.
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

    // holds the state symbol [name] to plot it in axis X later.
    vector<string> axisX;
    // holds the state duration to plot it in axis Y.
    vector<int> axisY;
    // print the state sequence [name & duration] along with it order in the sequence
    // and pushes the symbols to [axisX] & duration to [axisY].
    for (int i = 0; i < stateSequence.size(); i++) {
        cout << i + 1 << "\t-->\t\t\t" << stateSequence[i] << '\n';
        axisX.emplace_back(stateSequence[i].getName() + " " + to_string(i + 1));
        axisY.emplace_back(stateSequence[i].getDuration());
    }
    // sets the size of the figure and plots it.
    plt::figure_size(1000, 640);
    // "ro--" => r: red color, o -> o markers, --: dashed line.
    plt::plot(axisX, axisY, "ro--");
    plt::show();
}

#pragma clang diagnostic pop
