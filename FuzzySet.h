/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzySet.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYSET_H
#define FUZZYSET_H

class FuzzySet {
	public:
		// CONSTRUTORES
		FuzzySet();
		FuzzySet(float a, float b, float c, float d);
		// MÉTODOS PÚBLICOS
		float getPointA();
		float getPointB();
		float getPointC();
		float getPointD();
		bool calculatePertinence(float crispValue);
		void setPertinence(float pertinence);
		float getPertinence();
		void reset();

	private:
		// VARIÁVEIS
		float a;
		float b;
		float c;
		float d;
		float pertinence;
};
#endif