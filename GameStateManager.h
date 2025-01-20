#include <vector>
#include <stack>

template <typename T>
class HistoryManager {
public:
    void PushState(const T& state) {
        undoStack.push(state);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    bool Undo(T& state) {
        if (!undoStack.empty()) {
            redoStack.push(state);
            state = undoStack.top();
            undoStack.pop();
            return true;
        }
        return false;
    }

    bool Redo(T& state) {
        if (!redoStack.empty()) {
            undoStack.push(state);
            state = redoStack.top();
            redoStack.pop();
            return true;
        }
        return false;
    }

    void Clear() {
        while (!undoStack.empty()) {
            undoStack.pop();
        }
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }
    int GetUndoStackSize() const {
        return static_cast<int>(undoStack.size());
    }

    int GetRedoStackSize() const {
        return static_cast<int>(redoStack.size());
    }
private:
    std::stack<T> undoStack;
    std::stack<T> redoStack;
};
