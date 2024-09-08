#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int lerquantidade() {
    int n;

    do {
        cout << "Digite a quantidade de cidades (Min 4 - Max 20): " << endl;
        cin >> n;
        if (n < 4 or n > 20) {
            cout << "Quantidade fora do intervalo." << endl;
            cin.ignore();
        }
    } while (n < 4 or n> 20);

    return n;
}

int main() {
    int qtdcidades = lerquantidade();
    cout << qtdcidades << endl;

    return 0;
}