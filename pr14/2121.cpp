#include <iostream>

int main() {
    try {
        int dividend, divisor, quotient;

        std::cout << "Enter dividend: ";
        std::cin >> dividend;

        std::cout << "Enter divisor: ";
        std::cin >> divisor;

        if (divisor == 0) {
            throw "Division by zero is not allowed.";
        }

        quotient = dividend / divisor;

        std::cout << "Quotient: " << quotient << std::endl;
    }
    catch (const char* errorMessage) {
        std::cout << "Error: " << errorMessage << std::endl;
    }

    return 0;
}