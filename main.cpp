#include "sources.h"
#include "ui.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    SaveOutputTo("output.txt");

    std::ifstream fin("input.txt");
    if (!fin) {
        Warn("Cannot open input.txt");
        return 1;
    }

    std::string key;
    double sourceU, circuitU, circuitR, batteryU, batteryR, batteryC, load, newU;
    fin >> key >> sourceU;
    fin >> key >> circuitU >> circuitR;
    fin >> key >> batteryU >> batteryR >> batteryC;
    fin >> key >> load;
    fin >> key >> newU;

    VoltageSource source(sourceU);
    Circuit circuit(circuitU, circuitR);
    Battery battery(batteryU, batteryR, batteryC);

    PrintBox("<------- INHERITANCE: VOLTAGE SOURCES (VARIANT 10) ------->");

    PrintBox("Testing base class VoltageSource");
    PrintTable({"Object", "Voltage"}, {{"source", Num(source.GetVoltage()) + " V"}});
    source.SetVoltage(newU);
    Done("source.SetVoltage(" + Num(newU, 0) + ")");
    PrintTable({"Object", "Voltage"}, {{"source", Num(source.GetVoltage()) + " V"}});

    PrintBox("Testing derived class Circuit : VoltageSource");
    PrintTable({"Object", "Voltage", "Load R", "I = U / R", "P = U * I"},
               {{"circuit", Num(circuit.GetVoltage()) + " V", Num(circuit.GetLoadResistance()) + " Ohm",
                 Num(circuit.GetCurrent()) + " A", Num(circuit.GetPower()) + " W"}});

    PrintBox("Calling base class method: circuit.SetVoltage(" + Num(newU, 0) + ")");
    circuit.SetVoltage(newU);
    PrintTable({"Object", "Voltage", "Load R", "I = U / R", "P = U * I"},
               {{"circuit", Num(circuit.GetVoltage()) + " V", Num(circuit.GetLoadResistance()) + " Ohm",
                 Num(circuit.GetCurrent()) + " A", Num(circuit.GetPower()) + " W"}});

    PrintBox("Testing derived class Battery : VoltageSource");
    PrintTable({"Object", "Voltage", "Internal r", "Capacity"},
               {{"battery", Num(battery.GetVoltage()) + " V", Num(battery.GetInternalResistance()) + " Ohm",
                 Num(battery.GetCapacity()) + " Ah"}});
    std::cout << "Work time with I = " << Num(load) << " A : t = C / I = " << Num(battery.GetWorkTime(load)) << " h\n";
    std::cout << "Short circuit current   : I = U / r = " << Num(battery.GetShortCircuitCurrent()) << " A\n";

    PrintBox("Summary");
    PrintTable({"Class", "Parent", "Voltage", "Result"},
               {{"VoltageSource", "-", Num(source.GetVoltage()) + " V", "-"},
                {"Circuit", "VoltageSource", Num(circuit.GetVoltage()) + " V", "I = " + Num(circuit.GetCurrent()) + " A"},
                {"Battery", "VoltageSource", Num(battery.GetVoltage()) + " V", "t = " + Num(battery.GetWorkTime(load)) + " h"}});
    Done("Results saved to output.txt");
    return 0;
}
