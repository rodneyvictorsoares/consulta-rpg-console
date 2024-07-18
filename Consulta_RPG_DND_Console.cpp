// Consulta_RPG_DND_Console.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "FuncoesSQL.h"

int main()
{
    SetConsoleTitle(TEXT("CONECTANDO AO BANCO DE DADOS"));
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

	system("color 3");

    SQL.IniciarIdentificador();
    Sleep(1500);
    SQL.InserirAtributosDeConexao();
    Sleep(1500);
    SQL.RelocarIdentificador();
    Sleep(1500);
    SQL.AlocarConexao();
    Sleep(1500);
    SQL.ConectarAoBancoDeDados();
    Sleep(1000);

    SetConsoleTitle(TEXT("DUNGEONS & DRAGONS: CONSOLE DE CONSULTA DE CENARIOS"));
    SQL.menuConsole();

    /*system("color 4");
	Sleep(1000);
    SQL.CapturarEInserirCenario();

    system("color 6");
    Sleep(1500);
    SQL.ConsultarCenarios();*/

    //getchar();
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

