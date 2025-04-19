class Transition {
private:
    unsigned long start;
    unsigned long end;
    long startTime;
    long endTime;
    unsigned long current;
    bool transitionInProgress;

public:
    void startTransition(unsigned long startVal, unsigned long endVal, int duration);
    void tick();
    unsigned long getCurrent() {
        return current;
    }
    bool inProgress() {
        return transitionInProgress;
    }
};