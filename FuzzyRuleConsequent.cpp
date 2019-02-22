/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleConsequent.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyRuleConsequent.h"

// CONTRUCTORS
FuzzyRuleConsequent::FuzzyRuleConsequent()
{
    this->fuzzySetOutputs = NULL;
}

// DESTRUCTOR
FuzzyRuleConsequent::~FuzzyRuleConsequent()
{
    this->cleanFuzzySets(this->fuzzySetOutputs);
}

// PUBLIC METHODS

// Method to include a new FuzzySet (for Output) into FuzzyRuleConsequent
bool FuzzyRuleConsequent::addOutput(FuzzySet *fuzzySet)
{
    // auxiliary variable to handle the operation
    fuzzySetOutputArray *newOne;
    // allocating in memory
    if ((newOne = (fuzzySetOutputArray *)malloc(sizeof(fuzzySetOutputArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // building the object
    newOne->fuzzySet = fuzzySet;
    newOne->next = NULL;
    // if it is the first FuzzySet (for Output), set it as the head
    if (this->fuzzySetOutputs == NULL)
    {
        this->fuzzySetOutputs = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        fuzzySetOutputArray *aux = this->fuzzySetOutputs;
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

// Method to evaluate this FuzzyRuleConsequent
bool FuzzyRuleConsequent::evaluate(float power)
{
    // auxiliary variable to handle the operation
    fuzzySetOutputArray *aux = this->fuzzySetOutputs;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // set the pertinence of each FuzzySet with the power
        aux->fuzzySet->setPertinence(power);
        aux = aux->next;
    }
    return true;
}

// PRIVATE METHODS

// Method to recursively clean all fuzzySetOutputArray from memory
void FuzzyRuleConsequent::cleanFuzzySets(fuzzySetOutputArray *aux)
{
    if (aux != NULL)
    {
        this->cleanFuzzySets(aux->next);
        // emptying allocated memory
        free(aux);
    }
}