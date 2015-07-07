/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyIO.h"
#include "FuzzyComposition.h"

// Estrutura de uma linha
struct line{
	float xBegin;
	float yBegin;
	float xEnd;
	float yEnd;
};

class FuzzyOutput : public FuzzyIO {
	public:
		// CONSTRUTORES
		FuzzyOutput();
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
		bool rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* point, float* pertinence);
};
#endif