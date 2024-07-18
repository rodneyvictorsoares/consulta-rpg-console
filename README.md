
# Dungeons & Dragons: Console de Consulta de Cenários

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![SQL Server](https://img.shields.io/badge/SQL%20Server-CC2927?style=flat&logo=microsoft-sql-server&logoColor=white)

## Visão Geral

Bem-vindo ao projeto **Dungeons & Dragons: Console de Consulta de Cenários**. Este projeto é um aplicativo de console escrito em C++ que se conecta a um banco de dados SQL Server para gerenciar cenários de Dungeons & Dragons. O aplicativo permite inserir, consultar, visualizar e deletar cenários de uma base de dados. A seguir, você encontrará instruções detalhadas sobre como configurar e executar este projeto.

## Estrutura do Projeto

O projeto é composto por dois arquivos principais:

- `main.cpp`: Contém a função `main` e a lógica de inicialização do console e da conexão com o banco de dados.
- `FuncoesSQL.h`: Define a classe `cFuncoes` com métodos para gerenciar a conexão com o banco de dados e executar operações SQL.

### main.cpp

```cpp
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
}
```

### FuncoesSQL.h

```cpp
#pragma once

#include <Windows.h>
#include <WinUser.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma comment(lib,"user32.lib")
#pragma comment(lib, "kernel32.lib")

using namespace std;

class cFuncoes
{
private:
    SQLHENV SQLEnv;
    SQLHDBC SQLHdbc;
    SQLRETURN Retorno;

    SQLSMALLINT SqlSmallInt;

    string nome;
    string descricao;
    string estilo;

    int escolha;
    bool option;
    
public:
    void IniciarIdentificador();
    void InserirAtributosDeConexao();
    void RelocarIdentificador();
    void AlocarConexao();
    void ConectarAoBancoDeDados();
    void InserirCenario(const wstring& nome, const wstring& descricao, const wstring& estilo);
    void CapturarEInserirCenario();
    void ConsultarCenariosPorID();
    void ConsultarCenarios();
    void DeletarCenario();
    void menuConsole();
    void optionsMenu(int optionMenu);
} SQL;
```

## Funcionalidades

O projeto possui as seguintes funcionalidades:

1. **Cadastrar Novo Cenário**: Permite inserir um novo cenário no banco de dados.
2. **Consultar Cenário por ID**: Permite consultar um cenário específico pelo seu ID.
3. **Visualizar Lista de Cenários**: Exibe todos os cenários cadastrados no banco de dados.
4. **Remover Cenário**: Permite deletar um cenário específico do banco de dados.
5. **Sair**: Encerra o aplicativo.

## Requisitos

Para executar este projeto, você precisará dos seguintes requisitos:

- Visual Studio (ou qualquer outro IDE C++ compatível)
- SQL Server
- Driver ODBC para SQL Server

## Configuração do Ambiente

1. **Instalar o SQL Server**: Certifique-se de que o SQL Server está instalado e configurado corretamente.
2. **Configurar a Conexão ODBC**:
    - Abra o Painel de Controle.
    - Vá para Ferramentas Administrativas > Fontes de Dados (ODBC).
    - Configure uma nova fonte de dados com o driver ODBC para SQL Server.
3. **Configurar o Banco de Dados**:
    - Crie um banco de dados chamado `school_db`.
    - Crie uma tabela chamada `Cenario` com os seguintes campos:
        - `id` (int, Primary Key, Identity)
        - `nome` (nvarchar(30))
        - `descricao` (nvarchar(255))
        - `estilo` (nvarchar(20))

## Como Executar

1. **Clone o Repositório**:

    ```bash
    git clone https://github.com/rodneyvictorsoares/consulta-rpg-console.git
    cd consulta-rpg-console
    ```

2. **Abrir o Projeto no Visual Studio**:
    - Abra o Visual Studio.
    - Vá para `Arquivo > Abrir > Projeto/Solução` e selecione o arquivo `.sln` do projeto.

3. **Compilar e Executar**:
    - Pressione `Ctrl + F5` para compilar e executar o projeto.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests para melhorias e correções.

## 📄 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 👥 Contribuidores

- Rodney Victor (https://github.com/rodneyvictorsoares) - Desenvolvedor

## 📞 Contato

Para dúvidas ou sugestões, entre em contato através do email: ordabelem@hotmail.com

---
