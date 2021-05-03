/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyComposition.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYCOMPOSITION_H
#define FUZZYCOMPOSITION_H

// IMPORTING NECESSARY LIBRARIES
#include <stdlib.h>

// CONSTANTS
#define EPSILON_VALUE 1.0E-3

// Array struct for points objects
struct pointsArray
{
  pointsArray *previous;
  float point;
  float pertinence;
  pointsArray *next;
};

class FuzzyComposition
{
public:
  // CONTRUCTORS
  FuzzyComposition();
  // DESTRUCTOR
  ~FuzzyComposition();
  // PUBLIC METHODS
  bool addPoint(float point, float pertinence);
  bool checkPoint(float point, float pertinence);
  bool build();
  float calculate();
  bool empty();
  int countPoints();

private:
  // PRIVATE VARIABLES
  pointsArray *points;

  // PRIVATE METHODS
  void cleanPoints(pointsArray *aux);
  bool rebuild(pointsArray *aSegmentBegin, pointsArray *aSegmentEnd, pointsArray *bSegmentBegin, pointsArray *bSegmentEnd);
  bool rmvPoint(pointsArray *point);
};
#endif