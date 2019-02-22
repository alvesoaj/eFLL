/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleConsequent.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYRULECONSEQUENT_H
#define FUZZYRULECONSEQUENT_H

// IMPORTING NECESSARY LIBRARIES
#include <stdlib.h>
#include "FuzzySet.h"

// Array struct for fuzzySet (for Output) objects
struct fuzzySetOutputArray
{
  FuzzySet *fuzzySet;
  fuzzySetOutputArray *next;
};

class FuzzyRuleConsequent
{
public:
  // CONTRUCTORS
  FuzzyRuleConsequent();
  // DESTRUCTOR
  ~FuzzyRuleConsequent();
  // PUBLIC METHODS
  bool addOutput(FuzzySet *fuzzySet);
  bool evaluate(float power);

private:
  // PRIVATE VARIABLES
  fuzzySetOutputArray *fuzzySetOutputs;

  // PRIVATE METHODS
  void cleanFuzzySets(fuzzySetOutputArray *aux);
};
#endif