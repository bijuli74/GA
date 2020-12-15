// Filename: "cBoltzmann.h"

#ifndef CBOLTZMANN_H
#define CBOLTZMANN_H

#include "globals.h"

class cBoltzmann
{
private:
    int     nCities;        // number of cites.
    int     mUnits;         // network nodes.
    bool    *mOutput;       // node outputs.
    int     *mOn;           // total On states in consensus.
    int     *mOff;          // total Off states in consensus.
    float   *mThreshold;    // node thresholds.
    float   **mWeight;      // node connection weights.
    float   mTemperature;   // actual temperature.
    float   mGamma;         // learning rate.
    float   **mDistance;    // distance between cities.

    bool cBoltzmann::RandomEqualBool();
    int cBoltzmann::RandomEqualInt(int Low, int High);
    float cBoltzmann::RandomEqualfloat(float Low, float High);
    void cBoltzmann::PropagateUnit(int i);

public:
    cBoltzmann(int NumCities, float InitialTemperature, float GammaValue);
    ~cBoltzmann();
    void cBoltzmann::CalcWeights();
    float cBoltzmann::LengthOfTour();
    void cBoltzmann::SetRandom();
    void cBoltzmann::ReduceHeat();
    int cBoltzmann::getCities() const;
    int cBoltzmann::getUnits() const;
    void cBoltzmann::setUnits(int numberOfUnits);
    bool cBoltzmann::getOutput(int index) const;
    void cBoltzmann::setOutput(int index, bool newValue);
    int cBoltzmann::getOn(int index) const;
    void cBoltzmann::setOn(int index, int newValue);
    int cBoltzmann::getOff(int index) const;
    void cBoltzmann::setOff(int index, int newValue);
    float cBoltzmann::getThreshold(int index) const;
    void cBoltzmann::setThreshold(int index, float newValue);
    float cBoltzmann::getWeight(int x, int y) const;
    void cBoltzmann::setWeight(int x, int y, float newValue);
    float cBoltzmann::getTemperature() const;
    void cBoltzmann::setTemperature(float newValue);
    float cBoltzmann::getDistance(int x, int y) const;
    void cBoltzmann::setDistance(int x, int y, float newValue);

}; // end cBoltzmann class.

#endif
