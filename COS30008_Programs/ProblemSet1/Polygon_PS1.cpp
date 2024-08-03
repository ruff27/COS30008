#include "Polygon.h"
#include <cmath>

float Polygon::getSignedArea() const noexcept {
    float lArea = 0.0f;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        size_t j = (i + 1) % fNumberOfVertices;
        lArea += fVertices[i].x() * fVertices[j].y();
        lArea -= fVertices[j].x() * fVertices[i].y();
    }
    return lArea / 2.0f;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon lTransformedPolygon;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        const Vector3D& lVertex3D = Vector3D(fVertices[i].x(), fVertices[i].y(), 1.0f);
        Vector3D lTransformedVertex = aMatrix * lVertex3D;
        lTransformedPolygon.fVertices[i] = Vector2D(lTransformedVertex.x(), lTransformedVertex.y());
    }
    lTransformedPolygon.fNumberOfVertices = fNumberOfVertices;
    return lTransformedPolygon;
}