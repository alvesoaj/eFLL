/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *          Co authors: AJ Alves <aj.alves@zerokol.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyIO.h"
#include "FuzzyComposition.h"

class FuzzyOutput : public FuzzyIO {
	public:
		// CONSTRUTORES
		FuzzyOutput(int index);
		// DESTRUTOR
		~FuzzyOutput();
		// MÉTODOS PÚBLICOS
		bool truncate();
		float getCrispOutput();
		bool order();

	private:
		// VARIÁVEIS PRIVADAS
		FuzzyComposition fuzzyComposition;
		// MÉTODOS PRIVADOS
		bool swap(fuzzySetArray* fuzzySetA, fuzzySetArray* fuzzySetB);
};
#endif