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
}

FuzzyInput::FuzzyInput(int index) : FuzzyIO(index)
{
}

// DESTRUCTOR
FuzzyInput::~FuzzyInput()
{
}

// PUBLIC METHODS
bool FuzzyInput::calculateFuzzySetPertinences()
{
    fuzzySetArray *aux;
    aux = this->fuzzySets;

    while (aux != NULL)
    {
        if (aux->fuzzySet != NULL)
        {
            aux->fuzzySet->calculatePertinence(this->crispInput);
        }
        aux = aux->next;
    }

    return true;
}