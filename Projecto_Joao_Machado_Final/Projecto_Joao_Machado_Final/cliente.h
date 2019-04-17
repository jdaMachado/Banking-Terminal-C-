#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

class Cliente
{
private:

    int          idCliente, codigoPostal;

    std::string  nomeCliente, dataNascimento, nif, numIdCivil, contatoTelefonico,
                 email, morada, localidade;

public:
        Cliente(int idCliente, std::string nomeCliente, std::string dataNascimento, std::string nif,
                std::string numIdCivil, std::string contatoTelefonico, std::string email, std::string morada,
                int codigoPostal, std::string localidade);

        int getIdCliente();
        void setIdCliente(int value);

        std::string getNomeCliente();
        void setNomeCliente(std::string value);

        std::string getDataNascimento();
        void setDataNascimento(std::string value);

        std::string getNif();
        void setNif(std::string value);

        std::string getNumIdCivil();
        void setNumIdCivil(std::string value);

        std::string getContatoTelefonico();
        void setContatoTelefonico(std::string value);

        std::string getEmail();
        void setEmail(std::string value);

        std::string getMorada();
        void setMorada(std::string value);

        int getCodigoPostal();
        void setCodigoPostal(int value);

        std::string getLocalidade();
        void setLocalidade(std::string value);



};

#endif // CLIENTE_H
