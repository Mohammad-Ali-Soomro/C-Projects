
#include <iostream>
#include <conio.h>  // For getch()

using namespace std;

// Structure representing a car
struct Car {
    int position;
    int points;
};

// Nested structure representing the racing track
struct RacingTrack {
    int trackLength;
    Car car1;
    Car car2;
};

// Function to display the racing track
void displayTrack(const RacingTrack& track) {
    // Draw the top boundary of the track
    for (int i = 0; i < track.trackLength + 2; ++i) {
        cout << "-";
    }
    cout << endl;

    // Draw the track with cars
    cout << "|";
    for (int i = 0; i < track.trackLength; ++i) {
        if (i == track.car1.position) {
            cout << "CAR1";  // Display car 1
        } else {
            cout << " ";
        }
    }
    cout << "|" << endl;

    cout << "|";
    for (int i = 0; i < track.trackLength; ++i) {
        if (i == track.car2.position) {
            cout << "CAR2";  // Display car 2
        } else {
            cout << " ";
        }
    }
    cout << "|" << endl;

    // Draw the bottom boundary of the track
    for (int i = 0; i < track.trackLength + 2; ++i) {
        cout << "-";
    }
    cout << endl;

    // Display the current position and points of each car
    cout << "Car 1 - Position: " << track.car1.position << ", Points: " << track.car1.points << endl;
    cout << "Car 2 - Position: " << track.car2.position << ", Points: " << track.car2.points << endl;
}

// Function to update the game state based on user input
void updateGame(RacingTrack& track, char input) {
    // Update car positions based on user input
    switch (input) {
        case 'a':
            if (track.car1.position > 0) {
                track.car1.position--;
                track.car1.points--;  // Decrement points for car 1
            }
            break;
        case 'd':
            if (track.car1.position < track.trackLength - 1) {
                track.car1.position++;
                track.car1.points++;  // Increment points for car 1
            }
            break;
        case 'j':
            if (track.car2.position > 0) {
                track.car2.position--;
                track.car2.points--;  // Decrement points for car 2
            }
            break;
        case 'l':
            if (track.car2.position < track.trackLength - 1) {
                track.car2.position++;
                track.car2.points++;  // Increment points for car 2
            }
            break;
        case 'q':
            // Quit the game
            exit(0);
            break;
    }
}

int main() {
	
	
	cout<<"\t\t\t\t WELCOME TO THE GRAND CAR RACING GAME DEVELOPED BY MOHAMMAD ALI"<<endl;
	cout<<endl<<"Controls for CAR1  are  [press 'd' for moving right and press 'a' for moving left]"<<endl;
	cout<<endl<<"Controls for CAR2  are  [press 'l' for moving right and press 'j' for moving left]"<<endl;
    // Get user input for track length
    cout <<endl<< "Enter the track length: ";
    int trackLength;
    cin >> trackLength;

    // Initialize the racing track and cars
    RacingTrack track;
    track.trackLength = trackLength;
    track.car1 = {0, 0};  // Car 1 starts at position 0 with 0 points
    track.car2 = {0, 0};  // Car 2 starts at position 0 with 0 points

    // Display the cars initially
    displayTrack(track);

    // Game loop
    while (true) {
       
        char input = getch();

        // Update the game state based on user input
        updateGame(track, input);

        // Check for a winner
        if (track.car1.position >= track.trackLength - 1 || track.car2.position >= track.trackLength - 1) {
            // Clear the console screen
            system("cls");

            // Display the winning message
            cout << "==================================" << endl;
            cout << "Congratulations! ";
            if (track.car1.position > track.car2.position || track.car1.points > track.car2.points) {
                cout << "Car 1";
            } else {
                cout << "Car 2";
            }
            cout << " wins the race!" << endl;
            cout << "==================================" << endl;

            // Exit the game
            exit(0);
        }

        // Clear the console screen for the next iteration
        system("cls");

        // Display the racing track
        displayTrack(track);
    }

    return 0;
}
