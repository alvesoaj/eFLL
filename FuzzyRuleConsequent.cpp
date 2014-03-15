/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleConsequent.cpp
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyRuleConsequent.h"

// CONSTRUTORES
FuzzyRuleConsequent::FuzzyRuleConsequent(){
	this->fuzzySetOutputs = NULL;
	this->fuzzySetOutputsCursor = NULL;
}

// DESTRUTOR
FuzzyRuleConsequent::~FuzzyRuleConsequent(){
	this->cleanFuzzySets(this->fuzzySetOutputs);
}

// MÉTODOS PÚBLICOS
bool FuzzyRuleConsequent::addOutput(FuzzySet* fuzzySet){
	fuzzySetOutputArray *aux;
	// Alocando espaço na memória
	if((aux = (fuzzySetOutputArray *) malloc(sizeof(fuzzySetOutputArray))) == NULL){
		return false;
	}
	aux->fuzzySet 	= fuzzySet;
	aux->next 		= NULL;

	if(this->fuzzySetOutputs == NULL){
		this->fuzzySetOutputs = aux;
		this->fuzzySetOutputsCursor	= aux;
	}else{
		this->fuzzySetOutputsCursor->next = aux;
		this->fuzzySetOutputsCursor = aux;
	}
	return true;
}

bool FuzzyRuleConsequent::evaluate(float power){
	fuzzySetOutputArray *aux;
	aux = this->fuzzySetOutputs;
	while(aux != NULL){
		aux->fuzzySet->setPertinence(power);
		aux = aux->next;
	}
	return true;
}

// MÉTODOS PRIVADOS
void FuzzyRuleConsequent::cleanFuzzySets(fuzzySetOutputArray* aux){
	if(aux != NULL){
		// Esvaziando a memória alocada
		this->cleanFuzzySets(aux->next);
		free(aux);
	}
}