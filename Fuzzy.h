/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * Fuzzy.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZY_H
#define FUZZY_H

// IMPORTING NECESSARY LIBRARIES
#include <inttypes.h>
#include "FuzzyInput.h"
#include "FuzzyOutput.h"
#include "FuzzyRule.h"

// Array struct for FuzzyInput objects
struct fuzzyInputArray
{
  FuzzyInput *fuzzyInput;
  fuzzyInputArray *next;
};

// Array struct for FuzzyOutput objects
struct fuzzyOutputArray
{
  FuzzyOutput *fuzzyOutput;
  fuzzyOutputArray *next;
};

// Array struct for FuzzyRule objects
struct fuzzyRuleArray
{
  FuzzyRule *fuzzyRule;
  fuzzyRuleArray *next;
};

// Main class of this library
class Fuzzy
{
public:
  // CONTRUCTORS
  Fuzzy();

  // DESTRUCTOR
  ~Fuzzy();

  // PUBLIC METHODS
  bool addFuzzyInput(FuzzyInput *fuzzyInput);
  bool addFuzzyOutput(FuzzyOutput *fuzzyOutput);
  bool addFuzzyRule(FuzzyRule *fuzzyRule);
  bool setInput(int fuzzyInputIndex, float crispValue);
  bool fuzzify();
  bool isFiredRule(int fuzzyRuleIndex);
  float defuzzify(int fuzzyOutputIndex);

private:
  // PRIVATE VARIABLES
  // pointers to manage the array of FuzzyInput
  fuzzyInputArray *fuzzyInputs;
  // pointers to manage the array of FuzzyOutput
  fuzzyOutputArray *fuzzyOutputs;
  // pointers to manage the array of FuzzyRule
  fuzzyRuleArray *fuzzyRules;

  // PRIVATE METHODS
  void cleanFuzzyInputs(fuzzyInputArray *aux);
  void cleanFuzzyOutputs(fuzzyOutputArray *aux);
  void cleanFuzzyRules(fuzzyRuleArray *aux);
};
#endif