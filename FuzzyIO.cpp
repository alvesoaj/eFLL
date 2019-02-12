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
    // Iniciando os ponteiros como nulo
    this->fuzzySets = NULL;
    this->fuzzySetsCursor = NULL;
}

// DESTRUCTOR
FuzzyIO::~FuzzyIO()
{
    this->cleanFuzzySets(this->fuzzySets);
}

// PUBLIC METHODS
int FuzzyIO::getIndex()
{
    return this->index;
}

void FuzzyIO::setCrispInput(float crispInput)
{
    this->crispInput = crispInput;
}

float FuzzyIO::getCrispInput()
{
    return this->crispInput;
}

bool FuzzyIO::addFuzzySet(FuzzySet *fuzzySet)
{
    fuzzySetArray *aux;
    // Allocating in memory
    if ((aux = (fuzzySetArray *)malloc(sizeof(fuzzySetArray))) == NULL)
    {
        return false;
    }
    aux->fuzzySet = fuzzySet;
    aux->next = NULL;

    if (this->fuzzySets == NULL)
    {
        this->fuzzySets = aux;
        this->fuzzySetsCursor = aux;
    }
    else
    {
        this->fuzzySetsCursor->next = aux;
        this->fuzzySetsCursor = aux;
    }
    return true;
}

void FuzzyIO::resetFuzzySets()
{
    fuzzySetArray *fuzzySetsAux;
    fuzzySetsAux = this->fuzzySets;
    // Calculando as pertinências de totos os FuzzyInputs
    while (fuzzySetsAux != NULL)
    {
        fuzzySetsAux->fuzzySet->reset();
        fuzzySetsAux = fuzzySetsAux->next;
    }
}

// MÉTODOS PROTEGIDOS
void FuzzyIO::cleanFuzzySets(fuzzySetArray *aux)
{
    if (aux != NULL)
    {
        // emptying allocated memory
        this->cleanFuzzySets(aux->next);
        free(aux);
    }
}