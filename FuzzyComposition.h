/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyComposition.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYCOMPOSITION_H
#define FUZZYCOMPOSITION_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include <stdlib.h>

// CONSTANTES
#define EPS 1.0E-3

// Estrutura de uma lista para guardar os pontos
struct pointsArray{
    pointsArray* previous;
    float point;
    float pertinence;
    pointsArray* next;
};

class FuzzyComposition{
    public:
        // CONSTRUTORES
        FuzzyComposition();
        // DESTRUTOR
        ~FuzzyComposition();
        // MÉTODOS PÚBLICOS
        bool addPoint(float point, float pertinence);
        bool checkPoint(float point, float pertinence);
        bool build();
        float avaliate();
        bool empty();

    private:
        // VARIÁVEIS PRIVADAS
        pointsArray* pointsCursor;
        pointsArray* points;

        // MÉTODOS PRIVADOS
        void cleanPoints(pointsArray* aux);
        bool rebuild(pointsArray* aSegmentBegin, pointsArray* aSegmentEnd, pointsArray* bSegmentBegin, pointsArray* bSegmentEnd);
        bool rmvPoint(pointsArray* point);
};
#endif