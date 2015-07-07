/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyOutput.cpp
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyOutput.h"

// CONSTRUTORES
FuzzyOutput::FuzzyOutput() : FuzzyIO(){
}

FuzzyOutput::FuzzyOutput(int index) : FuzzyIO(index){
}

// DESTRUTOR
FuzzyOutput::~FuzzyOutput(){
	this->fuzzyComposition.empty();
}

// MÉTODOS PÚBLICOS
bool FuzzyOutput::truncate(){
	// esvaziando a composição
	this->fuzzyComposition.empty();

	fuzzySetArray *aux;
	aux = this->fuzzySets;
	while(aux != NULL){
		if(aux->fuzzySet->getPertinence() > 0.0){
			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointA(), 0.0) == false){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointA(), 0.0);
			}

			if(aux->fuzzySet->getPointB() == aux->fuzzySet->getPointC() && aux->fuzzySet->getPointA() != aux->fuzzySet->getPointD()){
				// se trinagulo
				if(aux->fuzzySet->getPertinence() == 1.0){
					if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence()) == false){
						this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
					}
				}else{
					float newPointB 		= aux->fuzzySet->getPointB();
					float newPertinenceB 	= aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointA(), 0.0, aux->fuzzySet->getPointB(), 1.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointB, &newPertinenceB);

					if(this->fuzzyComposition.checkPoint(newPointB, newPertinenceB) == false){
						this->fuzzyComposition.addPoint(newPointB, newPertinenceB);
					}

					float newPointC 		= aux->fuzzySet->getPointB();
					float newPertinenceC 	= aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointC(), 1.0, aux->fuzzySet->getPointD(), 0.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointC, &newPertinenceC);

					if(this->fuzzyComposition.checkPoint(newPointC, newPertinenceC) == false){
						this->fuzzyComposition.addPoint(newPointC, newPertinenceC);
					}
				}
			}else if(aux->fuzzySet->getPointB() != aux->fuzzySet->getPointC()){
				// se trapezio
				if(aux->fuzzySet->getPertinence() == 1.0){
					if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence()) == false){
						this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
					}

					if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence()) == false){
						this->fuzzyComposition.addPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence());
					}
				}else{
					float newPointB 		= aux->fuzzySet->getPointB();
					float newPertinenceB 	= aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointA(), 0.0, aux->fuzzySet->getPointB(), 1.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointB, &newPertinenceB);

					if(this->fuzzyComposition.checkPoint(newPointB, newPertinenceB) == false){
						this->fuzzyComposition.addPoint(newPointB, newPertinenceB);
					}

					float newPointC 		= aux->fuzzySet->getPointB();
					float newPertinenceC 	= aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointC(), 1.0, aux->fuzzySet->getPointD(), 0.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointC, &newPertinenceC);

					if(this->fuzzyComposition.checkPoint(newPointC, newPertinenceC) == false){
						this->fuzzyComposition.addPoint(newPointC, newPertinenceC);
					}
				}
			}else{
				//senao singleton
				if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence()) == false){
					this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
				}
			}

			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointD(), 0.0) == false || aux->fuzzySet->getPointD() == aux->fuzzySet->getPointA()){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointD(), 0.0);
			}
		}
		aux = aux->next;
	}

	this->fuzzyComposition.build();

	return true;
}

float FuzzyOutput::getCrispOutput(){
	return this->fuzzyComposition.avaliate();
}

// Um simples Bubble Sort
bool FuzzyOutput::order(){
	fuzzySetArray *aux1;
	fuzzySetArray *aux2;

	aux1 = this->fuzzySets;
	aux2 = this->fuzzySets;

	while(aux1 != NULL){
		while(aux2 != NULL){
			if(aux2->next != NULL){
				if(aux2->fuzzySet->getPointA() > aux2->next->fuzzySet->getPointA()){
					this->swap(aux2, aux2->next);
				}
			}
			aux2 = aux2->next;
		}
		aux2 = this->fuzzySets;
		aux1 = aux1->next;
	}
	return true;
}

// MÉTODOS PRIVADOS
bool FuzzyOutput::swap(fuzzySetArray* fuzzySetA, fuzzySetArray* fuzzySetB){
	FuzzySet* aux;
	
	aux = fuzzySetA->fuzzySet;
	fuzzySetA->fuzzySet = fuzzySetB->fuzzySet;
	fuzzySetB->fuzzySet = aux;

	return true;
}

bool FuzzyOutput::rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* point, float* pertinence){
	float denom, numera, numerb;
	float mua, mub;

	denom  = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	numera = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	numerb = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);

	if(denom < 0.0){
		denom *= -1.0;
	}
	if(numera < 0.0){
		numera *= -1.0;
	}
	if(numerb < 0.0){
		numerb *= -1.0;
	}

	// Se os seguimentos forem paralelos, retornar falso
	if(denom < EPS){
		return false;
	}

	// Verificar se há interseção ao longo do seguimento
	mua = numera / denom;
	mub = numerb / denom;
	if(mua < 0.0 || mua > 1.0 || mub < 0.0 || mub > 1.0){
		return false;
	}else{
		// Calculando o ponto e a pertinencia do novo elemento
		*point 		= x1 + mua * (x2 - x1);
		*pertinence 	= y1 + mua * (y2 - y1);

		return true;
	}
}