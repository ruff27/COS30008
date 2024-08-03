#include "PassiveResistor.h"

// constructor with default value
PassiveResistor::PassiveResistor(double aBaseValue) noexcept :
	ComponentBase(aBaseValue, "Ohm", "OkM")
{}

// returns true if aValue exceeds a magnitude (1000.0)
bool PassiveResistor::mustAdjust(double aValue) const noexcept
{
	return aValue >= 1000.0;
}

const double PassiveResistor::getScalar() const noexcept
{
	return 1.0 / 1000.0;
}


double PassiveResistor::getReactance(double aFrequency) const noexcept
{
	return getBaseValue();
}