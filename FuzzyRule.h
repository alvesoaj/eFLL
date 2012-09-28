/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRule.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *          Co authors: AJ Alves <aj.alves@zerokol.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYRULE_H
#define FUZZYRULE_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyRuleAntecedent.h"
#include "FuzzyRuleConsequent.h"

class FuzzyRule {
	public:
		// CONSTRUTORES
		FuzzyRule(int index, FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzyRuleConsequent* fuzzyRuleConsequent);
		// MÉTODOS PÚBLICOS
		int getIndex();
		bool evaluateExpression();
		bool isFired();

	private:
		// VARIÁVEIS PRIVADAS
		int index;
		bool fired;
		FuzzyRuleAntecedent* fuzzyRuleAntecedent;
		FuzzyRuleConsequent* fuzzyRuleConsequent;
};
#endif