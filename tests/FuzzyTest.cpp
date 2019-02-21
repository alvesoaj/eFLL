#include <iostream>
#include "gtest/gtest.h"
#include "../Fuzzy.h"
#include "../FuzzyComposition.h"
#include "../FuzzyIO.h"
#include "../FuzzyInput.h"
#include "../FuzzyOutput.h"
#include "../FuzzyRule.h"
#include "../FuzzyRuleAntecedent.h"
#include "../FuzzyRuleConsequent.h"
#include "../FuzzySet.h"

// ##### Tests of FuzzySet

TEST(FuzzySet, getPoints)
{
    FuzzySet *fuzzySet = new FuzzySet(0, 10, 20, 30);
    ASSERT_EQ(0, fuzzySet->getPointA());
    ASSERT_EQ(10, fuzzySet->getPointB());
    ASSERT_EQ(20, fuzzySet->getPointC());
    ASSERT_EQ(30, fuzzySet->getPointD());
}

TEST(FuzzySet, calculateAndGetPertinence)
{
    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);

    fuzzySet1->calculatePertinence(-5);
    ASSERT_FLOAT_EQ(0.0, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(5);
    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(10);
    ASSERT_FLOAT_EQ(1.0, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(15);
    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    fuzzySet1->calculatePertinence(25);
    ASSERT_FLOAT_EQ(0.0, fuzzySet1->getPertinence());

    FuzzySet *fuzzySet2 = new FuzzySet(0, 0, 20, 30);

    fuzzySet2->calculatePertinence(-5);
    ASSERT_FLOAT_EQ(1.0, fuzzySet2->getPertinence());

    FuzzySet *fuzzySet3 = new FuzzySet(0, 10, 20, 20);

    fuzzySet3->calculatePertinence(25);
    ASSERT_FLOAT_EQ(1.0, fuzzySet3->getPertinence());
}

// ##### Tests of FuzzyInput (It tests FuzzyIO too)

TEST(FuzzyInput, addFuzzySet)
{
    FuzzyInput *fuzzyInput = new FuzzyInput(1);
    FuzzySet *fuzzySet = new FuzzySet(0, 10, 10, 20);
    ASSERT_TRUE(fuzzyInput->addFuzzySet(fuzzySet));
}

TEST(FuzzyInput, setCrispInputAndGetCrispInput)
{
    FuzzyInput *fuzzyInput = new FuzzyInput(1);
    fuzzyInput->setCrispInput(10.190);
    ASSERT_FLOAT_EQ(10.190, fuzzyInput->getCrispInput());
}

TEST(FuzzyInput, calculateFuzzySetPertinences)
{
    FuzzyInput *fuzzyInput = new FuzzyInput(1);

    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);

    fuzzyInput->addFuzzySet(fuzzySet1);

    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);

    fuzzyInput->addFuzzySet(fuzzySet2);

    fuzzyInput->setCrispInput(5);

    ASSERT_TRUE(fuzzyInput->calculateFuzzySetPertinences());

    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());

    ASSERT_FLOAT_EQ(0.0, fuzzySet2->getPertinence());
}

// ##### Tests of FuzzyComposition

TEST(FuzzyComposition, addPointAndCheckPoint)
{
    FuzzyComposition *fuzzyComposition = new FuzzyComposition();

    ASSERT_TRUE(fuzzyComposition->addPoint(1, 0.1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(1, 0.1));

    ASSERT_TRUE(fuzzyComposition->addPoint(5, 0.5));
    ASSERT_TRUE(fuzzyComposition->checkPoint(5, 0.5));

    ASSERT_TRUE(fuzzyComposition->addPoint(9, 0.9));
    ASSERT_TRUE(fuzzyComposition->checkPoint(9, 0.9));

    ASSERT_FALSE(fuzzyComposition->checkPoint(5, 0.1));
}

TEST(FuzzyComposition, build)
{
    FuzzyComposition *fuzzyComposition = new FuzzyComposition();

    fuzzyComposition->addPoint(0, 0);
    fuzzyComposition->addPoint(10, 1);
    fuzzyComposition->addPoint(20, 0);

    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);

    ASSERT_TRUE(fuzzyComposition->build());

    ASSERT_TRUE(fuzzyComposition->checkPoint(0, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(10, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(15, 0.5));
    ASSERT_FALSE(fuzzyComposition->checkPoint(10, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(20, 1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(30, 0));
}

TEST(FuzzyComposition, calculateAndEmptyAndCountPoints)
{
    FuzzyComposition *fuzzyComposition = new FuzzyComposition();

    fuzzyComposition->addPoint(25, 1);
    fuzzyComposition->addPoint(25, 1);
    fuzzyComposition->build();
    ASSERT_EQ(2, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(25, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);
    fuzzyComposition->build();
    ASSERT_EQ(3, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(20, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(30, 1);
    fuzzyComposition->addPoint(50, 1);
    fuzzyComposition->addPoint(60, 0);
    fuzzyComposition->build();
    ASSERT_EQ(4, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(40, fuzzyComposition->calculate());
    ASSERT_TRUE(fuzzyComposition->empty());

    fuzzyComposition->addPoint(0, 0);
    fuzzyComposition->addPoint(10, 1);
    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(10, 0);
    fuzzyComposition->addPoint(20, 1);
    fuzzyComposition->addPoint(30, 0);
    fuzzyComposition->addPoint(20, 0);
    fuzzyComposition->addPoint(30, 1);
    fuzzyComposition->addPoint(40, 0);
    fuzzyComposition->build();
    ASSERT_EQ(7, fuzzyComposition->countPoints());
    ASSERT_FLOAT_EQ(20, fuzzyComposition->calculate());
}

// ##### Test of FuzzyOutput (It tests FuzzyIO too)

TEST(FuzzyOutput, getIndex)
{
    FuzzyOutput *fuzzyOutput = new FuzzyOutput(1);
    ASSERT_EQ(1, fuzzyOutput->getIndex());
}

TEST(FuzzyOutput, setCrispInputAndGetCrispInput)
{
    FuzzyOutput *fuzzyOutput = new FuzzyOutput(1);
    fuzzyOutput->setCrispInput(10.190);
    ASSERT_FLOAT_EQ(10.190, fuzzyOutput->getCrispInput());
}

TEST(FuzzyOutput, addFuzzySetAndResetFuzzySets)
{
    FuzzyOutput *fuzzyOutput = new FuzzyOutput(1);

    FuzzySet *fuzzySetTest = new FuzzySet(0, 10, 10, 20);

    ASSERT_TRUE(fuzzyOutput->addFuzzySet(fuzzySetTest));

    fuzzySetTest->setPertinence(0.242);
    ASSERT_FLOAT_EQ(0.242, fuzzySetTest->getPertinence());

    fuzzyOutput->resetFuzzySets();

    ASSERT_FLOAT_EQ(0.0, fuzzySetTest->getPertinence());
}

TEST(FuzzyOutput, truncateAndGetCrispOutputAndGetFuzzyComposition)
{
    FuzzyOutput *fuzzyOutput = new FuzzyOutput(1);

    ASSERT_EQ(1, fuzzyOutput->getIndex());

    FuzzySet *fuzzySetTest1 = new FuzzySet(0, 10, 10, 20);
    fuzzySetTest1->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest1);

    FuzzySet *fuzzySetTest2 = new FuzzySet(10, 20, 20, 30);
    fuzzySetTest2->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest2);

    FuzzySet *fuzzySetTest3 = new FuzzySet(20, 30, 30, 40);
    fuzzySetTest3->setPertinence(1);
    fuzzyOutput->addFuzzySet(fuzzySetTest3);

    ASSERT_TRUE(fuzzyOutput->truncate());

    FuzzyComposition *fuzzyComposition = fuzzyOutput->getFuzzyComposition();

    ASSERT_NE(nullptr, fuzzyComposition);

    ASSERT_EQ(7, fuzzyComposition->countPoints());

    ASSERT_TRUE(fuzzyComposition->checkPoint(0, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(10, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));

    ASSERT_TRUE(fuzzyComposition->checkPoint(15, 0.5));

    ASSERT_FALSE(fuzzyComposition->checkPoint(10, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(20, 1));
    ASSERT_FALSE(fuzzyComposition->checkPoint(30, 0));

    ASSERT_TRUE(fuzzyComposition->checkPoint(25, 0.5));

    ASSERT_FALSE(fuzzyComposition->checkPoint(20, 0));
    ASSERT_TRUE(fuzzyComposition->checkPoint(30, 1));
    ASSERT_TRUE(fuzzyComposition->checkPoint(40, 0));

    ASSERT_FLOAT_EQ(20.0, fuzzyOutput->getCrispOutput());
}

// ##### Tests for FuzzyRuleAntecedent

TEST(FuzzyRuleAntecedent, joinSingleAndEvaluate)
{
    FuzzyRuleAntecedent *fuzzyRuleAntecedent = new FuzzyRuleAntecedent();

    FuzzySet *fuzzySet = new FuzzySet(0, 10, 10, 20);
    fuzzySet->setPertinence(0.25);

    ASSERT_TRUE(fuzzyRuleAntecedent->joinSingle(fuzzySet));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent->evaluate());
}

TEST(FuzzyRuleAntecedent, joinTwoFuzzySetAndEvaluate)
{
    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent1->joinWithAND(fuzzySet1, fuzzySet2));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent1->evaluate());

    FuzzyRuleAntecedent *fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent2->joinWithOR(fuzzySet1, fuzzySet2));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent2->evaluate());
}

TEST(FuzzyRuleAntecedent, joinOneFuzzySetAndOneFuzzyAntecedentAndEvaluate)
{
    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet2);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent2->joinWithAND(fuzzySet1, fuzzyRuleAntecedent1));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent2->evaluate());

    FuzzyRuleAntecedent *fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzySet1));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent3->evaluate());

    FuzzyRuleAntecedent *fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent4->joinWithOR(fuzzySet1, fuzzyRuleAntecedent1));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent4->evaluate());

    FuzzyRuleAntecedent *fuzzyRuleAntecedent5 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent5->joinWithOR(fuzzyRuleAntecedent1, fuzzySet1));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent5->evaluate());
}

TEST(FuzzyRuleAntecedent, joinTwoFuzzyAntecedentAndEvaluate)
{
    FuzzyRuleAntecedent *fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet1);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);
    fuzzySet2->setPertinence(0.75);
    FuzzySet *fuzzySet3 = new FuzzySet(30, 40, 40, 50);
    fuzzySet3->setPertinence(0.5);
    fuzzyRuleAntecedent2->joinWithOR(fuzzySet2, fuzzySet3);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2));
    ASSERT_FLOAT_EQ(0.25, fuzzyRuleAntecedent3->evaluate());

    FuzzyRuleAntecedent *fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();
    ASSERT_TRUE(fuzzyRuleAntecedent4->joinWithOR(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2));
    ASSERT_FLOAT_EQ(0.75, fuzzyRuleAntecedent4->evaluate());
}

// ##### Tests for FuzzyRuleConsequent

TEST(FuzzyRuleConsequent, addOutputAndEvaluate)
{
    FuzzyRuleConsequent *fuzzyRuleConsequent = new FuzzyRuleConsequent();

    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);

    ASSERT_TRUE(fuzzyRuleConsequent->addOutput(fuzzySet1));

    fuzzyRuleConsequent->addOutput(fuzzySet2);

    ASSERT_TRUE(fuzzyRuleConsequent->evaluate(0.5));

    ASSERT_FLOAT_EQ(0.5, fuzzySet1->getPertinence());
    ASSERT_FLOAT_EQ(0.5, fuzzySet2->getPertinence());
}

// ##### Tests for FuzzyRule

TEST(FuzzyRule, getIndexAndEvaluateExpressionAndIsFired)
{
    FuzzyRuleAntecedent *fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet = new FuzzySet(0, 10, 10, 20);
    fuzzySet->setPertinence(0.75);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet2 = new FuzzySet(0, 10, 10, 20);
    fuzzySet2->setPertinence(0.25);
    fuzzyRuleAntecedent2->joinSingle(fuzzySet2);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
    fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

    FuzzyRuleConsequent *fuzzyRuleConsequent = new FuzzyRuleConsequent();
    FuzzySet *fuzzySet3 = new FuzzySet(0, 10, 10, 20);
    fuzzyRuleConsequent->addOutput(fuzzySet3);

    FuzzyRule *fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);

    ASSERT_EQ(1, fuzzyRule->getIndex());
    ASSERT_FALSE(fuzzyRule->isFired());

    ASSERT_TRUE(fuzzyRule->evaluateExpression());

    ASSERT_TRUE(fuzzyRule->isFired());
}

// ##### Tests for Fuzzy

TEST(Fuzzy, addFuzzyInput)
{
    Fuzzy *fuzzy = new Fuzzy();

    FuzzyInput *fuzzyInput = new FuzzyInput(1);

    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzyInput->addFuzzySet(fuzzySet1);
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);
    fuzzyInput->addFuzzySet(fuzzySet2);
    FuzzySet *fuzzySet3 = new FuzzySet(20, 30, 30, 40);
    fuzzyInput->addFuzzySet(fuzzySet3);

    ASSERT_TRUE(fuzzy->addFuzzyInput(fuzzyInput));
}

TEST(Fuzzy, addFuzzyOutput)
{
    Fuzzy *fuzzy = new Fuzzy();

    FuzzyOutput *fuzzyOutput = new FuzzyOutput(1);

    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzyOutput->addFuzzySet(fuzzySet1);
    FuzzySet *fuzzySet2 = new FuzzySet(10, 20, 20, 30);
    fuzzyOutput->addFuzzySet(fuzzySet2);
    FuzzySet *fuzzySet3 = new FuzzySet(20, 30, 30, 40);
    fuzzyOutput->addFuzzySet(fuzzySet3);

    ASSERT_TRUE(fuzzy->addFuzzyOutput(fuzzyOutput));
}

TEST(Fuzzy, addFuzzyRule)
{
    Fuzzy *fuzzy = new Fuzzy();

    FuzzyRuleAntecedent *fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet1 = new FuzzySet(0, 10, 10, 20);
    fuzzySet1->setPertinence(0.25);
    fuzzyRuleAntecedent1->joinSingle(fuzzySet1);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
    FuzzySet *fuzzySet2 = new FuzzySet(0, 10, 10, 20);
    fuzzySet2->setPertinence(0.75);
    fuzzyRuleAntecedent2->joinSingle(fuzzySet2);

    FuzzyRuleAntecedent *fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
    fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

    FuzzyRuleConsequent *fuzzyRuleConsequent = new FuzzyRuleConsequent();
    FuzzySet *fuzzySet3 = new FuzzySet(0, 10, 10, 20);
    fuzzyRuleConsequent->addOutput(fuzzySet3);

    FuzzyRule *fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);

    ASSERT_TRUE(fuzzy->addFuzzyRule(fuzzyRule));
}

TEST(Fuzzy, setInputAndFuzzifyAndIsFiredRuleAndDefuzzify)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *low = new FuzzySet(0, 10, 10, 20);
    temperature->addFuzzySet(low);
    FuzzySet *mean = new FuzzySet(10, 20, 30, 40);
    temperature->addFuzzySet(mean);
    FuzzySet *high = new FuzzySet(30, 40, 40, 50);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyOutput
    FuzzyOutput *climate = new FuzzyOutput(1);

    FuzzySet *cold = new FuzzySet(0, 10, 10, 20);
    climate->addFuzzySet(cold);
    FuzzySet *good = new FuzzySet(10, 20, 30, 40);
    climate->addFuzzySet(good);
    FuzzySet *hot = new FuzzySet(30, 40, 40, 50);
    climate->addFuzzySet(hot);

    fuzzy->addFuzzyOutput(climate);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureLow = new FuzzyRuleAntecedent();
    ifTemperatureLow->joinSingle(low);
    FuzzyRuleConsequent *thenClimateCold = new FuzzyRuleConsequent();
    thenClimateCold->addOutput(cold);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifTemperatureLow, thenClimateCold);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureMean = new FuzzyRuleAntecedent();
    ifTemperatureMean->joinSingle(mean);
    FuzzyRuleConsequent *thenClimateGood = new FuzzyRuleConsequent();
    thenClimateGood->addOutput(good);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifTemperatureMean, thenClimateGood);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureHigh = new FuzzyRuleAntecedent();
    ifTemperatureHigh->joinSingle(high);
    FuzzyRuleConsequent *thenClimateHot = new FuzzyRuleConsequent();
    thenClimateHot->addOutput(cold);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifTemperatureHigh, thenClimateHot);
    fuzzy->addFuzzyRule(fuzzyRule3);

    ASSERT_TRUE(fuzzy->setInput(1, 15));

    ASSERT_TRUE(fuzzy->fuzzify());

    ASSERT_TRUE(fuzzy->isFiredRule(1));
    ASSERT_TRUE(fuzzy->isFiredRule(2));
    ASSERT_FALSE(fuzzy->isFiredRule(3));

    ASSERT_FLOAT_EQ(19.729731, fuzzy->defuzzify(1));
}

// ##### Tests from explanation Fuzzy System
// https://www.massey.ac.nz/~nhreyes/MASSEY/159741/Lectures/Lec2012-3-159741-FuzzyLogic-v.2.pdf

TEST(Fuzzy, testFromLibraryUsersSystemsOne)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *size = new FuzzyInput(1);

    FuzzySet *smallSize = new FuzzySet(-5, -5, 0, 10);
    size->addFuzzySet(smallSize);
    FuzzySet *largeSize = new FuzzySet(0, 10, 15, 15);
    size->addFuzzySet(largeSize);

    fuzzy->addFuzzyInput(size);

    // FuzzyInput
    FuzzyInput *weight = new FuzzyInput(2);

    FuzzySet *smallWeight = new FuzzySet(-50, -50, 0, 100);
    weight->addFuzzySet(smallWeight);
    FuzzySet *largeWeight = new FuzzySet(0, 100, 150, 150);
    weight->addFuzzySet(largeWeight);

    fuzzy->addFuzzyInput(weight);

    // FuzzyOutput
    FuzzyOutput *quality = new FuzzyOutput(1);

    FuzzySet *bad = new FuzzySet(-0.25, -0.25, 0, 0.5);
    quality->addFuzzySet(bad);
    FuzzySet *medium = new FuzzySet(0, 0.5, 0.5, 1.0);
    quality->addFuzzySet(medium);
    FuzzySet *good = new FuzzySet(0.5, 1.0, 1.25, 1.25);
    quality->addFuzzySet(good);

    fuzzy->addFuzzyOutput(quality);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifSizeSmallAndWeightSmall = new FuzzyRuleAntecedent();
    ifSizeSmallAndWeightSmall->joinWithAND(smallSize, smallWeight);
    FuzzyRuleConsequent *thenQualityBad = new FuzzyRuleConsequent();
    thenQualityBad->addOutput(bad);
    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifSizeSmallAndWeightSmall, thenQualityBad);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifSizeSmallAndWeightLarge = new FuzzyRuleAntecedent();
    ifSizeSmallAndWeightLarge->joinWithAND(smallSize, largeWeight);
    FuzzyRuleConsequent *thenQualityMedium1 = new FuzzyRuleConsequent();
    thenQualityMedium1->addOutput(medium);
    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifSizeSmallAndWeightLarge, thenQualityMedium1);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifSizeLargeAndWeightSmall = new FuzzyRuleAntecedent();
    ifSizeLargeAndWeightSmall->joinWithAND(largeSize, smallWeight);
    FuzzyRuleConsequent *thenQualityMedium2 = new FuzzyRuleConsequent();
    thenQualityMedium2->addOutput(medium);
    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifSizeLargeAndWeightSmall, thenQualityMedium2);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifSizeLargeAndWeightLarge = new FuzzyRuleAntecedent();
    ifSizeLargeAndWeightLarge->joinWithAND(largeSize, largeWeight);
    FuzzyRuleConsequent *thenQualityGood = new FuzzyRuleConsequent();
    thenQualityGood->addOutput(good);
    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifSizeLargeAndWeightLarge, thenQualityGood);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // run it
    fuzzy->setInput(1, 2);
    fuzzy->setInput(2, 25);
    fuzzy->fuzzify();

    ASSERT_FLOAT_EQ(0.75, ifSizeSmallAndWeightSmall->evaluate());
    ASSERT_FLOAT_EQ(0.25, ifSizeSmallAndWeightLarge->evaluate());
    ASSERT_FLOAT_EQ(0.2, ifSizeLargeAndWeightSmall->evaluate());
    ASSERT_FLOAT_EQ(0.2, ifSizeLargeAndWeightLarge->evaluate());

    ASSERT_FLOAT_EQ(0.3698, fuzzy->defuzzify(1));
}

// ##### Tests from real systems, received from eFLL users

TEST(Fuzzy, testFromLibraryUsersSystemsTwo)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *low = new FuzzySet(0, 10, 10, 20);
    temperature->addFuzzySet(low);
    FuzzySet *mean = new FuzzySet(10, 20, 30, 40);
    temperature->addFuzzySet(mean);
    FuzzySet *high = new FuzzySet(30, 40, 40, 50);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *pressure = new FuzzyInput(2);

    FuzzySet *small = new FuzzySet(0, 10, 10, 20);
    pressure->addFuzzySet(small);
    FuzzySet *normal = new FuzzySet(10, 20, 30, 40);
    pressure->addFuzzySet(normal);
    FuzzySet *big = new FuzzySet(30, 40, 40, 50);
    pressure->addFuzzySet(big);

    fuzzy->addFuzzyInput(pressure);

    // FuzzyOutput
    FuzzyOutput *risk = new FuzzyOutput(1);

    FuzzySet *minimum = new FuzzySet(0, 10, 10, 20);
    risk->addFuzzySet(minimum);
    FuzzySet *average = new FuzzySet(10, 20, 30, 40);
    risk->addFuzzySet(average);
    FuzzySet *maximum = new FuzzySet(30, 40, 40, 50);
    risk->addFuzzySet(maximum);

    fuzzy->addFuzzyOutput(risk);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
    ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
    FuzzyRuleConsequent *thenRiskMinimum = new FuzzyRuleConsequent();
    thenRiskMinimum->addOutput(minimum);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
    ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
    FuzzyRuleConsequent *theRiskAverage = new FuzzyRuleConsequent();
    theRiskAverage->addOutput(average);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
    ifTemperatureHighAndPressureBig->joinWithAND(high, big);
    FuzzyRuleConsequent *thenRiskMaximum = new FuzzyRuleConsequent();
    thenRiskMaximum->addOutput(maximum);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, 15);
    fuzzy->setInput(2, 35);

    fuzzy->fuzzify();

    float output = fuzzy->defuzzify(1);

    ASSERT_GT(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify03)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *low = new FuzzySet(-30, -20, -20, -10);
    temperature->addFuzzySet(low);
    FuzzySet *mean = new FuzzySet(-20, -10, 10, 20);
    temperature->addFuzzySet(mean);
    FuzzySet *high = new FuzzySet(10, 20, 20, 30);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *pressure = new FuzzyInput(2);

    FuzzySet *small = new FuzzySet(-30, -20, -20, -10);
    pressure->addFuzzySet(small);
    FuzzySet *normal = new FuzzySet(-20, -10, 10, 20);
    pressure->addFuzzySet(normal);
    FuzzySet *big = new FuzzySet(10, 20, 20, 30);
    pressure->addFuzzySet(big);

    fuzzy->addFuzzyInput(pressure);

    // FuzzyOutput
    FuzzyOutput *risk = new FuzzyOutput(1);

    FuzzySet *minimum = new FuzzySet(-30, -20, -20, -10);
    risk->addFuzzySet(minimum);
    FuzzySet *average = new FuzzySet(-20, -10, 10, 20);
    risk->addFuzzySet(average);
    FuzzySet *maximum = new FuzzySet(10, 20, 20, 30);
    risk->addFuzzySet(maximum);

    fuzzy->addFuzzyOutput(risk);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
    ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
    FuzzyRuleConsequent *thenRiskMinimum = new FuzzyRuleConsequent();
    thenRiskMinimum->addOutput(minimum);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
    ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
    FuzzyRuleConsequent *theRiskAverage = new FuzzyRuleConsequent();
    theRiskAverage->addOutput(average);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
    ifTemperatureHighAndPressureBig->joinWithAND(high, big);
    FuzzyRuleConsequent *thenRiskMaximum = new FuzzyRuleConsequent();
    thenRiskMaximum->addOutput(maximum);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, -25);
    fuzzy->setInput(2, -15);

    fuzzy->fuzzify();

    bool fuzzyRule1IsFired = fuzzy->isFiredRule(1);

    float output = fuzzy->defuzzify(1);

    ASSERT_GT(0.0, output);
    ASSERT_TRUE(fuzzyRule1IsFired);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify04)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *low = new FuzzySet(-20, -20, -20, -10);
    temperature->addFuzzySet(low);
    FuzzySet *mean = new FuzzySet(-20, -10, 10, 20);
    temperature->addFuzzySet(mean);
    FuzzySet *high = new FuzzySet(10, 20, 20, 20);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *pressure = new FuzzyInput(2);

    FuzzySet *small = new FuzzySet(-20, -20, -20, -10);
    pressure->addFuzzySet(small);
    FuzzySet *normal = new FuzzySet(-20, -10, 10, 20);
    pressure->addFuzzySet(normal);
    FuzzySet *big = new FuzzySet(10, 20, 20, 20);
    pressure->addFuzzySet(big);

    fuzzy->addFuzzyInput(pressure);

    // FuzzyOutput
    FuzzyOutput *risk = new FuzzyOutput(1);

    FuzzySet *minimum = new FuzzySet(-20, -20, -20, -10);
    risk->addFuzzySet(minimum);
    FuzzySet *average = new FuzzySet(-20, -10, 10, 20);
    risk->addFuzzySet(average);
    FuzzySet *maximum = new FuzzySet(10, 20, 20, 20);
    risk->addFuzzySet(maximum);

    fuzzy->addFuzzyOutput(risk);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
    ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
    FuzzyRuleConsequent *thenRiskMinimum = new FuzzyRuleConsequent();
    thenRiskMinimum->addOutput(minimum);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
    ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
    FuzzyRuleConsequent *theRiskAverage = new FuzzyRuleConsequent();
    theRiskAverage->addOutput(average);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
    ifTemperatureHighAndPressureBig->joinWithAND(high, big);
    FuzzyRuleConsequent *thenRiskMaximum = new FuzzyRuleConsequent();
    thenRiskMaximum->addOutput(maximum);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, -25);
    fuzzy->setInput(2, -15);

    fuzzy->fuzzify();

    float output = fuzzy->defuzzify(1);

    ASSERT_EQ(0.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify05)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *low = new FuzzySet(-20, -20, -20, -20);
    temperature->addFuzzySet(low);
    FuzzySet *mean = new FuzzySet(-10, -10, -10, -10);
    temperature->addFuzzySet(mean);
    FuzzySet *high = new FuzzySet(10, 10, 10, 10);
    temperature->addFuzzySet(high);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *pressure = new FuzzyInput(2);

    FuzzySet *small = new FuzzySet(-20, -20, -20, -20);
    pressure->addFuzzySet(small);
    FuzzySet *normal = new FuzzySet(-10, -10, -10, -10);
    pressure->addFuzzySet(normal);
    FuzzySet *big = new FuzzySet(10, 10, 10, 10);
    pressure->addFuzzySet(big);

    fuzzy->addFuzzyInput(pressure);

    // FuzzyOutput
    FuzzyOutput *risk = new FuzzyOutput(1);

    FuzzySet *minimum = new FuzzySet(-20, -20, -20, -20);
    risk->addFuzzySet(minimum);
    FuzzySet *average = new FuzzySet(-10, -10, -10, -10);
    risk->addFuzzySet(average);
    FuzzySet *maximum = new FuzzySet(10, 10, 10, 10);
    risk->addFuzzySet(maximum);

    fuzzy->addFuzzyOutput(risk);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
    ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
    FuzzyRuleConsequent *thenRiskMinimum = new FuzzyRuleConsequent();
    thenRiskMinimum->addOutput(minimum);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
    ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
    FuzzyRuleConsequent *theRiskAverage = new FuzzyRuleConsequent();
    theRiskAverage->addOutput(average);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
    ifTemperatureHighAndPressureBig->joinWithAND(high, big);
    FuzzyRuleConsequent *thenRiskMaximum = new FuzzyRuleConsequent();
    thenRiskMaximum->addOutput(maximum);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, -20);
    fuzzy->setInput(2, -15);

    fuzzy->fuzzify();

    float output = fuzzy->defuzzify(1);

    ASSERT_EQ(0.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify06)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *distance = new FuzzyInput(1);

    FuzzySet *close = new FuzzySet(0, 20, 20, 40);
    distance->addFuzzySet(close);
    FuzzySet *safe = new FuzzySet(30, 50, 50, 70);
    distance->addFuzzySet(safe);
    FuzzySet *distante = new FuzzySet(60, 80, 100, 100);
    distance->addFuzzySet(distante);

    fuzzy->addFuzzyInput(distance);

    // FuzzyInput
    FuzzyInput *inputSpeed = new FuzzyInput(2);

    FuzzySet *stoped = new FuzzySet(0, 0, 0, 0);
    inputSpeed->addFuzzySet(stoped);
    FuzzySet *slow = new FuzzySet(1, 10, 10, 20);
    inputSpeed->addFuzzySet(slow);
    FuzzySet *normal = new FuzzySet(15, 30, 30, 50);
    inputSpeed->addFuzzySet(normal);
    FuzzySet *quick = new FuzzySet(45, 60, 70, 70);
    inputSpeed->addFuzzySet(quick);

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
    // adicionando speed como output também
    FuzzyOutput *outputSpeed = new FuzzyOutput(2);

    FuzzySet *stopedOut = new FuzzySet(0, 0, 0, 0);
    outputSpeed->addFuzzySet(stopedOut);
    FuzzySet *slowOut = new FuzzySet(1, 10, 10, 20);
    outputSpeed->addFuzzySet(slowOut);
    FuzzySet *normalOut = new FuzzySet(15, 30, 30, 50);
    outputSpeed->addFuzzySet(normalOut);
    FuzzySet *quickOut = new FuzzySet(45, 60, 70, 70);
    outputSpeed->addFuzzySet(quickOut);

    fuzzy->addFuzzyOutput(outputSpeed);

    // Building FuzzyRule
    FuzzyRuleAntecedent *distanceCloseAndSpeedQuick = new FuzzyRuleAntecedent();
    distanceCloseAndSpeedQuick->joinWithAND(close, quick);
    FuzzyRuleAntecedent *temperatureCold = new FuzzyRuleAntecedent();
    temperatureCold->joinSingle(cold);
    FuzzyRuleAntecedent *ifDistanceCloseAndSpeedQuickOrTemperatureCold = new FuzzyRuleAntecedent();
    ifDistanceCloseAndSpeedQuickOrTemperatureCold->joinWithOR(distanceCloseAndSpeedQuick, temperatureCold);

    FuzzyRuleConsequent *thenRisMaximumAndSpeedSlow = new FuzzyRuleConsequent();
    thenRisMaximumAndSpeedSlow->addOutput(maximum);
    thenRisMaximumAndSpeedSlow->addOutput(slowOut);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndSpeedQuickOrTemperatureCold, thenRisMaximumAndSpeedSlow);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *distanceSafeAndSpeedNormal = new FuzzyRuleAntecedent();
    distanceSafeAndSpeedNormal->joinWithAND(safe, normal);
    FuzzyRuleAntecedent *ifDistanceSafeAndSpeedNormalOrTemperatureGood = new FuzzyRuleAntecedent();
    ifDistanceSafeAndSpeedNormalOrTemperatureGood->joinWithOR(distanceSafeAndSpeedNormal, good);

    FuzzyRuleConsequent *thenRiskAverageAndSpeedNormal = new FuzzyRuleConsequent();
    thenRiskAverageAndSpeedNormal->addOutput(average);
    thenRiskAverageAndSpeedNormal->addOutput(normalOut);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifDistanceSafeAndSpeedNormalOrTemperatureGood, thenRiskAverageAndSpeedNormal);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *distanceDistanteAndSpeedSlow = new FuzzyRuleAntecedent();
    distanceDistanteAndSpeedSlow->joinWithAND(distante, slow);
    FuzzyRuleAntecedent *ifDistanceDistanteAndSpeedSlowOrTemperatureHot = new FuzzyRuleAntecedent();
    ifDistanceDistanteAndSpeedSlowOrTemperatureHot->joinWithOR(distanceDistanteAndSpeedSlow, hot);

    FuzzyRuleConsequent *thenRiskMinimumSpeedQuick = new FuzzyRuleConsequent();
    thenRiskMinimumSpeedQuick->addOutput(minimum);
    thenRiskMinimumSpeedQuick->addOutput(quickOut);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifDistanceDistanteAndSpeedSlowOrTemperatureHot, thenRiskMinimumSpeedQuick);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, 10);
    fuzzy->setInput(2, 30);
    fuzzy->setInput(3, -15);

    fuzzy->fuzzify();

    float output1 = fuzzy->defuzzify(1);
    float output2 = fuzzy->defuzzify(2);

    ASSERT_NEAR(80.0, output1, 0.01);
    ASSERT_NEAR(10.3889, output2, 0.01);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify07)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *distance = new FuzzyInput(1);

    FuzzySet *close = new FuzzySet(0, 20, 20, 40);
    distance->addFuzzySet(close);
    FuzzySet *safe = new FuzzySet(30, 50, 50, 70);
    distance->addFuzzySet(safe);
    FuzzySet *distante = new FuzzySet(60, 80, 100, 100);
    distance->addFuzzySet(distante);

    fuzzy->addFuzzyInput(distance);

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(2);

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

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifDistanceCloseAndTemperatureCold = new FuzzyRuleAntecedent();
    ifDistanceCloseAndTemperatureCold->joinWithAND(close, cold);

    FuzzyRuleConsequent *thenRiskMinimum1 = new FuzzyRuleConsequent();
    thenRiskMinimum1->addOutput(minimum);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndTemperatureCold, thenRiskMinimum1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifDistanceCloseAndTemperatureGood = new FuzzyRuleAntecedent();
    ifDistanceCloseAndTemperatureGood->joinWithAND(close, good);

    FuzzyRuleConsequent *thenRiskMinimum2 = new FuzzyRuleConsequent();
    thenRiskMinimum2->addOutput(minimum);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifDistanceCloseAndTemperatureGood, thenRiskMinimum2);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifDistanceSafeAndTemperatureCold = new FuzzyRuleAntecedent();
    ifDistanceSafeAndTemperatureCold->joinWithAND(safe, cold);

    FuzzyRuleConsequent *thenRiskMinimum3 = new FuzzyRuleConsequent();
    thenRiskMinimum3->addOutput(minimum);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifDistanceSafeAndTemperatureCold, thenRiskMinimum3);
    fuzzy->addFuzzyRule(fuzzyRule3);

    fuzzy->setInput(1, 10);
    fuzzy->setInput(2, -5);

    fuzzy->fuzzify();

    float output = fuzzy->defuzzify(1);

    ASSERT_EQ(20.0, output);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify08)
{
    Fuzzy *fuzzy = new Fuzzy();

    FuzzyInput *age = new FuzzyInput(1);

    FuzzySet *months = new FuzzySet(-360, -6, 5, 1200);
    age->addFuzzySet(months);

    fuzzy->addFuzzyInput(age);

    FuzzyOutput *quality = new FuzzyOutput(1);

    FuzzySet *avaliation = new FuzzySet(0, 1, 1, 1);
    quality->addFuzzySet(avaliation);

    fuzzy->addFuzzyOutput(quality);

    //-------------------- Montando as regras Fuzzy
    FuzzyRuleAntecedent *ifMonths = new FuzzyRuleAntecedent();
    ifMonths->joinSingle(months);

    FuzzyRuleConsequent *thenAvaliation = new FuzzyRuleConsequent();
    thenAvaliation->addOutput(avaliation);

    // Instanciando um objeto FuzzyRule
    FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifMonths, thenAvaliation);
    fuzzy->addFuzzyRule(fuzzyRule01);

    fuzzy->setInput(1, 50);

    fuzzy->fuzzify();
    // cout << "Pertinência (months): " << months->getPertinence() << endl;

    // cout << "Pertinência (avaliation): " << avaliation->getPertinence() << endl;

    float fuzzyAntecedentEvaluate = ifMonths->evaluate();

    // cout << "Entrada: " << dist << ", Saida: " << output << endl;

    ASSERT_EQ(months->getPertinence(), fuzzyAntecedentEvaluate);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify09)
{
    // Instantiating an object of library
    Fuzzy *fuzzy = new Fuzzy();

    FuzzyInput *shift;
    FuzzyInput *distance;

    FuzzyOutput *steeringangle;
    FuzzyOutput *runningspeed;

    FuzzyRuleAntecedent *ifShiftS_4AndDistanceD_0;
    FuzzyRuleConsequent *thenSteeringangleAng_4AndRunningspeedSpeed_2;
    FuzzyRule *fuzzyRule1;

    FuzzyRuleAntecedent *ifShiftS_4AndDistanceD_1;
    FuzzyRuleConsequent *thenSteeringangleAng_4AndRunningspeedSpeed_1;
    FuzzyRule *fuzzyRule2;

    FuzzyRuleAntecedent *ifShiftS_4AndDistanceD_2;
    FuzzyRule *fuzzyRule3;

    FuzzyRuleAntecedent *ifShiftS_4AndDistanceD_3;
    FuzzyRuleConsequent *thenSteeringangleAng_4AndRunningspeedSpeed_0;
    FuzzyRule *fuzzyRule4;

    FuzzyRuleAntecedent *ifShiftS_4AndDistanceD_4;
    FuzzyRule *fuzzyRule5;

    FuzzyRuleAntecedent *ifShiftS_3AndDistanceD_0;
    FuzzyRuleConsequent *thenSteeringangleAng_3AndRunningspeedSpeed_3;
    FuzzyRule *fuzzyRule6;

    FuzzyRuleAntecedent *ifShiftS_3AndDistanceD_1;
    FuzzyRuleConsequent *thenSteeringangleAng_3AndRunningspeedSpeed_2;
    FuzzyRule *fuzzyRule7;

    FuzzyRuleAntecedent *ifShiftS_3AndDistanceD_2;
    FuzzyRuleConsequent *thenSteeringangleAng_3AndRunningspeedSpeed_1;
    FuzzyRule *fuzzyRule8;

    FuzzyRuleAntecedent *ifShiftS_3AndDistanceD_3;
    FuzzyRule *fuzzyRule9;

    FuzzyRuleAntecedent *ifShiftS_3AndDistanceD_4;
    FuzzyRuleConsequent *thenSteeringangleAng_3AndRunningspeedSpeed_0;
    FuzzyRule *fuzzyRule10;

    FuzzyRuleAntecedent *ifShiftS_2;
    FuzzyRuleConsequent *thenSteeringangleAng_2AndRunningspeedSpeed_4;
    FuzzyRule *fuzzyRule11;

    FuzzyRuleAntecedent *ifShiftS_1AndDistanceD_0;
    FuzzyRuleConsequent *thenSteeringangleAng_1AndRunningspeedSpeed_3;
    FuzzyRule *fuzzyRule12;

    FuzzyRuleAntecedent *ifShiftS_1AndDistanceD_1;
    FuzzyRuleConsequent *thenSteeringangleAng_1AndRunningspeedSpeed_2;
    FuzzyRule *fuzzyRule13;

    FuzzyRuleAntecedent *ifShiftS_1AndDistanceD_2;
    FuzzyRuleConsequent *thenSteeringangleAng_1AndRunningspeedSpeed_1;
    FuzzyRule *fuzzyRule14;

    FuzzyRuleAntecedent *ifShiftS_1AndDistanceD_3;
    FuzzyRule *fuzzyRule15;

    FuzzyRuleAntecedent *ifShiftS_1AndDistanceD_4;
    FuzzyRuleConsequent *thenSteeringangleAng_1AndRunningspeedSpeed_0;
    FuzzyRule *fuzzyRule16;

    FuzzyRuleAntecedent *ifShiftS_0AndDistanceD_0;
    FuzzyRuleConsequent *thenSteeringangleAng_0AndRunningspeedSpeed_2;
    FuzzyRule *fuzzyRule17;

    FuzzyRuleAntecedent *ifShiftS_0AndDistanceD_1;
    FuzzyRuleConsequent *thenSteeringangleAng_0AndRunningspeedSpeed_1;
    FuzzyRule *fuzzyRule18;

    FuzzyRuleAntecedent *ifShiftS_0AndDistanceD_2;
    FuzzyRule *fuzzyRule19;

    FuzzyRuleAntecedent *ifShiftS_0AndDistanceD_3;
    FuzzyRuleConsequent *thenSteeringangleAng_0AndRunningspeedSpeed_0;
    FuzzyRule *fuzzyRule20;

    FuzzyRuleAntecedent *ifShiftS_0AndDistanceD_4;
    FuzzyRule *fuzzyRule21;

    // Fuzzy set
    FuzzySet *s_0 = new FuzzySet(9, 21, 21, 33);      //veri left
    FuzzySet *s_1 = new FuzzySet(24, 31.5, 31.5, 39); //medium left
    FuzzySet *s_2 = new FuzzySet(35, 39, 39, 43);     //zero
    FuzzySet *s_3 = new FuzzySet(39, 46.5, 46.5, 54); //medium right
    FuzzySet *s_4 = new FuzzySet(45, 57, 57, 69);     //very right

    FuzzySet *d_0 = new FuzzySet(0, 5, 5, 10);    //farthest
    FuzzySet *d_1 = new FuzzySet(5, 10, 10, 15);  //far
    FuzzySet *d_2 = new FuzzySet(10, 15, 15, 20); //middle
    FuzzySet *d_3 = new FuzzySet(15, 25, 25, 35); //near
    FuzzySet *d_4 = new FuzzySet(25, 42, 42, 59); //nearest

    FuzzySet *ang_0 = new FuzzySet(60, 70, 70, 80);     //leftmost
    FuzzySet *ang_1 = new FuzzySet(69, 79, 79, 89);     //left
    FuzzySet *ang_2 = new FuzzySet(88, 90, 90, 92);     //middle
    FuzzySet *ang_3 = new FuzzySet(91, 101, 101, 111);  //right
    FuzzySet *ang_4 = new FuzzySet(100, 110, 110, 120); // rightmost

    FuzzySet *speed_0 = new FuzzySet(50, 75, 75, 100);    //very slow
    FuzzySet *speed_1 = new FuzzySet(75, 110, 110, 145);  //slow
    FuzzySet *speed_2 = new FuzzySet(120, 150, 150, 180); //middle
    FuzzySet *speed_3 = new FuzzySet(155, 190, 190, 225); //fast
    FuzzySet *speed_4 = new FuzzySet(200, 225, 225, 250); //veryfast

    // Fuzzy input
    shift = new FuzzyInput(1);
    shift->addFuzzySet(s_0);
    shift->addFuzzySet(s_1);
    shift->addFuzzySet(s_2);
    shift->addFuzzySet(s_3);
    shift->addFuzzySet(s_4);
    fuzzy->addFuzzyInput(shift);

    distance = new FuzzyInput(2);
    distance->addFuzzySet(d_0);
    distance->addFuzzySet(d_1);
    distance->addFuzzySet(d_2);
    distance->addFuzzySet(d_3);
    distance->addFuzzySet(d_4);
    fuzzy->addFuzzyInput(distance);

    // Fuzzy output
    steeringangle = new FuzzyOutput(1);
    steeringangle->addFuzzySet(ang_0);
    steeringangle->addFuzzySet(ang_1);
    steeringangle->addFuzzySet(ang_2);
    steeringangle->addFuzzySet(ang_3);
    steeringangle->addFuzzySet(ang_4);
    fuzzy->addFuzzyOutput(steeringangle);

    runningspeed = new FuzzyOutput(2);
    runningspeed->addFuzzySet(speed_0);
    runningspeed->addFuzzySet(speed_1);
    runningspeed->addFuzzySet(speed_2);
    runningspeed->addFuzzySet(speed_3);
    fuzzy->addFuzzyOutput(runningspeed);

    // Fuzzy rule
    ifShiftS_4AndDistanceD_0 = new FuzzyRuleAntecedent();
    ifShiftS_4AndDistanceD_0->joinWithAND(s_4, d_0);
    thenSteeringangleAng_4AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
    thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(ang_4);
    thenSteeringangleAng_4AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule1 = new FuzzyRule(1, ifShiftS_4AndDistanceD_0, thenSteeringangleAng_4AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule1);

    ifShiftS_4AndDistanceD_1 = new FuzzyRuleAntecedent();
    ifShiftS_4AndDistanceD_1->joinWithAND(s_4, d_1);
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
    ifShiftS_4AndDistanceD_3->joinWithAND(s_4, d_3);
    thenSteeringangleAng_4AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
    thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
    thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule4 = new FuzzyRule(4, ifShiftS_4AndDistanceD_3, thenSteeringangleAng_4AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule4);

    ifShiftS_4AndDistanceD_4 = new FuzzyRuleAntecedent();
    ifShiftS_4AndDistanceD_4->joinWithAND(s_4, d_4);
    // FuzzyRuleConsequent* thenSteeringangleAng_4AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
    // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(ang_4);
    // thenSteeringangleAng_4AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule5 = new FuzzyRule(5, ifShiftS_4AndDistanceD_4, thenSteeringangleAng_4AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule5);

    ifShiftS_3AndDistanceD_0 = new FuzzyRuleAntecedent();
    ifShiftS_3AndDistanceD_0->joinWithAND(s_3, d_0);
    thenSteeringangleAng_3AndRunningspeedSpeed_3 = new FuzzyRuleConsequent();
    thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_3->addOutput(speed_3);
    fuzzyRule6 = new FuzzyRule(6, ifShiftS_3AndDistanceD_0, thenSteeringangleAng_3AndRunningspeedSpeed_3);
    fuzzy->addFuzzyRule(fuzzyRule6);

    ifShiftS_3AndDistanceD_1 = new FuzzyRuleAntecedent();
    ifShiftS_3AndDistanceD_1->joinWithAND(s_3, d_1);
    thenSteeringangleAng_3AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
    thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule7 = new FuzzyRule(7, ifShiftS_3AndDistanceD_1, thenSteeringangleAng_3AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule7);

    ifShiftS_3AndDistanceD_2 = new FuzzyRuleAntecedent();
    ifShiftS_3AndDistanceD_2->joinWithAND(s_3, d_2);
    thenSteeringangleAng_3AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
    thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule8 = new FuzzyRule(8, ifShiftS_3AndDistanceD_2, thenSteeringangleAng_3AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    ifShiftS_3AndDistanceD_3 = new FuzzyRuleAntecedent();
    ifShiftS_3AndDistanceD_3->joinWithAND(s_3, d_3);
    // FuzzyRuleConsequent* thenSteeringangleAng_3AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(ang_3);
    // thenSteeringangleAng_3AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule9 = new FuzzyRule(9, ifShiftS_3AndDistanceD_3, thenSteeringangleAng_3AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule9);

    ifShiftS_3AndDistanceD_4 = new FuzzyRuleAntecedent();
    ifShiftS_3AndDistanceD_4->joinWithAND(s_3, d_4);
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
    ifShiftS_1AndDistanceD_0->joinWithAND(s_1, d_0);
    thenSteeringangleAng_1AndRunningspeedSpeed_3 = new FuzzyRuleConsequent();
    thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_3->addOutput(speed_3);
    fuzzyRule12 = new FuzzyRule(12, ifShiftS_1AndDistanceD_0, thenSteeringangleAng_1AndRunningspeedSpeed_3);
    fuzzy->addFuzzyRule(fuzzyRule12);

    ifShiftS_1AndDistanceD_1 = new FuzzyRuleAntecedent();
    ifShiftS_1AndDistanceD_1->joinWithAND(s_1, d_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
    thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule13 = new FuzzyRule(13, ifShiftS_1AndDistanceD_1, thenSteeringangleAng_1AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule13);

    ifShiftS_1AndDistanceD_2 = new FuzzyRuleAntecedent();
    ifShiftS_1AndDistanceD_2->joinWithAND(s_1, d_2);
    thenSteeringangleAng_1AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule14 = new FuzzyRule(14, ifShiftS_1AndDistanceD_2, thenSteeringangleAng_1AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule14);

    ifShiftS_1AndDistanceD_3 = new FuzzyRuleAntecedent();
    ifShiftS_1AndDistanceD_3->joinWithAND(s_1, d_3);
    // FuzzyRuleConsequent* thenSteeringangleAng_1AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(ang_1);
    // thenSteeringangleAng_1AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule15 = new FuzzyRule(15, ifShiftS_1AndDistanceD_3, thenSteeringangleAng_1AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule15);

    ifShiftS_1AndDistanceD_4 = new FuzzyRuleAntecedent();
    ifShiftS_1AndDistanceD_4->joinWithAND(s_1, d_4);
    thenSteeringangleAng_1AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
    thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(ang_1);
    thenSteeringangleAng_1AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule16 = new FuzzyRule(16, ifShiftS_1AndDistanceD_4, thenSteeringangleAng_1AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule16);

    ifShiftS_0AndDistanceD_0 = new FuzzyRuleAntecedent();
    ifShiftS_0AndDistanceD_0->joinWithAND(s_0, d_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_2 = new FuzzyRuleConsequent();
    thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_2->addOutput(speed_2);
    fuzzyRule17 = new FuzzyRule(17, ifShiftS_0AndDistanceD_0, thenSteeringangleAng_0AndRunningspeedSpeed_2);
    fuzzy->addFuzzyRule(fuzzyRule17);

    ifShiftS_0AndDistanceD_1 = new FuzzyRuleAntecedent();
    ifShiftS_0AndDistanceD_1->joinWithAND(s_0, d_1);
    thenSteeringangleAng_0AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule18 = new FuzzyRule(18, ifShiftS_0AndDistanceD_1, thenSteeringangleAng_0AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule18);

    ifShiftS_0AndDistanceD_2 = new FuzzyRuleAntecedent();
    ifShiftS_0AndDistanceD_2->joinWithAND(s_0, d_2);
    // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_1 = new FuzzyRuleConsequent();
    // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(ang_0);
    // thenSteeringangleAng_0AndRunningspeedSpeed_1->addOutput(speed_1);
    fuzzyRule19 = new FuzzyRule(19, ifShiftS_0AndDistanceD_2, thenSteeringangleAng_0AndRunningspeedSpeed_1);
    fuzzy->addFuzzyRule(fuzzyRule19);

    ifShiftS_0AndDistanceD_3 = new FuzzyRuleAntecedent();
    ifShiftS_0AndDistanceD_3->joinWithAND(s_0, d_3);
    thenSteeringangleAng_0AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
    thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
    thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule20 = new FuzzyRule(20, ifShiftS_0AndDistanceD_3, thenSteeringangleAng_0AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule20);

    ifShiftS_0AndDistanceD_4 = new FuzzyRuleAntecedent();
    ifShiftS_0AndDistanceD_4->joinWithAND(s_0, d_4);
    // FuzzyRuleConsequent* thenSteeringangleAng_0AndRunningspeedSpeed_0 = new FuzzyRuleConsequent();
    // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(ang_0);
    // thenSteeringangleAng_0AndRunningspeedSpeed_0->addOutput(speed_0);
    fuzzyRule21 = new FuzzyRule(21, ifShiftS_0AndDistanceD_4, thenSteeringangleAng_0AndRunningspeedSpeed_0);
    fuzzy->addFuzzyRule(fuzzyRule21);

    float target_x = 21.88; //    key in the digital value
    float target_y = 32;

    // target_x and target_y are the inputs
    fuzzy->setInput(1, target_x); // shift
    fuzzy->setInput(2, target_y); // deistance

    fuzzy->fuzzify(); // Executing the fuzzification

    float output1 = fuzzy->defuzzify(1); // steering angle
    float output2 = fuzzy->defuzzify(2); // running speed

    ASSERT_NEAR(70.0, output1, 0.01);
    ASSERT_NEAR(75.0, output2, 0.01);
}

// ##### MAIN

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
