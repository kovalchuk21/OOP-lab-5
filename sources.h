#ifndef SOURCES_H
#define SOURCES_H

class VoltageSource
{
public:
    VoltageSource(double u = 0);

    bool SetVoltage(double u);
    double GetVoltage() const { return voltage; }

protected:
    double voltage;
};

class Circuit : public VoltageSource
{
public:
    Circuit(double u, double r);

    bool SetLoadResistance(double r);
    double GetLoadResistance() const { return loadResistance; }
    double GetCurrent() const;
    double GetPower() const;

private:
    double loadResistance;
};

class Battery : public VoltageSource
{
public:
    Battery(double u, double r, double c);

    double GetInternalResistance() const { return internalResistance; }
    double GetCapacity() const { return capacity; }
    double GetWorkTime(double loadCurrent) const;
    double GetShortCircuitCurrent() const;

private:
    double internalResistance;
    double capacity;
};

#endif
