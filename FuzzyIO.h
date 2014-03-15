/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyIO.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYIO_H
#define FUZZYIO_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include <stdlib.h>
#include "FuzzySet.h"

// Estrutura de uma lista de FuzzySet
struct fuzzySetArray{
	FuzzySet* fuzzySet;
	fuzzySetArray* next;
};

class FuzzyIO {
	public:
		// CONSTRUTORES
		FuzzyIO();
		FuzzyIO(int index);
		// DESTRUTOR
		~FuzzyIO();
		// MÉTODOS PÚBLICOS
		int getIndex();
		void setCrispInput(float crispInput);
		float getCrispInput();
		bool addFuzzySet(FuzzySet* fuzzySet);
		void resetFuzzySets();

	protected:
		// VARIÁVEIS PROTEGIDAS
		int index;
		float crispInput;
		fuzzySetArray* fuzzySets;
		fuzzySetArray* fuzzySetsCursor;
		// MÉTODOS PROTEGIDOS
		void cleanFuzzySets(fuzzySetArray* aux);
};
#endif