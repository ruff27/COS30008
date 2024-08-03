#include "KeyProvider.h"
#include <cctype>
#include <cassert>

std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
    std::string result;
    for (char c : aString)
    {
        if (isalpha(c))
        {
            result += toupper(c);
        }
    }
    return result;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept {
    std::string lKeyword = preprocessString(aKeyword);
    std::string lSource = preprocessString(aSource);
    for (size_t i = 0; i < lSource.length(); i++)
    {
        fKeys += lKeyword[i % lKeyword.length()];
    }
    fIndex = 0;
    assert(fKeys.length() == lSource.length());
}

char KeyProvider::operator*() const noexcept {
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept {
    fIndex++;
    return *this;
}

KeyProvider KeyProvider::operator++(int) noexcept {
    KeyProvider old = *this;
    ++(*this);
    return old;
}

bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept {
    return fIndex == aOther.fIndex && fKeys == aOther.fKeys;
}

bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept {
    return !(*this == aOther);
}

KeyProvider KeyProvider::begin() const noexcept {
    KeyProvider temp = *this;
    temp.fIndex = 0;
    return temp;
}

KeyProvider KeyProvider::end() const noexcept {
    KeyProvider temp = *this;
    temp.fIndex = fKeys.size();
    return temp;
}
