/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRule.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYRULE_H
#define FUZZYRULE_H

// IMPORTING NECESSARY LIBRARIES
#include "FuzzyRuleAntecedent.h"
#include "FuzzyRuleConsequent.h"

class FuzzyRule
{
public:
  // CONTRUCTORS
  FuzzyRule();
  FuzzyRule(int index, FuzzyRuleAntecedent *fuzzyRuleAntecedent, FuzzyRuleConsequent *fuzzyRuleConsequent);
  // PUBLIC METHODS
  int getIndex();
  bool evaluateExpression();
  bool isFired();

private:
  // PRIVATE VARIABLES
  int index;
  bool fired;
  FuzzyRuleAntecedent *fuzzyRuleAntecedent;
  FuzzyRuleConsequent *fuzzyRuleConsequent;
};
#endif