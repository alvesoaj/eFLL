/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * Fuzzy.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "Fuzzy.h"

// CONTRUCTORS
Fuzzy::Fuzzy()
{
    // Initializing pointers with NULL
    // FuzzyInput
    this->fuzzyInputs = NULL;
    // FuzzyOutput
    this->fuzzyOutputs = NULL;
    // FuzzyRule
    this->fuzzyRules = NULL;
}

// DESTRUCTOR
Fuzzy::~Fuzzy()
{
    this->cleanFuzzyInputs(this->fuzzyInputs);
    this->cleanFuzzyOutputs(this->fuzzyOutputs);
    this->cleanFuzzyRules(this->fuzzyRules);
}

// PUBLIC METHODS

// Method to include a new FuzzyInput into Fuzzy
bool Fuzzy::addFuzzyInput(FuzzyInput *fuzzyInput)
{
    // auxiliary variable to handle the operation
    fuzzyInputArray *newOne;
    // allocating in memory
    if ((newOne = (fuzzyInputArray *)malloc(sizeof(fuzzyInputArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // building the object
    newOne->fuzzyInput = fuzzyInput;
    newOne->next = NULL;
    // if it is the first FuzzyInput, set it as the head
    if (this->fuzzyInputs == NULL)
    {
        this->fuzzyInputs = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        fuzzyInputArray *aux = this->fuzzyInputs;
        // find the last element of the array
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                // make the ralations between them
                aux->next = newOne;
                return true;
            }
            aux = aux->next;
        }
    }
    return true;
}

// Method to include a new FuzzyOutput into Fuzzy
bool Fuzzy::addFuzzyOutput(FuzzyOutput *fuzzyOutput)
{
    // auxiliary variable to handle the operation
    fuzzyOutputArray *newOne;
    // allocating in memory
    if ((newOne = (fuzzyOutputArray *)malloc(sizeof(fuzzyOutputArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // building the object
    newOne->fuzzyOutput = fuzzyOutput;
    newOne->next = NULL;
    // sorting the fuzzyOutput
    fuzzyOutput->order();
    // if it is the first FuzzyOutput, set it as the head
    if (this->fuzzyOutputs == NULL)
    {
        this->fuzzyOutputs = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        fuzzyOutputArray *aux = this->fuzzyOutputs;
        // find the last element of the array
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                // make the ralations between them
                aux->next = newOne;
                return true;
            }
            aux = aux->next;
        }
    }
    return true;
}

// Method to include a new FuzzyRule into Fuzzy
bool Fuzzy::addFuzzyRule(FuzzyRule *fuzzyRule)
{
    // auxiliary variable to handle the operation
    fuzzyRuleArray *newOne;
    // allocating in memory
    if ((newOne = (fuzzyRuleArray *)malloc(sizeof(fuzzyRuleArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // building the object
    newOne->fuzzyRule = fuzzyRule;
    newOne->next = NULL;
    // if it is the first FuzzyOutput, set it as the head
    if (this->fuzzyRules == NULL)
    {
        this->fuzzyRules = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        fuzzyRuleArray *aux = this->fuzzyRules;
        // find the last element of the array
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                // make the ralations between them
                aux->next = newOne;
                return true;
            }
            aux = aux->next;
        }
    }
    return true;
}

// Method to set a crisp value to one FuzzyInput
bool Fuzzy::setInput(int fuzzyInputIndex, float crispValue)
{
    // auxiliary variable to handle the operation
    fuzzyInputArray *aux;
    // instantiate with the first element from array
    aux = this->fuzzyInputs;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // if the FuzzyInput index match with the desired
        if (aux->fuzzyInput->getIndex() == fuzzyInputIndex)
        {
            // set crisp value for this FuzzyInput and return true
            aux->fuzzyInput->setCrispInput(crispValue);
            return true;
        }
        aux = aux->next;
    }
    // if no FuzzyInput was found, return false
    return false;
}

// Method to start the calculate of the result
bool Fuzzy::fuzzify()
{
    // auxiliary variable to handle the operation
    fuzzyInputArray *fuzzyInputAux;
    fuzzyOutputArray *fuzzyOutputAux;
    fuzzyRuleArray *fuzzyRuleAux;
    // to reset the data of all FuzzyInput and FuzzyOutput objects
    // instantiate with first element of the array
    fuzzyInputAux = this->fuzzyInputs;
    // while not in the end of the array, iterate
    while (fuzzyInputAux != NULL)
    {
        // for each FuzzyInput, reset its data
        fuzzyInputAux->fuzzyInput->resetFuzzySets();
        fuzzyInputAux = fuzzyInputAux->next;
    }
    // instantiate with first element of the array
    fuzzyOutputAux = this->fuzzyOutputs;
    // while not in the end of the array, iterate
    while (fuzzyOutputAux != NULL)
    {
        // for each FuzzyOutput, reset its data
        fuzzyOutputAux->fuzzyOutput->resetFuzzySets();
        fuzzyOutputAux = fuzzyOutputAux->next;
    }
    // to calculate the pertinence of all FuzzyInput objects
    // instantiate with first element of the array
    fuzzyInputAux = this->fuzzyInputs;
    // while not in the end of the array, iterate
    while (fuzzyInputAux != NULL)
    {
        // for each FuzzyInput, calculate its pertinence
        fuzzyInputAux->fuzzyInput->calculateFuzzySetPertinences();
        fuzzyInputAux = fuzzyInputAux->next;
    }
    // to evaluate which rules were triggered
    // instantiate with first element of the array
    fuzzyRuleAux = this->fuzzyRules;
    // while not in the end of the array, iterate
    while (fuzzyRuleAux != NULL)
    {
        // for each FuzzyRule, evaluate its expressions
        fuzzyRuleAux->fuzzyRule->evaluateExpression();
        fuzzyRuleAux = fuzzyRuleAux->next;
    }
    // to truncate the output sets
    // instantiate with first element of the array
    fuzzyOutputAux = this->fuzzyOutputs;
    // while not in the end of the array, iterate
    while (fuzzyOutputAux != NULL)
    {
        // for each FuzzyOutput, truncate the result
        fuzzyOutputAux->fuzzyOutput->truncate();
        fuzzyOutputAux = fuzzyOutputAux->next;
    }
    return true;
}

// Method to verify if one specific FuzzyRule was triggered
bool Fuzzy::isFiredRule(int fuzzyRuleIndex)
{
    // auxiliary variable to handle the operation
    fuzzyRuleArray *aux;
    // instantiate with first element of the array
    aux = this->fuzzyRules;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // if the FuzzyRule index match with the desired
        if (aux->fuzzyRule->getIndex() == fuzzyRuleIndex)
        {
            // return the calculated result
            return aux->fuzzyRule->isFired();
        }
        aux = aux->next;
    }
    // if no FuzzyRule was found, return false
    return false;
}

// Method to retrieve the result of the process for one specific FuzzyOutput
float Fuzzy::defuzzify(int fuzzyOutputIndex)
{
    // auxiliary variable to handle the operation
    fuzzyOutputArray *aux;
    // instantiate with first element of the array
    aux = this->fuzzyOutputs;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // if the FuzzyOutput index match with the desired
        if (aux->fuzzyOutput->getIndex() == fuzzyOutputIndex)
        {
            // return the calculated result
            return aux->fuzzyOutput->getCrispOutput();
        }
        aux = aux->next;
    }
    return 0;
}

// PRIVATE METHODS

// Method to recursively clean all FuzzyInput from memory
void Fuzzy::cleanFuzzyInputs(fuzzyInputArray *aux)
{
    if (aux != NULL)
    {
        this->cleanFuzzyInputs(aux->next);
        // emptying allocated memory
        free(aux);
    }
}

// Method to recursively clean all FuzzyOutput from memory
void Fuzzy::cleanFuzzyOutputs(fuzzyOutputArray *aux)
{
    if (aux != NULL)
    {
        this->cleanFuzzyOutputs(aux->next);
        // emptying allocated memory
        free(aux);
    }
}

// Method to recursively clean all FuzzyRule from memory
void Fuzzy::cleanFuzzyRules(fuzzyRuleArray *aux)
{
    if (aux != NULL)
    {
        this->cleanFuzzyRules(aux->next);
        // emptying allocated memory
        free(aux);
    }
}