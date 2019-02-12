/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyIO.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYIO_H
#define FUZZYIO_H

// IMPORTING NECESSARY LIBRARIES
#include <stdlib.h>
#include "FuzzySet.h"

// Estrutura de uma lista de FuzzySet
struct fuzzySetArray
{
  FuzzySet *fuzzySet;
  fuzzySetArray *next;
};

class FuzzyIO
{
public:
  // CONTRUCTORS
  FuzzyIO();
  FuzzyIO(int index);
  // DESTRUCTOR
  ~FuzzyIO();
  // PUBLIC METHODS
  int getIndex();
  void setCrispInput(float crispInput);
  float getCrispInput();
  bool addFuzzySet(FuzzySet *fuzzySet);
  void resetFuzzySets();

protected:
  // VARIÁVEIS PROTEGIDAS
  int index;
  float crispInput;
  fuzzySetArray *fuzzySets;
  fuzzySetArray *fuzzySetsCursor;
  // MÉTODOS PROTEGIDOS
  void cleanFuzzySets(fuzzySetArray *aux);
};
#endif