/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyComposition.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyComposition.h"
#include <math.h>

// CONTRUCTORS
FuzzyComposition::FuzzyComposition()
{
    this->points = NULL;
}

// DESTRUCTOR
FuzzyComposition::~FuzzyComposition()
{
    this->cleanPoints(this->points);
}

// Method to include a new pointsArray struct into FuzzyComposition
bool FuzzyComposition::addPoint(float point, float pertinence)
{
    // auxiliary variable to handle the operation
    pointsArray *newOne;
    // allocating in memory
    if ((newOne = (pointsArray *)malloc(sizeof(pointsArray))) == NULL)
    {
        // return false if in out of memory
        return false;
    }
    // populate the struct
    newOne->previous = NULL;
    newOne->point = point;
    newOne->pertinence = pertinence;
    newOne->next = NULL;
    // if it is the first pointsArray, set it as the head
    if (this->points == NULL)
    {
        this->points = newOne;
    }
    else
    {
        // auxiliary variable to handle the operation
        pointsArray *aux = this->points;
        // find the last element of the array
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                // make the relations between them
                newOne->previous = aux;
                aux->next = newOne;
                return true;
            }
            aux = aux->next;
        }
    }
    return true;
}

// Method to check if FuzzyComposition contains an specific point and pertinence
bool FuzzyComposition::checkPoint(float point, float pertinence)
{
    // auxiliary variable to handle the operation
    pointsArray *aux = this->points;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // if params match with this point
        if (aux->point == point && aux->pertinence == pertinence)
        {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

// Method to iterate over the pointsArray, detect possible intersections and sent these points for "correction"
bool FuzzyComposition::build()
{
    // auxiliary variable to handle the operation, instantiate with the first element from array
    pointsArray *aux = this->points;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        // another auxiliary variable to handle the operation
        pointsArray *temp = aux;
        // while not in the beginning of the array, iterate
        while (temp->previous != NULL)
        {
            // if the previous point is greater then the current
            if (aux->point < temp->point)
            {
                // if yes, break an use this point
                break;
            }
            temp = temp->previous;
        }
        // iterate over the previous pointsArray
        while (temp->previous != NULL)
        {
            // if previous of previous point is not NULL, and some intersection was fixed by rebuild
            if (this->rebuild(aux, aux->next, temp, temp->previous) == true)
            {
                // move the first auxiliary to beginning of the array for a new validation, and breaks
                aux = this->points;
                break;
            }
            temp = temp->previous;
        }
        aux = aux->next;
    }
    return true;
}

// Method to calculate the center of the area of this FuzzyComposition
float FuzzyComposition::calculate()
{
    // auxiliary variable to handle the operation, instantiate with the first element from array
    pointsArray *aux = this->points;
    float numerator = 0.0;
    float denominator = 0.0;
    // while not in the end of the array, iterate
    while (aux != NULL && aux->next != NULL)
    {
        float area = 0.0;
        float middle = 0.0;
        // if it is a singleton
        if (aux->pertinence != aux->next->pertinence && aux->point == aux->next->point)
        {
            // enter in all points of singleton, but calculate only once
            if (aux->pertinence > 0.0)
            {
                area = aux->pertinence;
                middle = aux->point;
            }
        }
        // if a triangle (Not properly a membership function)
        else if (aux->pertinence == 0.0 || aux->next->pertinence == 0.0)
        {
            float pertinence;
            if (aux->pertinence > 0.0)
            {
                pertinence = aux->pertinence;
            }
            else
            {
                pertinence = aux->next->pertinence;
            }
            area = ((aux->next->point - aux->point) * pertinence) / 2.0;
            if (aux->pertinence < aux->next->pertinence)
            {
                middle = ((aux->next->point - aux->point) / 1.5) + aux->point;
            }
            else
            {
                middle = ((aux->next->point - aux->point) / 3.0) + aux->point;
            }
        }
        // else if a square (Not properly a membership function)
        else if ((aux->pertinence > 0.0 && aux->next->pertinence > 0.0) && aux->pertinence == aux->next->pertinence)
        {
            area = (aux->next->point - aux->point) * aux->pertinence;
            middle = ((aux->next->point - aux->point) / 2.0) + aux->point;
        }
        // else if a trapeze (Not properly a membership function)
        else if ((aux->pertinence > 0.0 && aux->next->pertinence > 0.0) && aux->pertinence != aux->next->pertinence)
        {
            area = ((aux->pertinence + aux->next->pertinence) / 2.0) * (aux->next->point - aux->point);
            middle = ((aux->next->point - aux->point) / 2.0) + aux->point;
        }
        numerator += middle * area;
        denominator += area;
        aux = aux->next;
    }
    // avoiding zero division
    if (denominator == 0.0)
    {
        return 0.0;
    }
    else
    {
        return numerator / denominator;
    }
}

// Method to reset the Object
bool FuzzyComposition::empty()
{
    // clean all pointsArray from memory
    this->cleanPoints(this->points);
    // reset the pointer
    this->points = NULL;
    return true;
}

// Method to count the amount of points used in this FuzzyComposition
int FuzzyComposition::countPoints()
{
    // variable to hold the count
    int count = 0;
    // auxiliary variable to handle the operation
    pointsArray *aux = this->points;
    // while not in the end of the array, iterate
    while (aux != NULL)
    {
        count = count + 1;
        aux = aux->next;
    }
    return count;
}

// PRIVATE METHODS

// Method to recursively clean all pointsArray structs from memory
void FuzzyComposition::cleanPoints(pointsArray *aux)
{
    if (aux != NULL)
    {
        this->cleanPoints(aux->next);
        // emptying allocated memory
        free(aux);
    }
}

// Method to search intersection between two segments, if found, create a new pointsArray (in found intersection) and remove not necessary ones
bool FuzzyComposition::rebuild(pointsArray *aSegmentBegin, pointsArray *aSegmentEnd, pointsArray *bSegmentBegin, pointsArray *bSegmentEnd)
{
    // create a reference for each point
    float x1 = aSegmentBegin->point;
    float y1 = aSegmentBegin->pertinence;
    float x2 = aSegmentEnd->point;
    float y2 = aSegmentEnd->pertinence;
    float x3 = bSegmentBegin->point;
    float y3 = bSegmentBegin->pertinence;
    float x4 = bSegmentEnd->point;
    float y4 = bSegmentEnd->pertinence;
    // calculate the denominator and numerator
    float denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    float numera = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    float numerb = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
    // if negative, convert to positive
    if (denom < 0.0)
    {
        denom *= -1.0;
    }
    // If the denominator is zero or close to it, it means that the lines are parallels, so return false for intersection
    if (denom < EPSILON_VALUE)
    {
        // return false for intersection
        return false;
    }
    // if negative, convert to positive
    if (numera < 0.0)
    {
        numera *= -1.0;
    }
    // if negative, convert to positive
    if (numerb < 0.0)
    {
        numerb *= -1.0;
    }
    // verify if has intersection between the segments
    float mua = numera / denom;
    float mub = numerb / denom;
    if (mua <= 0.0 || mua >= 1.0 || mub <= 0.0 || mub >= 1.0)
    {
        // return false for intersection
        return false;
    }
    else
    {
        // we found an intersection
        // auxiliary variable to handle the operation
        pointsArray *aux;
        // allocating in memory
        if ((aux = (pointsArray *)malloc(sizeof(pointsArray))) == NULL)
        {
            // return false if in out of memory
            return false;
        }
        // calculate the point (y) and its pertinence (y) for the new element (pointsArray)
        aux->previous = bSegmentEnd;
        aux->point = x1 + mua * (x2 - x1);
        aux->pertinence = y1 + mua * (y2 - y1);
        aux->next = aSegmentEnd;
        // changing pointsArray to accomplish with new state
        aSegmentBegin->next = aux;
        aSegmentEnd->previous = aux;
        bSegmentBegin->previous = aux;
        bSegmentEnd->next = aux;
        // initiate a proccess of remotion of not needed pointsArray
        // some variables to help in this proccess, the start pointsArray
        pointsArray *temp = bSegmentBegin;
        // do, while
        do
        {
            // hold next
            pointsArray *excl = temp->next;
            // remove it from array
            this->rmvPoint(temp);
            // set new current
            temp = excl;
            // check if it is the stop pointsArray
            if (temp != NULL && temp->point == aux->point && temp->pertinence == aux->pertinence)
            {
                // if true, stop the deletions
                break;
            }
        } while (temp != NULL);
        return true;
    }
}

// Function to remove (deallocate) some pointsArray
bool FuzzyComposition::rmvPoint(pointsArray *point)
{
    if (point != NULL)
    {
        // emptying allocated memory
        free(point);
    }
    return true;
}