/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
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
    this->fuzzySetOutputsCursor = NULL;
}

// DESTRUCTOR
FuzzyRuleConsequent::~FuzzyRuleConsequent()
{
    this->cleanFuzzySets(this->fuzzySetOutputs);
}

// PUBLIC METHODS
bool FuzzyRuleConsequent::addOutput(FuzzySet *fuzzySet)
{
    fuzzySetOutputArray *aux;
    // Allocating in memory
    if ((aux = (fuzzySetOutputArray *)malloc(sizeof(fuzzySetOutputArray))) == NULL)
    {
        return false;
    }
    aux->fuzzySet = fuzzySet;
    aux->next = NULL;

    if (this->fuzzySetOutputs == NULL)
    {
        this->fuzzySetOutputs = aux;
        this->fuzzySetOutputsCursor = aux;
    }
    else
    {
        this->fuzzySetOutputsCursor->next = aux;
        this->fuzzySetOutputsCursor = aux;
    }
    return true;
}

bool FuzzyRuleConsequent::evaluate(float power)
{
    fuzzySetOutputArray *aux;
    aux = this->fuzzySetOutputs;
    while (aux != NULL)
    {
        aux->fuzzySet->setPertinence(power);
        aux = aux->next;
    }
    return true;
}

// PRIVATE METHODS
void FuzzyRuleConsequent::cleanFuzzySets(fuzzySetOutputArray *aux)
{
    if (aux != NULL)
    {
        // emptying allocated memory
        this->cleanFuzzySets(aux->next);
        free(aux);
    }
}