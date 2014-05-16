/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzySet.cpp
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzySet.h"

FuzzySet::FuzzySet(){
}

FuzzySet::FuzzySet(float a, float b, float c, float d){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->pertinence = 0.0;
}

float FuzzySet::getPointA(){
	return this->a;
}

float FuzzySet::getPointB(){
	return this->b;
}

float FuzzySet::getPointC(){
	return this->c;
}

float FuzzySet::getPointD(){
	return this->d;
}

bool FuzzySet::calculatePertinence(float crispValue){
	float slope;

	if (crispValue < this->a){
		if (this->a == this->b && this->b != this->c && this->c != this->d){
			this->pertinence = 1.0;
		}else{
			this->pertinence = 0.0;
		}
	}else if (crispValue >= this->a && crispValue < this->b){
		slope = 1.0 / (this->b - this->a);
		this->pertinence = slope * (crispValue - this->b) + 1.0;
	}else if (crispValue >= this->b && crispValue <= this->c){
		this->pertinence = 1.0;
	}else if (crispValue > this->c && crispValue <= this->d){
		slope = 1.0 / (this->c - this->d);
		this->pertinence = slope * (crispValue - this->c) + 1.0;
	}else if (crispValue > this->d){
		if (this->c == this->d && this->c != this->b && this->b != this->a){
			this->pertinence = 1.0;
		}else{
			this->pertinence = 0.0;
		}
	}
	return true;
}

void FuzzySet::setPertinence(float pertinence){
	if(this->pertinence < pertinence){
		this->pertinence = pertinence;
	}
}

float FuzzySet::getPertinence(){
	return this->pertinence;
}

void FuzzySet::reset(){
	this->pertinence = 0.0;
}