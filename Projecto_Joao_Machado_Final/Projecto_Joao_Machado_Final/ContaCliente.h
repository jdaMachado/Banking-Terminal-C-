#ifndef CONTACLIENTE_H
#define CONTACLIENTE_H

#include <iostream>

class ContaCliente
{
private:
    int idContaCliente, conta, cliente;


public:
    ContaCliente(int idContaCliente, int conta, int cliente);

    int getIdContaCliente();
    void setIdContaCliente(int value);

    int getConta();
    void setConta(int value);

    int getCliente();
    void setCliente(int value);
};

#endif // CONTACLIENTE_H
