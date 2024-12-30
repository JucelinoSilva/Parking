// estacionamento.cpp
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include "precos.h"

using namespace std;

struct Estacionamento {
    string placa;
    string horarioEntrada;
};

map<string, Estacionamento> carros;

bool validarPlaca(const string& placa) {
    return placa.size() == 8 && isalpha(placa[0]) && isalpha(placa[1]) && isalpha(placa[2]) && placa[3] == '-' && isdigit(placa[4]) && isalpha(placa[5]) && isdigit(placa[6]) && isdigit(placa[7]);
}

bool validarHorario(const string& horario) {
    if (horario.size() != 5 || horario[2] != ':') return false;
    int horas = stoi(horario.substr(0, 2));
    int minutos = stoi(horario.substr(3, 2));
    return horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60;
}

int calcularMinutos(const string& horarioEntrada, const string& horarioSaida) {
    int horasEntrada = stoi(horarioEntrada.substr(0, 2));
    int minutosEntrada = stoi(horarioEntrada.substr(3, 2));
    int horasSaida = stoi(horarioSaida.substr(0, 2));
    int minutosSaida = stoi(horarioSaida.substr(3, 2));

    return (horasSaida * 60 + minutosSaida) - (horasEntrada * 60 + minutosEntrada);
}

void entrada() {
    string placa, horario;
    cout << "Digite a placa do carro (formato XXX-9X99): ";
    cin >> placa;

    if (!validarPlaca(placa)) {
        cout << "Placa invalida!" << endl;
        return;
    }

    cout << "Digite o horario de entrada (formato HH:MM): ";
    cin >> horario;

    if (!validarHorario(horario)) {
        cout << "Horario invalido!" << endl;
        return;
    }

    if (carros.find(placa) != carros.end()) {
        cout << "Carro ja registrado!" << endl;
        return;
    }

    carros[placa] = {placa, horario};
    cout << "Carro registrado com sucesso!" << endl;
}

void saida() {
    string placa, horario;
    cout << "Digite a placa do carro: ";
    cin >> placa;

    if (carros.find(placa) == carros.end()) {
        cout << "Carro nao encontrado!" << endl;
        return;
    }

    cout << "Digite o horario de saida (formato HH:MM): ";
    cin >> horario;

    if (!validarHorario(horario)) {
        cout << "Horario invalido!" << endl;
        return;
    }

    int minutosEstadia = calcularMinutos(carros[placa].horarioEntrada, horario);
    double valor = calcularPreco(minutosEstadia);

    cout << "Tempo de estadia: " << minutosEstadia << " minutos." << endl;
    cout << fixed << setprecision(2) << "Valor a ser pago: R$ " << valor << endl;

    carros.erase(placa);
}

int main() {
    int opcao;
    do {
        cout << "\nMenu:\n1 - Entrada\n2 - Saida\n3 - Sair do Sistema\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                entrada();
                break;
            case 2:
                saida();
                break;
            case 3:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 3);

    return 0;
}
