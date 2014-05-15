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
    Fuzzy* fuzzy = new Fuzzy();

    ///////////////////////////////////////////////////////////////////////////////
    FuzzySet* ErroAltoNegativo = new FuzzySet(-101, -101, -100, -50);
    FuzzySet* ErroMedioNegativo = new FuzzySet(-100, -50, -50, 0);
    FuzzySet* ErroBaixonegativo = new FuzzySet(-50, 0, 0, 0);
    FuzzySet* ErroBaixoPositivo = new FuzzySet(0, 0, 0, 50);
    FuzzySet* ErroMedioPositivo = new FuzzySet(0,50, 50, 100);
    FuzzySet* ErroAltoPositivo = new FuzzySet(50, 100, 101, 101);

    // Criando o FuzzyInput Erro
    FuzzyInput* Erro = new FuzzyInput(1);
    // Criando os FuzzySet que compoem o FuzzyInput distancia 
    Erro->addFuzzySet(ErroAltoNegativo); // Adicionando o FuzzySet small em Erro
    Erro->addFuzzySet(ErroMedioNegativo); // Adicionando o FuzzySet small em Erro
    Erro->addFuzzySet(ErroBaixonegativo); // Adicionando o FuzzySet small em Erro
    Erro->addFuzzySet(ErroBaixoPositivo); // Adicionando o FuzzySet small em Erro
    Erro->addFuzzySet(ErroMedioPositivo); // Adicionando o FuzzySet small em Erro
    Erro->addFuzzySet(ErroAltoPositivo); // Adicionando o FuzzySet small em Erro

    fuzzy->addFuzzyInput(Erro); // Adicionando o FuzzyInput no objeto Fuzzy  
    ///////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////

    FuzzySet* DerroAltoNegativo = new FuzzySet(-101, -101, -100, -50);
    FuzzySet* DerroMedioNegativo = new FuzzySet(-100, -50, -50, 0);
    FuzzySet* DerroBaixonegativo = new FuzzySet(-50, 0, 0, 0);
    FuzzySet* DerroBaixoPositivo = new FuzzySet(0, 0, 0, 50);
    FuzzySet* DerroMedioPositivo = new FuzzySet(0,50, 50, 100);
    FuzzySet* DerroAltoPositivo = new FuzzySet(50, 100, 101, 101);

    // Criando o FuzzyInput Derivada do Erro
    FuzzyInput* DErro = new FuzzyInput(2);
    // Criando os FuzzySet que compoem o FuzzyInput distancia 
    DErro->addFuzzySet(DerroAltoNegativo); // Adicionando o FuzzySet small em DErro
    DErro->addFuzzySet(DerroMedioNegativo); // Adicionando o FuzzySet small em DErro
    DErro->addFuzzySet(DerroBaixonegativo); // Adicionando o FuzzySet small em DErro
    DErro->addFuzzySet(DerroBaixoPositivo); // Adicionando o FuzzySet small em DErro
    DErro->addFuzzySet(DerroMedioPositivo); // Adicionando o FuzzySet small em DErro
    DErro->addFuzzySet(DerroAltoPositivo); // Adicionando o FuzzySet small em DErro

    fuzzy->addFuzzyInput(DErro); // Adicionando o FuzzyInput no objeto Fuzzy 
    //////////////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////////////    
    // Criando o FuzzyOutput Velocidade
    FuzzyOutput* Velocidade = new FuzzyOutput(1);

    FuzzySet* OutAltoNegativo = new FuzzySet(-101, -101, -100, -50);
    FuzzySet* OutMedioNegativo = new FuzzySet(-100, -50, -50, 0);
    FuzzySet* OutBaixonegativo = new FuzzySet(-50, 0, 0, 0);
    FuzzySet* OutBaixoPositivo = new FuzzySet(0, 0, 0, 50);
    FuzzySet* OutMedioPositivo = new FuzzySet(0,50, 50, 100);
    FuzzySet* OutAltoPositivo = new FuzzySet(50, 100, 101, 101);


    // Criando os FuzzySet que compoem o FuzzyOutput velocidade 
    Velocidade->addFuzzySet(OutAltoNegativo);  // Adicionando o FuzzySet slow em velocity
    Velocidade->addFuzzySet(OutMedioNegativo);  // Adicionando o FuzzySet slow em velocity
    Velocidade->addFuzzySet(OutBaixonegativo);  // Adicionando o FuzzySet slow em velocity
    Velocidade->addFuzzySet(OutBaixoPositivo);  // Adicionando o FuzzySet slow em velocity
    Velocidade->addFuzzySet(OutMedioPositivo);  // Adicionando o FuzzySet slow em velocity
    Velocidade->addFuzzySet(OutAltoPositivo);  // Adicionando o FuzzySet slow em velocity

    fuzzy->addFuzzyOutput(Velocidade); // Adicionando o FuzzyOutput no objeto Fuzzy   
    //////////////////////////////////////////////////////////////////////////////////




    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroAltoNegativo = new FuzzyRuleAntecedent();
    IfErroAltoNegativoAndDerroAltoNegativo->joinWithAND(ErroAltoNegativo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroMedioNegativo = new FuzzyRuleAntecedent();
    IfErroAltoNegativoAndDerroMedioNegativo->joinWithAND(ErroAltoNegativo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroBaixonegativo = new FuzzyRuleAntecedent();
    IfErroAltoNegativoAndDerroBaixonegativo->joinWithAND(ErroAltoNegativo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroBaixoPositivo = new FuzzyRuleAntecedent();
    IfErroAltoNegativoAndDerroBaixoPositivo->joinWithAND(ErroAltoNegativo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroMedioPositivo = new FuzzyRuleAntecedent(); 
    IfErroAltoNegativoAndDerroMedioPositivo->joinWithAND(ErroAltoNegativo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroAltoNegativoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroAltoNegativoAndDerroAltoPositivo->joinWithAND(ErroAltoNegativo,DerroAltoPositivo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroAltoNegativo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroAltoNegativo->joinWithAND(ErroMedioNegativo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroMedioNegativo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroMedioNegativo->joinWithAND(ErroMedioNegativo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroBaixonegativo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroBaixonegativo->joinWithAND(ErroMedioNegativo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroBaixoPositivo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroBaixoPositivo->joinWithAND(ErroMedioNegativo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroMedioPositivo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroMedioPositivo->joinWithAND(ErroMedioNegativo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroMedioNegativoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroMedioNegativoAndDerroAltoPositivo->joinWithAND(ErroMedioNegativo,DerroAltoPositivo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroAltoNegativo = new FuzzyRuleAntecedent(); 
    IfErroBaixonegativoAndDerroAltoNegativo->joinWithAND(ErroBaixonegativo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroMedioNegativo = new FuzzyRuleAntecedent();
    IfErroBaixonegativoAndDerroMedioNegativo->joinWithAND(ErroBaixonegativo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroBaixonegativo = new FuzzyRuleAntecedent(); 
    IfErroBaixonegativoAndDerroBaixonegativo->joinWithAND(ErroBaixonegativo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroBaixoPositivo = new FuzzyRuleAntecedent(); 
    IfErroBaixonegativoAndDerroBaixoPositivo->joinWithAND(ErroBaixonegativo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroMedioPositivo = new FuzzyRuleAntecedent(); 
    IfErroBaixonegativoAndDerroMedioPositivo->joinWithAND(ErroBaixonegativo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroBaixonegativoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroBaixonegativoAndDerroAltoPositivo->joinWithAND(ErroBaixonegativo,DerroAltoPositivo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroAltoNegativo = new FuzzyRuleAntecedent(); 
    IfErroBaixoPositivoAndDerroAltoNegativo->joinWithAND(ErroBaixoPositivo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroMedioNegativo = new FuzzyRuleAntecedent(); 
    IfErroBaixoPositivoAndDerroMedioNegativo->joinWithAND(ErroBaixoPositivo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroBaixonegativo = new FuzzyRuleAntecedent(); 
    IfErroBaixoPositivoAndDerroBaixonegativo->joinWithAND(ErroBaixoPositivo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroBaixoPositivo = new FuzzyRuleAntecedent(); 
    IfErroBaixoPositivoAndDerroBaixoPositivo->joinWithAND(ErroBaixoPositivo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroMedioPositivo = new FuzzyRuleAntecedent();
    IfErroBaixoPositivoAndDerroMedioPositivo->joinWithAND(ErroBaixoPositivo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroBaixoPositivoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroBaixoPositivoAndDerroAltoPositivo->joinWithAND(ErroBaixoPositivo,DerroAltoPositivo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroAltoNegativo = new FuzzyRuleAntecedent(); 
    IfErroMedioPositivoAndDerroAltoNegativo->joinWithAND(ErroMedioPositivo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroMedioNegativo = new FuzzyRuleAntecedent(); 
    IfErroMedioPositivoAndDerroMedioNegativo->joinWithAND(ErroMedioPositivo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroBaixonegativo = new FuzzyRuleAntecedent();
    IfErroMedioPositivoAndDerroBaixonegativo->joinWithAND(ErroMedioPositivo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroBaixoPositivo = new FuzzyRuleAntecedent(); 
    IfErroMedioPositivoAndDerroBaixoPositivo->joinWithAND(ErroMedioPositivo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroMedioPositivo = new FuzzyRuleAntecedent();
    IfErroMedioPositivoAndDerroMedioPositivo->joinWithAND(ErroMedioPositivo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroMedioPositivoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroMedioPositivoAndDerroAltoPositivo->joinWithAND(ErroMedioPositivo,DerroAltoPositivo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroAltoNegativo = new FuzzyRuleAntecedent(); 
    IfErroAltoPositivoAndDerroAltoNegativo->joinWithAND(ErroAltoPositivo,DerroAltoNegativo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroMedioNegativo = new FuzzyRuleAntecedent();
    IfErroAltoPositivoAndDerroMedioNegativo->joinWithAND(ErroAltoPositivo,DerroMedioNegativo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroBaixonegativo = new FuzzyRuleAntecedent(); 
    IfErroAltoPositivoAndDerroBaixonegativo->joinWithAND(ErroAltoPositivo,DerroBaixonegativo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroBaixoPositivo = new FuzzyRuleAntecedent();
    IfErroAltoPositivoAndDerroBaixoPositivo->joinWithAND(ErroAltoPositivo,DerroBaixoPositivo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroMedioPositivo = new FuzzyRuleAntecedent();
    IfErroAltoPositivoAndDerroMedioPositivo->joinWithAND(ErroAltoPositivo,DerroMedioPositivo);

    FuzzyRuleAntecedent* IfErroAltoPositivoAndDerroAltoPositivo = new FuzzyRuleAntecedent(); 
    IfErroAltoPositivoAndDerroAltoPositivo->joinWithAND(ErroAltoPositivo,DerroAltoPositivo);










    FuzzyRuleConsequent* ThenOutAltoPositivo = new FuzzyRuleConsequent(); 
    ThenOutAltoPositivo->addOutput(OutAltoPositivo);

    FuzzyRuleConsequent* ThenOutMedioPositivo = new FuzzyRuleConsequent();
    ThenOutMedioPositivo->addOutput(OutMedioPositivo);

    FuzzyRuleConsequent* ThenOutBaixoPositivo = new FuzzyRuleConsequent();
    ThenOutBaixoPositivo->addOutput(OutBaixoPositivo);

    FuzzyRuleConsequent* ThenOutBaixonegativo = new FuzzyRuleConsequent();
    ThenOutBaixonegativo->addOutput(OutBaixonegativo);

    FuzzyRuleConsequent* ThenOutMedioNegativo = new FuzzyRuleConsequent();
    ThenOutMedioNegativo->addOutput(OutMedioNegativo);

    FuzzyRuleConsequent* ThenOutAltoNegativo = new FuzzyRuleConsequent();
    ThenOutAltoNegativo->addOutput(OutAltoNegativo);








    FuzzyRule* fuzzyRule01 = new FuzzyRule(1, IfErroAltoNegativoAndDerroAltoNegativo, ThenOutAltoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule01);

    FuzzyRule* fuzzyRule02 = new FuzzyRule(2, IfErroAltoNegativoAndDerroMedioNegativo, ThenOutAltoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule02);

    FuzzyRule* fuzzyRule03 = new FuzzyRule(3, IfErroAltoNegativoAndDerroBaixonegativo, ThenOutAltoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule03);

    FuzzyRule* fuzzyRule04 = new FuzzyRule(4, IfErroAltoNegativoAndDerroBaixoPositivo, ThenOutMedioPositivo);
    fuzzy->addFuzzyRule(fuzzyRule04);

    FuzzyRule* fuzzyRule05 = new FuzzyRule(5, IfErroAltoNegativoAndDerroMedioPositivo, ThenOutMedioPositivo);
    fuzzy->addFuzzyRule(fuzzyRule05);

    FuzzyRule* fuzzyRule06 = new FuzzyRule(6, IfErroAltoNegativoAndDerroAltoPositivo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule06);

    FuzzyRule* fuzzyRule07 = new FuzzyRule(7, IfErroMedioNegativoAndDerroAltoNegativo, ThenOutAltoPositivo); 
    fuzzy->addFuzzyRule(fuzzyRule07);

    FuzzyRule* fuzzyRule08 = new FuzzyRule(8, IfErroMedioNegativoAndDerroMedioNegativo, ThenOutAltoPositivo); //++++
    fuzzy->addFuzzyRule(fuzzyRule08);

    FuzzyRule* fuzzyRule09 = new FuzzyRule(9, IfErroMedioNegativoAndDerroBaixonegativo, ThenOutMedioPositivo); //++++
    fuzzy->addFuzzyRule(fuzzyRule09);

    FuzzyRule* fuzzyRule10 = new FuzzyRule(10, IfErroMedioNegativoAndDerroBaixoPositivo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule10);

    FuzzyRule* fuzzyRule11 = new FuzzyRule(11, IfErroMedioNegativoAndDerroMedioPositivo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule11);

    FuzzyRule* fuzzyRule12 = new FuzzyRule(12, IfErroMedioNegativoAndDerroAltoPositivo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule12);

    FuzzyRule* fuzzyRule13 = new FuzzyRule(13, IfErroBaixonegativoAndDerroAltoNegativo, ThenOutMedioPositivo);
    fuzzy->addFuzzyRule(fuzzyRule13);

    FuzzyRule* fuzzyRule14 = new FuzzyRule(14, IfErroBaixonegativoAndDerroMedioNegativo, ThenOutMedioPositivo); //++++
    fuzzy->addFuzzyRule(fuzzyRule14);

    FuzzyRule* fuzzyRule15 = new FuzzyRule(15, IfErroBaixonegativoAndDerroBaixonegativo, ThenOutBaixoPositivo); //++++
    fuzzy->addFuzzyRule(fuzzyRule15);

    FuzzyRule* fuzzyRule16 = new FuzzyRule(16, IfErroBaixonegativoAndDerroBaixoPositivo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule16);

    FuzzyRule* fuzzyRule17 = new FuzzyRule(17, IfErroBaixonegativoAndDerroMedioPositivo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule17);

    FuzzyRule* fuzzyRule18 = new FuzzyRule(18, IfErroBaixonegativoAndDerroAltoPositivo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule18);

    FuzzyRule* fuzzyRule19 = new FuzzyRule(19, IfErroBaixoPositivoAndDerroAltoNegativo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule19);

    FuzzyRule* fuzzyRule20 = new FuzzyRule(20, IfErroBaixoPositivoAndDerroMedioNegativo, ThenOutBaixoPositivo);
    fuzzy->addFuzzyRule(fuzzyRule20);

    FuzzyRule* fuzzyRule21 = new FuzzyRule(21, IfErroBaixoPositivoAndDerroBaixonegativo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule21);

    FuzzyRule* fuzzyRule22 = new FuzzyRule(22, IfErroBaixoPositivoAndDerroBaixoPositivo, ThenOutBaixonegativo); //----
    fuzzy->addFuzzyRule(fuzzyRule22);

    FuzzyRule* fuzzyRule23 = new FuzzyRule(23, IfErroBaixoPositivoAndDerroMedioPositivo, ThenOutMedioNegativo); //----
    fuzzy->addFuzzyRule(fuzzyRule23);

    FuzzyRule* fuzzyRule24 = new FuzzyRule(24, IfErroBaixoPositivoAndDerroAltoPositivo, ThenOutMedioNegativo);
    fuzzy->addFuzzyRule(fuzzyRule24);

    FuzzyRule* fuzzyRule25 = new FuzzyRule(25, IfErroMedioPositivoAndDerroAltoNegativo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule25);

    FuzzyRule* fuzzyRule26 = new FuzzyRule(26, IfErroMedioPositivoAndDerroMedioNegativo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule26);

    FuzzyRule* fuzzyRule27 = new FuzzyRule(27, IfErroMedioPositivoAndDerroBaixonegativo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule27);

    FuzzyRule* fuzzyRule28 = new FuzzyRule(28, IfErroMedioPositivoAndDerroBaixoPositivo, ThenOutMedioNegativo);
    fuzzy->addFuzzyRule(fuzzyRule28);

    FuzzyRule* fuzzyRule29 = new FuzzyRule(29, IfErroMedioPositivoAndDerroMedioPositivo, ThenOutAltoNegativo); //----
    fuzzy->addFuzzyRule(fuzzyRule29);

    FuzzyRule* fuzzyRule30 = new FuzzyRule(30, IfErroMedioPositivoAndDerroAltoPositivo, ThenOutAltoNegativo);  //----
    fuzzy->addFuzzyRule(fuzzyRule30);

    FuzzyRule* fuzzyRule31 = new FuzzyRule(31, IfErroAltoPositivoAndDerroAltoNegativo, ThenOutBaixonegativo);
    fuzzy->addFuzzyRule(fuzzyRule31);

    FuzzyRule* fuzzyRule32 = new FuzzyRule(32, IfErroAltoPositivoAndDerroMedioNegativo, ThenOutMedioNegativo);
    fuzzy->addFuzzyRule(fuzzyRule32);

    FuzzyRule* fuzzyRule33 = new FuzzyRule(33, IfErroAltoPositivoAndDerroBaixonegativo, ThenOutMedioNegativo);
    fuzzy->addFuzzyRule(fuzzyRule33);

    FuzzyRule* fuzzyRule34 = new FuzzyRule(34, IfErroAltoPositivoAndDerroBaixoPositivo, ThenOutAltoNegativo); 
    fuzzy->addFuzzyRule(fuzzyRule34);

    FuzzyRule* fuzzyRule35 = new FuzzyRule(35, IfErroAltoPositivoAndDerroMedioPositivo, ThenOutAltoNegativo); 
    fuzzy->addFuzzyRule(fuzzyRule35);

    FuzzyRule* fuzzyRule36 = new FuzzyRule(36, IfErroAltoPositivoAndDerroAltoPositivo, ThenOutAltoNegativo); 
    fuzzy->addFuzzyRule(fuzzyRule36);

    fuzzy->setInput(1,-10);
    fuzzy->setInput(2,-10);    
    fuzzy->fuzzify();
    
    float outputPitch = fuzzy->defuzzify(1);
    
    std::cout << "Erro: " << ErroAltoNegativo->getPertinence() << ", " << ErroMedioNegativo->getPertinence() << ", " << ErroBaixonegativo->getPertinence() << ", " << ErroBaixoPositivo->getPertinence() << ", " << ErroMedioPositivo->getPertinence() << ", " << ErroAltoPositivo->getPertinence() << std::endl;
    std::cout << "DErro: " << DerroAltoNegativo->getPertinence() << ", " << DerroMedioNegativo->getPertinence() << ", " << DerroBaixonegativo->getPertinence() << ", " << DerroBaixoPositivo->getPertinence() << ", " << DerroMedioPositivo->getPertinence() << ", " << DerroAltoPositivo->getPertinence() << std::endl;
    std::cout << "velocidade: " << OutAltoNegativo->getPertinence() << ", " << OutMedioNegativo->getPertinence() << ", " << OutBaixonegativo->getPertinence() << ", " << OutBaixoPositivo->getPertinence() << ", " << OutMedioPositivo->getPertinence() << ", " << OutAltoPositivo->getPertinence() << std::endl;

    std::cout << "Output: " << outputPitch << std::endl;

    std::cout << "regras 1-15 : " << fuzzy->isFiredRule(1) << ", " << fuzzy->isFiredRule(2) << ", " << fuzzy->isFiredRule(3) << ", " << fuzzy->isFiredRule(4) << ", " << fuzzy->isFiredRule(5) << ", " << fuzzy->isFiredRule(6) << ", " << fuzzy->isFiredRule(7) << ", " << fuzzy->isFiredRule(8) << ", " << fuzzy->isFiredRule(9) << ", " << fuzzy->isFiredRule(10) << ", " << fuzzy->isFiredRule(11) << ", " << fuzzy->isFiredRule(12) << ", " << fuzzy->isFiredRule(13) << ", " << fuzzy->isFiredRule(14) << ", " << fuzzy->isFiredRule(15) << std::endl;
    std::cout << "regras 16-30 : " << fuzzy->isFiredRule(16) << ", " << fuzzy->isFiredRule(17) << ", " << fuzzy->isFiredRule(18) << ", " << fuzzy->isFiredRule(19) << ", " << fuzzy->isFiredRule(20) << ", " << fuzzy->isFiredRule(21) << ", " << fuzzy->isFiredRule(22) << ", " << fuzzy->isFiredRule(23) << ", " << fuzzy->isFiredRule(24) << ", " << fuzzy->isFiredRule(25) << ", " << fuzzy->isFiredRule(26) << ", " << fuzzy->isFiredRule(27) << ", " << fuzzy->isFiredRule(28) << ", " << fuzzy->isFiredRule(29) << ", " << fuzzy->isFiredRule(30) << std::endl;
    std::cout << "regras 31-36 : " << fuzzy->isFiredRule(31) << ", " << fuzzy->isFiredRule(32) << ", " << fuzzy->isFiredRule(33) << ", " << fuzzy->isFiredRule(34) << ", " << fuzzy->isFiredRule(35) << ", " << fuzzy->isFiredRule(36) << std::endl;

	return 0;
}