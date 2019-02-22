/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyInput.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyInput.h"

// CONTRUCTORS
FuzzyInput::FuzzyInput() : FuzzyIO()
{
    // no custom construction, using the father (FuzzyIO) constructor
}

FuzzyInput::FuzzyInput(int index) : FuzzyIO(index)
{
    // no custom construction, using the father (FuzzyIO) constructor
}

// DESTRUCTOR
FuzzyInput::~FuzzyInput()
{
    // no custom destruction, using the father (FuzzyIO) destructor
}

// PUBLIC METHODS

// Method to calculate the pertinence of all FuzzySet
bool FuzzyInput::calculateFuzzySetPertinences()
{
    // auxiliary variable to handle the operation
    fuzzySetArray *aux = this->fuzzySets;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // call calculatePertinence for each FuzzySet
        aux->fuzzySet->calculatePertinence(this->crispInput);
        aux = aux->next;
    }
    return true;
}