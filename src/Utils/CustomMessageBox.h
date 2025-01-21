#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <string>

// Enum for the button choices
enum class MessageBoxButton {
    Ok = 0,
    Cancel,
    Yes,
    No
};

// Class to display a message box
class CustomMessageBox {
public:
    // Constructor
    CustomMessageBox(const std::string& title, const std::string& message, int numButtons);

    // Show the message box and return the button clicked
    MessageBoxButton showMessageBox();

private:
    std::string title_;
    std::string message_;
    int numButtons_;
};

#endif // CUSTOMMESSAGEBOX_H
