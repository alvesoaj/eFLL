#include <iostream>
#include "../Fuzzy.h"
#include "../FuzzyComposition.h"
#include "../FuzzyIO.h"
#include "../FuzzyInput.h"
#include "../FuzzyOutput.h"
#include "../FuzzyRule.h"
#include "../FuzzyRuleAntecedent.h"
#include "../FuzzyRuleConsequent.h"
#include "../FuzzySet.h"
#include "gtest/gtest.h"

// ############### FUZZYSET

TEST(FuzzySet, setPertinenceAndgetPertinence){
  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  fuzzySet->setPertinence(0.5);

  float result = fuzzySet->getPertinence();

  EXPECT_EQ(0.5, result);
}

TEST(FuzzySet, calculatePertinenceAndgetPertinence){
  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  // Valor 1
  fuzzySet->calculatePertinence(-5);
  float result1 = fuzzySet->getPertinence();

  // Valor 2
  fuzzySet->calculatePertinence(5);
  float result2 = fuzzySet->getPertinence();

  // Valor 3
  fuzzySet->calculatePertinence(10);
  float result3 = fuzzySet->getPertinence();

  // Valor 4
  fuzzySet->calculatePertinence(15);
  float result4 = fuzzySet->getPertinence();

  // Valor 5
  fuzzySet->calculatePertinence(25);
  float result5 = fuzzySet->getPertinence();

  EXPECT_EQ(0.0, result1);
  EXPECT_EQ(0.5, result2);
  EXPECT_EQ(1.0, result3);
  EXPECT_EQ(0.5, result4);
  EXPECT_EQ(0.0, result5);
}

// ############### FUZZYINPUT

TEST(FuzzyInput, addFuzzySet){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyInput->addFuzzySet(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyInput, setCrispInputAndGetCrispInput){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  fuzzyInput->setCrispInput(10.190);

  EXPECT_FLOAT_EQ(10.190, fuzzyInput->getCrispInput());  
}

TEST(FuzzyInput, calculateFuzzySetPertinences){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  fuzzyInput->addFuzzySet(fuzzySetTest);

  bool result = fuzzyInput->calculateFuzzySetPertinences();

  EXPECT_TRUE(result);
}

// ############### FUZZYOUTPUT

TEST(FuzzyOutput, addFuzzySet){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyOutput->addFuzzySet(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyOutput, setCrispInputAndGetCrispInput){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  fuzzyOutput->setCrispInput(10.190);

  EXPECT_FLOAT_EQ(10.190, fuzzyOutput->getCrispInput());  
}

TEST(FuzzyOutput, truncate){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest1 = new FuzzySet(0, 10, 10, 20);
  fuzzyOutput->addFuzzySet(fuzzySetTest1);

  FuzzySet* fuzzySetTest2 = new FuzzySet(10, 20, 20, 30);
  fuzzyOutput->addFuzzySet(fuzzySetTest2);

  FuzzySet* fuzzySetTest3 = new FuzzySet(20, 30, 30, 40);
  fuzzyOutput->addFuzzySet(fuzzySetTest3);

  bool result = fuzzyOutput->truncate();

  EXPECT_TRUE(result);
}

TEST(FuzzyOutput, getCrispOutput){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest1 = new FuzzySet(0, 10, 10, 20);
  fuzzySetTest1->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest1);

  FuzzySet* fuzzySetTest2 = new FuzzySet(10, 20, 20, 30);
  fuzzySetTest2->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest2);

  FuzzySet* fuzzySetTest3 = new FuzzySet(20, 30, 30, 40);
  fuzzySetTest3->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest3);

  fuzzyOutput->truncate();

  float result = fuzzyOutput->getCrispOutput();

  EXPECT_GT(result, 0.0);
  EXPECT_GT(result, 15);
}

// ############### FUZZYRULEANTECEDENT

TEST(FuzzyRuleAntecedent, joinSingle){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent = new FuzzyRuleAntecedent();

  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyRuleAntecedent->joinSingle(fuzzySet);

  EXPECT_TRUE(result);
}

TEST(FuzzyRuleAntecedent, joinWithAND){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  bool result1 = fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  bool result2 = fuzzyRuleAntecedent2->joinWithAND(temperatureLow, pressureSmall);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  bool result3 = fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();
  bool result4 = fuzzyRuleAntecedent4->joinWithAND(fuzzyRuleAntecedent1, pressureSmall);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent5 = new FuzzyRuleAntecedent();
  bool result5 = fuzzyRuleAntecedent5->joinWithAND(temperatureLow, fuzzyRuleAntecedent2);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
  EXPECT_TRUE(result4);
  EXPECT_TRUE(result5);
}

TEST(FuzzyRuleAntecedent, joinWithOR){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  bool result1 = fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  bool result2 = fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  bool result3 = fuzzyRuleAntecedent3->joinWithOR(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);
  FuzzyRuleAntecedent* fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();

  bool result4 = fuzzyRuleAntecedent4->joinWithOR(fuzzyRuleAntecedent1, pressureSmall);
  FuzzyRuleAntecedent* fuzzyRuleAntecedent5 = new FuzzyRuleAntecedent();

  bool result5 = fuzzyRuleAntecedent5->joinWithOR(temperatureLow, fuzzyRuleAntecedent2);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
  EXPECT_TRUE(result4);
  EXPECT_TRUE(result5);
}

TEST(FuzzyRuleAntecedent, evaluate){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();

  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.5);
  fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.0);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

  float result = fuzzyRuleAntecedent3->evaluate();

  EXPECT_GT(result, 0.0);
}

// ############### FUZZYRULECONSEQUENTE

TEST(FuzzyRuleConsequent, addOutput){
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyRuleConsequent->addOutput(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyRuleConsequent, evaluate){
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  fuzzyRuleConsequent->addOutput(fuzzySetTest);

  bool result = fuzzyRuleConsequent->evaluate(0.5);

  EXPECT_TRUE(result);
}

// ############### FUZZYRULE

TEST(FuzzyRule, getIndex){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent = new FuzzyRuleAntecedent();
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzyRule* fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent, fuzzyRuleConsequent);
  
  int result = fuzzyRule->getIndex();

  EXPECT_EQ(1, result);
}

TEST(FuzzyRule, evaluateExpressionAndIsFired){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.5);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.7);
  fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent2, fuzzyRuleAntecedent1);

  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* dangerLow = new FuzzySet(0, 10, 10, 20);

  fuzzyRuleConsequent->addOutput(dangerLow);

  FuzzyRule* fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);
  
  bool result1 = fuzzyRule->evaluateExpression();

  bool result2 = fuzzyRule->isFired();

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
}

// ############### FUZZYCOMPOSITION

TEST(FuzzyComposition, addPoint){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  bool result1 = fuzzyComposition->addPoint(1, 0.1);

  bool result2 = fuzzyComposition->addPoint(5, 0.5);
  
  bool result3 = fuzzyComposition->addPoint(9, 0.9);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
}

TEST(FuzzyComposition, checkPoint){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(5, 0.5);

  bool result1 = fuzzyComposition->checkPoint(5, 0.5);

  bool result2 = fuzzyComposition->checkPoint(5, 0.1);

  EXPECT_TRUE(result1);
  EXPECT_FALSE(result2);
}


TEST(FuzzyComposition, build){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(0, 0);
  fuzzyComposition->addPoint(20, 0.7);
  fuzzyComposition->addPoint(40, 0);

  fuzzyComposition->addPoint(20, 0);
  fuzzyComposition->addPoint(40, 0.3);
  fuzzyComposition->addPoint(70, 0.3);
  fuzzyComposition->addPoint(80, 0);

  fuzzyComposition->addPoint(50, 0);
  fuzzyComposition->addPoint(80, 0.7);
  fuzzyComposition->addPoint(90, 0);

  bool result = fuzzyComposition->build();

  EXPECT_TRUE(result);
}

TEST(FuzzyComposition, avaliate){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(0, 0);
  fuzzyComposition->addPoint(20, 0.7);
  fuzzyComposition->addPoint(40, 0);

  fuzzyComposition->addPoint(20, 0);
  fuzzyComposition->addPoint(40, 0.3);
  fuzzyComposition->addPoint(70, 0.3);
  fuzzyComposition->addPoint(80, 0);

  fuzzyComposition->addPoint(50, 0);
  fuzzyComposition->addPoint(80, 0.7);
  fuzzyComposition->addPoint(90, 0);

  fuzzyComposition->build();

  float result = fuzzyComposition->avaliate();

  EXPECT_GT(result, 0.0);
}

// ############### FUZZY

TEST(Fuzzy, addFuzzyInput){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  bool result = fuzzy->addFuzzyInput(temperature);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, addFuzzyOutput){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyOutput* climate = new FuzzyOutput(1);

  FuzzySet* cold = new FuzzySet(0, 10, 10, 20);
  climate->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(10, 20, 30, 40);
  climate->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(30, 40, 40, 50);
  climate->addFuzzySet(hot);

  bool result = fuzzy->addFuzzyOutput(climate);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, addFuzzyRule){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyRuleAntecedent* seTemperatureLowOrpressureSmall = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.5);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  seTemperatureLowOrpressureSmall->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* andRiskMinimum = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.7);
  andRiskMinimum->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* seTemperatureLowOrpressureSmallandRiskMinimum = new FuzzyRuleAntecedent();
  seTemperatureLowOrpressureSmallandRiskMinimum->joinWithAND(seTemperatureLowOrpressureSmall, andRiskMinimum);

  FuzzyRuleConsequent* thenDangerLow = new FuzzyRuleConsequent();

  FuzzySet* dangerLow = new FuzzySet(0, 10, 10, 20);

  thenDangerLow->addOutput(dangerLow);

  FuzzyRule* fuzzyRule = new FuzzyRule(1, seTemperatureLowOrpressureSmallandRiskMinimum, thenDangerLow);
  
  bool result = fuzzy->addFuzzyRule(fuzzyRule);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify01){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyOutput
  FuzzyOutput* climate = new FuzzyOutput(1);

  FuzzySet* cold = new FuzzySet(0, 10, 10, 20);
  climate->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(10, 20, 30, 40);
  climate->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(30, 40, 40, 50);
  climate->addFuzzySet(hot);

  fuzzy->addFuzzyOutput(climate);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLow = new FuzzyRuleAntecedent();
  ifTemperatureLow->joinSingle(low);
  FuzzyRuleConsequent* thenClimateCold = new FuzzyRuleConsequent();
  thenClimateCold->addOutput(cold);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLow, thenClimateCold);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMean = new FuzzyRuleAntecedent();
  ifTemperatureMean->joinSingle(mean);
  FuzzyRuleConsequent* thenClimateGood = new FuzzyRuleConsequent();
  thenClimateGood->addOutput(good);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMean, thenClimateGood);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHigh = new FuzzyRuleAntecedent();
  ifTemperatureHigh->joinSingle(low);
  FuzzyRuleConsequent* thenClimateHot = new FuzzyRuleConsequent();
  thenClimateHot->addOutput(cold);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHigh, thenClimateHot);
  fuzzy->addFuzzyRule(fuzzyRule3);

  bool result1 = fuzzy->setInput(1, 15);

  bool result2 = fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_GT(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify02){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(0, 10, 10, 20);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(10, 20, 30, 40);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(30, 40, 40, 50);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(0, 10, 10, 20);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(10, 20, 30, 40);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(30, 40, 40, 50);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, 15);
  fuzzy->setInput(2, 35);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_GT(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify03){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-30, -20, -20, -10);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-20, -10, 10, 20);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 20, 20, 30);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-30, -20, -20, -10);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-20, -10, 10, 20);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 20, 20, 30);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-30, -20, -20, -10);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-20, -10, 10, 20);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 20, 20, 30);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -25);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  bool fuzzyRule1IsFired = fuzzy->isFiredRule(1);

  float output = fuzzy->defuzzify(1);

  EXPECT_GT(0.0, output);
  EXPECT_TRUE(fuzzyRule1IsFired);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify04){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-20, -20, -20, -10);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-20, -10, 10, 20);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 20, 20, 20);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-20, -20, -20, -10);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-20, -10, 10, 20);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 20, 20, 20);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-20, -20, -20, -10);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-20, -10, 10, 20);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 20, 20, 20);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -25);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(0.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify05){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-20, -20, -20, -20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-10, -10, -10, -10);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 10, 10, 10);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-20, -20, -20, -20);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-10, -10, -10, -10);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 10, 10, 10);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-20, -20, -20, -20);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-10, -10, -10, -10);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 10, 10, 10);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -20);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(0.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify06){
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

  float output1 = fuzzy->defuzzify(1);
  float output2 = fuzzy->defuzzify(2);

  EXPECT_EQ(80.0, output1);
  EXPECT_EQ(10.3889, output2);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify07){
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
  FuzzyInput* temperature = new FuzzyInput(2);

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

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceCloseAndTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceCloseAndTemperatureCold->joinWithAND(close, cold);

  FuzzyRuleConsequent* thenRiskMinimum1 = new FuzzyRuleConsequent();
  thenRiskMinimum1->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndTemperatureCold, thenRiskMinimum1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceCloseAndTemperatureGood = new FuzzyRuleAntecedent();
  ifDistanceCloseAndTemperatureGood->joinWithAND(close, good);

  FuzzyRuleConsequent* thenRiskMinimum2 = new FuzzyRuleConsequent();
  thenRiskMinimum2->addOutput(minimum);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifDistanceCloseAndTemperatureGood, thenRiskMinimum2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceSafeAndTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceSafeAndTemperatureCold->joinWithAND(safe, cold);

  FuzzyRuleConsequent* thenRiskMinimum3 = new FuzzyRuleConsequent();
  thenRiskMinimum3->addOutput(minimum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifDistanceSafeAndTemperatureCold, thenRiskMinimum3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, 10);
  fuzzy->setInput(2, -5);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(20.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify08){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyInput* age = new FuzzyInput(1);

  FuzzySet* months = new FuzzySet(-360, -6, 5, 1200);
  age->addFuzzySet(months);

  fuzzy->addFuzzyInput(age);

  FuzzyOutput* quality = new FuzzyOutput(1);

  FuzzySet* avaliation = new FuzzySet(0, 1, 1, 1);
  quality->addFuzzySet(avaliation);

  fuzzy->addFuzzyOutput(quality);

  //-------------------- Montando as regras Fuzzy
  FuzzyRuleAntecedent* ifMonths = new FuzzyRuleAntecedent();
  ifMonths->joinSingle(months);

  FuzzyRuleConsequent* thenAvaliation = new FuzzyRuleConsequent();
  thenAvaliation->addOutput(avaliation);
  
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifMonths, thenAvaliation);
  fuzzy->addFuzzyRule(fuzzyRule01);

  fuzzy->setInput(1, 50);

  fuzzy->fuzzify();
  // cout << "Pertinência (months): " << months->getPertinence() << endl;

  // cout << "Pertinência (avaliation): " << avaliation->getPertinence() << endl;

  float fuzzyAntecedentEvaluate = ifMonths->evaluate();

  // cout << "Entrada: " << dist << ", Saida: " << output << endl;

  EXPECT_EQ(months->getPertinence(), fuzzyAntecedentEvaluate);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify09){
  // Instantiating an object of library
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyInput* shift;
  FuzzyInput* distance;

  FuzzyOutput* steeringangle;
  FuzzyOutput* runningspeed;

  FuzzyRuleAntecedent* ifShiftS_4AndDistanceD_0;
  FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_2;
  FuzzyRule* fuzzyRule1;

  FuzzyRuleAntecedent* ifShiftS_4AndDistanceD_1;
  FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_1;
  FuzzyRule* fuzzyRule2;

  FuzzyRuleAntecedent* ifShiftS_4AndDistanceD_2;
  FuzzyRule* fuzzyRule3;

  FuzzyRuleAntecedent* ifShiftS_4AndDistanceD_3;
  FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_0;
  FuzzyRule *fuzzyRule4;

  FuzzyRuleAntecedent* ifShiftS_4AndDistanceD_4;
  FuzzyRule* fuzzyRule5;

  FuzzyRuleAntecedent* ifShiftS_3AndDistanceD_0;
  FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_3;
  FuzzyRule* fuzzyRule6;

  FuzzyRuleAntecedent* ifShiftS_3AndDistanceD_1;
  FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_2;
  FuzzyRule* fuzzyRule7;

  FuzzyRuleAntecedent* ifShiftS_3AndDistanceD_2;
  FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_1;
  FuzzyRule* fuzzyRule8;

  FuzzyRuleAntecedent* ifShiftS_3AndDistanceD_3;
  FuzzyRule* fuzzyRule9;

  FuzzyRuleAntecedent* ifShiftS_3AndDistanceD_4;
  FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_0;
  FuzzyRule* fuzzyRule10;

  FuzzyRuleAntecedent* ifShiftS_2;
  FuzzyRuleConsequent* thenSteeringangleAng_2AndRunningspeedSpeed_4;
  FuzzyRule* fuzzyRule11;

  FuzzyRuleAntecedent* ifShiftS_1AndDistanceD_0;
  FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_3;
  FuzzyRule* fuzzyRule12;

  FuzzyRuleAntecedent* ifShiftS_1AndDistanceD_1;
  FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_2;
  FuzzyRule* fuzzyRule13;

  FuzzyRuleAntecedent* ifShiftS_1AndDistanceD_2;
  FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_1;
  FuzzyRule* fuzzyRule14;

  FuzzyRuleAntecedent* ifShiftS_1AndDistanceD_3;
  FuzzyRule* fuzzyRule15;

  FuzzyRuleAntecedent* ifShiftS_1AndDistanceD_4;
  FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_0;
  FuzzyRule* fuzzyRule16;

  FuzzyRuleAntecedent* ifShiftS_0AndDistanceD_0;
  FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_2;
  FuzzyRule* fuzzyRule17;

  FuzzyRuleAntecedent* ifShiftS_0AndDistanceD_1;
  FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_1;
  FuzzyRule* fuzzyRule18;

  FuzzyRuleAntecedent* ifShiftS_0AndDistanceD_2;
  FuzzyRule* fuzzyRule19;

  FuzzyRuleAntecedent* ifShiftS_0AndDistanceD_3;
  FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_0;
  FuzzyRule* fuzzyRule20;

  FuzzyRuleAntecedent* ifShiftS_0AndDistanceD_4;
  FuzzyRule* fuzzyRule21;

  // Fuzzy set
  FuzzySet* s_0 = new FuzzySet (9, 21, 21, 33);        //veri left
  FuzzySet* s_1 = new FuzzySet (24, 31.5, 31.5, 39 );  //medium left
  FuzzySet* s_2 = new FuzzySet (35, 39, 39, 43);       //zero  
  FuzzySet* s_3 = new FuzzySet (39, 46.5, 46.5, 54);   //medium right
  FuzzySet* s_4 = new FuzzySet (45, 57, 57, 69);       //very right

  FuzzySet* d_0 = new FuzzySet (0, 5, 5, 10);      //farthest
  FuzzySet* d_1 = new FuzzySet (5, 10, 10, 15);      //far  
  FuzzySet* d_2 = new FuzzySet (10, 15, 15, 20);      //middle
  FuzzySet* d_3 = new FuzzySet (15, 25, 25, 35);  //near
  FuzzySet* d_4 = new FuzzySet (25, 42, 42, 59);          //nearest

  FuzzySet* ang_0 = new FuzzySet (60, 70, 70, 80);      //leftmost
  FuzzySet* ang_1 = new FuzzySet (69, 79, 79, 89);      //left
  FuzzySet* ang_2 = new FuzzySet (88, 90, 90, 92);      //middle
  FuzzySet* ang_3 = new FuzzySet (91, 101, 101, 111);    //right
  FuzzySet* ang_4 = new FuzzySet (100, 110, 110, 120);   // rightmost

  FuzzySet* speed_0 = new FuzzySet (50, 75, 75, 100);      //very slow
  FuzzySet* speed_1 = new FuzzySet (75, 110, 110, 145);    //slow
  FuzzySet* speed_2 = new FuzzySet (120, 150, 150, 180);    //middle
  FuzzySet* speed_3 = new FuzzySet (155, 190, 190, 225);    //fast
  FuzzySet* speed_4 = new FuzzySet (200, 225, 225, 250);    //veryfast

  // Fuzzy input
  shift = new FuzzyInput(1);
  shift-> addFuzzySet(s_0);
  shift-> addFuzzySet(s_1);
  shift-> addFuzzySet(s_2);
  shift-> addFuzzySet(s_3);
  shift-> addFuzzySet(s_4);
  fuzzy->addFuzzyInput(shift);

  distance = new FuzzyInput(2);
  distance-> addFuzzySet(d_0);
  distance-> addFuzzySet(d_1);
  distance-> addFuzzySet(d_2);
  distance-> addFuzzySet(d_3);
  distance-> addFuzzySet(d_4);
  fuzzy->addFuzzyInput(distance);

  // Fuzzy output
  steeringangle = new FuzzyOutput(1);
  steeringangle-> addFuzzySet(ang_0);
  steeringangle-> addFuzzySet(ang_1);
  steeringangle-> addFuzzySet(ang_2);
  steeringangle-> addFuzzySet(ang_3);
  steeringangle-> addFuzzySet(ang_4);
  fuzzy-> addFuzzyOutput(steeringangle);

  runningspeed = new FuzzyOutput(2);
  runningspeed-> addFuzzySet(speed_0);
  runningspeed-> addFuzzySet(speed_1);
  runningspeed-> addFuzzySet(speed_2);
  runningspeed-> addFuzzySet(speed_3);
  fuzzy-> addFuzzyOutput(runningspeed);

  // Fuzzy rule
  ifShiftS_4AndDistanceD_0 = new FuzzyRuleAntecedent();
  ifShiftS_4AndDistanceD_0 ->joinWithAND(s_4,d_0);
  thenSteeringangleAng_4AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
  thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(ang_4);
  thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(speed_2);
  fuzzyRule1 = new FuzzyRule(1, ifShiftS_4AndDistanceD_0, thenSteeringangleAng_4AndRunningspeedSpeed_2);
  fuzzy->addFuzzyRule(fuzzyRule1);

  ifShiftS_4AndDistanceD_1 = new FuzzyRuleAntecedent();
  ifShiftS_4AndDistanceD_1 ->joinWithAND(s_4,d_1);
  thenSteeringangleAng_4AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(ang_4);
  thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule2 = new FuzzyRule(2, ifShiftS_4AndDistanceD_1, thenSteeringangleAng_4AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule2);

  ifShiftS_4AndDistanceD_2 = new FuzzyRuleAntecedent();
  ifShiftS_4AndDistanceD_2->joinWithAND(s_4, d_2);
  // FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(ang_4);
  // thenSteeringangleAng_4AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule3 = new FuzzyRule(3, ifShiftS_4AndDistanceD_2, thenSteeringangleAng_4AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule3);

  ifShiftS_4AndDistanceD_3 = new FuzzyRuleAntecedent();
  ifShiftS_4AndDistanceD_3->joinWithAND(s_4,d_3);
  thenSteeringangleAng_4AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
  thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule4 = new FuzzyRule(4, ifShiftS_4AndDistanceD_3, thenSteeringangleAng_4AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule4);

  ifShiftS_4AndDistanceD_4 = new FuzzyRuleAntecedent();
  ifShiftS_4AndDistanceD_4->joinWithAND(s_4,d_4);
  // FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
  // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule5 = new FuzzyRule(5, ifShiftS_4AndDistanceD_4, thenSteeringangleAng_4AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule5);

  ifShiftS_3AndDistanceD_0 = new FuzzyRuleAntecedent();
  ifShiftS_3AndDistanceD_0->joinWithAND(s_3,d_0);
  thenSteeringangleAng_3AndRunningspeedSpeed_3 = new FuzzyRuleConsequent();
  thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(ang_3);
  thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(speed_3);
  fuzzyRule6 = new FuzzyRule(6, ifShiftS_3AndDistanceD_0, thenSteeringangleAng_3AndRunningspeedSpeed_3);
  fuzzy->addFuzzyRule(fuzzyRule6);

  ifShiftS_3AndDistanceD_1 = new FuzzyRuleAntecedent();
  ifShiftS_3AndDistanceD_1->joinWithAND(s_3,d_1);
  thenSteeringangleAng_3AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
  thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(ang_3);
  thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(speed_2);
  fuzzyRule7 = new FuzzyRule(7, ifShiftS_3AndDistanceD_1, thenSteeringangleAng_3AndRunningspeedSpeed_2);
  fuzzy->addFuzzyRule(fuzzyRule7);

  ifShiftS_3AndDistanceD_2 = new FuzzyRuleAntecedent();
  ifShiftS_3AndDistanceD_2->joinWithAND(s_3,d_2);
  thenSteeringangleAng_3AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
  thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule8 = new FuzzyRule(8, ifShiftS_3AndDistanceD_2, thenSteeringangleAng_3AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule8);

  ifShiftS_3AndDistanceD_3 = new FuzzyRuleAntecedent();
  ifShiftS_3AndDistanceD_3->joinWithAND(s_3,d_3);
  // FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
  // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule9 = new FuzzyRule(9, ifShiftS_3AndDistanceD_3, thenSteeringangleAng_3AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule9);

  ifShiftS_3AndDistanceD_4 = new FuzzyRuleAntecedent();
  ifShiftS_3AndDistanceD_4->joinWithAND(s_3,d_4);
  thenSteeringangleAng_3AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  thenSteeringangleAng_3AndRunningspeedSpeed_0->addOutput(ang_3);
  thenSteeringangleAng_3AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule10 = new FuzzyRule(10, ifShiftS_3AndDistanceD_4, thenSteeringangleAng_3AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule10);

  ifShiftS_2 = new FuzzyRuleAntecedent();
  ifShiftS_2->joinSingle(s_2);
  thenSteeringangleAng_2AndRunningspeedSpeed_4 = new FuzzyRuleConsequent();
  thenSteeringangleAng_2AndRunningspeedSpeed_4->addOutput(ang_2);
  thenSteeringangleAng_2AndRunningspeedSpeed_4->addOutput(speed_4);
  fuzzyRule11 = new FuzzyRule(11, ifShiftS_2, thenSteeringangleAng_2AndRunningspeedSpeed_4);
  fuzzy->addFuzzyRule(fuzzyRule11);

  ifShiftS_1AndDistanceD_0 = new FuzzyRuleAntecedent();
  ifShiftS_1AndDistanceD_0->joinWithAND(s_1,d_0);
  thenSteeringangleAng_1AndRunningspeedSpeed_3 = new FuzzyRuleConsequent();
  thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(ang_1);
  thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(speed_3);
  fuzzyRule12 = new FuzzyRule(12, ifShiftS_1AndDistanceD_0, thenSteeringangleAng_1AndRunningspeedSpeed_3);
  fuzzy->addFuzzyRule(fuzzyRule12);

  ifShiftS_1AndDistanceD_1 = new FuzzyRuleAntecedent();
  ifShiftS_1AndDistanceD_1->joinWithAND(s_1,d_1);
  thenSteeringangleAng_1AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
  thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(ang_1);
  thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(speed_2);
  fuzzyRule13 = new FuzzyRule(13, ifShiftS_1AndDistanceD_1, thenSteeringangleAng_1AndRunningspeedSpeed_2);
  fuzzy->addFuzzyRule(fuzzyRule13);

  ifShiftS_1AndDistanceD_2 = new FuzzyRuleAntecedent();
  ifShiftS_1AndDistanceD_2->joinWithAND(s_1,d_2);
  thenSteeringangleAng_1AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
  thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule14 = new FuzzyRule(14, ifShiftS_1AndDistanceD_2, thenSteeringangleAng_1AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule14);

  ifShiftS_1AndDistanceD_3 = new FuzzyRuleAntecedent();
  ifShiftS_1AndDistanceD_3->joinWithAND(s_1,d_3);
  // FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
  // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule15 = new FuzzyRule(15, ifShiftS_1AndDistanceD_3, thenSteeringangleAng_1AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule15);

  ifShiftS_1AndDistanceD_4 = new FuzzyRuleAntecedent();
  ifShiftS_1AndDistanceD_4->joinWithAND(s_1,d_4);
  thenSteeringangleAng_1AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(ang_1);
  thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule16 = new FuzzyRule(16, ifShiftS_1AndDistanceD_4, thenSteeringangleAng_1AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule16);

  ifShiftS_0AndDistanceD_0 = new FuzzyRuleAntecedent();
  ifShiftS_0AndDistanceD_0->joinWithAND(s_0,d_0);
  thenSteeringangleAng_0AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
  thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(ang_0);
  thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(speed_2);
  fuzzyRule17 = new FuzzyRule(17, ifShiftS_0AndDistanceD_0, thenSteeringangleAng_0AndRunningspeedSpeed_2);
  fuzzy->addFuzzyRule(fuzzyRule17);

  ifShiftS_0AndDistanceD_1 = new FuzzyRuleAntecedent();
  ifShiftS_0AndDistanceD_1->joinWithAND(s_0,d_1);
  thenSteeringangleAng_0AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
  thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule18 = new FuzzyRule(18, ifShiftS_0AndDistanceD_1, thenSteeringangleAng_0AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule18);

  ifShiftS_0AndDistanceD_2 = new FuzzyRuleAntecedent();
  ifShiftS_0AndDistanceD_2->joinWithAND(s_0,d_2);
  // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
  // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
  fuzzyRule19 = new FuzzyRule(19, ifShiftS_0AndDistanceD_2, thenSteeringangleAng_0AndRunningspeedSpeed_1);
  fuzzy->addFuzzyRule(fuzzyRule19);

  ifShiftS_0AndDistanceD_3 = new FuzzyRuleAntecedent();
  ifShiftS_0AndDistanceD_3->joinWithAND(s_0,d_3);
  thenSteeringangleAng_0AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
  thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule20 = new FuzzyRule(20, ifShiftS_0AndDistanceD_3, thenSteeringangleAng_0AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule20);

  ifShiftS_0AndDistanceD_4 = new FuzzyRuleAntecedent();
  ifShiftS_0AndDistanceD_4->joinWithAND(s_0,d_4);
  // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
  // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
  // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
  fuzzyRule21 = new FuzzyRule(21, ifShiftS_0AndDistanceD_4, thenSteeringangleAng_0AndRunningspeedSpeed_0);
  fuzzy->addFuzzyRule(fuzzyRule21);

  float target_x = 21.88;  //  key in the digital value
  float target_y = 32;

  // target_x and target_y are the inputs    
  fuzzy->setInput(1, target_x);  // shift
  fuzzy->setInput(2, target_y);  // deistance

  fuzzy->fuzzify(); // Executing the fuzzification

  float output1 = fuzzy->defuzzify(1);  // steering angle
  float output2 = fuzzy->defuzzify(2);  // running speed

  EXPECT_EQ(70, output1);
  EXPECT_EQ(75, output2);
}


// ############### MAIN

int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}