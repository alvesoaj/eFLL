#include <iostream>
#include "../../FuzzyRule.h"
#include "../../FuzzyComposition.h"
#include "../../Fuzzy.h"
#include "../../FuzzyRuleConsequent.h"
#include "../../FuzzyOutput.h"
#include "../../FuzzyInput.h"
#include "../../FuzzyIO.h"
#include "../../FuzzySet.h"
#include "../../FuzzyRuleAntecedent.h"

using namespace std;

int main(int argc, char *argv[]) {
	Fuzzy* fuzzy = new Fuzzy();

	// FuzzyInput
	FuzzyInput* distance = new FuzzyInput(1);

	FuzzySet* close = new FuzzySet(0, 20, 20, 40);
	distance->addFuzzySet(close);
	FuzzySet* safe = new FuzzySet(30, 50, 50, 70);
	distance->addFuzzySet(safe);
	FuzzySet* distante = new FuzzySet(60, 80, 100, 100);
	distance->addFuzzySet(distante);

	fuzzy->addFuzzyInput(distance);

	// FuzzyInput
	FuzzyInput* inputSpeed = new FuzzyInput(2);

	FuzzySet* stoped = new FuzzySet(0, 0, 0, 0);
	inputSpeed->addFuzzySet(stoped);
	FuzzySet* slow = new FuzzySet(1, 10, 10, 20);
	inputSpeed->addFuzzySet(slow);
	FuzzySet* normal = new FuzzySet(15, 30, 30, 50);
	inputSpeed->addFuzzySet(normal);
	FuzzySet* quick = new FuzzySet(45, 60, 70, 70);
	inputSpeed->addFuzzySet(quick);

	fuzzy->addFuzzyInput(inputSpeed);

	// FuzzyInput
	FuzzyInput* temperature = new FuzzyInput(3);

	FuzzySet* cold = new FuzzySet(-30, -30, -20, -10);
	temperature->addFuzzySet(cold);
	FuzzySet* good = new FuzzySet(-15, 0, 0, 15);
	temperature->addFuzzySet(good);
	FuzzySet* hot = new FuzzySet(10, 20, 30, 30);
	temperature->addFuzzySet(hot);

	fuzzy->addFuzzyInput(temperature);

	// FuzzyOutput
	FuzzyOutput* risk = new FuzzyOutput(1);

	FuzzySet* minimum = new FuzzySet(0, 20, 20, 40);
	risk->addFuzzySet(minimum);
	FuzzySet* average = new FuzzySet(30, 50, 50, 70);
	risk->addFuzzySet(average);
	FuzzySet* maximum = new FuzzySet(60, 80, 80, 100);
	risk->addFuzzySet(maximum);

	fuzzy->addFuzzyOutput(risk);

	// FuzzyOutput
	// adicionando speed como output também
	FuzzyOutput* outputSpeed = new FuzzyOutput(2);

	FuzzySet* stopedOut = new FuzzySet(0, 0, 0, 0);
	outputSpeed->addFuzzySet(stopedOut);
	FuzzySet* slowOut = new FuzzySet(1, 10, 10, 20);
	outputSpeed->addFuzzySet(slowOut);
	FuzzySet* normalOut = new FuzzySet(15, 30, 30, 50);
	outputSpeed->addFuzzySet(normalOut);
	FuzzySet* quickOut = new FuzzySet(45, 60, 70, 70);
	outputSpeed->addFuzzySet(quickOut);

	fuzzy->addFuzzyOutput(outputSpeed);

	// Building FuzzyRule
	FuzzyRuleAntecedent* distanceCloseAndSpeedQuick = new FuzzyRuleAntecedent();
	distanceCloseAndSpeedQuick->joinWithAND(close, quick);
	FuzzyRuleAntecedent* temperatureCold = new FuzzyRuleAntecedent();
	temperatureCold->joinSingle(cold);
	FuzzyRuleAntecedent* ifDistanceCloseAndSpeedQuickOrTemperatureCold = new FuzzyRuleAntecedent();
	ifDistanceCloseAndSpeedQuickOrTemperatureCold->joinWithOR(distanceCloseAndSpeedQuick, temperatureCold);

	FuzzyRuleConsequent* thenRisMaximumAndSpeedSlow = new FuzzyRuleConsequent();
	thenRisMaximumAndSpeedSlow->addOutput(maximum);
	thenRisMaximumAndSpeedSlow->addOutput(slowOut);

	FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndSpeedQuickOrTemperatureCold, thenRisMaximumAndSpeedSlow);
	fuzzy->addFuzzyRule(fuzzyRule1);

	// Building FuzzyRule
	FuzzyRuleAntecedent* distanceSafeAndSpeedNormal = new FuzzyRuleAntecedent();
	distanceSafeAndSpeedNormal->joinWithAND(safe, normal);
	FuzzyRuleAntecedent* ifDistanceSafeAndSpeedNormalOrTemperatureGood = new FuzzyRuleAntecedent();
	ifDistanceSafeAndSpeedNormalOrTemperatureGood->joinWithOR(distanceSafeAndSpeedNormal, good);

	FuzzyRuleConsequent* thenRiskAverageAndSpeedNormal = new FuzzyRuleConsequent();
	thenRiskAverageAndSpeedNormal->addOutput(average);
	thenRiskAverageAndSpeedNormal->addOutput(normalOut);

	FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifDistanceSafeAndSpeedNormalOrTemperatureGood, thenRiskAverageAndSpeedNormal);
	fuzzy->addFuzzyRule(fuzzyRule2);

	// Building FuzzyRule
	FuzzyRuleAntecedent* distanceDistanteAndSpeedSlow = new FuzzyRuleAntecedent();
	distanceDistanteAndSpeedSlow->joinWithAND(distante, slow);
	FuzzyRuleAntecedent* ifDistanceDistanteAndSpeedSlowOrTemperatureHot = new FuzzyRuleAntecedent();
	ifDistanceDistanteAndSpeedSlowOrTemperatureHot->joinWithOR(distanceDistanteAndSpeedSlow, hot);

	FuzzyRuleConsequent* thenRiskMinimumSpeedQuick = new FuzzyRuleConsequent();
	thenRiskMinimumSpeedQuick->addOutput(minimum);
	thenRiskMinimumSpeedQuick->addOutput(quickOut);

	FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifDistanceDistanteAndSpeedSlowOrTemperatureHot, thenRiskMinimumSpeedQuick);
	fuzzy->addFuzzyRule(fuzzyRule3);

	fuzzy->setInput(1, 10);
	fuzzy->setInput(2, 30);
	fuzzy->setInput(3, -15);

	fuzzy->fuzzify();

	cout << "Distância: " << close->getPertinence() << ", " << safe->getPertinence() << ", " << distante->getPertinence() << endl;
	cout << "Velocidade: " << stoped->getPertinence() << ", " << slow->getPertinence() << ", " << normal->getPertinence() << ", " << quick->getPertinence() << endl;
	cout << "Temperatura: " << cold->getPertinence() << ", " << good->getPertinence() << ", " << hot->getPertinence() << endl;

	cout << "regra1: " << fuzzyRule1->isFired() << ", regra2: " << fuzzyRule2->isFired() << ", regra3: " << fuzzyRule3->isFired() << endl;

	float output1 = fuzzy->defuzzify(1);
	float output2 = fuzzy->defuzzify(2);

	cout << "Saída Risco: " << output1 << ", Saída Velocidade: " << output2 << endl;
	
	return 0;
}