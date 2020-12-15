// Filename: "cBoltzmann.cpp"

#include "cBoltzmann.h"

cBoltzmann::cBoltzmann(int NumCities, float InitialTemperature, float GammaValue)
{
    nCities = NumCities;
    mUnits = nCities * nCities;
    mTemperature = InitialTemperature;
    mGamma = GammaValue;

    mOutput = NULL;
    mOutput = new bool[mUnits];

    mOn = NULL;
    mOn = new int[mUnits];

    mOff = NULL;
    mOff = new int[mUnits];

    mThreshold = NULL;
    mThreshold = new float[mUnits];

    mWeight = NULL;
    mWeight = new float*[mUnits];
    for(int i = 0; i < mUnits; i++)
    {
        mWeight[i] = new float[mUnits];
    }

    mDistance = NULL;
    mDistance = new float*[nCities];
    for(int i = 0; i < nCities; i++)
    {
        mDistance[i] = new float[nCities];
    }

    return;
}

cBoltzmann::~cBoltzmann()
{
    // Release any allocated memory to OS.
    if(mOutput != NULL){    
        delete [] mOutput;
    }
    if(mOn != NULL){    
        delete [] mOn;
    }
    if(mOff != NULL){    
        delete [] mOff;
    }
    if(mThreshold != NULL){    
        delete [] mThreshold;
    }
    if(mWeight != NULL){
        for(int i = 0; i < mUnits; i++)
        {
            delete [] mWeight[i];
        } // i
        delete [] mWeight;
    }
    if(mDistance != NULL){
        for(int i = 0; i < nCities; i++)
        {
            delete [] mDistance[i];
        } // i
        delete [] mDistance;
    }

    return;
}

bool cBoltzmann::RandomEqualBool()
{
    if(rand() % 2 == 1){
        return true;
    }else{
        return false;
    }
}

int cBoltzmann::RandomEqualInt(int Low, int High)
{
    return rand() % (High-Low+1) + Low;
}

float cBoltzmann::RandomEqualfloat(float Low, float High)
{
    return ((float) rand() / RAND_MAX) * (High-Low) + Low;
}

void cBoltzmann::CalcWeights()
{
    int     i, j;
    int     Pred_n3, Succ_n3;
    float   Weight;

    for(int n1 = 0; n1 < nCities; n1++)
    {
        for(int n2 = 0; n2 < nCities; n2++)
        {
            i = n1 * nCities + n2;
            for(int n3 = 0; n3 < nCities; n3++)
            {
                for(int n4 = 0; n4 < nCities; n4++)
                {
                    j = n3 * nCities + n4;
                    Weight = 0.0;
                    if(i != j){
                        Pred_n3 = (n3 == 0 ? nCities - 1 : n3 - 1);
                        Succ_n3 = (n3 == nCities - 1 ? 0 : n3 + 1);
                        if((n1 == n3) || (n2 == n4)){
                            Weight = -mGamma;
                        }else if ((n1 == Pred_n3) || (n1 == Succ_n3)){
                            Weight = -mDistance[n2][n4];
                        }
                    }
                    mWeight[i][j] = Weight;
                } // n4
            } // n3
            mThreshold[i] = (-mGamma / 2);
        } // n2
    } // n1

    return;
}

float cBoltzmann::LengthOfTour()
{
    float Length;

    Length = 0;
    for(int n1 = 0; n1 < nCities; n1++)
    {
        for(int n2 = 0; n2 < nCities; n2++)
        {
            if(mOutput[((n1) % nCities) * nCities + n2]){
                break;
            }
        } // n2

        for(int n3 = 0; n3 < nCities; n3++)
        {
            if(mOutput[((n1 + 1) % nCities) * nCities + n3]){
                break;
            }
        } // n3
        Length += mDistance[n2][n3];
    } // n1

    return Length;
}

void cBoltzmann::SetRandom()
{
    for(int i = 0; i < mUnits; i++)
    {
        mOutput[i] = RandomEqualBool();
    }

    return;
}

void cBoltzmann::PropagateUnit(int i)
{
    float  Sum = 0;
    float  Probability;

    for(int j = 0; j < mUnits; j++)
    {
        Sum += mWeight[i][j] * mOutput[j];
    }
    Sum -= mThreshold[i];

    Probability = 1 / (1 + exp(-Sum / mTemperature));

    if (RandomEqualfloat(0, 1) <= Probability){
        mOutput[i] = true;
    }else{
        mOutput[i] = false;
    }

    return;
}

void cBoltzmann::ReduceHeat()
{
    int index;

    for(int i = 0; i < mUnits; i++)
    {
        mOn[i] = 0;
        mOff[i] = 0;
    }

    for(int n = 0; n < 1000 * mUnits; n++)
    {
        PropagateUnit(index = RandomEqualInt(0, mUnits - 1));
    }

    for(int n = 0; n < 100 * mUnits; n++)
    {
        PropagateUnit(index = RandomEqualInt(0, mUnits - 1));
        if(mOutput[index]){
            mOn[index] += 1;
        }else{
            mOff[index] += 1;
        }
    }

    for(int i = 0; i < mUnits; i++)
    {
        mOutput[i] = (mOn[i] > mOff[i]);
    }

    return;
}

int cBoltzmann::getCities() const
{
    return nCities;
}

int cBoltzmann::getUnits() const
{
    return mUnits;
}

void cBoltzmann::setUnits(int numberOfUnits)
{
    mUnits = numberOfUnits;
}

bool cBoltzmann::getOutput(int index) const
{
    return mOutput[index];
}

void cBoltzmann::setOutput(int index, bool newValue)
{
    mOutput[index] = newValue;
}

int cBoltzmann::getOn(int index) const
{
    return mOn[index];
}

void cBoltzmann::setOn(int index, int newValue)
{
    mOn[index] = newValue;
}

int cBoltzmann::getOff(int index) const
{
    return mOff[index];
}

void cBoltzmann::setOff(int index, int newValue)
{
    mOff[index] = newValue;
}

float cBoltzmann::getThreshold(int index) const
{
    return mThreshold[index];
}

void cBoltzmann::setThreshold(int index, float newValue)
{
    mThreshold[index] = newValue;
}

float cBoltzmann::getWeight(int x, int y) const
{
    return mWeight[x][y];
}

void cBoltzmann::setWeight(int x, int y, float newValue)
{
    mWeight[x][y] = newValue;
}

float cBoltzmann::getTemperature() const
{
    return mTemperature;
}

void cBoltzmann::setTemperature(float newValue)
{
    mTemperature = newValue;
}

float cBoltzmann::getDistance(int x, int y) const
{
    return mDistance[x][y];
}

void cBoltzmann::setDistance(int x, int y, float newValue)
{
    mDistance[x][y] = newValue;
}
