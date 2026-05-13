#ifndef INPUT_READER_H_869677
#define INPUT_READER_H_869677

enum class Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    HARD_DROP,
    INVERT,
    HOLD_SWAP,
    QUIT,
    NONE
};

/// Reads a single raw keypress and maps it to a game Action.
class InputReader {
public:
    /// Blocking read of one character; returns the corresponding Action.
    Action readInput() const;

private:
    Action mapChar(char c) const;
};

#endif