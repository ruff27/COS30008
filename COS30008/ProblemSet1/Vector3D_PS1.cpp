#include "Vector3D.h"
#include <sstream>

std::string Vector3D::toString() const noexcept {
    std::stringstream lString;
    lString << "[" << std::round(x() * 10000.0f) / 10000.0f << ","
        << std::round(y() * 10000.0f) / 10000.0f << ","
        << std::round(w() * 10000.0f) / 10000.0f << "]";
    return lString.str();
}
