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
#include "FuzzyRule.h"

// CONTRUCTORS
FuzzyRule::FuzzyRule()
{
}

FuzzyRule::FuzzyRule(int index, FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzyRuleConsequent *fuzzyRuleConsequent)
{
    this->index = index;
    this->fired = false;
    this->fuzzyRuleAntecedent = fuzzyRuleAntecedent;
    this->fuzzyRuleConsequent = fuzzyRuleConsequent;
}

// PUBLIC METHODS

// Method to get the value of index
int FuzzyRule::getIndex()
{
    return this->index;
}

// Method to evaluate the total expression
bool FuzzyRule::evaluateExpression()
{
    // check if the FuzzyRuleAntecedent and FuzzyRuleConsequent are valid
    if (this->fuzzyRuleAntecedent != NULL && this->fuzzyRuleConsequent != NULL)
    {
        // call the evaluator in the FuzzyRuleAntecedent
        float powerOfAntecedent = this->fuzzyRuleAntecedent->evaluate();
        // if the power of FuzzyRuleAntecedent is bigget the 0.0, this rule was fired, else, no
        (powerOfAntecedent > 0.0) ? (this->fired = true) : (this->fired = false);
        // pass the power of FuzzyRuleAntecedent to FuzzyRuleConsequent by its evaluator
        this->fuzzyRuleConsequent->evaluate(powerOfAntecedent);
    }
    return this->fired;
}

// Method to get the value of fired
bool FuzzyRule::isFired()
{
    return this->fired;
}