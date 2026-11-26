#include "sources.h"

VoltageSource::VoltageSource(double u)
    : voltage(u >= 0 ? u : 0)
{
}

bool VoltageSource::SetVoltage(double u)
{
    if (u < 0) return false;
    voltage = u;
    return true;
}

Circuit::Circuit(double u, double r)
    : VoltageSource(u), loadResistance(r > 0 ? r : 1)
{
}

bool Circuit::SetLoadResistance(double r)
{
    if (r <= 0) return false;
    loadResistance = r;
    return true;
}

double Circuit::GetCurrent() const
{
    return voltage / loadResistance;
}

double Circuit::GetPower() const
{
    return voltage * GetCurrent();
}

Battery::Battery(double u, double r, double c)
    : VoltageSource(u), internalResistance(r > 0 ? r : 0.01), capacity(c > 0 ? c : 0)
{
}

double Battery::GetWorkTime(double loadCurrent) const
{
    if (loadCurrent <= 0) return 0;
    return capacity / loadCurrent;
}

double Battery::GetShortCircuitCurrent() const
{
    return voltage / internalResistance;
}
