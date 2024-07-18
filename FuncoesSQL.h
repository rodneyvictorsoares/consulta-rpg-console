#pragma once

#include <Windows.h>
#include <WinUser.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma comment(lib,"user32.lib")
#pragma	comment(lib, "kernel32.lib")

using namespace std;

class cFuncoes
{
private:
	SQLHENV SQLEnv;
	SQLHDBC SQLHdbc;
	SQLRETURN Retorno;

	SQLSMALLINT SqlSmallInt;

	//Variáveis para a inserção de dados no banco
	string nome;
	string descricao;
	string estilo;

	int escolha;
	bool option;
	
public:
	void IniciarIdentificador()
	{
		Retorno = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnv);

		if (Retorno == SQL_SUCCESS)
			cout << "SUCESSO AO ALOCAR IDENTIFICADOR\n";
		else
			cout << "ERRO AO ALOCAR O IDENTIFICADOR\n";
	}

	void InserirAtributosDeConexao()
	{
		Retorno = SQLSetEnvAttr(SQLEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

		if (Retorno == SQL_SUCCESS)
			cout << "SUCESSO AO INSERIR ATRIBUTOS DE CONEXAO.\n";
		else
			cout << "ERRO AO INSERIR ATRIBUTOS DE CONEXAO.\n";
	}

	void RelocarIdentificador()
	{
		Retorno = SQLAllocHandle(SQL_HANDLE_DBC, SQLEnv, &SQLHdbc);

		if (Retorno == SQL_SUCCESS)
			cout << "SUCESSO AO RELOCAR IDENTIFICADOR PARA PARAMETROS ODBC.\n";
		else
			cout << "ERRO AO RELOCAR IDENTIFICADOR PARA PARAMETROS ODBC.\n";
	}

	void AlocarConexao()
	{
		Retorno = SQLAllocConnect(SQLEnv, &SQLHdbc);

		if (Retorno == SQL_SUCCESS)
			cout << "CONEXAO A PARAMETROS ODBC FOI REALIZADA COM SUCESSO.\n";
		else
			cout << "ERRO AO REALIZAR A CONEXAO PARA PARAMETROS ODBC.\n";
	}

	void ConectarAoBancoDeDados()
	{
		SQLWCHAR connectionString[] = L"DRIVER={SQL Server};Server=W3-DEV-10\\SQLEXPRESS;Database=school_db;Trusted_Connection=yes;";

		Retorno = SQLDriverConnect(SQLHdbc, GetDesktopWindow(), connectionString, SQL_NTS, 0, 0, (SQLSMALLINT*)SqlSmallInt, SQL_DRIVER_NOPROMPT);

		if (Retorno == SQL_SUCCESS || Retorno == SQL_SUCCESS_WITH_INFO)
			cout << "CONECTADO COM SUCESSO AO BANCO DE DADOS.\n";
		else
			cout << "ERRO AO CONECTAR AO BANCO DE DADOS.\n";
	}

	void InserirCenario(const wstring& nome, const wstring& descricao, const wstring& estilo) {
		SQLWCHAR sqlInsert[] = L"INSERT INTO Cenario (nome, descricao, estilo) VALUES (?, ?, ?)";
		SQLHSTMT hStmt;

		Retorno = SQLAllocHandle(SQL_HANDLE_STMT, SQLHdbc, &hStmt);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao alocar o handle do statement.\n";
			return;
		}

		Retorno = SQLPrepare(hStmt, sqlInsert, SQL_NTS);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao preparar a instrução SQL.\n";
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		Retorno = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 30, 0, (SQLPOINTER)nome.c_str(), 0, NULL);
		Retorno = SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0, (SQLPOINTER)descricao.c_str(), 0, NULL);
		Retorno = SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLPOINTER)estilo.c_str(), 0, NULL);

		Retorno = SQLExecute(hStmt);
		if (Retorno == SQL_SUCCESS || Retorno == SQL_SUCCESS_WITH_INFO) {
			wcout << L"Registro inserido com sucesso.\n";
		}
		else {
			wcout << L"Erro ao inserir o registro.\n";
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	void CapturarEInserirCenario() {
		wstring nome, descricao, estilo;

		wcout << L" \n";
		getline(wcin, nome);
		wcout.clear();
		wcout.flush();
		wcin.clear();
		wcin.sync();

		wcout << L"Digite o nome do cenario: ";
		getline(wcin, nome);

		wcout << L"Digite a descricao do cenario: ";
		getline(wcin, descricao);

		wcout << L"Digite o estilo do cenario: ";
		getline(wcin, estilo);

		InserirCenario(nome, descricao, estilo);
	}

	void ConsultarCenariosPorID()
	{
		SQLWCHAR sqlQuery[] = L"SELECT id, nome, descricao, estilo FROM Cenario WHERE id = ?";
		SQLHSTMT hStmt;
		SQLINTEGER id;
		SQLWCHAR nome[31], descricao[256], estilo[21];
		int Id;
		
		wcout << L"Informe o ID do cenario a ser consultado: ";
		wcin >> Id;

		Retorno = SQLAllocHandle(SQL_HANDLE_STMT, SQLHdbc, &hStmt);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao alocar o handle do statement.\n";
			return;
		}

		Retorno = SQLPrepare(hStmt, sqlQuery, SQL_NTS);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao preparar a instrução SQL.\n";
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}
		
		Retorno = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &Id, 0, NULL);

		Retorno = SQLExecute(hStmt);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao executar a consulta SQL.\n";
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		if (SQLFetch(hStmt) == SQL_SUCCESS) {
			SQLGetData(hStmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);
			SQLGetData(hStmt, 2, SQL_C_WCHAR, nome, sizeof(nome), NULL);
			SQLGetData(hStmt, 3, SQL_C_WCHAR, descricao, sizeof(descricao), NULL);
			SQLGetData(hStmt, 4, SQL_C_WCHAR, estilo, sizeof(estilo), NULL);

			wcout << L"ID: " << id << L"\n";
			wcout << L"Nome: " << nome << L"\n";
			wcout << L"Descricao: " << descricao << L"\n";
			wcout << L"Estilo: " << estilo << L"\n";
		}
		else {
			wcout << L"Nenhum registro encontrado com o ID: " << id << L".\n";
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	void ConsultarCenarios() {
		SQLWCHAR sqlQuery[] = L"SELECT id, nome, descricao, estilo FROM Cenario";
		SQLHSTMT hStmt;
		SQLINTEGER id;
		SQLWCHAR nome[31], descricao[256], estilo[21];

		Retorno = SQLAllocHandle(SQL_HANDLE_STMT, SQLHdbc, &hStmt);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao alocar o handle do statement.\n";
			return;
		}

		Retorno = SQLExecDirect(hStmt, sqlQuery, SQL_NTS);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			wcout << L"Erro ao executar a consulta SQL.\n";
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			SQLGetData(hStmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);
			SQLGetData(hStmt, 2, SQL_C_WCHAR, nome, sizeof(nome), NULL);
			SQLGetData(hStmt, 3, SQL_C_WCHAR, descricao, sizeof(descricao), NULL);
			SQLGetData(hStmt, 4, SQL_C_WCHAR, estilo, sizeof(estilo), NULL);

			//wcout << L"ID: " << id << L", Nome: " << nome << L", Descricao: " << descricao << L", Estilo: " << estilo << L"\n";
			wcout << L"ID: " << id << L"\n";
			wcout << L"Nome: " << nome << L"\n";
			wcout << L"Descricao: " << descricao << L"\n";
			wcout << L"Estilo: " << estilo << L"\n";
			wcout << L" \n";
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	void DeletarCenario()
	{
		SQLWCHAR sqlQuery[] = L"DELETE FROM Cenario WHERE id = ?";
		SQLHSTMT hStmt;
		int id;
		
		wcout << L"Informe o ID do cenario a ser removido: ";
		wcin >> id;

		Retorno = SQLAllocHandle(SQL_HANDLE_STMT, SQLHdbc, &hStmt);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			std::wcout << L"Erro ao alocar o handle do statement.\n";
			return;
		}

		Retorno = SQLPrepare(hStmt, sqlQuery, SQL_NTS);
		if (Retorno != SQL_SUCCESS && Retorno != SQL_SUCCESS_WITH_INFO) {
			std::wcout << L"Erro ao preparar a instrução SQL.\n";
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		Retorno = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, NULL);

		Retorno = SQLExecute(hStmt);
		if (Retorno == SQL_SUCCESS || Retorno == SQL_SUCCESS_WITH_INFO) {
			std::wcout << L"Registro deletado com sucesso.\n";
		}
		else {
			std::wcout << L"Erro ao deletar o registro.\n";
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	void menuConsole()
	{
		escolha = 0;
		option = true;

		do
		{
			system("cls");
			system("color 2");

			wcout << L"MENU PRINCIPAL\n";
			wcout << L" \n";
			wcout << L"1 - CADASTRAR NOVO CENARIO\n";
			wcout << L"2 - CONSULTAR CENARIO POR ID\n";
			wcout << L"3 - VISUALIZAR LISTA DE CENARIOS\n";
			wcout << L"4 - REMOVER CENARIO\n";
			wcout << L"5 - SAIR...\n";
			wcout << L" \n";
			wcout << L"Digite a sua escolha e tecle ENTER para continuar: ";
			cin >> escolha;
			optionsMenu(escolha);

		} while (option);
	}

	void optionsMenu(int optionMenu)
	{
		switch (optionMenu)
		{
		case 1:
			system("cls");
			system("color 6");
			CapturarEInserirCenario();
			wcout << " \n";
			system("pause");
			break;
		case 2:
			system("cls");
			system("color 6");
			ConsultarCenariosPorID();
			wcout << " \n";
			system("pause");
			break;
		case 3:
			system("cls");
			system("color 6");
			ConsultarCenarios();
			wcout << " \n";
			system("pause");
			break;
		case 4:
			system("cls");
			system("color 6");
			DeletarCenario();
			wcout << " \n";
			system("pause");
			break;
		case 5:
			system("cls");
			system("color 3");
			cout << "ENCERRANDO O APLICATIVO...\n";
			option = false;
			Sleep(1500);
			break;
		}
	}
}SQL;

