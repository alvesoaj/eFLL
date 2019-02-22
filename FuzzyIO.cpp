/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyIO.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyIO.h"

// CONTRUCTORS
FuzzyIO::FuzzyIO()
{
}

FuzzyIO::FuzzyIO(int index)
{
    this->index = index;
    this->crispInput = 0.0;
    // Initializing pointers with NULL
    this->fuzzySets = NULL;
}

// DESTRUCTOR
FuzzyIO::~FuzzyIO()
{
    this->cleanFuzzySets(this->fuzzySets);
}

// PUBLIC METHODS

// Method to get the value of index
int FuzzyIO::getIndex()
{
    return this->index;
}

// Method to set the value of crispInput
void FuzzyIO::setCrispInput(float crispInput)
{
    this->crispInput = crispInput;
}

// Method to get the value of crispInput
float FuzzyIO::getCrispInput()
{
    return this->crispInput;
}

// Method to include a new FuzzySet into FuzzyIO
bool FuzzyIO::addFuzzySet(FuzzySet *fuzzySet)
{
    // auxiliary variable to handle the operation
    fuzzySetArray *newOne;
    // allocating in memory
    if ((newOne = (fuzzySetArray *)malloc(sizeof(fuzzySetArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // building the object
    newOne->fuzzySet = fuzzySet;
    newOne->next = NULL;
    // if it is the first FuzzySet, set it as the head
    if (this->fuzzySets == NULL)
    {
        this->fuzzySets = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        fuzzySetArray *aux = this->fuzzySets;
        // find the last element of the array
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                // make the relations between them
                aux->next = newOne;
                return true;
            }
            aux = aux->next;
        }
    }
    return true;
}

// Method to reset all FuzzySet of this collection
void FuzzyIO::resetFuzzySets()
{
    // auxiliary variable to handle the operation
    fuzzySetArray *fuzzySetsAux = this->fuzzySets;
    // while not in the end of the array, iterate
    while (fuzzySetsAux != NULL)
    {
        fuzzySetsAux->fuzzySet->reset();
        fuzzySetsAux = fuzzySetsAux->next;
    }
}

// PROTECTED METHODS

// Method to recursively clean all FuzzySet from memory
void FuzzyIO::cleanFuzzySets(fuzzySetArray *aux)
{
    if (aux != NULL)
    {
        this->cleanFuzzySets(aux->next);
        // emptying allocated memory
        free(aux);
    }
}