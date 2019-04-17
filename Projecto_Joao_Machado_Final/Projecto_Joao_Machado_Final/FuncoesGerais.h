#ifndef FUNCOESGERAIS_H
#define FUNCOESGERAIS_H
#include <mysql.h>
#include <iostream>
#include <chrono>


MYSQL_RES* Perform_Query(MYSQL* connection, const char* query);
void gotoxy( int column, int line );
std::string dataActual();

#endif // FUNCOESGERAIS_H
