#ifndef TIPOCONTA_H
#define TIPOCONTA_H

#include <iostream>


class TipoConta
{
private:

    int idTipoConta;
    std::string nomeTipoConta;
    float anuidade;

public:

    TipoConta(int idTipoConta, std::string nomeTipoConta, float anuidade);

    int getIdTipoConta();
    void setIdTipoConta(int value);

    std::string getNomeTipoConta();
    void setNomeTipoConta(std::string value);

    float getAnuidade();
    void setAnuidade(float value);


};

#endif // TIPOCONTA_H
