#include "cliente.h"

Cliente::Cliente(int idCliente, std::string nomeCliente, std::string dataNascimento, std::string nif,
                std::string numIdCivil, std::string contatoTelefonico, std::string email, std::string morada,
                int codigoPostal, std::string localidade)
{
    this -> idCliente = idCliente;
    this -> nomeCliente = nomeCliente;
    this -> dataNascimento = dataNascimento;
    this -> nif = nif;
    this -> numIdCivil = numIdCivil;
    this -> contatoTelefonico = contatoTelefonico;
    this -> email = email;
    this -> morada = morada;
    this -> codigoPostal = codigoPostal;
    this -> localidade = localidade;
}

int Cliente::getIdCliente(){return idCliente;}
void Cliente::setIdCliente(int value){idCliente = value;}

std::string Cliente::getNomeCliente(){return nomeCliente;}
void Cliente::setNomeCliente(std::string value){nomeCliente = value;}

std::string Cliente::getDataNascimento(){return dataNascimento;}
void Cliente::setDataNascimento(std::string value){dataNascimento = value;}

std::string Cliente::getNif(){return nif;}
void Cliente::setNif(std::string value){nif = value;}

std::string Cliente::getNumIdCivil(){return numIdCivil;}
void Cliente::setNumIdCivil(std::string value){numIdCivil = value;}

std::string Cliente::getContatoTelefonico(){return contatoTelefonico;}
void Cliente::setContatoTelefonico(std::string value){contatoTelefonico = value;}

std::string Cliente::getEmail(){return email;}
void Cliente::setEmail(std::string value){email = value;}

std::string Cliente::getMorada(){return morada;}
void Cliente::setMorada(std::string value){morada = value;}

int Cliente::getCodigoPostal(){return codigoPostal;}
void Cliente::setCodigoPostal(int value){codigoPostal = value;}

std::string Cliente::getLocalidade(){return localidade;}
void Cliente::setLocalidade(std::string value){localidade = value;}


