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
	// declare fuzzy stability variables
	Fuzzy* fuzzyStability = new Fuzzy;

	FuzzyInput* angleX = new FuzzyInput(1);
	FuzzyInput* angleY = new FuzzyInput(2);

	FuzzyOutput* motor0 = new FuzzyOutput(0);
	FuzzyOutput* motor1 = new FuzzyOutput(1);
	FuzzyOutput* motor2 = new FuzzyOutput(2);
	FuzzyOutput* motor3 = new FuzzyOutput(3);

	FuzzySet* neg[2];
	FuzzySet* zero[2];
	FuzzySet* pos[2];

	FuzzySet* slow[4];
	FuzzySet* medium[4];
	FuzzySet* fast[4];

	// declare fuzzy movement variables
	Fuzzy* fuzzyMovement = new Fuzzy;

	FuzzyInput* inputAngle = new FuzzyInput(1);

	FuzzyOutput* mmotor0 = new FuzzyOutput(0);
	FuzzyOutput* mmotor1 = new FuzzyOutput(1);
	FuzzyOutput* mmotor2 = new FuzzyOutput(2);
	FuzzyOutput* mmotor3 = new FuzzyOutput(3);

	FuzzySet* rright;
	FuzzySet* forward;
	FuzzySet* left;
	FuzzySet* back;
	FuzzySet* lright;

	FuzzySet* mslow[4];
	FuzzySet* mfast[4];

	int i;
    for(i = 0; i < 2; i++) {
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
    
    fuzzyStability->addFuzzyInput(angleX);
    fuzzyStability->addFuzzyInput(angleY);
    
    fuzzyStability->addFuzzyOutput(motor0);
    fuzzyStability->addFuzzyOutput(motor1);
    fuzzyStability->addFuzzyOutput(motor2);
    fuzzyStability->addFuzzyOutput(motor3);
    
    // ifs
    FuzzyRuleAntecedent* movingFront = new FuzzyRuleAntecedent();
    FuzzyRuleAntecedent* movingBack = new FuzzyRuleAntecedent();
    FuzzyRuleAntecedent* movingLeft = new FuzzyRuleAntecedent();
    FuzzyRuleAntecedent* movingRight = new FuzzyRuleAntecedent();
    FuzzyRuleAntecedent* stable = new FuzzyRuleAntecedent();
    
    // thens
    FuzzyRuleConsequent* moveFront = new FuzzyRuleConsequent();
    FuzzyRuleConsequent* moveBack = new FuzzyRuleConsequent();
    FuzzyRuleConsequent* moveLeft = new FuzzyRuleConsequent();
    FuzzyRuleConsequent* moveRight = new FuzzyRuleConsequent();
    FuzzyRuleConsequent* holdOn = new FuzzyRuleConsequent();

    // setup ifs
    movingFront->joinWithAND(neg[0], pos[1]);
    movingBack->joinWithAND(pos[0], neg[1]);
    movingLeft->joinWithAND(neg[0], neg[1]);
    movingRight->joinWithAND(pos[0], pos[1]);
    stable->joinWithAND(zero[0], zero[1]);

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
    
    holdOn->addOutput(medium[0]);
    holdOn->addOutput(medium[1]);
    holdOn->addOutput(medium[2]);
    holdOn->addOutput(medium[3]);
    
    FuzzyRule* rule1 = new FuzzyRule(1, movingFront, moveBack);
    FuzzyRule* rule2 = new FuzzyRule(2, movingBack, moveFront);
    FuzzyRule* rule3 = new FuzzyRule(3, movingLeft, moveRight);
    FuzzyRule* rule4 = new FuzzyRule(4, movingRight, moveLeft);
    FuzzyRule* rule5 = new FuzzyRule(5, stable, holdOn);
    
    fuzzyStability->addFuzzyRule(rule1);
    fuzzyStability->addFuzzyRule(rule2);
    fuzzyStability->addFuzzyRule(rule3);
    fuzzyStability->addFuzzyRule(rule4);
    fuzzyStability->addFuzzyRule(rule5);

    rright = new FuzzySet(0, 0, 0, 55);
	forward = new FuzzySet(30, 90, 90, 150);
	left = new FuzzySet(120, 180, 180, 240);
	back = new FuzzySet(210, 270, 270, 330);
	lright = new FuzzySet(300, 360, 360, 360);

	for(int i = 0; i < 4; i++) {
		mslow[i] = new FuzzySet(-0.4, 0, 0, 0.8);
		mfast[i] = new FuzzySet(0.2, 1, 1, 1.4);
	}

	inputAngle->addFuzzySet(rright);
	inputAngle->addFuzzySet(forward);
	inputAngle->addFuzzySet(left);
	inputAngle->addFuzzySet(back);
	inputAngle->addFuzzySet(lright);

	mmotor0->addFuzzySet(mslow[0]);
	mmotor0->addFuzzySet(mfast[0]);
	mmotor1->addFuzzySet(mslow[1]);
	mmotor1->addFuzzySet(mfast[1]);
	mmotor2->addFuzzySet(mslow[2]);
	mmotor2->addFuzzySet(mfast[2]);
	mmotor3->addFuzzySet(mslow[3]);
	mmotor3->addFuzzySet(mfast[3]);

	fuzzyMovement->addFuzzyInput(inputAngle);
	fuzzyMovement->addFuzzyOutput(mmotor0);
	fuzzyMovement->addFuzzyOutput(mmotor1);
	fuzzyMovement->addFuzzyOutput(mmotor2);
	fuzzyMovement->addFuzzyOutput(mmotor3);

	FuzzyRuleAntecedent* cmdForward = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* cmdBack = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* cmdLeft = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* cmdLRight = new FuzzyRuleAntecedent();
	FuzzyRuleAntecedent* cmdRRight = new FuzzyRuleAntecedent();

	// thens
	FuzzyRuleConsequent* goForward = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* goBack = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* goLeft = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* goLRight = new FuzzyRuleConsequent();
	FuzzyRuleConsequent* goRRight = new FuzzyRuleConsequent();

	cmdForward->joinSingle(forward);
	cmdBack->joinSingle(back);
	cmdLeft->joinSingle(left);
	cmdLRight->joinSingle(lright);
	cmdRRight->joinSingle(rright);

	goForward->addOutput(mfast[0]);
	goForward->addOutput(mfast[1]);
	goForward->addOutput(mslow[2]);
	goForward->addOutput(mslow[3]);

	goBack->addOutput(mslow[0]);
	goBack->addOutput(mslow[1]);
	goBack->addOutput(mfast[2]);
	goBack->addOutput(mfast[3]);

	goLeft->addOutput(mfast[0]);
	goLeft->addOutput(mslow[1]);
	goLeft->addOutput(mfast[2]);
	goLeft->addOutput(mslow[3]);

	goLRight->addOutput(mslow[0]);
	goLRight->addOutput(mfast[1]);
	goLRight->addOutput(mslow[2]);
	goLRight->addOutput(mfast[3]);

	goRRight->addOutput(mslow[0]);
	goRRight->addOutput(mfast[1]);
	goRRight->addOutput(mslow[2]);
	goRRight->addOutput(mfast[3]);

	fuzzyMovement->addFuzzyRule(new FuzzyRule(1, cmdForward, goForward));
	fuzzyMovement->addFuzzyRule(new FuzzyRule(2, cmdBack, goBack));
	fuzzyMovement->addFuzzyRule(new FuzzyRule(3, cmdLeft, goLeft));
	fuzzyMovement->addFuzzyRule(new FuzzyRule(4, cmdLRight, goLRight));
	fuzzyMovement->addFuzzyRule(new FuzzyRule(5, cmdRRight, goRRight));

	double dx = 10;
	double dy = -4;

	double m1out;
	double m2out;
	double m3out;
	double m4out;

	long entrada = 0;

	bool moving;

	for(i=0; i < 360; i++){

		if(i%360 == 0){
			moving = false;
		}else{
			moving = true;
		}

		if (!moving) {
			fuzzyStability->setInput(1, dx);
			fuzzyStability->setInput(2, dy);
			fuzzyStability->fuzzify();

			m1out = fuzzyStability->defuzzify(0);
			m2out = fuzzyStability->defuzzify(1);
			m3out = fuzzyStability->defuzzify(2);
			m4out = fuzzyStability->defuzzify(3);
		}else {
			fuzzyMovement->setInput(1, entrada);
			fuzzyMovement->fuzzify();

			m1out = fuzzyMovement->defuzzify(0);
			m2out = fuzzyMovement->defuzzify(1);
			m3out = fuzzyMovement->defuzzify(2);
			m4out = fuzzyMovement->defuzzify(3);
		}

		std::cout << "entrada: " << entrada << " dx: " << dx << " dy: " << dy << " m1out: " << m1out << " m2out: " << m2out << " m3out: " << m3out << " m4out: " << m4out << std::endl;

		entrada++;
		if (entrada > 360) {
			entrada = 0;
		}
	}

	return 0;
}