#include <iostream>
#include "../FuzzyRule.h"
#include "../FuzzyComposition.h"
#include "../Fuzzy.h"
#include "../FuzzyRuleConsequent.h"
#include "../FuzzyOutput.h"
#include "../FuzzyInput.h"
#include "../FuzzyIO.h"
#include "../FuzzySet.h"
#include "../FuzzyRuleAntecedent.h"

using namespace std;

int main(int argc, char *argv[]) {
	Fuzzy* fuzzy = new Fuzzy;

	FuzzyInput* angleX = new FuzzyInput(1);
	FuzzyInput* angleY = new FuzzyInput(2);

	FuzzyOutput* motor0 = new FuzzyOutput(0);
	FuzzyOutput* motor1 = new FuzzyOutput(1);
	FuzzyOutput* motor2 = new FuzzyOutput(2);
	FuzzyOutput* motor3 = new FuzzyOutput(3);

	float m1out;
	float m2out;
	float m3out;
	float m4out;

	FuzzySet* neg[2];
	FuzzySet* zero[2];
	FuzzySet* pos[2];

	FuzzySet* slow[4];
	FuzzySet* medium[4];
	FuzzySet* fast[4];

	int i;
	for(i =0; i < 2; i++) {
		// conjuntos de entrada
		neg[i] = new FuzzySet(-16, -15, -7.5, 0);
		zero[i] = new FuzzySet(-10, 0, 0, 10);
		pos[i] = new FuzzySet(0, 7.5, 15, 16);
	}

	for(i = 0; i < 4; i++) {
		// conjuntos de saída
		slow[i] = new FuzzySet(-0.4, 0, 0, 0.4);
		medium[i] = new FuzzySet(0.1, 0.5, 0.5, 0.9);
		fast[i] = new FuzzySet(0.6, 1, 1, 1.4);
	}

	angleX->addFuzzySet(neg[0]);
	angleX->addFuzzySet(zero[0]);
	angleX->addFuzzySet(pos[0]);

	angleY->addFuzzySet(neg[1]);
	angleY->addFuzzySet(zero[1]);
	angleY->addFuzzySet(pos[1]);

	motor0->addFuzzySet(slow[0]);
	motor0->addFuzzySet(medium[0]);
	motor0->addFuzzySet(fast[0]);

	motor1->addFuzzySet(slow[1]);
	motor1->addFuzzySet(medium[1]);
	motor1->addFuzzySet(fast[1]);

	motor2->addFuzzySet(slow[2]);
	motor2->addFuzzySet(medium[2]);
	motor2->addFuzzySet(fast[2]);

	motor3->addFuzzySet(slow[3]);
	motor3->addFuzzySet(medium[3]);
	motor3->addFuzzySet(fast[3]);

	fuzzy->addFuzzyInput(angleX);
	fuzzy->addFuzzyInput(angleY);

	fuzzy->addFuzzyOutput(motor0);
	fuzzy->addFuzzyOutput(motor1);
	fuzzy->addFuzzyOutput(motor2);
	fuzzy->addFuzzyOutput(motor3);

	// ifs
	FuzzyRuleAntecedent* movingFront = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* movingBack = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* movingLeft = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* movingRight = new FuzzyRuleAntecedent();
	//    FuzzyRuleAntecedent* stable = new FuzzyRuleAntecedent();

	// thens
	FuzzyRuleConsequent* moveFront = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* moveBack = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* moveLeft = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* moveRight = new FuzzyRuleConsequent();

	// setup ifs
	movingFront->joinWithAND(neg[0], pos[1]);
	movingBack->joinWithAND(pos[0], neg[1]);
	movingLeft->joinWithAND(neg[0], neg[1]);
	movingRight->joinWithAND(pos[0], pos[1]);
	//    stable->joinWithAND(zero[0], zero[1]);

	//setup thens
	moveFront->addOutput(slow[0]);
	moveFront->addOutput(slow[1]);
	moveFront->addOutput(fast[2]);
	moveFront->addOutput(fast[3]);

	moveBack->addOutput(fast[0]);
	moveBack->addOutput(fast[1]);
	moveBack->addOutput(slow[2]);
	moveBack->addOutput(slow[3]);

	moveLeft->addOutput(fast[0]);
	moveLeft->addOutput(slow[1]);
	moveLeft->addOutput(fast[2]);
	moveLeft->addOutput(slow[3]);

	moveRight->addOutput(slow[0]);
	moveRight->addOutput(fast[1]);
	moveRight->addOutput(slow[2]);
	moveRight->addOutput(fast[3]);

	//rules
	FuzzyRule* rule1 = new FuzzyRule(1, movingFront, moveBack);
	FuzzyRule* rule2 = new FuzzyRule(2, movingBack, moveFront);
	FuzzyRule* rule3 = new FuzzyRule(3, movingLeft, moveRight);
	FuzzyRule* rule4 = new FuzzyRule(4, movingRight, moveLeft);

	fuzzy->addFuzzyRule(rule1);
	fuzzy->addFuzzyRule(rule2);
	fuzzy->addFuzzyRule(rule3);
	fuzzy->addFuzzyRule(rule4);

	float dx = -10;
	float dy = 10;

	fuzzy->setInput(1, dx);
	fuzzy->setInput(2, dy);

	fuzzy->fuzzify();

	m1out = fuzzy->defuzzify(0);
	m2out = fuzzy->defuzzify(1);
	m3out = fuzzy->defuzzify(2);
	m4out = fuzzy->defuzzify(3);

	cout << "m1out: " << m1out << ", m2out: " << m2out << ", m3out: " << m3out << ", m4out: " << m4out << endl;
	
	return 0;
}