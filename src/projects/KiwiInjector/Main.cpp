#include <windows.h>
#include <iostream>
#include <string>

std::string RGB2ANSI(int r, int g, int b)
{
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string HEX2ANSI(unsigned int hex)
{
    int r = (hex >> 16) & 0xFF;
    int g = (hex >> 8) & 0xFF;
    int b = hex & 0xFF;

    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

int main(int argc, char* argv[])
{
    std::cout << HEX2ANSI(0x0080ff) << "[i]" << HEX2ANSI(0xffffff) << " KiwiInjector started!" << '\n';

    std::string injection_method = "";
    std::cout << HEX2ANSI(0x0db300) << "[?]" << HEX2ANSI(0xffffff) << " Injection method (Proccess > 1:NAME or 2:PID)\n>>> ";
    std::getline(std::cin, injection_method);
    std::cout << '\n';

    return EXIT_SUCCESS;
}