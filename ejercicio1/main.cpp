#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "Error en la apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "Error en la lectura del archivo: " << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}

int main() {
    cout << "Bienvenido a la carga de scripts en Tiny-Lisp" << endl;

    while (true) {
        cout << "1. Cargar script desde archivo\n"
                "2. Salir\n"
                "Seleccione una opción: ";

        int option;
        cin >> option;

        switch (option) {
            case 1:
                load_script();
                break;
            case 2:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor, seleccione nuevamente." << endl;
                break;
        }
    }

    return 0;
}

