#include "Sphere3D.h"

#include "Assertion.h"
#include "MathUtils.h"

bool Sphere3D::Intersect(const Sphere3D& sphere) const
{
	float lengthSq = MathUtils::LengthSquare(center_ - sphere.GetCenter());
	float sumRadius = (radius_ + sphere.GetRadius());

	return lengthSq <= (sumRadius * sumRadius);
}