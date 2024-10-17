#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>


using namespace std;
#define TMAX 10


typedef struct 
{
    int matricula;
    string data;
    bool devolucao;
}Emprestimo;


typedef struct 
{
    string titulo, autor, isbn;
    int qtdExemplares, qtdDiponivle;

}Livro;

int menuInicial (); //Tela Inicial
int pesquisarLivroRec(Livro livros[], int qtdLivro, string); // pesquisar um livro em recursivo e trazer a posição
void lerLivros (Livro[], int &); // Incluir novo livro
bool validarSBN(string);
void maiusc(string &); // Tranformar em maiusculo
bool ehNumero(string);//Validação de número 
bool ehLetra (string); // Conferir se é letra
void exibirLivros (); // Mostrar na tela os livros // Não fiz ainda
void realizarEmprestimo(Livro livros[], int qtdLivro);
void ordenarLivrosRec(Livro livros[], int n);
void exibirLivros(Livro livros[], int qtdLivros);
void realizarDevolucao(Livro livros[], int qtdLivro);
bool isbnJaCadastrado(Livro livros[], int qtdLivros, const string &isbn);
void exibirRelatorioEmprestimosAtivos(Livro livros[], int qtdLivro); // exibir relatorio de emprestimos ativos

int main() {
   
    Livro livros [TMAX];
    string titulo;
    int pesquisa;
    int qtdLivro = 0; 
    do{
        int resp = menuInicial();
        switch (resp){

            case 1:
                  exibirLivros(livros, qtdLivro);
                  break;

            case 2:
                realizarEmprestimo(livros,qtdLivro);
                break;
            case 3:
                lerLivros(livros, qtdLivro);
                break; 

            case 4:
                realizarDevolucao(livros, qtdLivro);
                break;  

            case 5:
                exibirRelatorioEmprestimosAtivos(livros, qtdLivro);
                break;

            case 6: 
                cout<<"Digite o nome do livro: "<<endl;
                getline(cin,titulo);
                maiusc(titulo);
                pesquisa = pesquisarLivroRec(livros, qtdLivro, titulo);
                if (pesquisa>-1){
                    cout << "-----------------------------------" << endl;
                    cout << "Título: " << livros[pesquisa].titulo << endl;
                    cout << "Autor: " << livros[pesquisa].autor << endl;
                    cout << "ISBN: " << livros[pesquisa].isbn << endl;
                    cout << "Quantidade de Exemplares: " << livros[pesquisa].qtdExemplares << endl;
                    cout << "Quantidade Disponível: " << livros[pesquisa].qtdDiponivle << endl;
                    cout << "-----------------------------------" << endl;
                }else
                    cout<<"Titulo não encontrado"<<endl;    
        
        
        }

        
        
    }while (true);
    
    
    return 0;
}


//Menu inicial
int menuInicial (){

    string n;
    int num;
    bool ehnum; 
    do{
        cout<<"1 - Biblioteca"<<endl;
        cout<<"2 - Emprestimo"<<endl;
        cout<<"3 - Incluir um novo livro"<<endl;
        cout<<"4 - Devolução"<<endl;
        cout << "5 - Relatório de empréstimos ativos"<<endl;
        getline (cin, n);
        ehNumero(n);
        if (ehNumero(n))
            ehnum = true;            
        else{    
            system("cls");
            cout << "Numero invalido. Digite novamente." << endl;
        }    
    }while (not ehnum);
    num = atoi(n.c_str());
    return num;
}

int pesquisarLivroRec(Livro livros[], int qtdLivro, string titulo) { 
    
    if (qtdLivro == 1) {
        if (titulo == livros[0].titulo) {
            return 0; 
        } else {
            return -1; 
        }
    } 

    
    if (livros[qtdLivro - 1].titulo == titulo) {
        return qtdLivro - 1;
    } 
    
   
    return pesquisarLivroRec(livros, qtdLivro - 1, titulo);
}
void lerLivros(Livro livros[],int& qtdLivro){
    string titulo, autor, isbn, exemplares;
    int jatem = -1;
    bool entradavalida = false;
        
        do{
            cout<<"Digite o nome/Titulo do livro: "<<endl;
            getline(cin, titulo);
            maiusc(titulo);
            entradavalida = ehLetra(titulo); 
            if (entradavalida){ 
                if (qtdLivro>0){
                    jatem = pesquisarLivroRec(livros, qtdLivro, titulo); 
                    if (jatem>-1){
                        cout<<"Livro já foi cadastrado."<<endl;
                    }
                    
                }           
            }
        }while (jatem>-1 or entradavalida == false);
        livros[qtdLivro].titulo = titulo;
        entradavalida = false;
        do{
            cout << "Digite o autor do livro: "<<endl;  
            getline(cin, autor);
            maiusc(autor);
            if (ehLetra (autor))
                entradavalida = true;
            else{
                system("cls");
                cout<<"Entrada invalida. Digite novamente"<<endl;
                cin.ignore();                
            }
        }while (entradavalida == false); 
        livros[qtdLivro].autor = autor;        
        entradavalida = false;
        do {
        cout << "Digite o ISBN do livro: ";
        getline(cin, isbn);
        if (validarSBN(isbn)) {
            if (isbnJaCadastrado(livros, qtdLivro, isbn)) {
                cout << "ISBN já cadastrado. Digite um ISBN diferente." << endl;
            } else {
                entradavalida = true;
                livros[qtdLivro].isbn = isbn;
                cout << "correto" << endl;
            }
        } else {
            cout << "Entrada invalida. Digite novamente" << endl;
        }
        }while (entradavalida==false);        
        entradavalida = false;
        do {
            cout << "Digite a quantidade de exemplares: ";
            getline(cin, exemplares);
            if(ehNumero (exemplares)){
                livros[qtdLivro].qtdExemplares = atoi(exemplares.c_str());
                livros[qtdLivro].qtdDiponivle = livros[qtdLivro].qtdExemplares;
                entradavalida = true;
            }else{
                system("cls");
                cout<<"Entrada invalida. Digite novamente"<<endl;
            }                 
        }while (entradavalida == false); 
        
        cout<<"LIVRO CADASTRADO."<<endl;
        qtdLivro++; //soma +1 depois que cadastrar um livro | Variavel está por referencia

        ordenarLivrosRec(livros, qtdLivro);
}

bool validarSBN(string sbn) { 
    if (sbn.size() != 17) {
        cout<<"ERRO 1"<<endl;
        return false;
    }

    // Verifica se a posição 4 é um hífen
    if (sbn[3] != '-'){ 
        return false;
        cout<<"ERRO 2"<<endl;
    }
    // Verifica se o dígito verificador na posição 15 é um dígito
    if (not isdigit(sbn[16])) {
          cout<<"ERRO 3"<<endl;
        return false;

    }

    // Verifica o Prefixo (3 dígitos)
    for (int i = 0; i < 3; i++) {
        if (not isdigit(sbn[i])) {
              cout<<"ERRO 4"<<endl;
            return false;
        }
    }

    // Verifica o Grupo (até 5 dígitos)
    int j = 4; // começa da posição 4
    while (j < 9 and sbn[j] != '-') {
        if (not isdigit(sbn[j])) {
            cout<<"ERRO 5"<<endl;
            return false;
        }
        j++;
    }

    // Se encontrar o '-', avança para a próxima posição
    if (sbn[j] == '-') {
        j++;
    } else {
          cout<<"ERRO 6"<<endl;
        return false; 
    }

    // Verifica o Registrante (até 7 dígitos)
    while (j < 15 and sbn[j] != '-') {
        if (not isdigit(sbn[j])) {
              cout<<"ERRO 7"<<endl;
            return false;
        }
        j++;
    }

    // Se encontrar o '-', avança para a próxima posição
    if (sbn[j] == '-') {
        j++;
    } else {
          cout<<"ERRO 8"<<endl;
        return false; 
    }

    // Verifica o Elemento (até 6 dígitos)
    while (j < 15 and sbn[j] != '-') {
        if (not isdigit(sbn[j])) {
              cout<<"ERRO 9"<<endl;
            return false;
        }
        j++;
    }

    // Verifica se há um hífen antes do dígito verificador
    if (j < 15 and sbn[j] != '-') {
          cout<<"ERRO 10"<<endl;
        return false;
    }

    return true; 
}


void maiusc(string &frase) {
    for (int i = 0; i < frase.size(); i++) {
        frase[i] = toupper(frase[i]);
    }
}


//Validação de número 
bool ehNumero(string numero) {
    if (numero[0] == '-' or not isdigit(numero[0])) 
        return false;
    for (int i = 1; i< numero.size(); i++)
        if (not isdigit(numero[i])) 
            return false;
        
    return true;
}

// Conferir se é letra
bool ehLetra(string letra) {
    if (letra[0] == ' ') {
        cout << "Entrada inválida" << endl;
        return false;
    }
    for (int i = 0; i < letra.size(); i++) {
        if (not (isalpha(letra[i])) and (letra[i] != ' ') or (i > 0 and isspace(letra[i]) and isspace(letra[i - 1]))) {
            cout << "Entrada inválida" << endl;
            return false;
        }
    }     
    return true;
}

// Função para realizar o empréstimo
void realizarEmprestimo(Livro livros[], int qtdLivro) {
    if (qtdLivro == 0) {
        cout << "Nenhum livro cadastrado." << endl;
        return;
    }
    
    string titulo;
    cout << "Digite o titulo do livro que deseja emprestar: ";
    getline(cin, titulo);
    maiusc(titulo);
    
    int pos = pesquisarLivroRec(livros, qtdLivro, titulo);
    if (pos == -1) {
        cout << "Título inexistente." << endl;
    } else if (livros[pos].qtdDiponivle > 0) {
        livros[pos].qtdDiponivle--;
        cout << "Empréstimo realizado – código " << pos << endl;
    } else {
        cout << "Exemplar indisponível para empréstimo." << endl;
    }
}


    // Função da ordenação recursiva
void ordenarLivrosRec(Livro livros[], int n) {
    if (n == 1) {
        return;
    }

    int menor = 0;
    for (int i = 1; i < n; i++) {
        if (livros[i].titulo < livros[menor].titulo) {
            menor = i;
        }
    }

    if (menor != 0) {
        Livro aux = livros[0];
        livros[0] = livros[menor];
        livros[menor] = aux;
    }


    ordenarLivrosRec(livros + 1, n - 1);
}
//relatório 1
void exibirLivros(Livro livros[], int qtdLivros) {
    if (qtdLivros == 0) {
        cout << "Nenhum livro cadastrado no acervo." << endl;
        return;
    }

    cout << "Livros no Acervo:" << endl;
    for (int i = 0; i < qtdLivros; i++) {
        cout << "-----------------------------------" << endl;
        cout << "Título: " << livros[i].titulo << endl;
        cout << "Autor: " << livros[i].autor << endl;
        cout << "ISBN: " << livros[i].isbn << endl;
        cout << "Quantidade de Exemplares: " << livros[i].qtdExemplares << endl;
        cout << "Quantidade Disponível: " << livros[i].qtdDiponivle << endl;
    }
    cout << "-----------------------------------" << endl;
}

void realizarDevolucao(Livro livros[], int qtdLivro) {
    if (qtdLivro == 0) {
        cout << "Nenhum livro cadastrado." << endl;
        return;
    }
    
    string titulo;
    cout << "Digite o título do livro que deseja devolver: ";
    getline(cin, titulo);
    maiusc(titulo);
    
    int pos = pesquisarLivroRec(livros, qtdLivro, titulo);
    if (pos == -1) {
        cout << "Título inexistente." << endl;
    } else {
        livros[pos].qtdDiponivle++; 
        cout << "Devolução realizada – código " << pos << endl;
    }
}

bool isbnJaCadastrado(Livro livros[], int qtdLivros, const string &isbn) {
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].isbn == isbn) {
            return true; // ISBN já cadastrado
        }
    }
    return false; // ISBN não cadastrado
}

// Função para exibir relatório de empréstimos ativos
void exibirRelatorioEmprestimosAtivos(Livro livros[], int qtdLivro) {
    if (qtdLivro == 0) {
        cout << "Nenhum livro cadastrado." << endl;
        return;
    }

    cout << "Relatório de Empréstimos Ativos:" << endl;
    for (int i = 0; i < qtdLivro; i++) {
        int emprestimosAtivos = livros[i].qtdExemplares - livros[i].qtdDiponivle;

        cout << "-----------------------------------" << endl;
        cout << "Título: " << livros[i].titulo << endl;
        cout << "ISBN: " << livros[i].isbn << endl;
        cout << "Empréstimos Ativos: " << emprestimosAtivos << endl;
    }
}