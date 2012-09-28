#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

// Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();

FuzzySet* close = new FuzzySet(0, 20, 20, 40);
FuzzySet* safe = new FuzzySet(30, 50, 50, 70);
FuzzySet* distante = new FuzzySet(60, 80, 100, 100);

FuzzySet* stoped = new FuzzySet(0, 0, 0, 0);
FuzzySet* slow = new FuzzySet(1, 10, 10, 20);
FuzzySet* normal = new FuzzySet(15, 30, 30, 50);
FuzzySet* quick = new FuzzySet(45, 60, 70, 70);

FuzzySet* cold = new FuzzySet(-30, -30, -20, -10);
FuzzySet* good = new FuzzySet(-15, 0, 0, 15);
FuzzySet* hot = new FuzzySet(10, 20, 30, 30);

void setup(){
  Serial.begin(9600);
  
  // FuzzyInput
  FuzzyInput* distance = new FuzzyInput(1);
  distance->addFuzzySet(close);
  distance->addFuzzySet(safe);
  distance->addFuzzySet(distante);

  fuzzy->addFuzzyInput(distance);

  // FuzzyInput
  FuzzyInput* inputSpeed = new FuzzyInput(2);
  inputSpeed->addFuzzySet(stoped);
  inputSpeed->addFuzzySet(slow);
  inputSpeed->addFuzzySet(normal);
  inputSpeed->addFuzzySet(quick);

  fuzzy->addFuzzyInput(inputSpeed);

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(3);
  temperature->addFuzzySet(cold);
  temperature->addFuzzySet(good);
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
}

void loop(){
  fuzzy->setInput(1, 10);
  fuzzy->setInput(2, 30);
  fuzzy->setInput(3, -15);

  fuzzy->fuzzify();
  
  Serial.print("Distancia: ");
  Serial.print(close->getPertinence());
  Serial.print(", ");
  Serial.print(safe->getPertinence());
  Serial.print(", ");
  Serial.println(distante->getPertinence());
  
  Serial.print("Velocidade: ");
  Serial.print(stoped->getPertinence());
  Serial.print(", ");
  Serial.print(slow->getPertinence());
  Serial.print(", ");
  Serial.print(normal->getPertinence());
  Serial.print(", ");
  Serial.println(quick->getPertinence());
  
  Serial.print("Temperatura: ");
  Serial.print(cold->getPertinence());
  Serial.print(", ");
  Serial.print(good->getPertinence());
  Serial.print(", ");
  Serial.println(hot->getPertinence());

  float output1 = fuzzy->defuzzify(1);
  float output2 = fuzzy->defuzzify(2);
  
  Serial.print("Saida risco: ");
  Serial.print(output1);
  Serial.print(", Saida velocidade: ");
  Serial.println(output2);

  delay(100000);
}