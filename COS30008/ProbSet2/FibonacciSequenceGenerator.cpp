#include "FibonacciSequenceGenerator.h"

// Constructor to set up a Fibonacci sequence
FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID) noexcept
    : fID(aID), fPrevious(0), fCurrent(1) {}

// Get sequence ID
const std::string& FibonacciSequenceGenerator::id() const noexcept {
    return fID;
}

// Get current Fibonacci number
const long long& FibonacciSequenceGenerator::operator*() const noexcept {
    return fCurrent;
}

// Type conversion to bool
// Returns true if there is a next Fibonacci number to be generated
FibonacciSequenceGenerator::operator bool() const noexcept {
    return hasNext();
}

// Reset sequence generator to first Fibonacci number
void FibonacciSequenceGenerator::reset() noexcept {
    fPrevious = 0;
    fCurrent = 1;
}

bool FibonacciSequenceGenerator::hasNext() const noexcept {
    return fCurrent <= (LLONG_MAX - fPrevious);
}

// Advance to next Fibonacci number
void FibonacciSequenceGenerator::next() noexcept {
    
    long long lNext = fCurrent + fPrevious;
    fPrevious = fCurrent;
    fCurrent = lNext;
}


