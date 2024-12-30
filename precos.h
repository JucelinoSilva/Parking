// precos.h
#ifndef PRECOS_H
#define PRECOS_H

double calcularPreco(int minutos) {
    if (minutos <= 30) {
        return 5.00;
    } else if (minutos <= 120) {
        return 20.00;
    } else {
        return 20.00 + ((minutos - 120) / 60.0) * 2.00;
    }
}

#endif // PRECOS_H