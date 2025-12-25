#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void countdownTimer(int minutes) {
    int seconds = minutes * 60; // Convert minutes to seconds
    
    while (seconds > 0) {
        // Calculate minutes and seconds remaining
        int mins_remaining = seconds / 60;
        int secs_remaining = seconds % 60;
        
        // Clear the line and print the time
        cout << "\r"; // Return to start of line
        cout << "Time remaining: " 
             << mins_remaining << ":" 
             << (secs_remaining < 10 ? "0" : "") << secs_remaining
             << flush;
        
        // Wait for 1 second
        this_thread::sleep_for(chrono::seconds(1));
        
        // Decrement the counter
        seconds--;
    }
    
    cout << "\rTime's up!            " << endl; // Extra spaces to clear previous text
}

int main() {
    int minutes;
    cout << "Enter countdown time in minutes (3 for 3 minutes): ";
    cin >> minutes;
    
    cout << "Starting " << minutes << " minute countdown..." << endl;
    countdownTimer(minutes);
    
    return 0;
}