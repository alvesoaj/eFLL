/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

// IMPORTING NECESSARY LIBRARIES
#include "FuzzyIO.h"
#include "FuzzyComposition.h"

class FuzzyOutput : public FuzzyIO
{
public:
  // CONTRUCTORS
  FuzzyOutput();
  FuzzyOutput(int index);
  // DESTRUCTOR
  ~FuzzyOutput();
  // PUBLIC METHODS
  bool truncate();
  float getCrispOutput();
  bool order();
  FuzzyComposition *getFuzzyComposition();

private:
  // PRIVATE VARIABLES
  FuzzyComposition *fuzzyComposition;

  // PRIVATE METHODS
  bool swap(fuzzySetArray *fuzzySetA, fuzzySetArray *fuzzySetB);
  bool rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *point, float *pertinence);
};
#endif