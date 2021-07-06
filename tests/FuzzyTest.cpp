#include "gtest/gtest.h"
#include "../Fuzzy.h"

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

    fuzzyComposition->addPoint(25, 0);
    fuzzyComposition->addPoint(25, 1);
    fuzzyComposition->addPoint(25, 0);
    fuzzyComposition->build();
    ASSERT_EQ(3, fuzzyComposition->countPoints());
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

    ASSERT_EQ(8, fuzzyComposition->countPoints());

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

    ASSERT_FLOAT_EQ(19.375, fuzzy->defuzzify(1));
}

// ##### Tests from explanation Fuzzy System

// From: https://www.massey.ac.nz/~nhreyes/MASSEY/159741/Lectures/Lec2012-3-159741-FuzzyLogic-v.2.pdf
TEST(Fuzzy, testFromLectureSystemsOne)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *size = new FuzzyInput(1);

    FuzzySet *smallSize = new FuzzySet(0, 0, 0, 10);
    size->addFuzzySet(smallSize);
    FuzzySet *largeSize = new FuzzySet(0, 10, 10, 10);
    size->addFuzzySet(largeSize);

    fuzzy->addFuzzyInput(size);

    // FuzzyInput
    FuzzyInput *weight = new FuzzyInput(2);

    FuzzySet *smallWeight = new FuzzySet(0, 0, 0, 100);
    weight->addFuzzySet(smallWeight);
    FuzzySet *largeWeight = new FuzzySet(0, 100, 100, 100);
    weight->addFuzzySet(largeWeight);

    fuzzy->addFuzzyInput(weight);

    // FuzzyOutput
    FuzzyOutput *quality = new FuzzyOutput(1);

    FuzzySet *bad = new FuzzySet(0, 0, 0, 0.5);
    quality->addFuzzySet(bad);
    FuzzySet *medium = new FuzzySet(0, 0.5, 0.5, 1.0);
    quality->addFuzzySet(medium);
    FuzzySet *good = new FuzzySet(0.5, 1.0, 1.0, 1.0);
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

    ASSERT_FLOAT_EQ(0.37692466, fuzzy->defuzzify(1)); // 0.3698 on the paper
}

// From: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.486.1238&rep=rep1&type=pdf
TEST(Fuzzy, testFromLectureSystemsTwo)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *veryLow = new FuzzySet(-5, -5, -5, 15);
    temperature->addFuzzySet(veryLow);
    FuzzySet *low = new FuzzySet(10, 20, 20, 30);
    temperature->addFuzzySet(low);
    FuzzySet *high = new FuzzySet(25, 30, 30, 35);
    temperature->addFuzzySet(high);
    FuzzySet *veryHigh = new FuzzySet(30, 50, 50, 50);
    temperature->addFuzzySet(veryHigh);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *humidity = new FuzzyInput(2);

    FuzzySet *dry = new FuzzySet(-5, -5, -5, 30);
    humidity->addFuzzySet(dry);
    FuzzySet *comfortable = new FuzzySet(20, 35, 35, 50);
    humidity->addFuzzySet(comfortable);
    FuzzySet *humid = new FuzzySet(40, 55, 55, 70);
    humidity->addFuzzySet(humid);
    FuzzySet *sticky = new FuzzySet(60, 100, 100, 100);
    humidity->addFuzzySet(sticky);

    fuzzy->addFuzzyInput(humidity);

    // FuzzyOutput
    FuzzyOutput *speed = new FuzzyOutput(1);

    FuzzySet *off = new FuzzySet(0, 0, 0, 0);
    speed->addFuzzySet(off);
    FuzzySet *lowHumidity = new FuzzySet(30, 45, 45, 60);
    speed->addFuzzySet(lowHumidity);
    FuzzySet *medium = new FuzzySet(50, 65, 65, 80);
    speed->addFuzzySet(medium);
    FuzzySet *fast = new FuzzySet(70, 90, 95, 95);
    speed->addFuzzySet(fast);

    fuzzy->addFuzzyOutput(speed);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndDry = new FuzzyRuleAntecedent();
    ifVeryLowAndDry->joinWithAND(veryLow, dry);
    FuzzyRuleConsequent *thenOff1 = new FuzzyRuleConsequent();
    thenOff1->addOutput(off);
    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifVeryLowAndDry, thenOff1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndComfortable = new FuzzyRuleAntecedent();
    ifVeryLowAndComfortable->joinWithAND(veryLow, comfortable);
    FuzzyRuleConsequent *thenOff2 = new FuzzyRuleConsequent();
    thenOff2->addOutput(off);
    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifVeryLowAndComfortable, thenOff2);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndHumid = new FuzzyRuleAntecedent();
    ifVeryLowAndHumid->joinWithAND(veryLow, humid);
    FuzzyRuleConsequent *thenOff3 = new FuzzyRuleConsequent();
    thenOff3->addOutput(off);
    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifVeryLowAndHumid, thenOff3);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndSticky = new FuzzyRuleAntecedent();
    ifVeryLowAndSticky->joinWithAND(veryLow, sticky);
    FuzzyRuleConsequent *thenLow1 = new FuzzyRuleConsequent();
    thenLow1->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifVeryLowAndSticky, thenLow1);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndDry = new FuzzyRuleAntecedent();
    ifLowAndDry->joinWithAND(low, dry);
    FuzzyRuleConsequent *thenOff4 = new FuzzyRuleConsequent();
    thenOff4->addOutput(off);
    FuzzyRule *fuzzyRule5 = new FuzzyRule(5, ifLowAndDry, thenOff4);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndComfortable = new FuzzyRuleAntecedent();
    ifLowAndComfortable->joinWithAND(low, comfortable);
    FuzzyRuleConsequent *thenOff5 = new FuzzyRuleConsequent();
    thenOff5->addOutput(off);
    FuzzyRule *fuzzyRule6 = new FuzzyRule(6, ifLowAndComfortable, thenOff5);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndHumid = new FuzzyRuleAntecedent();
    ifLowAndHumid->joinWithAND(low, humid);
    FuzzyRuleConsequent *thenLow2 = new FuzzyRuleConsequent();
    thenLow2->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule7 = new FuzzyRule(7, ifLowAndHumid, thenLow2);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndSticky = new FuzzyRuleAntecedent();
    ifLowAndSticky->joinWithAND(low, sticky);
    FuzzyRuleConsequent *thenMedium1 = new FuzzyRuleConsequent();
    thenMedium1->addOutput(medium);
    FuzzyRule *fuzzyRule8 = new FuzzyRule(8, ifLowAndSticky, thenMedium1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndDry = new FuzzyRuleAntecedent();
    ifHighAndDry->joinWithAND(high, dry);
    FuzzyRuleConsequent *thenLow3 = new FuzzyRuleConsequent();
    thenLow3->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule9 = new FuzzyRule(9, ifHighAndDry, thenLow3);
    fuzzy->addFuzzyRule(fuzzyRule9);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndComfortable = new FuzzyRuleAntecedent();
    ifHighAndComfortable->joinWithAND(high, comfortable);
    FuzzyRuleConsequent *thenMedium2 = new FuzzyRuleConsequent();
    thenMedium2->addOutput(medium);
    FuzzyRule *fuzzyRule10 = new FuzzyRule(10, ifHighAndComfortable, thenMedium2);
    fuzzy->addFuzzyRule(fuzzyRule10);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndHumid = new FuzzyRuleAntecedent();
    ifHighAndHumid->joinWithAND(high, humid);
    FuzzyRuleConsequent *thenFast1 = new FuzzyRuleConsequent();
    thenFast1->addOutput(fast);
    FuzzyRule *fuzzyRule11 = new FuzzyRule(11, ifHighAndHumid, thenFast1);
    fuzzy->addFuzzyRule(fuzzyRule11);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndSticky = new FuzzyRuleAntecedent();
    ifHighAndSticky->joinWithAND(high, sticky);
    FuzzyRuleConsequent *thenFast2 = new FuzzyRuleConsequent();
    thenFast2->addOutput(fast);
    FuzzyRule *fuzzyRule12 = new FuzzyRule(12, ifHighAndSticky, thenFast2);
    fuzzy->addFuzzyRule(fuzzyRule12);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndDry = new FuzzyRuleAntecedent();
    ifVeryHighAndDry->joinWithAND(veryHigh, dry);
    FuzzyRuleConsequent *thenMedium3 = new FuzzyRuleConsequent();
    thenMedium3->addOutput(medium);
    FuzzyRule *fuzzyRule13 = new FuzzyRule(13, ifVeryHighAndDry, thenMedium3);
    fuzzy->addFuzzyRule(fuzzyRule13);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndComfortable = new FuzzyRuleAntecedent();
    ifVeryHighAndComfortable->joinWithAND(veryHigh, comfortable);
    FuzzyRuleConsequent *thenFast3 = new FuzzyRuleConsequent();
    thenFast3->addOutput(fast);
    FuzzyRule *fuzzyRule14 = new FuzzyRule(14, ifVeryHighAndComfortable, thenFast3);
    fuzzy->addFuzzyRule(fuzzyRule14);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndHumid = new FuzzyRuleAntecedent();
    ifVeryHighAndHumid->joinWithAND(veryHigh, humid);
    FuzzyRuleConsequent *thenFast4 = new FuzzyRuleConsequent();
    thenFast4->addOutput(fast);
    FuzzyRule *fuzzyRule15 = new FuzzyRule(15, ifVeryHighAndHumid, thenFast4);
    fuzzy->addFuzzyRule(fuzzyRule15);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndSticky = new FuzzyRuleAntecedent();
    ifVeryHighAndSticky->joinWithAND(veryHigh, sticky);
    FuzzyRuleConsequent *thenFast5 = new FuzzyRuleConsequent();
    thenFast5->addOutput(fast);
    FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ifVeryHighAndSticky, thenFast5);
    fuzzy->addFuzzyRule(fuzzyRule16);

    // run it
    fuzzy->setInput(1, 20);
    fuzzy->setInput(2, 65);
    fuzzy->fuzzify();

    ASSERT_FLOAT_EQ(50.568535, fuzzy->defuzzify(1)); // This value was not extracted from the paper
}

// ##### Tests from real systems, received from eFLL users

// From miss Casco (Paraguay)
TEST(Fuzzy, testFromLibraryUsersSystemsCasco)
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *humedad = new FuzzyInput(1);

    FuzzySet *seco = new FuzzySet(0, 0, 0, 42.5);
    humedad->addFuzzySet(seco);
    FuzzySet *humedo = new FuzzySet(37.5, 60, 60, 82.5);
    humedad->addFuzzySet(humedo);
    FuzzySet *encharcado = new FuzzySet(77.5, 100, 100, 100);
    humedad->addFuzzySet(encharcado);

    fuzzy->addFuzzyInput(humedad);

    // FuzzyInput
    FuzzyInput *temperatura = new FuzzyInput(2);

    FuzzySet *frio = new FuzzySet(-5, -5, -5, 12.5);
    temperatura->addFuzzySet(frio);
    FuzzySet *templado = new FuzzySet(7.5, 17.5, 17.5, 27.5);
    temperatura->addFuzzySet(templado);
    FuzzySet *calor = new FuzzySet(22.5, 45, 45, 45);
    temperatura->addFuzzySet(calor);

    fuzzy->addFuzzyInput(temperatura);

    // FuzzyInput
    FuzzyInput *mes = new FuzzyInput(3);

    FuzzySet *verano = new FuzzySet(0, 0, 0, 3.5);
    mes->addFuzzySet(verano);
    FuzzySet *otono = new FuzzySet(2.5, 4.5, 4.5, 6.5);
    mes->addFuzzySet(otono);
    FuzzySet *invierno = new FuzzySet(5.5, 7.5, 7.5, 9.5);
    mes->addFuzzySet(invierno);
    FuzzySet *primavera = new FuzzySet(8.5, 12, 12, 12);
    mes->addFuzzySet(primavera);

    fuzzy->addFuzzyInput(mes);

    // FuzzyOutput
    FuzzyOutput *tiempo = new FuzzyOutput(1);

    FuzzySet *nada = new FuzzySet(0, 0, 0, 0);
    tiempo->addFuzzySet(nada);
    FuzzySet *muyPoco = new FuzzySet(0, 0, 0, 5.5);
    tiempo->addFuzzySet(muyPoco);
    FuzzySet *poco = new FuzzySet(4.5, 7.5, 7.5, 10.5);
    tiempo->addFuzzySet(poco);
    FuzzySet *medio = new FuzzySet(9.5, 12.5, 12.5, 15.5);
    tiempo->addFuzzySet(medio);
    FuzzySet *bastante = new FuzzySet(14.5, 17.5, 17.5, 20.5);
    tiempo->addFuzzySet(bastante);
    FuzzySet *mucho = new FuzzySet(19.5, 22.5, 22.5, 25.5);
    tiempo->addFuzzySet(mucho);
    FuzzySet *muchisimo = new FuzzySet(24.5, 30, 30, 30);
    tiempo->addFuzzySet(muchisimo);

    fuzzy->addFuzzyOutput(tiempo);

    // ############## Rule 1
    FuzzyRuleAntecedent *fuzzyAntecedentA_1 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_1->joinWithAND(seco, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_1 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_1->joinWithAND(fuzzyAntecedentA_1, verano);
    FuzzyRuleConsequent *fuzzyConsequent_1 = new FuzzyRuleConsequent();
    fuzzyConsequent_1->addOutput(medio);

    FuzzyRule *fuzzyRule_1 = new FuzzyRule(1, fuzzyAntecedentB_1, fuzzyConsequent_1);
    fuzzy->addFuzzyRule(fuzzyRule_1);

    // ############## Rule 2
    FuzzyRuleAntecedent *fuzzyAntecedentA_2 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_2->joinWithAND(seco, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_2 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_2->joinWithAND(fuzzyAntecedentA_2, otono);
    FuzzyRuleConsequent *fuzzyConsequent_2 = new FuzzyRuleConsequent();
    fuzzyConsequent_2->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_2 = new FuzzyRule(2, fuzzyAntecedentB_2, fuzzyConsequent_2);
    fuzzy->addFuzzyRule(fuzzyRule_2);

    // ############## Rule 3
    FuzzyRuleAntecedent *fuzzyAntecedentA_3 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_3->joinWithAND(seco, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_3 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_3->joinWithAND(fuzzyAntecedentA_3, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_3 = new FuzzyRuleConsequent();
    fuzzyConsequent_3->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_3 = new FuzzyRule(3, fuzzyAntecedentB_3, fuzzyConsequent_3);
    fuzzy->addFuzzyRule(fuzzyRule_3);

    // ############## Rule 4
    FuzzyRuleAntecedent *fuzzyAntecedentA_4 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_4->joinWithAND(seco, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_4 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_4->joinWithAND(fuzzyAntecedentA_4, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_4 = new FuzzyRuleConsequent();
    fuzzyConsequent_4->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_4 = new FuzzyRule(4, fuzzyAntecedentB_4, fuzzyConsequent_4);
    fuzzy->addFuzzyRule(fuzzyRule_4);

    // ############## Rule 5
    FuzzyRuleAntecedent *fuzzyAntecedentA_5 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_5->joinWithAND(humedo, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_5 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_5->joinWithAND(fuzzyAntecedentA_5, verano);
    FuzzyRuleConsequent *fuzzyConsequent_5 = new FuzzyRuleConsequent();
    fuzzyConsequent_5->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_5 = new FuzzyRule(5, fuzzyAntecedentB_5, fuzzyConsequent_5);
    fuzzy->addFuzzyRule(fuzzyRule_5);

    // ############## Rule 6
    FuzzyRuleAntecedent *fuzzyAntecedentA_6 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_6->joinWithAND(humedo, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_6 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_6->joinWithAND(fuzzyAntecedentA_6, otono);
    FuzzyRuleConsequent *fuzzyConsequent_6 = new FuzzyRuleConsequent();
    fuzzyConsequent_6->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_6 = new FuzzyRule(6, fuzzyAntecedentB_6, fuzzyConsequent_6);
    fuzzy->addFuzzyRule(fuzzyRule_6);

    // ############## Rule 7
    FuzzyRuleAntecedent *fuzzyAntecedentA_7 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_7->joinWithAND(humedo, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_7 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_7->joinWithAND(fuzzyAntecedentA_7, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_7 = new FuzzyRuleConsequent();
    fuzzyConsequent_7->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_7 = new FuzzyRule(7, fuzzyAntecedentB_7, fuzzyConsequent_7);
    fuzzy->addFuzzyRule(fuzzyRule_7);

    // ############## Rule 8
    FuzzyRuleAntecedent *fuzzyAntecedentA_8 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_8->joinWithAND(humedo, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_8 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_8->joinWithAND(fuzzyAntecedentA_8, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_8 = new FuzzyRuleConsequent();
    fuzzyConsequent_8->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_8 = new FuzzyRule(8, fuzzyAntecedentB_8, fuzzyConsequent_8);
    fuzzy->addFuzzyRule(fuzzyRule_8);

    // ############## Rule 9
    FuzzyRuleAntecedent *fuzzyAntecedentA_9 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_9->joinWithAND(encharcado, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_9 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_9->joinWithAND(fuzzyAntecedentA_9, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_9 = new FuzzyRuleConsequent();
    fuzzyConsequent_9->addOutput(nada);

    FuzzyRule *fuzzyRule_9 = new FuzzyRule(9, fuzzyAntecedentB_9, fuzzyConsequent_9);
    fuzzy->addFuzzyRule(fuzzyRule_9);

    // ############## Rule 10
    FuzzyRuleAntecedent *fuzzyAntecedentA_10 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_10->joinWithAND(encharcado, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_10 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_10->joinWithAND(fuzzyAntecedentA_10, otono);
    FuzzyRuleConsequent *fuzzyConsequent_10 = new FuzzyRuleConsequent();
    fuzzyConsequent_10->addOutput(nada);

    FuzzyRule *fuzzyRule_10 = new FuzzyRule(10, fuzzyAntecedentB_10, fuzzyConsequent_10);
    fuzzy->addFuzzyRule(fuzzyRule_10);

    // ############## Rule 11
    FuzzyRuleAntecedent *fuzzyAntecedentA_11 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_11->joinWithAND(encharcado, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_11 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_11->joinWithAND(fuzzyAntecedentA_11, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_11 = new FuzzyRuleConsequent();
    fuzzyConsequent_11->addOutput(nada);

    FuzzyRule *fuzzyRule_11 = new FuzzyRule(11, fuzzyAntecedentB_11, fuzzyConsequent_11);
    fuzzy->addFuzzyRule(fuzzyRule_11);

    // ############## Rule 12
    FuzzyRuleAntecedent *fuzzyAntecedentA_12 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_12->joinWithAND(encharcado, frio);
    FuzzyRuleAntecedent *fuzzyAntecedentB_12 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_12->joinWithAND(fuzzyAntecedentA_12, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_12 = new FuzzyRuleConsequent();
    fuzzyConsequent_12->addOutput(nada);

    FuzzyRule *fuzzyRule_12 = new FuzzyRule(12, fuzzyAntecedentB_12, fuzzyConsequent_12);
    fuzzy->addFuzzyRule(fuzzyRule_12);

    // ############## Rule 13
    FuzzyRuleAntecedent *fuzzyAntecedentA_13 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_13->joinWithAND(seco, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_13 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_13->joinWithAND(fuzzyAntecedentA_13, verano);
    FuzzyRuleConsequent *fuzzyConsequent_13 = new FuzzyRuleConsequent();
    fuzzyConsequent_13->addOutput(bastante);

    FuzzyRule *fuzzyRule_13 = new FuzzyRule(13, fuzzyAntecedentB_13, fuzzyConsequent_13);
    fuzzy->addFuzzyRule(fuzzyRule_13);

    // ############## Rule 14
    FuzzyRuleAntecedent *fuzzyAntecedentA_14 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_14->joinWithAND(seco, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_14 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_14->joinWithAND(fuzzyAntecedentA_14, otono);
    FuzzyRuleConsequent *fuzzyConsequent_14 = new FuzzyRuleConsequent();
    fuzzyConsequent_14->addOutput(medio);

    FuzzyRule *fuzzyRule_14 = new FuzzyRule(14, fuzzyAntecedentB_14, fuzzyConsequent_14);
    fuzzy->addFuzzyRule(fuzzyRule_14);

    // ############## Rule 15
    FuzzyRuleAntecedent *fuzzyAntecedentA_15 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_15->joinWithAND(seco, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_15 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_15->joinWithAND(fuzzyAntecedentA_15, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_15 = new FuzzyRuleConsequent();
    fuzzyConsequent_15->addOutput(poco);

    FuzzyRule *fuzzyRule_15 = new FuzzyRule(15, fuzzyAntecedentB_15, fuzzyConsequent_15);
    fuzzy->addFuzzyRule(fuzzyRule_15);

    // ############## Rule 16
    FuzzyRuleAntecedent *fuzzyAntecedentA_16 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_16->joinWithAND(seco, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_16 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_16->joinWithAND(fuzzyAntecedentA_16, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_16 = new FuzzyRuleConsequent();
    fuzzyConsequent_16->addOutput(bastante);

    FuzzyRule *fuzzyRule_16 = new FuzzyRule(16, fuzzyAntecedentB_16, fuzzyConsequent_16);
    fuzzy->addFuzzyRule(fuzzyRule_16);

    // ############## Rule 17
    FuzzyRuleAntecedent *fuzzyAntecedentA_17 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_17->joinWithAND(humedo, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_17 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_17->joinWithAND(fuzzyAntecedentA_17, verano);
    FuzzyRuleConsequent *fuzzyConsequent_17 = new FuzzyRuleConsequent();
    fuzzyConsequent_17->addOutput(medio);

    FuzzyRule *fuzzyRule_17 = new FuzzyRule(17, fuzzyAntecedentB_17, fuzzyConsequent_17);
    fuzzy->addFuzzyRule(fuzzyRule_17);

    // ############## Rule 18
    FuzzyRuleAntecedent *fuzzyAntecedentA_18 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_18->joinWithAND(humedo, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_18 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_18->joinWithAND(fuzzyAntecedentA_18, otono);
    FuzzyRuleConsequent *fuzzyConsequent_18 = new FuzzyRuleConsequent();
    fuzzyConsequent_18->addOutput(poco);

    FuzzyRule *fuzzyRule_18 = new FuzzyRule(18, fuzzyAntecedentB_18, fuzzyConsequent_18);
    fuzzy->addFuzzyRule(fuzzyRule_18);

    // ############## Rule 19
    FuzzyRuleAntecedent *fuzzyAntecedentA_19 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_19->joinWithAND(humedo, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_19 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_19->joinWithAND(fuzzyAntecedentA_19, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_19 = new FuzzyRuleConsequent();
    fuzzyConsequent_19->addOutput(poco);

    FuzzyRule *fuzzyRule_19 = new FuzzyRule(19, fuzzyAntecedentB_19, fuzzyConsequent_19);
    fuzzy->addFuzzyRule(fuzzyRule_19);

    // ############## Rule 20
    FuzzyRuleAntecedent *fuzzyAntecedentA_20 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_20->joinWithAND(humedo, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_20 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_20->joinWithAND(fuzzyAntecedentA_20, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_20 = new FuzzyRuleConsequent();
    fuzzyConsequent_20->addOutput(medio);

    FuzzyRule *fuzzyRule_20 = new FuzzyRule(20, fuzzyAntecedentB_20, fuzzyConsequent_20);
    fuzzy->addFuzzyRule(fuzzyRule_20);

    // ############## Rule 21
    FuzzyRuleAntecedent *fuzzyAntecedentA_21 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_21->joinWithAND(encharcado, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_21 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_21->joinWithAND(fuzzyAntecedentA_21, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_21 = new FuzzyRuleConsequent();
    fuzzyConsequent_21->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_21 = new FuzzyRule(21, fuzzyAntecedentB_21, fuzzyConsequent_21);
    fuzzy->addFuzzyRule(fuzzyRule_21);

    // ############## Rule 22
    FuzzyRuleAntecedent *fuzzyAntecedentA_22 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_22->joinWithAND(encharcado, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_22 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_22->joinWithAND(fuzzyAntecedentA_22, otono);
    FuzzyRuleConsequent *fuzzyConsequent_22 = new FuzzyRuleConsequent();
    fuzzyConsequent_22->addOutput(nada);

    FuzzyRule *fuzzyRule_22 = new FuzzyRule(22, fuzzyAntecedentB_22, fuzzyConsequent_22);
    fuzzy->addFuzzyRule(fuzzyRule_22);

    // ############## Rule 23
    FuzzyRuleAntecedent *fuzzyAntecedentA_23 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_23->joinWithAND(encharcado, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_23 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_23->joinWithAND(fuzzyAntecedentA_23, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_23 = new FuzzyRuleConsequent();
    fuzzyConsequent_23->addOutput(nada);

    FuzzyRule *fuzzyRule_23 = new FuzzyRule(23, fuzzyAntecedentB_23, fuzzyConsequent_23);
    fuzzy->addFuzzyRule(fuzzyRule_23);

    // ############## Rule 24
    FuzzyRuleAntecedent *fuzzyAntecedentA_24 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_24->joinWithAND(encharcado, templado);
    FuzzyRuleAntecedent *fuzzyAntecedentB_24 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_24->joinWithAND(fuzzyAntecedentA_24, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_24 = new FuzzyRuleConsequent();
    fuzzyConsequent_24->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_24 = new FuzzyRule(24, fuzzyAntecedentB_24, fuzzyConsequent_24);
    fuzzy->addFuzzyRule(fuzzyRule_24);

    // ############## Rule 25
    FuzzyRuleAntecedent *fuzzyAntecedentA_25 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_25->joinWithAND(seco, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_25 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_25->joinWithAND(fuzzyAntecedentA_25, verano);
    FuzzyRuleConsequent *fuzzyConsequent_25 = new FuzzyRuleConsequent();
    fuzzyConsequent_25->addOutput(mucho);

    FuzzyRule *fuzzyRule_25 = new FuzzyRule(25, fuzzyAntecedentB_25, fuzzyConsequent_25);
    fuzzy->addFuzzyRule(fuzzyRule_25);

    // ############## Rule 26
    FuzzyRuleAntecedent *fuzzyAntecedentA_26 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_26->joinWithAND(seco, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_26 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_26->joinWithAND(fuzzyAntecedentA_26, otono);
    FuzzyRuleConsequent *fuzzyConsequent_26 = new FuzzyRuleConsequent();
    fuzzyConsequent_26->addOutput(medio);

    FuzzyRule *fuzzyRule_26 = new FuzzyRule(26, fuzzyAntecedentB_26, fuzzyConsequent_26);
    fuzzy->addFuzzyRule(fuzzyRule_26);

    // ############## Rule 27
    FuzzyRuleAntecedent *fuzzyAntecedentA_27 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_27->joinWithAND(seco, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_27 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_27->joinWithAND(fuzzyAntecedentA_27, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_27 = new FuzzyRuleConsequent();
    fuzzyConsequent_27->addOutput(medio);

    FuzzyRule *fuzzyRule_27 = new FuzzyRule(27, fuzzyAntecedentB_27, fuzzyConsequent_27);
    fuzzy->addFuzzyRule(fuzzyRule_27);

    // ############## Rule 28
    FuzzyRuleAntecedent *fuzzyAntecedentA_28 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_28->joinWithAND(seco, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_28 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_28->joinWithAND(fuzzyAntecedentA_28, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_28 = new FuzzyRuleConsequent();
    fuzzyConsequent_28->addOutput(mucho);

    FuzzyRule *fuzzyRule_28 = new FuzzyRule(28, fuzzyAntecedentB_28, fuzzyConsequent_28);
    fuzzy->addFuzzyRule(fuzzyRule_28);

    // ############## Rule 29
    FuzzyRuleAntecedent *fuzzyAntecedentA_29 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_29->joinWithAND(humedo, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_29 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_29->joinWithAND(fuzzyAntecedentA_29, verano);
    FuzzyRuleConsequent *fuzzyConsequent_29 = new FuzzyRuleConsequent();
    fuzzyConsequent_29->addOutput(bastante);

    FuzzyRule *fuzzyRule_29 = new FuzzyRule(29, fuzzyAntecedentB_29, fuzzyConsequent_29);
    fuzzy->addFuzzyRule(fuzzyRule_29);

    // ############## Rule 30
    FuzzyRuleAntecedent *fuzzyAntecedentA_30 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_30->joinWithAND(humedo, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_30 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_30->joinWithAND(fuzzyAntecedentA_30, otono);
    FuzzyRuleConsequent *fuzzyConsequent_30 = new FuzzyRuleConsequent();
    fuzzyConsequent_30->addOutput(bastante);

    FuzzyRule *fuzzyRule_30 = new FuzzyRule(30, fuzzyAntecedentB_30, fuzzyConsequent_30);
    fuzzy->addFuzzyRule(fuzzyRule_30);

    // ############## Rule 31
    FuzzyRuleAntecedent *fuzzyAntecedentA_31 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_31->joinWithAND(humedo, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_31 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_31->joinWithAND(fuzzyAntecedentA_31, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_31 = new FuzzyRuleConsequent();
    fuzzyConsequent_31->addOutput(bastante);

    FuzzyRule *fuzzyRule_31 = new FuzzyRule(31, fuzzyAntecedentB_31, fuzzyConsequent_31);
    fuzzy->addFuzzyRule(fuzzyRule_31);

    // ############## Rule 32
    FuzzyRuleAntecedent *fuzzyAntecedentA_32 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_32->joinWithAND(humedo, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_32 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_32->joinWithAND(fuzzyAntecedentA_32, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_32 = new FuzzyRuleConsequent();
    fuzzyConsequent_32->addOutput(medio);

    FuzzyRule *fuzzyRule_32 = new FuzzyRule(32, fuzzyAntecedentB_32, fuzzyConsequent_32);
    fuzzy->addFuzzyRule(fuzzyRule_32);

    // ############## Rule 33
    FuzzyRuleAntecedent *fuzzyAntecedentA_33 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_33->joinWithAND(encharcado, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_33 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_33->joinWithAND(fuzzyAntecedentA_33, verano);
    FuzzyRuleConsequent *fuzzyConsequent_33 = new FuzzyRuleConsequent();
    fuzzyConsequent_33->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_33 = new FuzzyRule(33, fuzzyAntecedentB_33, fuzzyConsequent_33);
    fuzzy->addFuzzyRule(fuzzyRule_33);

    // ############## Rule 34
    FuzzyRuleAntecedent *fuzzyAntecedentA_34 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_34->joinWithAND(encharcado, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_34 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_34->joinWithAND(fuzzyAntecedentA_34, otono);
    FuzzyRuleConsequent *fuzzyConsequent_34 = new FuzzyRuleConsequent();
    fuzzyConsequent_34->addOutput(nada);

    FuzzyRule *fuzzyRule_34 = new FuzzyRule(34, fuzzyAntecedentB_34, fuzzyConsequent_34);
    fuzzy->addFuzzyRule(fuzzyRule_34);

    // ############## Rule 35
    FuzzyRuleAntecedent *fuzzyAntecedentA_35 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_35->joinWithAND(encharcado, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_35 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_35->joinWithAND(fuzzyAntecedentA_35, invierno);
    FuzzyRuleConsequent *fuzzyConsequent_35 = new FuzzyRuleConsequent();
    fuzzyConsequent_35->addOutput(nada);

    FuzzyRule *fuzzyRule_35 = new FuzzyRule(35, fuzzyAntecedentB_35, fuzzyConsequent_35);
    fuzzy->addFuzzyRule(fuzzyRule_35);

    // ############## Rule 36
    FuzzyRuleAntecedent *fuzzyAntecedentA_36 = new FuzzyRuleAntecedent();
    fuzzyAntecedentA_36->joinWithAND(encharcado, calor);
    FuzzyRuleAntecedent *fuzzyAntecedentB_36 = new FuzzyRuleAntecedent();
    fuzzyAntecedentB_36->joinWithAND(fuzzyAntecedentA_36, primavera);
    FuzzyRuleConsequent *fuzzyConsequent_36 = new FuzzyRuleConsequent();
    fuzzyConsequent_36->addOutput(muyPoco);

    FuzzyRule *fuzzyRule_36 = new FuzzyRule(36, fuzzyAntecedentB_36, fuzzyConsequent_36);
    fuzzy->addFuzzyRule(fuzzyRule_36);

    // TEST 01
    fuzzy->setInput(1, 54.82);
    fuzzy->setInput(2, 20);
    fuzzy->setInput(3, 6);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(7.5, fuzzy->defuzzify(1));

    // TEST 02
    fuzzy->setInput(1, 12.65);
    fuzzy->setInput(2, 1.928);
    fuzzy->setInput(3, 6);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(2.4226191, fuzzy->defuzzify(1)); // 2.35 on original file

    // TEST 03
    fuzzy->setInput(1, 25.9);
    fuzzy->setInput(2, 8.55);
    fuzzy->setInput(3, 6);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(6.4175873, fuzzy->defuzzify(1)); // 6.21 on original file

    // TEST 04
    fuzzy->setInput(1, 71.69);
    fuzzy->setInput(2, 8.554);
    fuzzy->setInput(3, 6);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(4.2093439, fuzzy->defuzzify(1)); // 4.12 on original file

    // TEST 05
    fuzzy->setInput(1, 71.69);
    fuzzy->setInput(2, 27.83);
    fuzzy->setInput(3, 9.036);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(15.478251, fuzzy->defuzzify(1)); // 15.5 on original file

    // TEST 06
    fuzzy->setInput(1, 16.27);
    fuzzy->setInput(2, 27.83);
    fuzzy->setInput(3, 9.036);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(16.58123, fuzzy->defuzzify(1)); // 16.6 on original file

    // TEST 07
    fuzzy->setInput(1, 82.53);
    fuzzy->setInput(2, 27.83);
    fuzzy->setInput(3, 10.63);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(2.4555054, fuzzy->defuzzify(1)); // 2.38 on original file

    // TEST 08
    fuzzy->setInput(1, 7.831);
    fuzzy->setInput(2, 27.83);
    fuzzy->setInput(3, 10.63);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(22.5, fuzzy->defuzzify(1));

    // TEST 09
    fuzzy->setInput(1, 7.831);
    fuzzy->setInput(2, 7.952);
    fuzzy->setInput(3, 10.63);

    fuzzy->fuzzify();

    EXPECT_FLOAT_EQ(5.0615907, fuzzy->defuzzify(1)); // 4.96 on original file
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
