#ifndef CONTA_H
#define CONTA_H

#include <iostream>

class Conta
{
private:

    int         idConta, tipoConta;
    std::string nomeConta, dataAbertura;
    float       saldo;


public:
    Conta(int idConta, std::string nomeConta, std::string dataAbertura, float saldo, int tipoConta);

    int getIdConta();
    void setIdConta(int value);

    std::string getNomeConta();
    void setNomeConta(std::string value);

    std::string getDataAbertura();
    void setDataAbertura(std::string value);

    float getSaldo();
    void setSaldo(float value);

    int getTipoConta();
    void setTipoConta(int value);
};

#endif // CONTA_H
