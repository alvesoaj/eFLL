/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyOutput.h"

// CONTRUCTORS
FuzzyOutput::FuzzyOutput() : FuzzyIO()
{
    // instantiating a FuzzyComposition object
    this->fuzzyComposition = new FuzzyComposition();
}

FuzzyOutput::FuzzyOutput(int index) : FuzzyIO(index)
{
    // instantiating a FuzzyComposition object
    this->fuzzyComposition = new FuzzyComposition();
}

// DESTRUCTOR
FuzzyOutput::~FuzzyOutput()
{
    // reset fuzzyComposition object
    this->fuzzyComposition->empty();
}

// PUBLIC METHODS

bool FuzzyOutput::truncate()
{
    // reset fuzzyComposition object
    this->fuzzyComposition->empty();
    // auxiliary variable to handle the operation
    fuzzySetArray *aux = this->fuzzySets;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // if the FuzzySet was trigged (has some pertinence)
        if (aux->fuzzySet->getPertinence() > 0.0)
        {
            // Check if it is not a "trapeze" without its left triangle or singleton, before include the point A
            if (aux->fuzzySet->getPointA() != aux->fuzzySet->getPointB())
            {
                // include it
                this->fuzzyComposition->addPoint(aux->fuzzySet->getPointA(), 0.0);
            }
            // check if it is a triangle (B == C) and (A <> D)
            if (aux->fuzzySet->getPointB() == aux->fuzzySet->getPointC() && aux->fuzzySet->getPointA() != aux->fuzzySet->getPointD())
            {
                // check if the pertinence is the max
                if (aux->fuzzySet->getPertinence() == 1.0)
                {
                    // include it (it will replace previous point if left triangle)
                    this->fuzzyComposition->addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
                    // include it (it will replace previous point if right triangle)
                    this->fuzzyComposition->addPoint(aux->fuzzySet->getPointD(), 0.0);
                }
                // if the pertinence is below the max, and it is a triangle, calculate the new point B and C
                else
                {
                    // rebuild the new point finding the intersection of two lines, the first is the segment from A to B (pertinence here is the y) and the segment of truncate, from A to D
                    // initiate a new point with current values of B (here it does matters, it always will be changed)
                    float newPointB = aux->fuzzySet->getPointB();
                    float newPertinenceB = aux->fuzzySet->getPertinence();
                    // only if a regular triangle
                    this->rebuild(aux->fuzzySet->getPointA(), 0.0, aux->fuzzySet->getPointB(), 1.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointB, &newPertinenceB);
                    // include it
                    this->fuzzyComposition->addPoint(newPointB, newPertinenceB);
                    // rebuild the new point finding the intersection of two lines, the second is the segment from C to D (pertinence here is the y) and the segment of truncate, from A to D
                    // initiate a new point with current values of C (here it does matters, it always will be changed)
                    float newPointC = aux->fuzzySet->getPointC();
                    float newPertinenceC = aux->fuzzySet->getPertinence();
                    // only if a regular triangle
                    this->rebuild(aux->fuzzySet->getPointC(), 1.0, aux->fuzzySet->getPointD(), 0.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointC, &newPertinenceC);
                    // include it
                    this->fuzzyComposition->addPoint(newPointC, newPertinenceC);
                }
            }
            // if until now, it was not a triangle
            // check if (B <> C), if true, it is a trapeze (this code is the same of the triangle, except when the pertinence is 1.0, here we include the two points [B and C], because they are not equal)
            else if (aux->fuzzySet->getPointB() != aux->fuzzySet->getPointC())
            {
                // check if the pertinence is the max
                if (aux->fuzzySet->getPertinence() == 1.0)
                {
                    // include it
                    this->fuzzyComposition->addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
                    // include it
                    this->fuzzyComposition->addPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence());
                }
                // if the pertinence is below the max, and it is a triangle, calculate the new point B and C
                else
                {
                    // initiate a new point with current values of B
                    float newPointB = aux->fuzzySet->getPointB();
                    float newPertinenceB = aux->fuzzySet->getPertinence();
                    // rebuild the new point finding the intersection of two lines, the first is the segment from A to B (pertinence here is the y) and the segment of truncate, from A to D
                    this->rebuild(aux->fuzzySet->getPointA(), 0.0, aux->fuzzySet->getPointB(), 1.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointB, &newPertinenceB);
                    // include it
                    this->fuzzyComposition->addPoint(newPointB, newPertinenceB);
                    // initiate a new point with current values of C
                    float newPointC = aux->fuzzySet->getPointC();
                    float newPertinenceC = aux->fuzzySet->getPertinence();
                    // rebuild the new point finding the intersection of two lines, the first is the segment from C to D (pertinence here is the y) and the segment of truncate, from A to D
                    this->rebuild(aux->fuzzySet->getPointC(), 1.0, aux->fuzzySet->getPointD(), 0.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointC, &newPertinenceC);
                    // include it
                    this->fuzzyComposition->addPoint(newPointC, newPertinenceC);
                }
            }
            // if it is not a triangle non a trapeze, it is a singleton
            else
            {
                // include it
                this->fuzzyComposition->addPoint(aux->fuzzySet->getPointB(), 0.0);
                // include it
                this->fuzzyComposition->addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
                // include it
                this->fuzzyComposition->addPoint(aux->fuzzySet->getPointB(), 0.0);
            }
            // Check if it is not a "trapeze" without its right triangle or singleton, before include the point D
            if (aux->fuzzySet->getPointC() != aux->fuzzySet->getPointD())
            {
                // include it
                this->fuzzyComposition->addPoint(aux->fuzzySet->getPointD(), 0.0);
            }
        }
        aux = aux->next;
    }
    // call build from FuzzyComposition for its self building
    this->fuzzyComposition->build();
    return true;
}

// Method to run the calculate of FuzzyComposition and return the result
float FuzzyOutput::getCrispOutput()
{
    return this->fuzzyComposition->calculate();
}

// Method to sort the FuzzySet by the reference of the point A in an ascending order
// It is just a simple Bubble Sort
bool FuzzyOutput::order()
{
    // instantiating some auxiliary variables
    fuzzySetArray *aux1 = this->fuzzySets;
    fuzzySetArray *aux2 = this->fuzzySets;
    // while not in the end of the array, iterate
    while (aux1 != NULL)
    {
        // iterate again to ensure all matches, for the worst case (complet inversion)
        while (aux2 != NULL)
        {
            // check if not in the last element
            if (aux2->next != NULL)
            {
                // check if the point from the first is bigger the the second
                if (aux2->fuzzySet->getPointA() > aux2->next->fuzzySet->getPointA())
                {
                    // if true, swap the FuzzySet
                    this->swap(aux2, aux2->next);
                }
            }
            aux2 = aux2->next;
        }
        // restarting the second auxiliary variable
        aux2 = this->fuzzySets;
        aux1 = aux1->next;
    }
    return true;
}

// Method to get the value (pointer) of fuzzyComposition
FuzzyComposition *FuzzyOutput::getFuzzyComposition()
{
    return this->fuzzyComposition;
}

// PRIVATE METHODS

// Method to invert the values (references) of two FuzzySet
bool FuzzyOutput::swap(fuzzySetArray *fuzzySetA, fuzzySetArray *fuzzySetB)
{
    // put the first into an auxiliary variable
    FuzzySet *aux = fuzzySetA->fuzzySet;
    // put the second into the first
    fuzzySetA->fuzzySet = fuzzySetB->fuzzySet;
    // put the auxiliary into the second
    fuzzySetB->fuzzySet = aux;
    return true;
}

// Method to rebuild some point, the new point is calculated finding the intersection between two lines
bool FuzzyOutput::rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *point, float *pertinence)
{
    // help variables
    float denom, numera, numerb;
    float mua, mub;
    // calculate the denominator and numerator
    denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    numera = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    numerb = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
    // if negative, convert to positive
    if (denom < 0.0)
    {
        denom *= -1.0;
    }
    // If the denominator is zero or close to it, it means that the lines are parallels, so return false for intersection
    if (denom < EPSILON_VALUE)
    {
        // return false for intersection
        return false;
    }
    // if negative, convert to positive
    if (numera < 0.0)
    {
        numera *= -1.0;
    }
    // if negative, convert to positive
    if (numerb < 0.0)
    {
        numerb *= -1.0;
    }
    // verify if has intersection between the segments
    mua = numera / denom;
    mub = numerb / denom;
    if (mua < 0.0 || mua > 1.0 || mub < 0.0 || mub > 1.0)
    {
        // return false for intersection
        return false;
    }
    else
    {
        // calculate and setting the new point and pertinence
        *point = x1 + mua * (x2 - x1);
        *pertinence = y1 + mua * (y2 - y1);
        // return true for intersection
        return true;
    }
}