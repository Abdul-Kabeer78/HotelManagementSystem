#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

// Function to set text color
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to clear screen
void ClearScreen() {
    system("cls");
}

// Function to pause
void Pause() {
    cout << "\nPress any key to continue...";
    getch();
}

// Structure for Room
struct Room {
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
    bool isAC;
    int maxGuests;
};

// Structure for Booking
struct Booking {
    int bookingID;
    int roomNumber;
    string customerName;
    string customerPhone;
    string checkInDate;
    string checkOutDate;
    int numberOfGuests;
    double totalAmount;
    bool isPaid;
};

// Global variables
vector<Room> rooms;
vector<Booking> bookings;
int nextBookingID = 1001;

// Function declarations
void initializeRooms();
void saveData();
void loadData();
void displayMainMenu();
void addNewRoom();
void displayAllRooms();
void bookRoom();
void displayAllBookings();
void checkOut();
void searchBooking();
void deleteBooking();
void generateBill(int bookingIndex);

// Display hotel logo
void displayHotelLogo() {
    SetColor(13);
    cout << "\n===================================\n";
    cout << "     GRAND PLAZA HOTEL SYSTEM      \n";
    cout << "===================================\n";
    SetColor(15);
}

// Initialize sample rooms
void initializeRooms() {
    rooms.push_back({101, "Standard", 1500.00, true, false, 2});
    rooms.push_back({102, "Standard", 1500.00, true, false, 2});
    rooms.push_back({103, "Deluxe", 2500.00, true, true, 3});
    rooms.push_back({104, "Deluxe", 2500.00, true, true, 3});
    rooms.push_back({105, "Suite", 5000.00, true, true, 4});
    rooms.push_back({106, "Suite", 5000.00, true, true, 4});
}

// Add new room
void addNewRoom() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== ADD NEW ROOM ==========\n";
    SetColor(15);
    
    Room newRoom;
    cout << "Enter Room Number: ";
    cin >> newRoom.roomNumber;
    
    for(const auto& room : rooms) {
        if(room.roomNumber == newRoom.roomNumber) {
            SetColor(12);
            cout << "Room already exists!\n";
            SetColor(15);
            Pause();
            return;
        }
    }
    
    cout << "Enter Room Type: ";
    cin >> ws;
    getline(cin, newRoom.roomType);
    
    cout << "Enter Price Per Night: ";
    cin >> newRoom.pricePerNight;
    
    cout << "Is AC Available? (1=Yes, 0=No): ";
    cin >> newRoom.isAC;
    
    cout << "Enter Maximum Guests: ";
    cin >> newRoom.maxGuests;
    
    newRoom.isAvailable = true;
    rooms.push_back(newRoom);
    
    SetColor(10);
    cout << "\nRoom added successfully!\n";
    SetColor(15);
    Pause();
}

// Display all rooms
void displayAllRooms() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== ALL ROOMS ==========\n";
    SetColor(15);
    
    if(rooms.empty()) {
        SetColor(12);
        cout << "No rooms available!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    cout << "\n" << string(70, '-') << endl;
    cout << left << setw(10) << "Room No." << setw(15) << "Type" << setw(15) << "Price/Night"
         << setw(12) << "AC" << setw(15) << "Max Guests" << setw(12) << "Status" << endl;
    cout << string(70, '-') << endl;
    
    for(const auto& room : rooms) {
        cout << left << setw(10) << room.roomNumber << setw(15) << room.roomType 
             << setw(15) << fixed << setprecision(2) << room.pricePerNight
             << setw(12) << (room.isAC ? "Yes" : "No") << setw(15) << room.maxGuests;
             
        if(room.isAvailable) {
            SetColor(10);
            cout << setw(12) << "Available";
            SetColor(15);
        } else {
            SetColor(12);
            cout << setw(12) << "Booked";
            SetColor(15);
        }
        cout << endl;
    }
    cout << string(70, '-') << endl;
    Pause();
}

// Book a room
void bookRoom() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== BOOK A ROOM ==========\n";
    SetColor(15);
    
    // Show available rooms
    cout << "\nAvailable Rooms:\n";
    cout << string(70, '-') << endl;
    cout << left << setw(10) << "Room No." << setw(15) << "Type" << setw(15) << "Price/Night"
         << setw(12) << "AC" << setw(15) << "Max Guests" << endl;
    cout << string(70, '-') << endl;
    
    bool availableRooms = false;
    for(const auto& room : rooms) {
        if(room.isAvailable) {
            availableRooms = true;
            cout << left << setw(10) << room.roomNumber << setw(15) << room.roomType 
                 << setw(15) << fixed << setprecision(2) << room.pricePerNight
                 << setw(12) << (room.isAC ? "Yes" : "No") << setw(15) << room.maxGuests << endl;
        }
    }
    
    if(!availableRooms) {
        SetColor(12);
        cout << "No rooms available for booking!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    cout << string(70, '-') << endl;
    int roomNumber;
    cout << "\nEnter Room Number to book: ";
    cin >> roomNumber;
    
    int roomIndex = -1;
    for(int i = 0; i < rooms.size(); i++) {
        if(rooms[i].roomNumber == roomNumber) {
            roomIndex = i;
            break;
        }
    }
    
    if(roomIndex == -1) {
        SetColor(12);
        cout << "Room not found!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    if(!rooms[roomIndex].isAvailable) {
        SetColor(12);
        cout << "Room is already booked!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    // Create booking
    Booking newBooking;
    newBooking.bookingID = nextBookingID++;
    newBooking.roomNumber = roomNumber;
    
    cout << "Enter Customer Name: ";
    cin >> ws;
    getline(cin, newBooking.customerName);
    
    cout << "Enter Customer Phone: ";
    cin >> ws;
    getline(cin, newBooking.customerPhone);
    
    cout << "Enter Check-in Date (DD-MM-YYYY): ";
    cin >> newBooking.checkInDate;
    
    cout << "Enter Check-out Date (DD-MM-YYYY): ";
    cin >> newBooking.checkOutDate;
    
    cout << "Enter Number of Guests: ";
    cin >> newBooking.numberOfGuests;
    
    if(newBooking.numberOfGuests > rooms[roomIndex].maxGuests) {
        SetColor(12);
        cout << "Too many guests for this room!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    newBooking.totalAmount = rooms[roomIndex].pricePerNight;
    newBooking.isPaid = false;
    
    bookings.push_back(newBooking);
    rooms[roomIndex].isAvailable = false;
    
    SetColor(10);
    cout << "\nBooking successful! Booking ID: " << newBooking.bookingID << endl;
    SetColor(15);
    Pause();
}

// Display all bookings
void displayAllBookings() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== ALL BOOKINGS ==========\n";
    SetColor(15);
    
    if(bookings.empty()) {
        SetColor(12);
        cout << "No bookings found!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    cout << "\n" << string(90, '-') << endl;
    cout << left << setw(12) << "Booking ID" << setw(10) << "Room No." << setw(20) << "Customer Name"
         << setw(15) << "Phone" << setw(12) << "Check-in" << setw(12) << "Check-out"
         << setw(10) << "Amount" << setw(8) << "Status" << endl;
    cout << string(90, '-') << endl;
    
    for(const auto& booking : bookings) {
        cout << left << setw(12) << booking.bookingID << setw(10) << booking.roomNumber 
             << setw(20) << booking.customerName << setw(15) << booking.customerPhone
             << setw(12) << booking.checkInDate << setw(12) << booking.checkOutDate
             << setw(10) << fixed << setprecision(2) << booking.totalAmount;
             
        if(booking.isPaid) {
            SetColor(10);
            cout << setw(8) << "Paid";
            SetColor(15);
        } else {
            SetColor(12);
            cout << setw(8) << "Unpaid";
            SetColor(15);
        }
        cout << endl;
    }
    cout << string(90, '-') << endl;
    Pause();
}

// Generate bill
void generateBill(int bookingIndex) {
    ClearScreen();
    displayHotelLogo();
    SetColor(13);
    cout << "\n========== HOTEL BILL ==========\n";
    SetColor(15);
    
    cout << "\nBooking ID: " << bookings[bookingIndex].bookingID << endl;
    cout << "Customer Name: " << bookings[bookingIndex].customerName << endl;
    cout << "Phone: " << bookings[bookingIndex].customerPhone << endl;
    cout << "Room Number: " << bookings[bookingIndex].roomNumber << endl;
    cout << "Check-in Date: " << bookings[bookingIndex].checkInDate << endl;
    cout << "Check-out Date: " << bookings[bookingIndex].checkOutDate << endl;
    cout << "Number of Guests: " << bookings[bookingIndex].numberOfGuests << endl;
    
    cout << "\n" << string(40, '-') << endl;
    cout << "Total Amount: Rs. " << fixed << setprecision(2) << bookings[bookingIndex].totalAmount << endl;
    cout << string(40, '-') << endl;
    cout << "\nThank you for staying with us!\n";
}

// Check out
void checkOut() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== CHECK OUT ==========\n";
    SetColor(15);
    
    int bookingID;
    cout << "Enter Booking ID for checkout: ";
    cin >> bookingID;
    
    int bookingIndex = -1;
    for(int i = 0; i < bookings.size(); i++) {
        if(bookings[i].bookingID == bookingID) {
            bookingIndex = i;
            break;
        }
    }
    
    if(bookingIndex == -1) {
        SetColor(12);
        cout << "Booking not found!\n";
        SetColor(15);
        Pause();
        return;
    }
    
    generateBill(bookingIndex);
    bookings[bookingIndex].isPaid = true;
    
    for(int i = 0; i < rooms.size(); i++) {
        if(rooms[i].roomNumber == bookings[bookingIndex].roomNumber) {
            rooms[i].isAvailable = true;
            break;
        }
    }
    
    SetColor(10);
    cout << "\nCheckout completed!\n";
    SetColor(15);
    Pause();
}

// Search booking
void searchBooking() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== SEARCH BOOKING ==========\n";
    SetColor(15);
    
    int choice;
    cout << "Search by:\n1. Booking ID\n2. Customer Name\n3. Room Number\nEnter choice: ";
    cin >> choice;
    
    if(choice == 1) {
        int bookingID;
        cout << "Enter Booking ID: ";
        cin >> bookingID;
        
        for(const auto& booking : bookings) {
            if(booking.bookingID == bookingID) {
                cout << "\nBooking Found:\n";
                cout << "Booking ID: " << booking.bookingID << endl;
                cout << "Customer Name: " << booking.customerName << endl;
                cout << "Phone: " << booking.customerPhone << endl;
                cout << "Room Number: " << booking.roomNumber << endl;
                cout << "Check-in: " << booking.checkInDate << endl;
                cout << "Check-out: " << booking.checkOutDate << endl;
                cout << "Amount: Rs. " << fixed << setprecision(2) << booking.totalAmount << endl;
                cout << "Status: " << (booking.isPaid ? "Paid" : "Unpaid") << endl;
                Pause();
                return;
            }
        }
        SetColor(12);
        cout << "Booking not found!\n";
        SetColor(15);
    }
    else if(choice == 2) {
        string name;
        cout << "Enter Customer Name: ";
        cin >> ws;
        getline(cin, name);
        
        bool found = false;
        for(const auto& booking : bookings) {
            if(booking.customerName.find(name) != string::npos) {
                if(!found) {
                    cout << "\nSearch Results:\n";
                    found = true;
                }
                cout << "ID: " << booking.bookingID << ", Name: " << booking.customerName 
                     << ", Room: " << booking.roomNumber << endl;
            }
        }
        if(!found) {
            SetColor(12);
            cout << "No bookings found!\n";
            SetColor(15);
        }
    }
    else if(choice == 3) {
        int roomNumber;
        cout << "Enter Room Number: ";
        cin >> roomNumber;
        
        bool found = false;
        for(const auto& booking : bookings) {
            if(booking.roomNumber == roomNumber) {
                if(!found) {
                    cout << "\nSearch Results:\n";
                    found = true;
                }
                cout << "ID: " << booking.bookingID << ", Name: " << booking.customerName 
                     << ", Dates: " << booking.checkInDate << " to " << booking.checkOutDate << endl;
            }
        }
        if(!found) {
            SetColor(12);
            cout << "No bookings found!\n";
            SetColor(15);
        }
    }
    else {
        SetColor(12);
        cout << "Invalid choice!\n";
        SetColor(15);
    }
    Pause();
}

// Delete booking
void deleteBooking() {
    ClearScreen();
    displayHotelLogo();
    SetColor(11);
    cout << "\n========== DELETE BOOKING ==========\n";
    SetColor(15);
    
    int bookingID;
    cout << "Enter Booking ID to delete: ";
    cin >> bookingID;
    
    for(int i = 0; i < bookings.size(); i++) {
        if(bookings[i].bookingID == bookingID) {
            int roomNumber = bookings[i].roomNumber;
            bookings.erase(bookings.begin() + i);
            
            for(int j = 0; j < rooms.size(); j++) {
                if(rooms[j].roomNumber == roomNumber) {
                    rooms[j].isAvailable = true;
                    break;
                }
            }
            
            SetColor(10);
            cout << "Booking deleted successfully!\n";
            SetColor(15);
            Pause();
            return;
        }
    }
    
    SetColor(12);
    cout << "Booking not found!\n";
    SetColor(15);
    Pause();
}

// Save data
void saveData() {
    ofstream roomFile("rooms.txt");
    ofstream bookingFile("bookings.txt");
    
    if(roomFile.is_open()) {
        for(const auto& room : rooms) {
            roomFile << room.roomNumber << "," << room.roomType << "," << room.pricePerNight << ","
                     << room.isAvailable << "," << room.isAC << "," << room.maxGuests << "\n";
        }
        roomFile.close();
    }
    
    if(bookingFile.is_open()) {
        for(const auto& booking : bookings) {
            bookingFile << booking.bookingID << "," << booking.roomNumber << "," << booking.customerName << ","
                        << booking.customerPhone << "," << booking.checkInDate << "," << booking.checkOutDate << ","
                        << booking.numberOfGuests << "," << booking.totalAmount << "," << booking.isPaid << "\n";
        }
        bookingFile.close();
        
        ofstream idFile("nextid.txt");
        if(idFile.is_open()) {
            idFile << nextBookingID;
            idFile.close();
        }
    }
    
    SetColor(10);
    cout << "\nData saved successfully!\n";
    SetColor(15);
    Pause();
}

// Load data
void loadData() {
    ifstream roomFile("rooms.txt");
    if(!roomFile.good()) {
        initializeRooms();
        return;
    }
    
    rooms.clear();
    string line;
    while(getline(roomFile, line)) {
        Room room;
        size_t pos = 0;
        string token;
        vector<string> tokens;
        
        while((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);
        
        if(tokens.size() >= 6) {
            room.roomNumber = stoi(tokens[0]);
            room.roomType = tokens[1];
            room.pricePerNight = stod(tokens[2]);
            room.isAvailable = (tokens[3] == "1");
            room.isAC = (tokens[4] == "1");
            room.maxGuests = stoi(tokens[5]);
            rooms.push_back(room);
        }
    }
    roomFile.close();
    
    bookings.clear();
    ifstream bookingFile("bookings.txt");
    if(bookingFile.is_open()) {
        while(getline(bookingFile, line)) {
            Booking booking;
            size_t pos = 0;
            string token;
            vector<string> tokens;
            
            while((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            
            if(tokens.size() >= 9) {
                booking.bookingID = stoi(tokens[0]);
                booking.roomNumber = stoi(tokens[1]);
                booking.customerName = tokens[2];
                booking.customerPhone = tokens[3];
                booking.checkInDate = tokens[4];
                booking.checkOutDate = tokens[5];
                booking.numberOfGuests = stoi(tokens[6]);
                booking.totalAmount = stod(tokens[7]);
                booking.isPaid = (tokens[8] == "1");
                bookings.push_back(booking);
            }
        }
        bookingFile.close();
    }
    
    ifstream idFile("nextid.txt");
    if(idFile.is_open()) {
        idFile >> nextBookingID;
        idFile.close();
    } else {
        nextBookingID = 1001;
    }
}

// Main menu
void displayMainMenu() {
    int choice;
    do {
        ClearScreen();
        displayHotelLogo();
        SetColor(11);
        cout << "\n========== MAIN MENU ==========\n";
        SetColor(15);
        
        cout << "1. Add New Room\n";
        cout << "2. Display All Rooms\n";
        cout << "3. Book a Room\n";
        cout << "4. Display All Bookings\n";
        cout << "5. Check Out\n";
        cout << "6. Search Booking\n";
        cout << "7. Delete Booking\n";
        cout << "8. Save Data\n";
        cout << "9. Exit\n";
        
        SetColor(14);
        cout << "\nEnter your choice (1-9): ";
        SetColor(15);
        cin >> choice;
        
        switch(choice) {
            case 1: addNewRoom(); break;
            case 2: displayAllRooms(); break;
            case 3: bookRoom(); break;
            case 4: displayAllBookings(); break;
            case 5: checkOut(); break;
            case 6: searchBooking(); break;
            case 7: deleteBooking(); break;
            case 8: saveData(); break;
            case 9: 
                saveData();
                SetColor(10);
                cout << "\nThank you for using Hotel Booking System!\n";
                SetColor(15);
                break;
            default:
                SetColor(12);
                cout << "Invalid choice! Please try again.\n";
                SetColor(15);
                Pause();
        }
    } while(choice != 9);
}

// Main function
int main() {
    loadData();
    displayMainMenu();
    return 0;
}