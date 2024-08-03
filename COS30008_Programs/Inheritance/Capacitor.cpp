#define _USE_MATH_DEFINES

#include "Capacitor.h"
#include <cmath>

// constructor with a default value
Capacitor::Capacitor(double aBaseValue) noexcept :
	ComponentBase(aBaseValue, "uF", "F")
{}

// returns true if aValue exceeds a magnitude (<1.0)
bool Capacitor::mustAdjust(double aValue) const noexcept
{
	return aValue < 1.0;
}

// returns component dependent scalar (1000.0)
const double Capacitor::getScalar() const noexcept
{
	return 1/0.001;
}

// returns (frequency-dependent) passive resistance value (capacitive reactance)
double Capacitor::getReactance(double aFrequency) const noexcept
{
	// Implement the formula for capacitive reactance here
	// Capacitive reactance = 1 / (2 * pi * frequency * capacitance)
	constexpr double PI = M_PI; // Using the constant from cmath
	return 1.0 / (2.0 * PI * aFrequency * getBaseValue());
}