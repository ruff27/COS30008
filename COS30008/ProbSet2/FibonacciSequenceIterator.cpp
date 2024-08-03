#include "FibonacciSequenceIterator.h"

FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSequenceObject,
    long long aStart) noexcept :
    fSequenceObject(aSequenceObject), fIndex(aStart)
{}

// iterator methods
const long long& FibonacciSequenceIterator::operator*() const noexcept
{
    return *fSequenceObject;
}

FibonacciSequenceIterator& FibonacciSequenceIterator::operator++() noexcept
{
    fSequenceObject.next();
    fIndex++;
    return *this;
}

FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int) noexcept
{
    FibonacciSequenceIterator lOld = *this;
    ++(*this);
    return lOld;
}

bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const noexcept
{
    return fIndex == aOther.fIndex;
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const noexcept
{
    return !(*this == aOther);
}

// iterator auxiliary methods

// return new iterator positioned at start
FibonacciSequenceIterator FibonacciSequenceIterator::begin() const noexcept
{
    FibonacciSequenceIterator lTemp = *this;
    lTemp.fIndex = 1;
    return lTemp;
}

// return new iterator positioned at limit
FibonacciSequenceIterator FibonacciSequenceIterator::end() const noexcept
{
    FibonacciSequenceIterator lTemp = *this;
    lTemp.fIndex = 93;
    return lTemp;
}