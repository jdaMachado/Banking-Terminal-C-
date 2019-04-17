#include "conta.h"

int Conta::getIdConta()
{
    return idConta;
}

void Conta::setIdConta(int value)
{
    idConta = value;
}

std::string Conta::getNomeConta()
{
    return nomeConta;
}

void Conta::setNomeConta(std::string value)
{
    nomeConta = value;
}

std::string Conta::getDataAbertura()
{
    return dataAbertura;
}

void Conta::setDataAbertura(std::string value)
{
    dataAbertura = value;
}

float Conta::getSaldo()
{
    return saldo;
}

void Conta::setSaldo(float value)
{
    saldo = value;
}

int Conta::getTipoConta()
{
    return tipoConta;
}

void Conta::setTipoConta(int value)
{
    tipoConta = value;
}

Conta::Conta(int idConta, std::string nomeConta, std::string dataAbertura, float saldo, int tipoConta)
{
   this -> idConta      = idConta;
   this -> nomeConta    = nomeConta;
   this -> dataAbertura = dataAbertura;
   this -> saldo        = saldo;
   this -> tipoConta    = tipoConta;
}
