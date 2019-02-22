/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzySet.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYSET_H
#define FUZZYSET_H

class FuzzySet
{
public:
  // CONTRUCTORS
  FuzzySet();
  FuzzySet(float a, float b, float c, float d);
  // PUBLIC METHODS
  float getPointA();
  float getPointB();
  float getPointC();
  float getPointD();
  bool calculatePertinence(float crispValue);
  void setPertinence(float pertinence);
  float getPertinence();
  void reset();

private:
  // PRIVATE VARIABLES
  float a;
  float b;
  float c;
  float d;
  float pertinence;
};
#endif