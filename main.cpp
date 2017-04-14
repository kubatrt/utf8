#include <iostream>
#include <locale>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
    locale newloc(locale(), new gel::stdx::utf8cvt<true>);
    
    string file = "test.txt";
   
    if(argc > 1) {
        file = string(argv[1]);
    } 
    cout << "Load file: " << file << endl;

    locale loc;
    cout << "Local locale: " << loc.name() << endl;
 
    wstring strpol = L"To jest przykład polskiej czcionki. Aąńóćźż.";
    wcout << strpol << endl;
    
    // use utf8 converter
    const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

    locale::global(utf8_locale);
    cout << "New locale: " << utf8_locale.name() << endl;
    
    try
    {
        wstring text;
        wifstream wif(file.c_str());
        wif.imbue(utf8_locale); // apply locale to file stream

        if(wif.is_open())
        {
            wstringstream wss;
            wss << wif.rdbuf();
            text = wss.str();
        }
        else 
        {
            throw("Failed to open file.");
        }
        wcout << text << endl;
    }
    catch(const exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Everything else..." << endl;
    }

    return 0;
}
