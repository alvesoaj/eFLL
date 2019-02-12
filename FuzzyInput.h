/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyInput.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYINPUT_H
#define FUZZYINPUT_H

// IMPORTING NECESSARY LIBRARIES
#include "FuzzyIO.h"

class FuzzyInput : public FuzzyIO
{
public:
  // CONTRUCTORS
  FuzzyInput();
  FuzzyInput(int index);
  // DESTRUCTOR
  ~FuzzyInput();
  // PUBLIC METHODS
  bool calculateFuzzySetPertinences();
};
#endif