/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * Fuzzy.cpp
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "Fuzzy.h"

// CONSTRUTORES
Fuzzy::Fuzzy(){
    // Iniciando os ponteiros como nulo
    // FuzzyInput
    this->fuzzyInputs       = NULL;
    this->fuzzyInputsCursor = NULL;
    // FuzzyOutput
    this->fuzzyOutputs          = NULL;
    this->fuzzyOutputsCursor    = NULL;
    // FuzzyRule
    this->fuzzyRules        = NULL;
    this->fuzzyRulesCursor  = NULL;
}

// DESTRUTOR
Fuzzy::~Fuzzy(){
    this->cleanFuzzyInputs(this->fuzzyInputs);
    this->cleanFuzzyOutputs(this->fuzzyOutputs);
    this->cleanFuzzyRules(this->fuzzyRules);
}

// MÉTODOS PÚBLICOS
bool Fuzzy::addFuzzyInput(FuzzyInput* fuzzyInput){
    fuzzyInputArray* aux;
    
    // Alocando espaço na memória
    if((aux = (fuzzyInputArray *) malloc(sizeof(fuzzyInputArray))) == NULL){
        return false;
    }

    aux->fuzzyInput = fuzzyInput;
    aux->next = NULL;

    if(this->fuzzyInputs == NULL){
        this->fuzzyInputs = aux;
        this->fuzzyInputsCursor  = aux;
    }else{
        this->fuzzyInputsCursor->next = aux;
        this->fuzzyInputsCursor = aux;
    }

    return true;
}

bool Fuzzy::addFuzzyOutput(FuzzyOutput* fuzzyOutput){
    fuzzyOutputArray *aux;
    // Alocando espaço na memória
    if((aux = (fuzzyOutputArray *) malloc(sizeof(fuzzyOutputArray))) == NULL){
        return false;
    }
    aux->fuzzyOutput = fuzzyOutput;
    aux->next = NULL;

    // Ordenando o fuzzyOutput
    fuzzyOutput->order();

    if(this->fuzzyOutputs == NULL){
        this->fuzzyOutputs = aux;
        this->fuzzyOutputsCursor  = aux;
    }else{
        this->fuzzyOutputsCursor->next = aux;
        this->fuzzyOutputsCursor = aux;
    }
    return true;
}

bool Fuzzy::addFuzzyRule(FuzzyRule* fuzzyRule){
    fuzzyRuleArray* aux;
    // Alocando espaço na memória
    if((aux = (fuzzyRuleArray *) malloc(sizeof(fuzzyRuleArray))) == NULL){
        return false;
    }
    aux->fuzzyRule = fuzzyRule;
    aux->next = NULL;

    if(this->fuzzyRules == NULL){
        this->fuzzyRules = aux;
        this->fuzzyRulesCursor  = aux;
    }else{
        this->fuzzyRulesCursor->next = aux;
        this->fuzzyRulesCursor = aux;
    }
    return true;
}

bool Fuzzy::setInput(int fuzzyInputIndex, float crispValue){
    fuzzyInputArray *aux;
    aux = this->fuzzyInputs;

    while(aux != NULL){
        if(aux->fuzzyInput->getIndex() == fuzzyInputIndex){
            aux->fuzzyInput->setCrispInput(crispValue);
            return true;
        }
        aux = aux->next;
    }
    return false;
}

bool Fuzzy::fuzzify(){
    fuzzyInputArray* fuzzyInputAux;

    fuzzyOutputArray *fuzzyOutputAux;

    fuzzyInputAux = this->fuzzyInputs;
    while(fuzzyInputAux != NULL){
        fuzzyInputAux->fuzzyInput->resetFuzzySets();
        fuzzyInputAux = fuzzyInputAux->next;
    }

    fuzzyOutputAux = this->fuzzyOutputs;
    while(fuzzyOutputAux != NULL){
        fuzzyOutputAux->fuzzyOutput->resetFuzzySets();
        fuzzyOutputAux = fuzzyOutputAux->next;
    }

    // Calculando a pertinência de todos os FuzzyInputs
    fuzzyInputAux = this->fuzzyInputs;
    while(fuzzyInputAux != NULL){
        fuzzyInputAux->fuzzyInput->calculateFuzzySetPertinences();
        fuzzyInputAux = fuzzyInputAux->next;
    }

    // Avaliando quais regras foram disparadas
    fuzzyRuleArray* fuzzyRuleAux;
    fuzzyRuleAux = this->fuzzyRules;
    // Calculando as pertinências de totos os FuzzyInputs
    while(fuzzyRuleAux != NULL){
        fuzzyRuleAux->fuzzyRule->evaluateExpression();
        fuzzyRuleAux = fuzzyRuleAux->next;
    }

    // Truncado os conjuntos de saída
    fuzzyOutputAux = this->fuzzyOutputs;
    while(fuzzyOutputAux != NULL){
        fuzzyOutputAux->fuzzyOutput->truncate();
        fuzzyOutputAux = fuzzyOutputAux->next;
    }

    return true;
}

bool Fuzzy::isFiredRule(int fuzzyRuleIndex){
    fuzzyRuleArray *aux;
    aux = this->fuzzyRules;
    while(aux != NULL){
        if(aux->fuzzyRule->getIndex() == fuzzyRuleIndex){
            return aux->fuzzyRule->isFired();
        }
        aux = aux->next;
    }
    return false;
}

float Fuzzy::defuzzify(int fuzzyOutputIndex){
    fuzzyOutputArray *aux;
    aux = this->fuzzyOutputs;
    while(aux != NULL){
        if(aux->fuzzyOutput->getIndex() == fuzzyOutputIndex){
            return aux->fuzzyOutput->getCrispOutput();
        }
        aux = aux->next;
    }
    return 0;
}

// MÉTODOS PRIVADOS
void Fuzzy::cleanFuzzyInputs(fuzzyInputArray* aux){
    if(aux != NULL){
        // Esvaziando a memória alocada
        this->cleanFuzzyInputs(aux->next);
        free(aux);
    }
}

void Fuzzy::cleanFuzzyOutputs(fuzzyOutputArray* aux){
    if(aux != NULL){
        // Esvaziando a memória alocada
        this->cleanFuzzyOutputs(aux->next);
        free(aux);
    }
}

void Fuzzy::cleanFuzzyRules(fuzzyRuleArray* aux){
    if(aux != NULL){
        // Esvaziando a memória alocada
        this->cleanFuzzyRules(aux->next);
        free(aux);
    }
}