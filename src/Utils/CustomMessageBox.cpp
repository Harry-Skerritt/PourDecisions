#include "CustomMessageBox.h"
#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <Cocoa/Cocoa.h>
#elif __linux__
#include <cstdlib>
#endif

// Constructor
CustomMessageBox::CustomMessageBox(const std::string& title, const std::string& message, int numButtons)
    : title_(title), message_(message), numButtons_(numButtons) {}

// Show the message box and return the button clicked
MessageBoxButton CustomMessageBox::showMessageBox() {
#ifdef _WIN32
    // Windows Message Box
    int result = MessageBoxA(NULL, message_.c_str(), title_.c_str(), MB_OKCANCEL | MB_ICONINFORMATION);
    if (result == IDOK) {
        return MessageBoxButton::Ok;
    }
    else {
        return MessageBoxButton::Cancel;
    }
#elif __APPLE__
    // macOS Message Box using Cocoa (Objective-C)
    @autoreleasepool {
        NSApplication* app = [NSApplication sharedApplication];
        NSAlert* alert = [[NSAlert alloc]init];
        [alert setMessageText : [NSString stringWithUTF8String : title_.c_str()] ] ;
        [alert setInformativeText : [NSString stringWithUTF8String : message_.c_str()] ] ;

        if (numButtons_ == 1) {
            [alert addButtonWithTitle : @"OK"] ;
        }
        else if (numButtons_ == 2) {
            [alert addButtonWithTitle : @"OK"] ;
            [alert addButtonWithTitle : @"Cancel"] ;
        }
        else if (numButtons_ == 3) {
            [alert addButtonWithTitle : @"Yes"] ;
            [alert addButtonWithTitle : @"No"] ;
        }

        int result = [alert runModal];

        if (result == NSAlertFirstButtonReturn) {
            return MessageBoxButton::Ok;
        }
        else if (result == NSAlertSecondButtonReturn) {
            if (numButtons_ == 2) {
                return MessageBoxButton::Cancel;
            }
            else {
                return MessageBoxButton::Yes;
            }
        }
        else {
            return MessageBoxButton::No;
        }
    }
#elif __linux__
    // Linux Message Box using zenity
    std::string command = "zenity --info --text=\"" + message_ + "\" --title=\"" + title_ + "\"";
    if (numButtons_ == 2) {
        command = "zenity --question --text=\"" + message_ + "\" --title=\"" + title_ + "\"";
    }
    else if (numButtons_ == 3) {
        command = "zenity --question --text=\"" + message_ + "\" --title=\"" + title_ + "\"";
    }

    int result = system(command.c_str());
    if (result == 0) {
        return MessageBoxButton::Ok;  // OK/Yes
    }
    else {
        return MessageBoxButton::Cancel;  // Cancel/No
    }
#endif
}
