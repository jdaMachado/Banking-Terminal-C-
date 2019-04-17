#include "ContaCliente.h"

ContaCliente::ContaCliente(int idContaCliente, int conta, int cliente)
{
    this -> idContaCliente = idContaCliente;
    this -> conta = conta;
    this -> cliente = cliente;
}


int ContaCliente::getIdContaCliente(){return idContaCliente;}
void ContaCliente::setIdContaCliente(int value){idContaCliente = value;}

int ContaCliente::getConta(){return conta;}
void ContaCliente::setConta(int value){conta = value;}

int ContaCliente::getCliente(){return cliente;}
void ContaCliente::setCliente(int value){cliente = value;}
