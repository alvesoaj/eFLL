/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzySet.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzySet.h"

// CONTRUCTORS
FuzzySet::FuzzySet()
{
}

FuzzySet::FuzzySet(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->pertinence = 0.0;
}

// PUBLIC METHODS

// Method to get the value of point A
float FuzzySet::getPointA()
{
    return this->a;
}

// Method to get the value of point B
float FuzzySet::getPointB()
{
    return this->b;
}

// Method to get the value of point C
float FuzzySet::getPointC()
{
    return this->c;
}

// Method to get the value of point D
float FuzzySet::getPointD()
{
    return this->d;
}

// Method to calculate the pertinence of the FuzzySet, according with the crispValue
bool FuzzySet::calculatePertinence(float crispValue)
{
    // check the crispValue is small then A
    if (crispValue < this->a)
    {
        // check if this FuzzySet represents "everithing small is true"
        if (this->a == this->b && this->b != this->c && this->c != this->d)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }
    }
    // check if the crispValue is between A and B
    else if (crispValue >= this->a && crispValue < this->b)
    {
        // calculate a slope
        float slope = 1.0 / (this->b - this->a);
        // calculate the value of pertinence
        this->pertinence = slope * (crispValue - this->b) + 1.0;
    }
    // check if the pertinence is between B and C
    else if (crispValue >= this->b && crispValue <= this->c)
    {
        this->pertinence = 1.0;
    }
    // check if the pertinence is between C and D
    else if (crispValue > this->c && crispValue <= this->d)
    {
        // calculate a slope
        float slope = 1.0 / (this->c - this->d);
        // calculate the value of pertinence
        this->pertinence = slope * (crispValue - this->c) + 1.0;
    }
    // check the crispValue is bigger then D
    else if (crispValue > this->d)
    {
        // check if this FuzzySet represents "everithing bigger is true"
        if (this->c == this->d && this->c != this->b && this->b != this->a)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }
    }
    return true;
}

// Method to set the value of pertinence
void FuzzySet::setPertinence(float pertinence)
{
    // check if the new pertinence is bigger then the current value because it can be called more then once by different FuzzyRuleConsequent
    if (this->pertinence < pertinence)
    {
        this->pertinence = pertinence;
    }
}

// Method to get the value of pertinence
float FuzzySet::getPertinence()
{
    return this->pertinence;
}

// Method to reset the value of pertinence
void FuzzySet::reset()
{
    this->pertinence = 0.0;
}