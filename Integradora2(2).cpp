#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

struct Bitacora {
    string mes;
    int dia;
    string hora;
    string ipOrigen;
    int puerto;
    string razonFalla;
};


void leerArchivo(const string& bitacora, vector<Bitacora>& bitacora1) {
    ifstream archivo(bitacora);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    map<string, int> meses = { {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12} };

    string mes, hora, ip, razonFalla;
    int dia, puerto;

    while (archivo >> mes >> dia >> hora >> ip >> puerto >> razonFalla) {
        Bitacora b;
        b.mes = meses[mes];
        b.dia = dia;
        b.hora = hora;
        b.ipOrigen = ip + ":" + to_string(puerto);
        b.razonFalla = razonFalla;

        bitacora1.push_back(b);
    }

    archivo.close();
}


int partition(vector<Bitacora>& bitacora, int low, int high) {
    string pivot = bitacora[high].ipOrigen;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (bitacora[j].ipOrigen < pivot) {
            i++;
            swap(bitacora[i], bitacora[j]);
        }
    }
    swap(bitacora[i + 1], bitacora[high]);
    return (i + 1);
}

void quickSort(vector<Bitacora>& bitacora, int low, int high) {
    if (low < high) {
        int pi = partition(bitacora, low, high);
        quickSort(bitacora, low, pi - 1);
        quickSort(bitacora, pi + 1, high);
    }
}

int main() {
    vector<Bitacora> bitacora1;
    leerArchivo("bitacora.txt", bitacora1);
    quickSort(bitacora1, 0, bitacora1.size() - 1);

    string ipInicio, ipFin;
    cout << "Introduzca la dirección IP de inicio: ";
    cin >> ipInicio;
    cout << "Introduzca la dirección IP de fin: ";
    cin >> ipFin;

    // punto 4
    cout << "Registros correspondientes a las IPs entre " << ipInicio << " y " << ipFin << ":" << endl;
    for (const Bitacora& registro : bitacora1) {
        if (registro.ipOrigen >= ipInicio && registro.ipOrigen <= ipFin) {
            cout << registro.mes << " " << registro.dia << " " << registro.hora << " " << registro.ipOrigen << " " << registro.puerto << " " << registro.razonFalla << endl;
        }
    }

    // punto 5
    ofstream archivoOrdenado("bitacora_ordenada.txt");
    if (!archivoOrdenado) {
        cerr << "No se pudo abrir el archivo para escribir el resultado del ordenamiento." << endl;
        return 1; // Indicar error
    }

    for (const Bitacora& registro : bitacora1) {
        archivoOrdenado << registro.mes << " " << registro.dia << " " << registro.hora << " " << registro.ipOrigen << " " << registro.puerto << " " << registro.razonFalla << endl;
    }

    archivoOrdenado.close();

    return 0;
}
