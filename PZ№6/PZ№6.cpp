#include <iostream>
#include <Windows.h>

typedef int64_t(*SafeAdd)(int64_t, int64_t);
typedef int64_t(*SafeSubtract)(int64_t, int64_t);
typedef int64_t(*SafeMultiply)(int64_t, int64_t);
typedef int64_t(*SafeDivide)(int64_t, int64_t);

int main() {
    HMODULE hModule = LoadLibrary(TEXT("Dll1.dll")); 
    if (!hModule) {
        std::cerr << "Unable to load DLL!\n";
        return 1;
    }

    SafeAdd safe_add = (SafeAdd)GetProcAddress(hModule, "safe_add");
    SafeSubtract safe_subtract = (SafeSubtract)GetProcAddress(hModule, "safe_subtract");
    SafeMultiply safe_multiply = (SafeMultiply)GetProcAddress(hModule, "safe_multiply");
    SafeDivide safe_divide = (SafeDivide)GetProcAddress(hModule, "safe_divide");

    if (!safe_add || !safe_subtract || !safe_multiply || !safe_divide) {
        std::cerr << "Function not found!\n";
        FreeLibrary(hModule);
        return 1;
    }

    try {
        std::cout << "Adding 1 and 2 gives " << safe_add(1, 2) << std::endl;
        std::cout << "Subtracting 5 from 10 gives " << safe_subtract(10, 5) << std::endl;
        std::cout << "Multiplying 2 and 3 gives " << safe_multiply(2, 3) << std::endl;
        std::cout << "Dividing 10 by 2 gives " << safe_divide(10, 2) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    FreeLibrary(hModule);
    return 0;
}
