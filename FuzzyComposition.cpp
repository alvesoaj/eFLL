/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyComposition.cpp
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyComposition.h"
#include <math.h>

// CONSTRUTORES
FuzzyComposition::FuzzyComposition(){
	this->pointsCursor 	= NULL;
	this->points 		= NULL;
}

// DESTRUTOR
FuzzyComposition::~FuzzyComposition(){
	this->cleanPoints(this->points);
}

bool FuzzyComposition::addPoint(float point, float pertinence){
	pointsArray* aux;
	// Alocando espaço na memória
	if((aux = (pointsArray* ) malloc(sizeof(pointsArray))) == NULL){
		return false;
	}
	aux->previous = NULL;
	aux->point = point;
	aux->pertinence = pertinence;
	aux->next = NULL;

	if(this->points == NULL){
		this->points = aux;
		this->pointsCursor  = aux;
	}else{
		aux->previous = this->pointsCursor;
		this->pointsCursor = aux;
		aux->previous->next = this->pointsCursor;
	}
	return true;
}

bool FuzzyComposition::checkPoint(float point, float pertinence){
	pointsArray* aux;
	aux = this->pointsCursor;
	while(aux != NULL){
		if(aux->point == point && aux->pertinence == pertinence){
			return true;
		}
		aux = aux->previous;
	}
	return false;
}

bool FuzzyComposition::build(){
	pointsArray* aux;

	aux = this->points;
	while(aux != NULL){
		pointsArray* temp = aux;
		while(temp->previous != NULL){
			if(temp->point < temp->previous->point){
				break;
			}
			temp = temp->previous;
		}
		pointsArray* zPoint;
		if(temp != NULL){
			zPoint = temp;
			while(temp->previous != NULL){
				bool result = false;
				if(temp->previous->previous != NULL){
					result = rebuild(zPoint, zPoint->next, temp->previous, temp->previous->previous);
				}
				if(result == true){
					aux = this->points;
					break;
				}
				temp = temp->previous;
			}
		}
		aux = aux->next;
	}
	return true;
}

float FuzzyComposition::avaliate(){
	pointsArray* aux;
	float numerator 	= 0.0;
	float denominator 	= 0.0;

	aux = this->points;
	while(aux != NULL){
		if(aux->next != NULL){
			float area = 0.0;
			float middle = 0.0;
			if(aux->point == aux->next->point){
				// Se Singleton
				area 	= aux->pertinence;
				middle 	= aux->point;
			}else if(aux->pertinence == 0.0 || aux->next->pertinence == 0.0){
				// Se triangulo
				float pertinence;
				if(aux->pertinence > 0.0){
					pertinence = aux->pertinence;
				}else{
					pertinence = aux->next->pertinence;
				}
				area 	= ((aux->next->point - aux->point) * pertinence) / 2.0;
				if(aux->pertinence < aux->next->pertinence){
					middle 	= ((aux->next->point - aux->point) / 1.5) + aux->point;
				}else{
					middle 	= ((aux->next->point - aux->point) / 3.0) + aux->point;
				}
			}else if((aux->pertinence > 0.0 && aux->next->pertinence > 0.0) && (aux->pertinence == aux->next->pertinence)){
				// Se quadrado
				area 	= (aux->next->point - aux->point) * aux->pertinence;
				middle 	= ((aux->next->point - aux->point) / 2.0) + aux->point;
			}else if((aux->pertinence > 0.0 && aux->next->pertinence > 0.0) && (aux->pertinence != aux->next->pertinence)){
				// Se trapezio
				area 	= ((aux->pertinence + aux->next->pertinence) / 2.0) * (aux->next->point - aux->point);
				middle 	= ((aux->next->point - aux->point) / 2.0) + aux->point;
			}
			numerator 	+= middle * area;
			denominator += area;
		}
		aux = aux->next;
	}

	if(denominator == 0.0){
		return 0.0;
	}else{
		return numerator / denominator;
	}
}

bool FuzzyComposition::empty(){
	// limpando a memória
	this->cleanPoints(this->points);
	// resetando os ponteiros
	this->points = NULL;
	this->pointsCursor = NULL;
	return true;
}

// MÉTODOS PRIVADOS
void FuzzyComposition::cleanPoints(pointsArray* aux){
	if(aux != NULL){
		// Esvaziando a memória alocada
		this->cleanPoints(aux->next);
		free(aux);
	}
}

bool FuzzyComposition::rebuild(pointsArray* aSegmentBegin, pointsArray* aSegmentEnd, pointsArray* bSegmentBegin, pointsArray* bSegmentEnd){
	float x1 = aSegmentBegin->point;
	float y1 = aSegmentBegin->pertinence;
	float x2 = aSegmentEnd->point;
	float y2 = aSegmentEnd->pertinence;
	float x3 = bSegmentBegin->point;
	float y3 = bSegmentBegin->pertinence;
	float x4 = bSegmentEnd->point;
	float y4 = bSegmentEnd->pertinence;
	float point, pertinence;
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
		point 		= x1 + mua * (x2 - x1);
		pertinence 	= y1 + mua * (y2 - y1);

		// Adicionando um novo ponto
		pointsArray* aux;
		// Alocando espaço na memória
		if((aux = (pointsArray *) malloc(sizeof(pointsArray))) == NULL){
			return false;
		}

		aux->previous = bSegmentEnd;
		aux->point = point;
		aux->pertinence = pertinence;
		aux->next = aSegmentEnd;

		bSegmentEnd->next = aux;
		aSegmentEnd->previous = aux;

		float stopPoint = bSegmentBegin->point;
		float stopPertinence = bSegmentBegin->pertinence;

		pointsArray* temp = aSegmentBegin;
		pointsArray* excl;

		do{
			float pointToCompare = temp->point;
			float pertinenceToCompare = temp->pertinence;

			excl = temp->previous;

			this->rmvPoint(temp);

			temp = excl;

			if(stopPoint == pointToCompare && stopPertinence == pertinenceToCompare){
				break;
			}
		}while(temp != NULL);

		return true;
	}
}

bool FuzzyComposition::rmvPoint(pointsArray* point){
	if(point != NULL){
		free(point);
	}
	return true;
}
