#include <cctype>
#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(const std::string& aKeyword, const std::string& aSource, EVigenereMode aMode) noexcept :
    fMode(aMode),
    fKeys(aKeyword, aSource),
    fSource(aSource),
    fIndex(-1),
    fCurrentChar('\0')
{
    initializeTable();
}

void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char sourceChar = fSource[fIndex];
    if (std::isalpha(sourceChar))
    {
        char keywordChar = std::toupper(*fKeys);
        size_t row = keywordChar - 'A';
        size_t col = std::toupper(sourceChar) - 'A';
        char encodedChar = fMappingTable[row][col];
        if (std::islower(sourceChar)) {
            fCurrentChar = std::tolower(encodedChar);
        }
        else {
            fCurrentChar = encodedChar;
        }
        fKeys++;
    }
    else {
        fCurrentChar = sourceChar;
    }
}

void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char sourceChar = fSource[fIndex];
    if (std::isalpha(sourceChar))
    {
        char keywordChar = std::toupper(*fKeys);
        size_t row = keywordChar - 'A';
        for (size_t i = 0; i < CHARACTERS; ++i) {
            if (fMappingTable[row][i] == std::toupper(sourceChar)) {
                char decodedChar = 'A' + i;
                if (std::islower(sourceChar)) {
                    fCurrentChar = std::tolower(decodedChar);
                }
                else {
                    fCurrentChar = decodedChar;
                }
                break;
            }
        }
        fKeys++;
    }
    else {
        fCurrentChar = sourceChar;
    }
}


char VigenereForwardIterator::operator*() const noexcept {
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {
    fIndex++;
    if (fIndex < fSource.size())
    {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator old = *this;
    ++(*this);
    return old;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
    return fIndex == aOther.fIndex && fSource == aOther.fSource;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const noexcept {
    VigenereForwardIterator result = *this;
    if (result.fIndex < result.fSource.size())
    {
        if (result.fMode == EVigenereMode::Encode) {
            result.encodeCurrentChar();
        }
        else {
            result.decodeCurrentChar();
        }
    }
    return result;
}

VigenereForwardIterator VigenereForwardIterator::end() const noexcept {
    VigenereForwardIterator result = *this;
    result.fIndex = fSource.size();
    return result;
}
