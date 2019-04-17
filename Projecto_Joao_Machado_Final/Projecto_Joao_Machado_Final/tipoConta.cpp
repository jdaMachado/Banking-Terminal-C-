#include "tipoConta.h"

TipoConta::TipoConta(int idTipoConta, std::string nomeTipoConta, float anuidade)
{
    this -> idTipoConta     = idTipoConta;
    this -> nomeTipoConta   = nomeTipoConta;
    this -> anuidade        = anuidade;
}

int TipoConta::getIdTipoConta()
{
    return idTipoConta;
}

void TipoConta::setIdTipoConta(int value)
{
    idTipoConta = value;
}

std::string TipoConta::getNomeTipoConta()
{
    return nomeTipoConta;
}

void TipoConta::setNomeTipoConta(std::string value)
{
    nomeTipoConta = value;
}

float TipoConta::getAnuidade()
{
    return anuidade;
}
void TipoConta::setAnuidade(float value)
{
    anuidade = value;
}

