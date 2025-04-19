#include "transition.h"
#include "util.h"

void Transition::startTransition(unsigned long startVal, unsigned long endVal, int durationMs) {
    if(transitionInProgress) {
        start = current;
    } else {
        start = startVal;
    }
    end = endVal;
    transitionInProgress = true;
    startTime = getEpochTime();
    endTime = startTime + durationMs;
}

void Transition::tick() {
    if(transitionInProgress) {
        int64_t time = getEpochTime();
        int64_t timeSinceStart = time - startTime;
        double currentProgress = (double)timeSinceStart / (double)(endTime - startTime);
        if(currentProgress >= 1) {
            current = end;
            transitionInProgress = false;
        }
        if(start > end) {
            unsigned long diff = start - end;
            current = start - (diff * currentProgress);
        } else {
            unsigned long diff = end - start;
            current = start + (diff * currentProgress);
        }
    }
}