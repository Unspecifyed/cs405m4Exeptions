// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>

// Custom exception class derived from std::exception
class CustomException : public std::exception {
public:
    // Override the what() method to provide a custom message
    const char* what() const noexcept override {
        return "Custom Exception occurred!";
    }
};

bool do_even_more_custom_application_logic()
{
    // Throw any standard exception
    // Here, we're throwing a runtime_error, which is a standard exception
    throw std::runtime_error("Standard exception occurred in do_even_more_custom_application_logic");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        // Wrap the call to do_even_more_custom_application_logic() with an exception handler
        // that catches std::exception, displays a message and the exception.what(), then continues processing
        if(do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    } catch (const std::exception& e) {
        // Catch any std::exception and display the message and exception details
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception
    // This will be explicitly caught in main
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using a standard C++ defined exception
    if (den == 0) {
        throw std::overflow_error("Divide by zero exception");
    }
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    try {
        // Create an exception handler to capture ONLY the exception thrown by divide
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    } catch (const std::overflow_error& e) {
        // Catch the specific overflow_error exception and display the message
        std::cerr << "Exception caught in do_division: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        // Wrap the whole main function with exception handlers that catch (in this order):
        // your custom exception, std::exception, and any uncaught exceptions
        do_division();
        do_custom_application_logic();
    } catch (const CustomException& e) {
        // Catch the custom exception and display the message
        std::cerr << "CustomException caught in main: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Catch any std::exception and display the message
        std::cerr << "std::exception caught in main: " << e.what() << std::endl;
    } catch (...) {
        // Catch all other unhandled exceptions and display a message
        std::cerr << "Unhandled exception caught in main" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
