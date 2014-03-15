/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleConsequent.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYRULECONSEQUENT_H
#define FUZZYRULECONSEQUENT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include <stdlib.h>
#include "FuzzySet.h"

// Estrutura de uma lista de FuzzySet
struct fuzzySetOutputArray{
	FuzzySet* fuzzySet;
	fuzzySetOutputArray* next;
};

class FuzzyRuleConsequent {
	public:
		// CONSTRUTORES
		FuzzyRuleConsequent();
		// DESTRUTOR
		~FuzzyRuleConsequent();
		// MÉTODOS PÚBLICOS
		bool addOutput(FuzzySet* fuzzySet);
		bool evaluate(float power);

	private:
		// VARIÁVEIS PRIVADAS
		fuzzySetOutputArray* fuzzySetOutputsCursor;
		fuzzySetOutputArray* fuzzySetOutputs;
		// MÉTODOS PRIVADOS
		void cleanFuzzySets(fuzzySetOutputArray* aux);
};
#endif