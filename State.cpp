#include <string>

class State {
private:
    std::u16string _data;
    int _weight;
    State *_parent;

public:

    static int width;
    static int height;

    State(std::string& data) {
        //interpret;
        _data = data;
        _weight = 0;
        _parent = NULL;
    }

    State(State* parent, Movement direction) {
        _parent = parent;
        _weight = parent->_weight + 1;

        //do string shifting thing
    }

    bool IsSolvable() {
        std::string solve;

        //solve

    }

    enum Movement {
        Up,
        Right,
        Down,
        Left,
    };
};
