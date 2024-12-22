#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Flight Class
class Flight {
private:
    string flightID;
    string source;
    string destination;
    int availableSeats;
    string departureTime;
    string arrivalTime;

public:
    Flight(string id, string src, string dest, int seats, string dept, string arr)
        : flightID(id), source(src), destination(dest), availableSeats(seats), departureTime(dept), arrivalTime(arr) {}

    string getFlightID() const { return flightID; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    int getAvailableSeats() const { return availableSeats; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }

    void displayFlightDetails() const {
        cout << "Flight ID: " << flightID << ", From: " << source << " To: " << destination
             << ", Seats Available: " << availableSeats << ", Departure: " << departureTime
             << ", Arrival: " << arrivalTime << endl;
    }

    void decreaseSeats(int count) {
        if (availableSeats >= count) {
            availableSeats -= count;
        } else {
            cout << "Not enough available seats.\n";
        }
    }

    void increaseSeats(int count) {
        availableSeats += count;
        cout << "Seats updated successfully.\n";
    }
};

// Passenger Class
class Passenger {
private:
    string passengerID;
    string name;
    string contact;

public:
    Passenger(string id, string nm, string cont) : passengerID(id), name(nm), contact(cont) {}

    string getPassengerID() const { return passengerID; }
    string getName() const { return name; }
    string getContact() const { return contact; }

    void updateDetails(string nm, string cont) {
        name = nm;
        contact = cont;
        cout << "Details updated successfully.\n";
    }
};

// Booking Class
class Booking {
private:
    string bookingID;
    Passenger passenger;
    Flight flight;
    bool bookingStatus; // true = active, false = canceled

public:
    Booking(string bID, Passenger p, Flight f) : bookingID(bID), passenger(p), flight(f), bookingStatus(true) {}

    void cancelBooking() {
        bookingStatus = false;
        flight.increaseSeats(1); // Revert the seat count when canceled
        cout << "Booking canceled successfully.\n";
    }

    void displayBookingDetails() const {
        cout << "Booking ID: " << bookingID << ", Passenger: " << passenger.getName()
             << ", Flight ID: " << flight.getFlightID() << ", Status: "
             << (bookingStatus ? "Active" : "Canceled") << endl;
    }
};

// User Class
class User {
private:
    string username;
    string password;
    bool isAdmin;

public:
    User(string user, string pass, bool admin = false) : username(user), password(pass), isAdmin(admin) {}

    bool authenticate(string user, string pass) {
        return (user == username && pass == password);
    }

    bool getIsAdmin() const { return isAdmin; }
};

// FlightReservationSystem Class
class FlightReservationSystem {
private:
    vector<Flight> flightList;
    vector<Passenger> passengerList;
    vector<Booking> bookingList;
    vector<User> userList;

public:
    FlightReservationSystem() {
        // Adding a default admin user
        userList.push_back(User("admin", "adminpass", true));
    }

    void addNewFlight(string id, string src, string dest, int seats, string dept, string arr) {
        flightList.push_back(Flight(id, src, dest, seats, dept, arr));
        cout << "Flight added successfully.\n";
    }

    void removeFlight(string flightID) {
        for (auto it = flightList.begin(); it != flightList.end(); ++it) {
            if (it->getFlightID() == flightID) {
                flightList.erase(it);
                cout << "Flight " << flightID << " removed successfully.\n";
                return;
            }
        }
        cout << "Flight not found!\n";
    }

    void updateFlight(string id, string dept, string arr, int seats) {
        for (Flight &flight : flightList) {
            if (flight.getFlightID() == id) {
                flight = Flight(id, flight.getSource(), flight.getDestination(), seats, dept, arr);
                cout << "Flight details updated successfully.\n";
                return;
            }
        }
        cout << "Flight not found!\n";
    }

    void searchFlight(string src, string dest) {
        cout << "Searching flights from " << src << " to " << dest << ":\n";
        for (const Flight &flight : flightList) {
            if (flight.getSource() == src && flight.getDestination() == dest) {
                flight.displayFlightDetails();
            }
        }
    }

    void searchFlightByDate(string src, string dest, string date) {
        cout << "Searching flights from " << src << " to " << dest << " on " << date << ":\n";
        for (const Flight &flight : flightList) {
            if (flight.getSource() == src && flight.getDestination() == dest) {
                if (flight.getDepartureTime().substr(0, 10) == date) {
                    flight.displayFlightDetails();
                }
            }
        }
    }

    void addPassenger(string id, string name, string contact) {
        passengerList.push_back(Passenger(id, name, contact));
        cout << "Passenger added successfully.\n";
    }

    void makeBooking(string passengerID, string flightID) {
        Passenger *passenger = nullptr;
        Flight *flight = nullptr;

        for (auto &p : passengerList) {
            if (p.getPassengerID() == passengerID) {
                passenger = &p;
                break;
            }
        }

        for (auto &f : flightList) {
            if (f.getFlightID() == flightID) {
                flight = &f;
                break;
            }
        }

        if (passenger && flight && flight->getAvailableSeats() > 0) {
            string bookingID = "B" + to_string(bookingList.size() + 1);
            bookingList.push_back(Booking(bookingID, *passenger, *flight));
            flight->decreaseSeats(1);
            cout << "Booking successful. Booking ID: " << bookingID << endl;
        } else {
            cout << "Booking failed. Please check flight availability.\n";
        }
    }

    void cancelBooking(string bookingID) {
        for (Booking &booking : bookingList) {
            if (bookingID == bookingID) {
                booking.cancelBooking();
                return;
            }
        }
        cout << "Booking not found!\n";
    }

    void viewAllBookings() const {
        cout << "All Bookings:\n";
        for (const Booking &booking : bookingList) {
            booking.displayBookingDetails();
        }
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nFlight Reservation System Menu:\n"
                 << "1. Add New Flight\n"
                 << "2. Update Flight Details\n"
                 << "3. Register Passenger\n"
                 << "4. Book Flight\n"
                 << "5. Cancel Booking\n"
                 << "6. View Available Flights\n"
                 << "7. View Passenger Booking History\n"
                 << "8. Admin Panel\n"
                 << "9. View All Bookings\n"
                 << "10. Search Flights by Date\n"
                 << "11. Exit\n";
            cin >> choice;

            switch (choice) {
            case 1:
                {
                    string id, source, dest, dept, arr;
                    int seats;
                    cout << "Enter Flight ID: ";
                    cin >> id;

                    cout << "Enter Source (Airport): ";
                    cin >> source;

                    cout << "Enter Destination (Airport): ";
                    cin >> dest;

                    cout << "Enter Number of Seats: ";
                    cin >> seats;

                    cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                    cin >> dept;

                    cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                    cin >> arr;

                    addNewFlight(id, source, dest, seats, dept, arr);
                }
                break;
            case 2:
                {
                    string id, dept, arr;
                    int seats;
                    cout << "Enter Flight ID to update, Departure Time, Arrival Time, and Number of Seats: ";
                    cin >> id >> dept >> arr >> seats;
                    updateFlight(id, dept, arr, seats);
                }
                break;
            case 3:
                {
                    string id, name, contact;
                    cout << "Enter Passenger ID, Name, and Contact: ";
                    cin >> id >> name >> contact;
                    addPassenger(id, name, contact);
                }
                break;
            case 4:
                {
                    string passengerID, flightID;
                    cout << "Enter Passenger ID and Flight ID: ";
                    cin >> passengerID >> flightID;
                    makeBooking(passengerID, flightID);
                }
                break;
            case 5:
                {
                    string bookingID;
                    cout << "Enter Booking ID to cancel: ";
                    cin >> bookingID;
                    cancelBooking(bookingID);
                }
                break;
            case 6:
                {
                    string source, destination;
                    cout << "Enter Source and Destination: ";
                    cin >> source >> destination;
                    searchFlight(source, destination);
                }
                break;
            case 7:
                {
                    string passengerID;
                    cout << "Enter Passenger ID: ";
                    cin >> passengerID;
                    // This is for the future - to display booking history of the passenger
                }
                break;
            case 8:
                {
                    // Admin specific actions
                    cout << "Admin Panel: You can add/remove flights, view all bookings, etc.\n";
                }
                break;
            case 9:
                viewAllBookings();
                break;
            case 10:
                {
                    string source, destination, date;
                    cout << "Enter Source, Destination, and Date (YYYY-MM-DD): ";
                    cin >> source >> destination >> date;
                    searchFlightByDate(source, destination, date);
                }
                break;
            case 11:
                cout << "Exiting system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 11);
    }
};

int main() {
    FlightReservationSystem system;

    // Example admin and user login
    User admin("admin", "adminpass", true);
    User user("john_doe", "password123");

    // Admin adds a flight
    system.addNewFlight("F101", "NYC", "LA", 100, "2024-12-25 08:00", "2024-12-25 11:00");

    // User makes a booking
    system.addPassenger("P001", "John Doe", "123-456-7890");
    system.makeBooking("P001", "F101");

    // View all bookings
    system.viewAllBookings();

    // Display the menu
    system.displayMenu();

    return 0;
}
