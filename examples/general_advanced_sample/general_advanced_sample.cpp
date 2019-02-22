#include <iostream>
#include <time.h>
#include "../../Fuzzy.h"

using namespace std;

int random(int from, int to)
{
  return (rand() % (to - from)) + from;
}

int main(int argc, char *argv[])
{
  // Set a seed to rand
  srand((unsigned)time(0));

  Fuzzy *fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput *distance = new FuzzyInput(1);

  FuzzySet *near = new FuzzySet(0, 20, 20, 40);
  distance->addFuzzySet(near);
  FuzzySet *safe = new FuzzySet(30, 50, 50, 70);
  distance->addFuzzySet(safe);
  FuzzySet *distant = new FuzzySet(60, 80, 100, 100);
  distance->addFuzzySet(distant);

  fuzzy->addFuzzyInput(distance);

  // FuzzyInput
  FuzzyInput *inputSpeed = new FuzzyInput(2);

  FuzzySet *stopedInput = new FuzzySet(0, 0, 0, 0);
  inputSpeed->addFuzzySet(stopedInput);
  FuzzySet *slowInput = new FuzzySet(1, 10, 10, 20);
  inputSpeed->addFuzzySet(slowInput);
  FuzzySet *normalInput = new FuzzySet(15, 30, 30, 50);
  inputSpeed->addFuzzySet(normalInput);
  FuzzySet *quickInput = new FuzzySet(45, 60, 70, 70);
  inputSpeed->addFuzzySet(quickInput);

  fuzzy->addFuzzyInput(inputSpeed);

  // FuzzyInput
  FuzzyInput *temperature = new FuzzyInput(3);

  FuzzySet *cold = new FuzzySet(-30, -30, -20, -10);
  temperature->addFuzzySet(cold);
  FuzzySet *good = new FuzzySet(-15, 0, 0, 15);
  temperature->addFuzzySet(good);
  FuzzySet *hot = new FuzzySet(10, 20, 30, 30);
  temperature->addFuzzySet(hot);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyOutput
  FuzzyOutput *risk = new FuzzyOutput(1);

  FuzzySet *minimum = new FuzzySet(0, 20, 20, 40);
  risk->addFuzzySet(minimum);
  FuzzySet *average = new FuzzySet(30, 50, 50, 70);
  risk->addFuzzySet(average);
  FuzzySet *maximum = new FuzzySet(60, 80, 80, 100);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // FuzzyOutput
  FuzzyOutput *speedOutput = new FuzzyOutput(2);

  FuzzySet *stopedOutput = new FuzzySet(0, 0, 0, 0);
  speedOutput->addFuzzySet(stopedOutput);
  FuzzySet *slowOutput = new FuzzySet(1, 10, 10, 20);
  speedOutput->addFuzzySet(slowOutput);
  FuzzySet *normalOutput = new FuzzySet(15, 30, 30, 50);
  speedOutput->addFuzzySet(normalOutput);
  FuzzySet *quickOutput = new FuzzySet(45, 60, 70, 70);
  speedOutput->addFuzzySet(quickOutput);

  fuzzy->addFuzzyOutput(speedOutput);

  // Building FuzzyRule
  FuzzyRuleAntecedent *distanceCloseAndSpeedQuick = new FuzzyRuleAntecedent();
  distanceCloseAndSpeedQuick->joinWithAND(near, quickInput);
  FuzzyRuleAntecedent *temperatureCold = new FuzzyRuleAntecedent();
  temperatureCold->joinSingle(cold);
  FuzzyRuleAntecedent *ifDistanceCloseAndSpeedQuickOrTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceCloseAndSpeedQuickOrTemperatureCold->joinWithOR(distanceCloseAndSpeedQuick, temperatureCold);

  FuzzyRuleConsequent *thenRisMaximumAndSpeedSlow = new FuzzyRuleConsequent();
  thenRisMaximumAndSpeedSlow->addOutput(maximum);
  thenRisMaximumAndSpeedSlow->addOutput(slowOutput);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndSpeedQuickOrTemperatureCold, thenRisMaximumAndSpeedSlow);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent *distanceSafeAndSpeedNormal = new FuzzyRuleAntecedent();
  distanceSafeAndSpeedNormal->joinWithAND(safe, normalInput);
  FuzzyRuleAntecedent *ifDistanceSafeAndSpeedNormalOrTemperatureGood = new FuzzyRuleAntecedent();
  ifDistanceSafeAndSpeedNormalOrTemperatureGood->joinWithOR(distanceSafeAndSpeedNormal, good);

  FuzzyRuleConsequent *thenRiskAverageAndSpeedNormal = new FuzzyRuleConsequent();
  thenRiskAverageAndSpeedNormal->addOutput(average);
  thenRiskAverageAndSpeedNormal->addOutput(normalOutput);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifDistanceSafeAndSpeedNormalOrTemperatureGood, thenRiskAverageAndSpeedNormal);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent *distanceDistantAndSpeedSlow = new FuzzyRuleAntecedent();
  distanceDistantAndSpeedSlow->joinWithAND(distant, slowInput);
  FuzzyRuleAntecedent *ifDistanceDistantAndSpeedSlowOrTemperatureHot = new FuzzyRuleAntecedent();
  ifDistanceDistantAndSpeedSlowOrTemperatureHot->joinWithOR(distanceDistantAndSpeedSlow, hot);

  FuzzyRuleConsequent *thenRiskMinimumSpeedQuick = new FuzzyRuleConsequent();
  thenRiskMinimumSpeedQuick->addOutput(minimum);
  thenRiskMinimumSpeedQuick->addOutput(quickOutput);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifDistanceDistantAndSpeedSlowOrTemperatureHot, thenRiskMinimumSpeedQuick);
  fuzzy->addFuzzyRule(fuzzyRule3);

  // get random entrances
  int input1 = random(0, 100);
  int input2 = random(0, 70);
  int input3 = random(-30, 30);

  cout << "\n\n\nEntrance: \n\t\t\tDistance: " << input1 << ", Speed: " << input2 << ", and Temperature: " << input3 << endl;

  fuzzy->setInput(1, input1);
  fuzzy->setInput(2, input2);
  fuzzy->setInput(3, input3);

  fuzzy->fuzzify();

  cout << "Input: \n\tDistance: Near-> " << near->getPertinence() << ", Safe->" << safe->getPertinence() << ", Distant-> " << distant->getPertinence() << endl;
  cout << "\tSpeed: Stoped-> " << stopedInput->getPertinence() << ",  Slow-> " << slowInput->getPertinence() << ",  Normal-> " << normalInput->getPertinence() << ",  Quick-> " << quickInput->getPertinence() << endl;
  cout << "\tTemperature: Cold->" << cold->getPertinence() << ", Good-> " << good->getPertinence() << ", Hot-> " << hot->getPertinence() << endl;

  cout << "Roles: \n\tRole01-> " << fuzzyRule1->isFired() << ", Role02-> " << fuzzyRule2->isFired() << ", Role03-> " << fuzzyRule3->isFired() << endl;

  float output1 = fuzzy->defuzzify(1);
  float output2 = fuzzy->defuzzify(2);

  cout << "Output: \n\tRisk: Minimum-> " << minimum->getPertinence() << ", Average->" << average->getPertinence() << ", Maximum-> " << maximum->getPertinence() << endl;
  cout << "\tSpeed: Stoped-> " << stopedOutput->getPertinence() << ",  Slow-> " << slowOutput->getPertinence() << ",  Normal-> " << normalOutput->getPertinence() << ",  Quick-> " << quickOutput->getPertinence() << endl;

  cout << "Result: \n\t\t\tRisk: " << output1 << ", and Speed: " << output2 << endl;

  return 0;
}