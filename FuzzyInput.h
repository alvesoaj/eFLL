/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyInput.h
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYINPUT_H
#define FUZZYINPUT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyIO.h"

class FuzzyInput : public FuzzyIO {
    public:
        // CONSTRUTORES
        FuzzyInput();
        FuzzyInput(int index);
        // DESTRUTOR
        ~FuzzyInput();
        // MÉTODOS PÚBLICOS
        bool calculateFuzzySetPertinences();
};
#endif