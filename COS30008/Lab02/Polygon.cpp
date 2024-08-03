#include "Polygon.h"
#include <stdexcept>

Polygon::Polygon() noexcept :
    fNumberOfVertices()
{}

size_t Polygon::getNumberOfVertices() const noexcept
{
    return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const
{
    if (aIndex < fNumberOfVertices)
    {
        return fVertices[aIndex];
    }

    throw std::out_of_range("Illegal index value.");
}

void Polygon::readData(std::istream& aIStream)
{
    while (aIStream >> fVertices[fNumberOfVertices])
    {
        fNumberOfVertices++;
        if (fNumberOfVertices >= MAX_VERTICES)  // Ensure not to exceed the array size
        {
            break;
        }
    }
}

float Polygon::getPerimeter() const noexcept
{
    float Result = 0.0f;

    if (fNumberOfVertices > 2)
    {
        for (size_t i = 1; i < fNumberOfVertices; i++)
        {
            Result += (fVertices[i] - fVertices[i - 1]).length();
        }

        Result += (fVertices[0] - fVertices[fNumberOfVertices - 1]).length();
    }

    return Result;
}

Polygon Polygon::scale(float aScalar) const noexcept
{
    Polygon Result = *this;

    for (size_t i = 0; i < fNumberOfVertices; i++)
    {
        Result.fVertices[i] = fVertices[i] * aScalar;
    }

    return Result;
}