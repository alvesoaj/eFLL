/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleAntecedent.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyRuleAntecedent.h"

// CONTRUCTORS
FuzzyRuleAntecedent::FuzzyRuleAntecedent()
{
    // set the initial values
    this->op = 0;
    this->mode = 0;
    this->fuzzySet1 = NULL;
    this->fuzzySet2 = NULL;
    this->fuzzyRuleAntecedent1 = NULL;
    this->fuzzyRuleAntecedent2 = NULL;
}

// PUBLIC METHODS

// Method to create a FuzzyRuleAntecedent with just one single FuzzySet
bool FuzzyRuleAntecedent::joinSingle(FuzzySet *fuzzySet)
{
    // check if FuzzySet is not null
    if (fuzzySet != NULL)
    {
        // set the mode and reference
        this->mode = MODE_FS;
        this->fuzzySet1 = fuzzySet;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with two FuzzySet, with AND
bool FuzzyRuleAntecedent::joinWithAND(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2)
{
    // check if two FuzzySet are valid
    if (fuzzySet1 != NULL && fuzzySet2 != NULL)
    {
        // set the mode and references
        this->op = OP_AND;
        this->mode = MODE_FS_FS;
        this->fuzzySet1 = fuzzySet1;
        this->fuzzySet2 = fuzzySet2;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with two FuzzySet, with OR
bool FuzzyRuleAntecedent::joinWithOR(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2)
{
    // check if two FuzzySet are valid
    if (fuzzySet1 != NULL && fuzzySet2 != NULL)
    {
        // set the mode and references
        this->op = OP_OR;
        this->mode = MODE_FS_FS;
        this->fuzzySet1 = fuzzySet1;
        this->fuzzySet2 = fuzzySet2;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with one FuzzySet and one FuzzyRuleAntecedent, with AND
bool FuzzyRuleAntecedent::joinWithAND(FuzzySet *fuzzySet, FuzzyRuleAntecedent *fuzzyRuleAntecedent)
{
    // check if the FuzzySet and FuzzyRuleAntecedent are valid
    if (fuzzySet != NULL && fuzzyRuleAntecedent != NULL)
    {
        // set the mode and references
        this->op = OP_AND;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with one FuzzySet and one FuzzyRuleAntecedent, with AND (Inverse Params)
bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet)
{
    return this->joinWithAND(fuzzySet, fuzzyRuleAntecedent);
}

// Method to create a FuzzyRuleAntecedent with one FuzzySet and one FuzzyRuleAntecedent, with OR
bool FuzzyRuleAntecedent::joinWithOR(FuzzySet *fuzzySet, FuzzyRuleAntecedent *fuzzyRuleAntecedent)
{
    // check if the FuzzySet and FuzzyRuleAntecedent are valid
    if (fuzzySet != NULL && fuzzyRuleAntecedent != NULL)
    {
        // set the mode and references
        this->op = OP_OR;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with one FuzzySet and one FuzzyRuleAntecedent, with OR (Inverse Params)
bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet)
{
    return this->joinWithOR(fuzzySet, fuzzyRuleAntecedent);
}

// Method to create a FuzzyRuleAntecedent with two FuzzyRuleAntecedent, with AND
bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent *fuzzyRuleAntecedent1, FuzzyRuleAntecedent *fuzzyRuleAntecedent2)
{
    // check if two FuzzyRuleAntecedent are valid
    if (fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL)
    {
        // set the mode and references
        this->op = OP_AND;
        this->mode = MODE_FRA_FRA;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
        this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
        return true;
    }
    return false;
}

// Method to create a FuzzyRuleAntecedent with two FuzzyRuleAntecedent, with OR
bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent *fuzzyRuleAntecedent1, FuzzyRuleAntecedent *fuzzyRuleAntecedent2)
{
    // check if two FuzzyRuleAntecedent are valid
    if (fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL)
    {
        // set the mode and references
        this->op = OP_OR;
        this->mode = MODE_FRA_FRA;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
        this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
        return true;
    }
    return false;
}

// Method to evaluate this FuzzyRuleAntecedent
float FuzzyRuleAntecedent::evaluate()
{
    // switch by the mode value
    switch (this->mode)
    {
    case MODE_FS:
        // case it is a single FuzzySet join, just return its pertinence
        return this->fuzzySet1->getPertinence();
        break;
    case MODE_FS_FS:
        // case it is a join of two FuzzySet, switch by the operator
        switch (this->op)
        {
        case OP_AND:
            // case the operator is AND, check if both has pertinence bigger then 0.0
            if (this->fuzzySet1->getPertinence() > 0.0 && this->fuzzySet2->getPertinence() > 0.0)
            {
                // in this case, return the small pertinence between two FuzzySet
                if (this->fuzzySet1->getPertinence() < this->fuzzySet2->getPertinence())
                {
                    return this->fuzzySet1->getPertinence();
                }
                else
                {
                    return this->fuzzySet2->getPertinence();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        case OP_OR:
            // case the operator is OR, check if one has pertinence bigger then 0.0
            if (this->fuzzySet1->getPertinence() > 0.0 || this->fuzzySet2->getPertinence() > 0.0)
            {
                // in this case, return the one pertinence is bigger
                if (this->fuzzySet1->getPertinence() > this->fuzzySet2->getPertinence())
                {
                    return this->fuzzySet1->getPertinence();
                }
                else
                {
                    return this->fuzzySet2->getPertinence();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        }
        break;
    case MODE_FS_FRA:
        // case it is a join of one FuzzySet and one FuzzyRuleAntecedent, switch by the operator
        switch (this->op)
        {
        case OP_AND:
            // case the operator is AND, check if both has pertinence bigger then 0.0
            if (this->fuzzySet1->getPertinence() > 0.0 && fuzzyRuleAntecedent1->evaluate() > 0.0)
            {
                // in this case, return the small pertinence between two FuzzySet
                if (this->fuzzySet1->getPertinence() < fuzzyRuleAntecedent1->evaluate())
                {
                    return this->fuzzySet1->getPertinence();
                }
                else
                {
                    return fuzzyRuleAntecedent1->evaluate();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        case OP_OR:
            // case the operator is OR, check if one has pertinence bigger then 0.0
            if (this->fuzzySet1->getPertinence() > 0.0 || fuzzyRuleAntecedent1->evaluate() > 0.0)
            {
                // in this case, return the one pertinence is bigger
                if (this->fuzzySet1->getPertinence() > fuzzyRuleAntecedent1->evaluate())
                {
                    return this->fuzzySet1->getPertinence();
                }
                else
                {
                    return fuzzyRuleAntecedent1->evaluate();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        }
        break;
    case MODE_FRA_FRA:
        // case it is a join of two FuzzyRuleAntecedent, switch by the operator
        switch (this->op)
        {
        case OP_AND:
            // case the operator is AND, check if both has pertinence bigger then 0.0
            if (fuzzyRuleAntecedent1->evaluate() > 0.0 && fuzzyRuleAntecedent2->evaluate() > 0.0)
            {
                // in this case, return the small pertinence between two FuzzySet
                if (fuzzyRuleAntecedent1->evaluate() < fuzzyRuleAntecedent2->evaluate())
                {
                    return fuzzyRuleAntecedent1->evaluate();
                }
                else
                {
                    return fuzzyRuleAntecedent2->evaluate();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        case OP_OR:
            // case the operator is OR, check if one has pertinence bigger then 0.0
            if (fuzzyRuleAntecedent1->evaluate() > 0.0 || fuzzyRuleAntecedent2->evaluate() > 0.0)
            {
                // in this case, return the one pertinence is bigger
                if (fuzzyRuleAntecedent1->evaluate() > fuzzyRuleAntecedent2->evaluate())
                {
                    return fuzzyRuleAntecedent1->evaluate();
                }
                else
                {
                    return fuzzyRuleAntecedent2->evaluate();
                }
            }
            else
            {
                return 0.0;
            }
            break;
        }
        break;
    }
    return 0.0;
}