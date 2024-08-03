#include "ifstream12.h"
#include <cassert>

void ifstream12::reset() {
    for (size_t i = 0; i < fBufferSize; i++)
        fBuffer[i] &= std::byte{ 0 };
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex = 7;
}

void ifstream12::fetch_data() {
    fIStream.read(reinterpret_cast<char*>(fBuffer), fBufferSize);
    fByteCount = fIStream.gcount();
    fByteIndex = 0;
    fBitIndex = 7;
}

std::optional<size_t> ifstream12::readBit() {
    if (fByteCount == 0) {
        if (fIStream.eof()) {
            return std::nullopt;  // Return no value if EOF is reached
        }
        fetch_data();
    }

    std::byte lByte = fBuffer[fByteIndex] & (std::byte{ 1 } << fBitIndex);
    size_t lBitValue = std::to_integer<size_t>(lByte);

    fBitIndex--;
    if (fBitIndex < 0) {
        fBitIndex = 7;
        fByteIndex++;
        fByteCount--;
    }

    if (lBitValue == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

ifstream12::ifstream12(const char* aFileName, size_t aBufferSize) :
    fBuffer(new std::byte[aBufferSize]), fBufferSize(aBufferSize),
    fByteCount(0), fByteIndex(0), fBitIndex(7) {

    if (aFileName) {
        open(aFileName);
    }
}

ifstream12::~ifstream12() {
    close();
    delete[] fBuffer;
}

void ifstream12::open(const char* aFileName) {
    assert(!isOpen());

    if (aFileName) {
        fIStream.open(aFileName, std::ifstream::binary);
    }
}

void ifstream12::close() {
    assert(isOpen());
    fIStream.close();
}

bool ifstream12::isOpen() const {
    return fIStream.is_open();
}

bool ifstream12::good() const {
    return fIStream.good() && (fByteCount > 0 || !fIStream.eof());
}

bool ifstream12::eof() const {
    return fByteCount == 0;
}

ifstream12& ifstream12::operator>>(size_t& aValue) {
    aValue = 0;
    for (size_t i = 0; i < 12; i++) {
        auto bitOpt = readBit();
        if (!bitOpt) {
            break;
        }
        if (bitOpt == 1) {
            aValue += (1 << i);
        }
    }

    return *this;
}