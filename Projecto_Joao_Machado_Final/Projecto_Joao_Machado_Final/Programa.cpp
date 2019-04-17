#include <iostream>
#include "todasclasses.h"
#include <windows.h>
#include <vector>
#include <conio.h>
#include <chrono>
#include <mysql.h>
#include <sstream>
#include <iomanip>
#include <fstream>


using namespace std;

vector <Conta>          listaContas;
vector <TipoConta>      listaTiposConta;
vector <Cliente>        listaClientes;
vector <ContaCliente>   listaContaCliente;
vector <int> contas;
vector <int> clientes;

MYSQL *conn;
MYSQL_ROW row;
MYSQL_RES *res;

//const int     KEY_UP       = 72;
//const int     KEY_DOWN     = 80;
const int     KEY_LEFT = 75;
const int     KEY_RIGHT = 77;
const char    ENTER = '\r';
const int     ESC = 27;
const int     UM = 149;
const int     DOIS = 250;

const string  mainServer = "127.0.0.1";
const string  mainDbUser = "root";
const string  mainDbPass = "root";


int         detectar = 0;
int         posicaoTecla = 0;

ofstream  escrita;


// Funcoes Gerais
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

const string dataActual()
{
	time_t     now = time(0);
	struct tm  newDate;
	char       buf[80];
	localtime_s(&newDate, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &newDate);

	return buf;

}



const string horaActual()
{
	time_t     now = time(0);
	struct tm  newTime;
	char       buf[80];
	localtime_s(&newTime, &now);
	strftime(buf, sizeof(buf), "%X", &newTime);

	return buf;
}

//Fim das funcoes gerais
/*******************************************************************/

/*******************************************************************

template <typename T>
ostream &operator<<(ofstream& out, string msg){

stringstream ss;

//ss << dataActual() << "_" << horaActual() << "_" << msg;
string ajuda = "";

ajuda += dataActual();
msg = ss.str();

out << ajuda << endl;

return out;
}

/********************************************************************/




/**
Abre o ficheiro e escreve a mensagem contextual com registo de horas

@param mensagem        - mensagem a escrever no ficheiro

*/
void escreverNoFicheiro(string mensagem)
{
	escrita.open("registo_log.txt", ios_base::out | ios_base::app);
	if (escrita.is_open()) {
		//escrita << mensagem;
		escrita << dataActual() << ":::" << horaActual() << ":::" << mensagem << endl;
	}
	escrita.close();
}








/**
Pesquisa de contas relacionadas com o ID de cliente e passagem para um vector dinamico.

@param idCliente        - numero de cliente

*/
void procurarContasCliente_idCliente(int idCliente)
{

	size_t tamanhoListaContaCliente = listaContaCliente.size();

	for (int i = 0; i < tamanhoListaContaCliente; i++)
	{
		if (listaContaCliente[i].getCliente() == idCliente)
		{
			contas.push_back(listaContaCliente[i].getConta());
		}

	}
}





/**
Pesquisa de clientes relacionadas com o ID de conta e passagem para um vector dinamico.

@param idConta        - numero de conta

*/
void procurarContasCliente_idConta(int idConta)
{

	size_t tamanhoListaContaCliente = listaContaCliente.size();

	for (int i = 0; i < tamanhoListaContaCliente; i++)
	{
		if (listaContaCliente[i].getConta() == idConta)
		{
			clientes.push_back(listaContaCliente[i].getCliente());
		}

	}
}






/**
Pesquisa de elementos pelo ID da conta no array global das contas
e no array global dos tipos de conta, com passagem de dados para um
novo array.

@param id        - numero de identifica�ao da conta
@param dados[]   - array para receber os dados da conta

*/
void procurarDadosConta(int id, string dados[])
{
	stringstream ss;
	bool dadosEncontrados = false;

	size_t tamanhoListaContas = listaContas.size();
	size_t tamamnhoListaTiposConta = listaTiposConta.size();

	for (int i = 0; i < tamanhoListaContas; i++)
	{
		if (listaContas[i].getIdConta() == id)
		{
			dados[0] = listaContas[i].getNomeConta();                                       //dados[0]  <-  Nome da Conta
			dados[1] = listaContas[i].getDataAbertura();                                    //dados[1]  <-  Data de Abertura
			ss << fixed << setprecision(2) << listaContas[i].getSaldo();
			dados[2] = ss.str();                                                            //dados[2]  <-  Saldo
			ss.str("");

			for (int j = 0; j < tamamnhoListaTiposConta; j++)
			{
				if (listaContas[i].getTipoConta() == listaTiposConta[j].getIdTipoConta())
				{
					dados[3] = listaTiposConta[j].getNomeTipoConta();                       //dados[3]  <-  Tipo de Conta
					ss << fixed << setprecision(2) << listaTiposConta[j].getAnuidade();
					dados[4] = ss.str();                                                    //dados[4]  <-  Anuidade dependente do seu tipo
					break;
				}
			}
			dadosEncontrados = true;
			break;
		}

	}
	if (!dadosEncontrados)
		dados[0] = "Inexistente";
}






/**
Pesquisa de elementos pelo no. do cliente no array global dos clientes
com passagem de dados para um novo array.

@param id        - numero de cliente
@param dados[]   - array para receber os dados do cliente

*/
void procurarDadosCliente(int id, string dados[])
{
	bool dadosEncontrados = false;

	size_t tamanhoListaClientes = listaClientes.size();

	for (int i = 0; i < tamanhoListaClientes; i++)
	{
		if (listaClientes[i].getIdCliente() == id)
		{
			dados[0] = listaClientes[i].getNomeCliente();                   //dados[0]  <-  Nome do Cliente
			dados[1] = listaClientes[i].getDataNascimento();
			dados[2] = listaClientes[i].getNif();
			dados[3] = listaClientes[i].getNumIdCivil();
			dados[4] = listaClientes[i].getContatoTelefonico();
			dados[5] = listaClientes[i].getEmail();
			dados[6] = listaClientes[i].getMorada();
			dados[7] = to_string(listaClientes[i].getCodigoPostal());
			dados[8] = listaClientes[i].getLocalidade();

			dadosEncontrados = true;
			break;
		}

	}
	if (!dadosEncontrados)
		dados[0] = "Inexistente";
}








/**
Pesquisa do indice da conta no array das contas atraves do ID

@param id - numero de identificacao da conta

*/
int procurarDadosContaIndex(int id)
{
	size_t n = listaContas.size();
	for (int i = 0; i < n; i++)
	{
		if (listaContas[i].getIdConta() == id)
		{
			return i;
		}

	}
	return -1;
}








/**
Pesquisa do indice do cliente no array dos clientes atraves do ID

@param id - numero de identificacao do cliente

*/
int procurarDadosClienteIndex(int id)
{
	size_t n = listaClientes.size();
	for (int i = 0; i < n; i++)
	{
		if (listaClientes[i].getIdCliente() == id)
		{
			return i;
		}
	}

	return -1;
}





/**
Elimina dados da lista ContaCliente com base no id de Cliente

@param id - numero de identificacao do cliente

*/
void eliminaDadosContaClienteIndex_idCliente(int id)
{
	size_t n = listaContaCliente.size();
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	stringstream ss;
	string queryInserir = "";
	const char* q;

	for (int i = 0; i < n; i++)
	{
		if (listaContaCliente[i].getCliente() == id)
		{
			ss.clear();
			ss << "delete from conta_cliente where cliente = " << id << ";";
			queryInserir = ss.str();
			q = queryInserir.c_str();
			mysql_query(conn, q);
			listaContaCliente.erase(listaContaCliente.begin() + i);
		}
	}

}







/**
Elimina dados da lista ContaCliente com base no id de Conta

@param id - numero de identificacao da Conta

*/
void eliminaDadosContaClienteIndex_idConta(int id)
{
	size_t n = listaContaCliente.size();
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	stringstream ss;
	string queryInserir = "";
	const char* q;

	for (int i = 0; i < n; i++)
	{
		if (listaContaCliente[i].getConta() == id)
		{
			ss.clear();
			ss << "delete from conta_cliente where conta = " << id << ";";
			queryInserir = ss.str();
			q = queryInserir.c_str();
			mysql_query(conn, q);
			listaContaCliente.erase(listaContaCliente.begin() + i);
		}
	}

}









/**
Inicializa o array dos tipos de conta a partir da base de dados

*/
void inicializaListaTiposConta()
{
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	mysql_query(conn, "select * from tipoconta");
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)))
	{
		listaTiposConta.push_back(TipoConta(atoi(row[0]), row[1], (float)atof(row[2])));
	}
	mysql_free_result(res);
}








/**
Inicializa o array das contas a partir da base de dados

*/
void inicializaListaContas()
{
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	mysql_query(conn, "select * from conta");
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)))
	{
		listaContas.push_back(Conta(atoi(row[0]), row[1], row[2], (float)atof(row[3]), atoi(row[4])));
	}
	mysql_free_result(res);
}








/**
Inicializa o array dos clientes a partir da base de dados

*/
void inicializaListaClientes()
{
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	mysql_query(conn, "select * from cliente");
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)))
	{
		listaClientes.push_back(Cliente(atoi(row[0]), row[1], row[2], row[3], row[4], row[5], row[6], row[7], atoi(row[8]), row[9]));
	}
	mysql_free_result(res);
}








/**
Inicializa o array do relacionamento conta <-> cliente a partir da base de dados

*/
void inicializaListaContaCliente()
{
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
	mysql_query(conn, "select * from conta_cliente");
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)))
	{
		listaContaCliente.push_back(ContaCliente(atoi(row[0]), atoi(row[1]), atoi(row[2])));
	}
	mysql_free_result(res);
	mysql_close(conn);

}






/**
Menu de associacao entre a conta <-> cliente

*/
void associarContaCliente(int id)
{

	int idConta;
	system("cls");
	stringstream ss;
	string mensagem = " ###############################################################################\n"
		" #                               Espaco Cliente                                #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Criar Cliente         [CONSULTAR CLIENTE]           Terminar Cliente   #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(10, 9);
	cout << "Associar o cliente numero " << id << " a conta com o NIB: ";
	cin >> idConta;

	if (procurarDadosContaIndex(idConta) == -1) {
		gotoxy(10, 11);
		cout << "Conta com o ID " << idConta << " nao existe!";
		gotoxy(0, 29);
		do {
			detectar = _getch();

		} while (detectar != ESC);

		return;
	}

	ss << "insert into conta_cliente(conta,cliente) values ("
		<< idConta << "," << id << ");";


	string queryInserir = ss.str();
	const char* q = queryInserir.c_str();

	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);

	mysql_query(conn, q);

	mysql_query(conn, "select max(id) from cliente;");

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	int idContaCliente = atoi(row[0]);
	listaContaCliente.push_back(ContaCliente(idContaCliente, idConta, id));


	if (conn)
	{
		gotoxy(0, 25);
		cout << " #       Conta associada com sucesso!";
		gotoxy(0, 29);
	}

	do
	{
		detectar = _getch();
	} while (detectar != ESC);

	mysql_free_result(res);
	mysql_close(conn);
}



void clientesDaConta(int id);


/**
Menu da consulta de conta no array das contas atraves do ID para exibicao a partir do menu do cliente

*/
void consultarContaDoCliente(int id)
{
	system("cls");

	string dados[5];

	string mensagem = " ###############################################################################\n"
		" #                                Espaco Conta                                 #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Abrir Conta            [CONSULTAR CONTA]               Fechar Conta    #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Identificacao Bancaria:                                      #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(42, 10);
	cout << id;

	procurarDadosConta(id, dados);

	gotoxy(0, 12);
	cout << " #      Nome da Conta: " << dados[0];
	gotoxy(0, 14);
	cout << " #      Data de Abertura: " << dados[1];
	gotoxy(0, 16);
	cout << " #      Saldo: " << dados[2];
	gotoxy(0, 18);
	cout << " #      Tipo de Conta: " << dados[3];
	gotoxy(0, 20);
	cout << " #      Anuidade: " << dados[4];

	gotoxy(0, 26);
	cout << " #      <--   Clientes           {wip}  Transaccoes                            #\n";
	gotoxy(0, 29);

	do
	{
		detectar = _getch();

	} while (detectar != ESC && detectar != KEY_LEFT);

	if (detectar == KEY_LEFT) {

		clientesDaConta(id);
	}
}



void contasDoCliente(int id);



/**
Menu da consulta de cliente no array dos clientes atraves do ID

*/
void consultarClienteDaConta(int id)
{

	system("cls");

	string dados[9];

	string mensagem = " ###############################################################################\n"
		" #                               Espaco Cliente                                #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Criar Cliente         [CONSULTAR CLIENTE]           Terminar Cliente   #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Cliente :                                                    #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(28, 10);
	cout << id;

	procurarDadosCliente(id, dados);

	escreverNoFicheiro("Clientes consultado com o id " + to_string(id) );

	gotoxy(0, 12);
	cout << " #      Nome do Cliente: " << dados[0];
	gotoxy(0, 13);
	cout << " #      Data de Nascimento: " << dados[1];
	gotoxy(0, 14);
	cout << " #      Numero de Identificacao Fiscal: " << dados[2];
	gotoxy(0, 15);
	cout << " #      Numero de Identificacao Civil: " << dados[3];
	gotoxy(0, 16);
	cout << " #      Contacto Telefonico: " << dados[4];
	gotoxy(0, 17);
	cout << " #      Contacto Email: " << dados[5];
	gotoxy(0, 18);
	cout << " #      Morada: " << dados[6];
	gotoxy(0, 19);
	cout << " #      Codigo Postal: " << dados[7];
	gotoxy(0, 20);
	cout << " #      Localidade: " << dados[8];


	gotoxy(0, 26);
	cout << " #       <--- Associar            ---> Contas                                  #\n";
	gotoxy(0, 29);


	do
	{
		detectar = _getch();

	} while (detectar != ESC && detectar != KEY_LEFT && detectar != KEY_RIGHT);

	if (detectar == KEY_LEFT)
		associarContaCliente(id);

	if (detectar == KEY_RIGHT)
		contasDoCliente(id);
}


















/**
Menu de de consulta das contas do cliente com o ID passado nos argumentos

@param idCliente - Numero de Identificacao do Cliente

*/
void contasDoCliente(int idCliente)
{

	system("cls");

	escreverNoFicheiro("Contas do Cliente com o id " + to_string(idCliente) + " consultadas");

	string mensagem = " ###############################################################################\n"
		" #                           Contas do Cliente #                               #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;
	gotoxy(48, 1);
	cout << idCliente;

	procurarContasCliente_idCliente(idCliente);

	for (unsigned int i = 0; i < contas.size(); i++)
	{
		gotoxy(8, 3 + i);
		cout << "NIB da " << i + 1 << "a conta: " << contas[i];
	}

	gotoxy(0, 25);
	cout << " #      ESC - SAIR                     --->  Consultar Conta";
	gotoxy(0, 29);


	do {
		detectar = _getch();
	} while (detectar != ESC && detectar != KEY_RIGHT);

	if (detectar == KEY_RIGHT)
	{
		gotoxy(0, 23);
		cout << " #      NIB da Conta: ";
		cin >> detectar;
		consultarContaDoCliente(detectar);

	}

}






/**
Menu de de consulta das contas do cliente com o ID passado nos argumentos

@param idCliente - Numero de Identificacao do Cliente

*/
void clientesDaConta(int idConta)
{

	system("cls");

	escreverNoFicheiro("Clientes da Conta com o id " + to_string(idConta) + " consultados");

	string mensagem = " ###############################################################################\n"
		" #                           Clientes da Conta #                               #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;
	gotoxy(48, 1);
	cout << idConta;

	procurarContasCliente_idConta(idConta);

	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		gotoxy(8, 3 + i);
		cout << "Numero do " << i + 1 << "o cliente: " << clientes[i];
	}

	gotoxy(0, 25);
	cout << " #      ESC - SAIR                     --->  Consultar Cliente";
	gotoxy(0, 29);


	do {
		detectar = _getch();
	} while (detectar != ESC && detectar != KEY_RIGHT);

	if (detectar == KEY_RIGHT)
	{
		gotoxy(0, 23);
		cout << " #      Numero do Cliente: ";
		cin >> detectar;
		consultarClienteDaConta(detectar);

	}

}






/**
Menu de abertura de contas e insercao dos dados na BD

*/
void abrirConta()
{
	string nomeConta, dataAbertura;
	float saldo;
	int tipoConta;
	stringstream ss;
	bool inscricao = false;


	system("cls");

	cout << " ###############################################################################\n"
		<< " #                                Espaco Conta                                 #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #     [ABRIR CONTA]            Consultar Conta                Fechar Conta    #\n"
		<< " #                                                                             #\n"
		<< " #                               ESC  -  Recuar                                #\n"
		<< " ###############################################################################\n"
		<< " #                                                                             #\n"
		<< " #       Nome da Conta:                                                        #\n"
		<< " #                                                                             #\n"
		<< " #       Saldo de Abertura:                                                    #\n"
		<< " #                                                                             #\n"
		<< " #       Tipo de conta: [ ]                                                    #\n"
		<< " #           |                                                                 #\n"
		<< " #           |                                                                 #\n"
		<< " #           |_____ >  1: Conta Normal                                         #\n"
		<< " #             |                                                               #\n"
		<< " #             |___ >  2: Conta Universitario                                  #\n"
		<< " #               |                                                             #\n"
		<< " #               |_ >  3: Conta Poupanca                                       #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " ###############################################################################\n"
		;

	do
	{
		gotoxy(8, 10);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(24, 10);
		getline(cin >> ws, nomeConta);

		gotoxy(8, 12);
		detectar = _getch();
		if (detectar == ESC)
			return;

		do
		{
			gotoxy(28, 12);
			cin >> saldo;
			//falta validacao
			if (saldo < 0)
			{
				gotoxy(28, 12);
				cout << "                                                   #\n";
			}
		} while (saldo < 0);

		gotoxy(8, 14);
		detectar = _getch();
		if (detectar == ESC)
			return;

		do
		{
			gotoxy(25, 14);
			cin >> tipoConta;
		} while (tipoConta != 1 && tipoConta != 2 && tipoConta != 3);



		dataAbertura = dataActual();

		ss << "insert into conta(nomeConta,dataAbertura,saldo,tipoConta) values ("
			<< "'" << nomeConta << "','" << dataAbertura << "'," << saldo << "," << tipoConta << ");";


		string queryInserir = ss.str();
		const char* q = queryInserir.c_str();

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);

		mysql_query(conn, q);

		mysql_query(conn, "select max(id) from conta;");

		res = mysql_store_result(conn);

		
	    row = mysql_fetch_row(res);
		

		int id = atoi(row[0]);




		listaContas.push_back(Conta(id, nomeConta, dataAbertura, saldo, tipoConta));


		if (conn)
		{
			gotoxy(0, 25);
			cout << " #       Conta aberta com sucesso!";
			gotoxy(0, 26);
			cout << " #       Numero de Identificacao Bancaria: " + to_string(id);
			gotoxy(0, 29);

			escreverNoFicheiro("Conta aberta com o id " + to_string(id));
			inscricao = true;
		}
	} while (!inscricao);

	mysql_free_result(res);
	mysql_close(conn);

	do
	{
		detectar = _getch();
	} while (detectar != ESC);


}






/**
Menu da consulta de conta no array das contas atraves do ID

*/
void consultarConta()
{
	system("cls");

	int id;

	string dados[5];

	string mensagem = " ###############################################################################\n"
		" #                                Espaco Conta                                 #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Abrir Conta            [CONSULTAR CONTA]               Fechar Conta    #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Identificacao Bancaria:                                      #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(42, 10);
	cin >> id;

	procurarDadosConta(id, dados);

	gotoxy(0, 12);
	cout << " #      Nome da Conta: " << dados[0];
	gotoxy(0, 14);
	cout << " #      Data de Abertura: " << dados[1];
	gotoxy(0, 16);
	cout << " #      Saldo: " << dados[2];
	gotoxy(0, 18);
	cout << " #      Tipo de Conta: " << dados[3];
	gotoxy(0, 20);
	cout << " #      Anuidade: " << dados[4];

	gotoxy(0, 26);
	cout << " #      <--   Clientes           {wip}  Transaccoes                            #\n";
	gotoxy(0, 29);

	escreverNoFicheiro("Conta consultada com o id " + to_string(id));
	do
	{
		detectar = _getch();

	} while (detectar != ESC && detectar != KEY_LEFT);

	if (detectar == KEY_LEFT) {

		clientesDaConta(id);
	}

}















/**
Menu do fecho de conta

*/
void fecharConta()
{
	system("cls");

	int id;

	string mensagem = " ###############################################################################\n"
		" #                                Espaco Conta                                 #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Abrir Conta             Consultar Conta               [FECHAR CONTA]   #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Identificacao Bancaria:                                      #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(42, 10);
	cin >> id;

	gotoxy(0, 12);
	cout << " #      Tem a certeza que pretende fechar a conta com o NIB " << id << " ?(S/N)";
	detectar = _getch();

	if (detectar == 115 || detectar == 83)
	{
		stringstream ss;
		ss << "delete from conta where id = " << id << ";";
		string queryInserir = ss.str();
		const char* q = queryInserir.c_str();

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
		if (conn)
		{
			mysql_query(conn, q);

			listaContas.erase(listaContas.begin() + procurarDadosContaIndex(id));

			eliminaDadosContaClienteIndex_idConta(id);


			gotoxy(0, 16);
			cout << " #      Conta fechada com sucesso!\n";
			gotoxy(0, 29);
			escreverNoFicheiro("Conta terminada com o id " + to_string(id));

		}
		else
		{
			gotoxy(0, 16);
			cout << " #      Problema na coneccao\n";
			gotoxy(0, 29);
		}
		do {
			detectar = _getch();
		} while (detectar != ESC);
	}
}








/**
Menu de abertura de contas e insercao dos dados na BD

*/
void criarCliente()
{
	string nomeCliente, dataNascimento, nif, numIdCivil, contatoTelefonico, email, morada, localidade;
	int codigoPostal, id;

	stringstream ss;
	bool inscricao = false;


	system("cls");

	cout << " ###############################################################################\n"
		<< " #                               Espaco Cliente                                #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #     [CRIAR CLIENTE]         Consultar Cliente            Terminar Cliente   #\n"
		<< " #                                                                             #\n"
		<< " #                               ESC  -  Recuar                                #\n"
		<< " ###############################################################################\n"
		<< " #                                                                             #\n"
		<< " #       Nome do Cliente:                                                      #\n"
		<< " #       Data de Nascimento:                                                   #\n"
		<< " #       Numero de Identificacao Fiscal:                                       #\n"
		<< " #       Numero de Identificacao Civil:                                        #\n"
		<< " #       Contacto Telefonico:                                                  #\n"
		<< " #       Email:                                                                #\n"
		<< " #       Morada:                                                               #\n"
		<< " #       Codigo Postal:                                                        #\n"
		<< " #       Localidade:                                                           #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " #                                                                             #\n"
		<< " ###############################################################################\n"
		;

	do
	{
		gotoxy(8, 10);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(26, 10);
		getline(cin >> ws, nomeCliente);

		gotoxy(8, 11);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(29, 11);
		cin >> dataNascimento;

		gotoxy(8, 12);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(41, 12);
		cin >> nif;

		gotoxy(8, 13);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(40, 13);
		cin >> numIdCivil;

		gotoxy(8, 14);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(30, 14);
		cin >> contatoTelefonico;

		gotoxy(8, 15);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(16, 15);
		cin >> email;

		gotoxy(8, 16);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(17, 16);
		getline(cin >> ws, morada);

		gotoxy(8, 17);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(24, 17);
		cin >> codigoPostal;

		gotoxy(8, 18);
		detectar = _getch();
		if (detectar == ESC)
			return;

		gotoxy(21, 18);
		getline(cin >> ws, localidade);


		ss << "insert into cliente(nomeCliente,dataNascimento,nif,numIDCivil,contatoTelefonico,email,morada,codigoPostal,localidade) values ("
			<< "'" << nomeCliente << "','" << dataNascimento << "','" << nif << "','" << numIdCivil << "','" << contatoTelefonico << "','" << email << "','" << morada << "'," << codigoPostal << ",'" << localidade << "');";


		string queryInserir = ss.str();
		const char* q = queryInserir.c_str();

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);

		mysql_query(conn, q);

		mysql_query(conn, "select max(id) from cliente;");

		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		id = atoi(row[0]);


		listaClientes.push_back(Cliente(id, nomeCliente, dataNascimento, nif, numIdCivil, contatoTelefonico, email, morada, codigoPostal, localidade));


		if (conn)
		{
			gotoxy(0, 25);
			cout << " #       Cliente registado com sucesso!";

			escreverNoFicheiro("Cliente criado com o id " + to_string(id));

			gotoxy(0, 26);
			cout << " #       Numero de Cliente: " + to_string(id);
			gotoxy(0, 29);
			inscricao = true;
		}
	} while (!inscricao);

	mysql_free_result(res);
	mysql_close(conn);

	do
	{
		detectar = _getch();
	} while (detectar != ESC);
}







/**
Menu da consulta de cliente no array dos clientes atraves do ID

*/
void consultarCliente()
{

	system("cls");

	int id;

	string dados[9];

	string mensagem = " ###############################################################################\n"
		" #                               Espaco Cliente                                #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Criar Cliente         [CONSULTAR CLIENTE]           Terminar Cliente   #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Cliente :                                                    #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(28, 10);
	cin >> id;

	procurarDadosCliente(id, dados);

	escreverNoFicheiro("Cliente consultado com o id " + to_string(id));

	gotoxy(0, 12);
	cout << " #      Nome do Cliente: " << dados[0];
	gotoxy(0, 13);
	cout << " #      Data de Nascimento: " << dados[1];
	gotoxy(0, 14);
	cout << " #      Numero de Identificacao Fiscal: " << dados[2];
	gotoxy(0, 15);
	cout << " #      Numero de Identificacao Civil: " << dados[3];
	gotoxy(0, 16);
	cout << " #      Contacto Telefonico: " << dados[4];
	gotoxy(0, 17);
	cout << " #      Contacto Email: " << dados[5];
	gotoxy(0, 18);
	cout << " #      Morada: " << dados[6];
	gotoxy(0, 19);
	cout << " #      Codigo Postal: " << dados[7];
	gotoxy(0, 20);
	cout << " #      Localidade: " << dados[8];


	gotoxy(0, 26);
	cout << " #       <--- Associar            ---> Contas                                  #\n";
	gotoxy(0, 29);


	do
	{
		detectar = _getch();

	} while (detectar != ESC && detectar != KEY_LEFT && detectar != KEY_RIGHT);

	if (detectar == KEY_LEFT)
		associarContaCliente(id);

	if (detectar == KEY_RIGHT)
		contasDoCliente(id);
}








/**
Menu do fecho de cliente

*/
void terminarCliente()
{
	system("cls");

	int id;

	string mensagem = " ###############################################################################\n"
		" #                               Espaco Cliente                                #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #      Criar Cliente          Consultar Cliente           [TERMINAR CLIENTE]  #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #      Numero de Cliente:                                                     #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;
	cout << mensagem;

	gotoxy(27, 10);
	cin >> id;

	gotoxy(0, 12);
	cout << " #      Tem a certeza que pretende terminar o cliente com o numero " << id << " ?(S/N)";
	detectar = _getch();

	if (detectar == 115 || detectar == 83)
	{
		stringstream ss;
		ss << "delete from cliente where id = " << id << ";";
		string queryInserir = ss.str();
		const char* q = queryInserir.c_str();

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);
		if (conn)
		{
			mysql_query(conn, q);

			listaClientes.erase(listaClientes.begin() + procurarDadosClienteIndex(id));

			eliminaDadosContaClienteIndex_idCliente(id);
			ss.clear();
			ss << "delete from conta_cliente where cliente = " << id << ";";
			queryInserir = ss.str();
			q = queryInserir.c_str();
			mysql_query(conn, q);

			gotoxy(0, 16);
			cout << " #      Cliente terminado com sucesso!\n";
			gotoxy(0, 29);
			escreverNoFicheiro("Cliente terminado com o id " + to_string(id));
			ss.clear();
			ss << "Cliente com o id " << id << "terminado";
			escreverNoFicheiro(ss.str());

		}
		else
		{
			gotoxy(0, 16);
			cout << " #      Problema na coneccao\n";
			gotoxy(0, 29);
		}
		do {
			detectar = _getch();
		} while (detectar != ESC);
	}
}








/**
Menu inicial do espaco conta

*/
void menuConta()
{
	posicaoTecla = 0;

	system("cls");

	string mensagem = " ###############################################################################\n"
		" #                                Espaco Conta                                 #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #     [Abrir Conta]            Consultar Conta                Fechar Conta    #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;

	escreverNoFicheiro("Menu espaco Conta acedido.");

	cout << mensagem;
	do {
		detectar = _getch();
		if (detectar == KEY_RIGHT && posicaoTecla == 0)
		{
			gotoxy(0, 5);
			cout << " #      Abrir Conta            [Consultar Conta]               Fechar Conta    #\n";
			posicaoTecla = 1;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 0)
		{
			abrirConta();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_LEFT && posicaoTecla == 1)
		{
			gotoxy(0, 5);
			cout << " #     [Abrir Conta]            Consultar Conta                Fechar Conta    #\n";
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 1)
		{
			consultarConta();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_RIGHT && posicaoTecla == 1)
		{
			gotoxy(0, 5);
			cout << " #      Abrir Conta             Consultar Conta               [Fechar Conta]   #\n";
			posicaoTecla = 2;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_LEFT && posicaoTecla == 2)
		{
			gotoxy(0, 5);
			cout << " #      Abrir Conta            [Consultar Conta]               Fechar Conta    #\n";
			posicaoTecla = 1;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 2)
		{
			fecharConta();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == ESC)
		{
			return;
		}

	} while (true);

}








/**
Menu inicial do espaco cliente

*/
void menuCliente()
{
	posicaoTecla = 0;

	system("cls");

	string mensagem = " ###############################################################################\n"
		" #                               Espaco Cliente                                #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #     [Criar Cliente]         Consultar Cliente            Terminar Cliente   #\n"
		" #                                                                             #\n"
		" #                               ESC  -  Recuar                                #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;

	escreverNoFicheiro("Menu espaco Cliente acedido.");

	cout << mensagem;
	do {
		detectar = _getch();
		if (detectar == KEY_RIGHT && posicaoTecla == 0)
		{
			gotoxy(0, 5);
			cout << " #      Criar Cliente         [Consultar Cliente]           Terminar Cliente   #\n";
			posicaoTecla = 1;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 0)
		{
			criarCliente();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_LEFT && posicaoTecla == 1)
		{
			gotoxy(0, 5);
			cout << " #     [Criar Cliente]         Consultar Cliente            Terminar Cliente   #\n";
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 1)
		{
			consultarCliente();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_RIGHT && posicaoTecla == 1)
		{
			gotoxy(0, 5);
			cout << " #      Criar Cliente          Consultar Cliente           [Terminar Cliente]  #\n";
			posicaoTecla = 2;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_LEFT && posicaoTecla == 2)
		{
			gotoxy(0, 5);
			cout << " #      Criar Cliente         [Consultar Cliente]           Terminar Cliente   #\n";
			posicaoTecla = 1;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 2)
		{
			terminarCliente();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == ESC)
		{
			return;
		}

	} while (true);

}








/**
Menu inicial do programa

*/
void menuInicial()
{
	posicaoTecla = 0;

	system("cls");

	string mensagem = " ###############################################################################\n"
		" #                             Terminal Bancario                               #\n"
		" #                                                                             #\n"
		" #                           projecto realizado por:                           #\n"
		" #                        Joao David dos Anjos Machado                         #\n"
		" ###############################################################################\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" #        [Espaco Conta]                                Espaco Cliente         #\n"
		" #                                                                             #\n"
		" #                                 ESC - Sair                                  #\n"
		" #                                                                             #\n"
		" #                                                                             #\n"
		" ###############################################################################\n"
		;

	cout << mensagem;

	do {
		detectar = _getch();
		if (detectar == KEY_RIGHT && posicaoTecla == 0)
		{
			gotoxy(0, 23);
			cout << " #         Espaco Conta                                [Espaco Cliente]        #\n";
			posicaoTecla = 1;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 0)
		{
			menuConta();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}
		else if (detectar == KEY_LEFT && posicaoTecla == 1)
		{
			gotoxy(0, 23);
			cout << " #        [Espaco Conta]                                Espaco Cliente         #\n";
			posicaoTecla--;
			gotoxy(0, 29);
		}
		else if (detectar == ENTER && posicaoTecla == 1)
		{
			menuCliente();
			system("cls");
			cout << mensagem;
			posicaoTecla = 0;
			gotoxy(0, 29);
		}

		else if (detectar == ESC)
		{
			system("cls");
			break;
		}
	} while (true);
}






int main()
{
	setlocale(LC_ALL, "Portuguese");
	system("COLOR 0A");




	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "terminaldb", 0, NULL, 0);

	if (conn) {
		cout << "Conectado\n";
		system("pause");
		mysql_close(conn);
		escreverNoFicheiro("Conecção à base de dados.");
	}
	else {
		cout << "Falha na coneccao\n";
		escreverNoFicheiro("Falha na conecção à base de dados.");
		system("pause");
		mysql_close(conn);
		return 0;
	}


	inicializaListaTiposConta();
	inicializaListaContas();
	inicializaListaClientes();
	inicializaListaContaCliente();

	menuInicial();
	return 0;
}