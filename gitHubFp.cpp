#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <cctype>
#include <limits>

using namespace std;

//Function Declarations
string getValidStringInput(const string& prompt);
string getValidPhoneInput(const string& prompt);
char getYesNoInput(const string& prompt);

// Forward declarations
class Table;
class Payment;
class RegisteredUsers;

class Table {
    private:
        string tableId;
        int tableNumber;
        int seatingCapacity;
        string status;
  
    public:
        Table(string tableId, int tableNumber, int seatingCapacity, string status = "Available")
            : tableId(tableId), tableNumber(tableNumber), seatingCapacity(seatingCapacity), status(status) {}

        void display() const {
            cout << "Table ID: " << tableId << ", Number: " << tableNumber << ", Capacity: " << seatingCapacity << ", Status: " << status << endl;
        }
        
        void updateTableStatus(const string& newStatus) {
            status = newStatus;
            cout << "Table " << tableNumber << " status updated to " << status << endl;
        }
        
        string getId() const { return tableId; }
        string getTableId() const { return tableId; }
        int getSeatingCapacity() const { return seatingCapacity; }
        string getStatus() const { return status; }
};


// Singleton class for the Reservation System
class ReservationSystem {
    private:
        static ReservationSystem* instance;

        ReservationSystem() {} // Private constructor

    public:
        static ReservationSystem* getInstance() {
            if (!instance) {
                instance = new ReservationSystem();
            }
        return instance;
        }

        void showWelcomeMessage() {
            cout << "\nWelcome to the Restaurant Reservation System!" << endl;
        }
};

   ReservationSystem* ReservationSystem::instance = nullptr;

   bool isValidPositiveInteger(const string& input) {
        if (input.empty() || input[0] == '-') return false;
        for (char c : input) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    int getValidIntegerInput(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            string input;
            cin >> input;

            if (isValidPositiveInteger(input)) {
                return stoi(input);
            } else {
                cout << "Invalid input. Please enter a positive integer." << endl;
            }
        }
    }

// Abstract class for Payment Strategy
class PaymentStrategy {
    public:
        virtual ~PaymentStrategy() {}
        virtual void processPayment(float amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
    private:
        bool paymentSuccessful; // Track payment success

    public:
        CreditCardPayment() : paymentSuccessful(false) {}

        void processPayment(float amount) override {
            if (amount <= 0) {
                cout << "Invalid payment amount. Payment must be a positive integer." << endl;
                return;
            }

        string cardNumber, expiryDate;
        cout << "Enter card number: ";
        cin >> cardNumber;
        cout << "Enter expiry date (MM/YY): ";
        cin >> expiryDate;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char confirmation;
        cout << "Confirm Payment of $" << amount << "? (y/n): ";
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            cout << "\nPayment of $" << amount << " successful.\n";
            paymentSuccessful = true;
        } else {
            cout << "\nPayment canceled.\n";
            paymentSuccessful = false;
        }
    }

        bool isPaymentSuccessful() const {
            return paymentSuccessful;
        }
};

class PayPalPayment : public PaymentStrategy {
    private:
        bool paymentSuccessful;

    public:
        PayPalPayment() : paymentSuccessful(false) {}

        void processPayment(float amount) override {
        if (amount <= 0) {
            cout << "Invalid payment amount. Payment must be a positive integer." << endl;
            return;
        }

        string email, password;
        cout << "Enter Paypal Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> password;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char confirmation;
        cout << "Confirm Payment of $" << amount << "? (y/n): ";
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            cout << "Payment of $" << amount << " via PayPal successful.\n";
            paymentSuccessful = true; // Set payment as successful
        } else {
            cout << "Payment canceled.\n";
            paymentSuccessful = false; // Set payment as not successful
        }
    }

        bool isPaymentSuccessful() const {
            return paymentSuccessful; // Return payment status
        }
};


class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (year < 2023) {
            throw invalid_argument("Year must be 2023 or later.");
        }
        if (month < 1 || month > 12) {
            throw invalid_argument("Month must be between 1 and 12.");
        }
        if (day < 1 || day > 31) {
            throw invalid_argument("Day must be between 1 and 31.");
        }

        // Check for months with less than 31 days
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            throw invalid_argument("This month has only 30 days.");
        }
        // Check for February
        if (month == 2) {
            if (day > 29) {
                throw invalid_argument("February has at most 29 days.");
            }
            if (day == 29 && !isLeapYear(year)) {
                throw invalid_argument("February has only 28 days in non-leap years.");
            }
        }
    }

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    void display() const {
        cout << day << "/" << month << "/" << year;
    }
};

class Time {
    private:
        int hour;
        int minute;

    public:
        Time(int hour, int minute) : hour(hour), minute(minute) {
            if (hour < 0 || hour > 23) {
            throw invalid_argument("Hour must be between 0 and 23.");
        }
        if (minute < 0 || minute > 59) {
            throw invalid_argument("Minute must be between 0 and 59.");
        }
    }

        void display() const {
            cout << hour << ":" << (minute < 10 ? "0" : "") << minute; // Format minutes with leading zero
        }
};

class Reservation {
    private:
        string reservationId;
        Date date;
        Time time;
        int numberOfGuests;
        string status;
        RegisteredUsers* customer;
        Table* table;

    public:
        Reservation(string reservationId, Date date, Time time, int numberOfGuests, string status, RegisteredUsers* customer, Table* table)
            : reservationId(reservationId), date(date), time(time), numberOfGuests(numberOfGuests), status(status), customer(customer), table(table) {}

        void createReservation() {
            cout << "Reservation " << reservationId << " created for " << numberOfGuests << " guests." << endl;
        }

        void cancelReservation() {
            status = "Canceled";
        }

        void viewReservation() const {
            cout << "Reservation ID: " << reservationId << ", Guests: " << numberOfGuests << ", Status: " << status << endl;
            cout << "Date: "; date.display(); cout << ", Time: "; time.display(); cout << endl;
        }

        void updateStatus(const string& newStatus) {
            status = newStatus;
        }

        string getStatus() const { return status; }
        string getReservationId() const { return reservationId; }
        Date getDate() const { return date; }
        Time getTime() const { return time; }
};


class User {
    protected:
        string userId;
        string name;
        string email;
        string phone;
        string password;

    public:
        User(string userId, string name, string email, string phone, string password)
            : userId(userId), name(name), email(email), phone(phone), password(password) {}

        virtual void createProfile() {
            cout << "Profile created for " << name << endl;
        }

        virtual void updateProfile(const string& newName, const string& newEmail, const string& newPhone) {
            if (newName.empty() || newEmail.empty() || newPhone.empty()) {
                cout << "Error: All fields must be provided.\n";
                return;
            }
      
            name = newName;
            email = newEmail;
            phone = newPhone;
            cout << "Profile updated for " << name << endl;
        }

        virtual void deleteProfile() {
            cout << "Profile deleted for " << name << endl;
            name = email = phone = password = "";
        }

        string getPassword() const {
            return password;
        }

        string getName() const {
            return name;
        }

        string getEmail() const {
            return email;
        }

        string getPhone() const {
            return phone;
        }

        bool login(const string& inputEmail, const string& inputPassword) const {
            return email == inputEmail && password == inputPassword;
        }
};


class RegisteredUsers : public User {
    private:
        vector<shared_ptr<Reservation>> reservationHistory;
        vector<float> bills;
        bool profileCreated;

    public:
        RegisteredUsers(string userId, string name, string email, string phone, string password)
            : User(userId, name, email, phone, password), profileCreated(false) {}

        void createProfile() {
            if (profileCreated) {
                cout << "Profile already created.\n";
            } else {
                cout << "Profile created for " << name << endl;
                profileCreated = true;
            }
        }

        void updateProfile() {
            while (true) {
                string newName = getValidStringInput("Enter new Name (or -1 to cancel): ");
                if (newName == "-1") {
                    cout << "Update Profile canceled." << endl;
                    return;
                }

                string newEmail = getValidStringInput("Enter new Email (or -1 to cancel): ");
                if (newEmail == "-1") {
                    cout << "Update Profile canceled." << endl;
                    return;
                }

                string newPhone = getValidPhoneInput("Enter new Phone # (or -1 to cancel): ");
                if (newPhone == "-1") {
                    cout << "Update Profile canceled." << endl;
                    return;
                }

                name = newName;
                email = newEmail;
                phone = newPhone;
                cout << "Profile updated for " << name << endl;
                break;
            }
        }

        const vector<shared_ptr<Reservation>>& getReservationHistory() const {
            return reservationHistory;
        }

        void makeReservation(shared_ptr<Reservation> reservation, vector<Table>& tables) {
            string reservationId;
            int month, day, year, hour, minute, numberOfGuests;

            // Reservation ID
            while (true) {
                cout << "\nEnter Reservation ID (-1 to cancel): ";
                cin >> reservationId;
                if (reservationId == "-1") {
                    cout << "Reservation process canceled." << endl;
                    return;
                }
                if (!all_of(reservationId.begin(), reservationId.end(), ::isdigit) || reservationId.empty()) {
                    cout << "Invalid input. Please enter a positive integer." << endl;
                    continue;
                }

                reservationId = "C-" + reservationId; // Prefix with "C-"
                break;
            }

            // Date
            while (true) {
                cout << "\n---Enter Date---" << endl;
                month = getValidIntegerInput("Month (1-12): ");
                day = getValidIntegerInput("Day: ");
                year = getValidIntegerInput("Year (2023 or later): ");
        
                if (month < 1 || month > 12 || day < 1 || year < 2023 || (month == 2 && day > 29) ||
                    ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (day > 31)) {
                        cout << "Invalid date. Please try again." << endl;
                        continue;
                    }
                break;
            }

            // Time
            while (true) {
                cout << "\n---Enter Time---" << endl;
                hour = getValidIntegerInput("Hour (0-23): ");
                minute = getValidIntegerInput("Minute (0-59): ");
        
                if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
                    cout << "Invalid time. Please try again." << endl;
                    continue;
                }
                break;
            }

            // Guests
            while (true) {
                numberOfGuests = getValidIntegerInput("Enter Number of Guests: ");
                if (numberOfGuests <= 0) {
                    cout << "Invalid input. Please enter a positive integer." << endl;
                    continue;
                }
                break;
            }

            cout << "\nAvailable Tables:\n";
            bool hasAvailableTables = false;
            Table* selectedTable = nullptr;

            for (auto& table : tables) {
                if (table.getStatus() == "Available") {
                table.display();
                hasAvailableTables = true;
            }
        }

        if (!hasAvailableTables) {
            cout << "No Available Tables." << endl;
            return;
        }

        // Let user choose a table
        string tableId;
        while (true) {
            cout << "\nEnter the Table ID to reserve (or -1 to cancel): ";
            cin >> tableId;
            if (tableId == "-1") {
                cout << "Reservation process canceled." << endl;
                return;
            }

            bool tableFound = false;
            for (auto& table : tables) {
                if (table.getId() == tableId && table.getStatus() == "Available") {
                    // Check if the table has sufficient capacity
                    if (numberOfGuests > table.getSeatingCapacity()) {
                        char continueChoice = getYesNoInput("Table " + table.getTableId() + " has insufficient capacity for " + to_string(numberOfGuests) + " guests, would you like to continue? (y/n): ");
                        if (continueChoice == 'n') {
                            cout << "Reservation process canceled." << endl;
                            return;
                        }
                    }

                    int paymentChoice;
                    cout << "Select Payment Method:\n";
                    cout << " 1. Credit Card\n";
                    cout << "2. PayPal\n";
                    cout << "3. Pay Later\n";
                    cout << "Please select an option (1-3): ";
                    paymentChoice = getValidIntegerInput("");

                    float amount = 50.0; // Example amount for reservation payment

                    switch (paymentChoice) {
                        case 1: { // Credit Card
                            CreditCardPayment paymentStrategy;
                            paymentStrategy.processPayment(amount);
                            if (paymentStrategy.isPaymentSuccessful()) {
                                table.updateTableStatus("Reserved");
                                reservation = make_shared<Reservation>(reservationId, Date(day, month, year), Time(hour, minute), numberOfGuests, "Confirmed", this, &table);
                                reservationHistory.push_back(reservation);
                                reservation->createReservation();
                                cout << "Reservation successful for Table ID: " << tableId << endl;
                            } else {
                                cout << "Payment was not successful. Reservation is on hold." << endl;
                                addBill(amount); // Add the amount to the user's bills
                                table.updateTableStatus("Reserved");
                                reservation = make_shared<Reservation>(reservationId, Date(day, month, year), Time(hour, minute), numberOfGuests, "Payment On Hold", this, &table);
                                reservationHistory.push_back(reservation);
                                reservation->createReservation();
                            }
                            break;
                        }
                        case 2: { // PayPal
                            PayPalPayment paymentStrategy;
                            paymentStrategy.processPayment(amount);
                            if (paymentStrategy.isPaymentSuccessful()) {
                                table.updateTableStatus("Reserved");
                                reservation = make_shared<Reservation>(reservationId, Date(day, month, year), Time(hour, minute), numberOfGuests, "Confirmed", this, &table);
                                reservationHistory.push_back(reservation);
                                reservation->createReservation();
                                cout << "Reservation successful for Table ID: " << tableId << endl;
                            } else {
                                cout << "Payment was not successful. Reservation is on hold." << endl;
                                addBill(amount); // Add the amount to the user's bills
                                table.updateTableStatus("Reserved");
                                reservation = make_shared<Reservation>(reservationId, Date(day, month, year), Time(hour, minute), numberOfGuests, "Payment On Hold", this, &table);
                                reservationHistory.push_back(reservation);
                                reservation->createReservation();
                            }
                            break;
                        }
                        case 3: { // Pay Later
                            cout << "\nBill would be placed under 'Make Payment Menu'.\n";
                            addBill(amount); // Add the amount to the user's bills
                            table.updateTableStatus("Reserved");
                            reservation = make_shared<Reservation>(reservationId, Date(day, month, year), Time(hour, minute), numberOfGuests, "Payment On Hold", this, &table);
                            reservationHistory.push_back(reservation);
                            reservation->createReservation();
                            cout << "Reservation successful for Table ID: " << tableId << endl;
                            break;
                        }
                        default:
                            cout << "Invalid payment method selected. Please try again." << endl;
                            continue; // Restart the payment method selection
                    }

                    tableFound = true;
                    break;
                }
            }

            if (!tableFound) {
                cout << "Invalid Table ID / Table is already reserved / No Available Table / Invalid Input. Please try again." << endl;
            } else {
                break;
            }
        }
    }

        void cancelReservation() {
            if (reservationHistory.empty()) {
                cout << "No Reservations to cancel." << endl;
                return;
            }

            cout << "\nAvailable Reservations to Cancel:\n";
            for (const auto& reservation : reservationHistory) {
                cout << "Reservation ID: " << reservation->getReservationId() << endl;
            }

            string reservationId;
            while (true) {
                cout << "Enter Reservation ID to cancel (-1 to cancel action): ";
                cin >> reservationId;

                if (reservationId == "-1") {
                    cout << "Cancel action aborted." << endl;
                    return;
                }

                // Check if the reservation ID exists in the history
                auto it = find_if(reservationHistory.begin(), reservationHistory.end(),
                    [&reservationId](const shared_ptr<Reservation>& reservation) {
                        return reservation->getReservationId() == reservationId;
                    });

                    if (it != reservationHistory.end()) {
                        // Cancel the reservation
                        (*it)->cancelReservation(); // Update status
                        reservationHistory.erase(it); // Remove from history
                        cout << "Reservation " << reservationId << " has been canceled." << endl;
                        return;
                    } else {
                        cout << "Invalid Reservation ID. Please try again." << endl; // Clearer message
                    }
                }
            }
            
        void addReservation(shared_ptr<Reservation> reservation) {
            reservationHistory.push_back(reservation);
        }

        void removeReservation(const string& reservationId) {
            auto it = find_if(reservationHistory.begin(), reservationHistory.end(),
                [&reservationId](const shared_ptr<Reservation>& reservation) {
                    return reservation->getReservationId() == reservationId;
                });
                if (it != reservationHistory.end()) {
                    reservationHistory.erase(it);
                }
            }

        void viewReservationHistory() const {
            if (reservationHistory.empty()) {
                cout << "No History to View." << endl;
                return;
            }

            cout << "\nReservation history for " << getName() << ":" << endl;
            for (const auto& reservation : reservationHistory) {
                reservation->viewReservation();
            }
        }

        void addBill(float amount) {
            bills.push_back(amount);
        }

        void makePayment(PaymentStrategy* paymentStrategy, float amount) {
            if (bills.empty()) {
                cout << "No Bills to be paid." << endl;
                return;
            }

            cout << "\nBills to be paid:\n";
            for (size_t i = 0; i < bills.size(); ++i) {
                cout << "Bill " << (i + 1) << ": $" << fixed << setprecision(2) << bills[i] << endl;
            }

            // Payment method selection
            int paymentChoice;
            cout << "Select Payment Method:\n";
            cout << "1. Credit Card\n";
            cout << "2. PayPal\n";
            cout << "3. Cancel\n";
            cout << "Please select an option (1-3): ";
            paymentChoice = getValidIntegerInput("");

            if (paymentChoice == 3) {
                cout << "Payment process canceled." << endl;
                return; // Exit payment process
            }

            // Process payment for each bill
            for (float billAmount : bills) {
                switch (paymentChoice) {
                    case 1:
                        paymentStrategy = new CreditCardPayment();
                        break;
                    case 2:
                        paymentStrategy = new PayPalPayment();
                        break;
                    default:
                        cout << "Invalid payment method selected. Please try again." << endl;
                        return; // Exit payment process
                }

                paymentStrategy->processPayment(billAmount);
                delete paymentStrategy; // Clean up
            }

            // Clear bills after payment
            bills.clear();
            cout << "All bills have been paid." << endl;

            // Update reservation status for those that were on hold
            for (auto& reservation : reservationHistory) {
                if (reservation->getStatus() == "Payment On Hold") {
                    reservation->updateStatus("Reserved"); // Update status to Reserved
                    cout << "Reservation ID: " << reservation->getReservationId() << " status updated to Reserved." << endl;
                }
            }
        }

        size_t getReservationCount() const {
            return reservationHistory.size();
        }
};

bool isValidName(const string& name);

class Staff : public User {
    private:
        string role;

    public:
        Staff(string userId, string name, string email, string phone, string password, string role)
            : User(userId, name, email, phone, password), role(role) {}


        void manageUsers(vector<shared_ptr<RegisteredUsers>>& users) {
            while (true) {
                cout << "\nUser  Management Menu:\n";
                cout << "1. View All Users\n";
                cout << "2. Delete a User by Name\n";
                cout << "3. Back to Previous Menu\n";
                int choice = getValidIntegerInput("Enter your choice (1-3): ");

            switch (choice) {
                case 1: {
                    // View all registered users
                    if (users.empty()) {
                        cout << "No registered users to display.\n";
                    } else {
                        cout << "\nRegistered Users:\n";
                        for (const auto& user : users) {
                            cout << "Name: " << user->getName()
                                << ", Email: " << user->getEmail()
                                << ", Phone: " << user->getPhone() << endl;
                        }
                    }
                    break;
                }
                case 2: {
                    // Delete a user by name
                    if (users.empty()) {
                        cout << "No registered users to delete.\n";
                        break;
                    }

                    string nameToDelete = getValidStringInput("Enter Name of the user to delete (or -1 to cancel): ");
                    if (nameToDelete == "-1") {
                        cout << "Delete action canceled." << endl;
                        break;
                    }

                    if (!isValidName(nameToDelete)) {
                        cout << "Invalid name. Please enter a valid name (letters and spaces only).\n";
                        continue; // Restart the deletion process
                    }

                    // Convert name to lowercase for case-insensitive comparison
                    string lowerNameToDelete = nameToDelete;
                    transform(lowerNameToDelete.begin(), lowerNameToDelete.end(), lowerNameToDelete.begin(), ::tolower);

                    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<RegisteredUsers>& user) {
                        string userName = user->getName();
                        transform(userName.begin(), userName.end(), userName.begin(), ::tolower);
                        return userName == lowerNameToDelete;
                    });

                    if (it != users.end()) {
                        string userName = (*it)->getName();
                        users.erase(it);
                        cout << "User  " << userName << " deleted successfully.\n";
                    } else {
                        cout << "User  with name " << nameToDelete << " not found.\n";
                    }
                    break;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

        void manageReservations(vector<shared_ptr<RegisteredUsers>>& customers, vector<Table>& tables) {
            while (true) {
                cout << "\nManage Reservations Menu:\n";
                cout << "1. View All Reservations\n";
                cout << "2. Cancel a Reservation\n";
                cout << "3. Back to Previous Menu\n";
                int choice = getValidIntegerInput("Please select an option (1-3): ");

            switch (choice) {
                case 1: {
                    // View all reservations
                    cout << "\nCurrent Reservations:\n";
                    bool hasReservations = false; // Flag to check if there are any reservations

                    for (const auto& customer : customers) {
                        const auto& reservations = customer->getReservationHistory();
                        if (!reservations.empty()) {
                            hasReservations = true; // Set flag to true if there are reservations
                            for (const auto& reservation : reservations) {
                                reservation->viewReservation(); // Display each reservation
                            }
                        }
                    }

                    if (!hasReservations) {
                        cout << "No Reservations to View." << endl; // Output message when there are no reservations
                    }
                    break;
                }
                case 2: {
                    // Cancel a reservation
                    string reservationId;
                    cout << "Enter Reservation ID to cancel (-1 to cancel action): ";
                    cin >> reservationId;

                    if (reservationId == "-1") {
                        cout << "Cancel action aborted." << endl;
                        break;
                    }

                    // Find the reservation in all customers' histories
                    bool found = false;
                    for (const auto& customer : customers) {
                        auto& reservations = customer->getReservationHistory();
                        auto it = find_if(reservations.begin(), reservations.end(),
                        [&reservationId](const shared_ptr<Reservation>& reservation) {
                            return reservation->getReservationId() == reservationId;
                        });

                        if (it != reservations.end()) {
                            (*it)->cancelReservation(); // Update status
                            customer->removeReservation(reservationId); // Remove from history
                            cout << "Reservation " << reservationId << " has been canceled." << endl;
                            found = true;
                            break; // Exit the loop after cancellation
                        }
                    }

                    if (!found) {
                        cout << "Reservation ID not found. Please try again." << endl;
                    }
                    break;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

        void manageTables(vector<Table>& tables) {
            while (true) {
                cout << "\nManage Tables Menu:\n";
                cout << "1. Add a Table\n";
                cout << "2. View All Tables\n";
                cout << "3. Back to Previous Menu\n";
                int choice = getValidIntegerInput("Please select an option (1-3): ");

            switch (choice) {
                case 1: {
                    // Add a Table
                    string tableId;
                    int tableNumber, seatingCapacity;

                    // Get Table ID
                    while (true) {
                        cout << "Enter Table ID (or -1 to cancel): ";
                        cin >> tableId;
                        if (tableId == "-1") {
                            cout << "Adding table canceled." << endl;
                            return; 
                        }
                        if (tableId.empty()) {
                            cout << "Table ID cannot be empty. Please try again." << endl;
                            continue;
                        }
                        break;
                    }

                    // Get Table Number
                    while (true) {
                        tableNumber = getValidIntegerInput("Enter Table Number: ");
                        if (tableNumber <= 0) {
                            cout << "Table Number must be a positive integer. Please try again." << endl;
                            continue;
                        }
                        break;
                    }

                    // Get Seating Capacity
                    while (true) {
                        seatingCapacity = getValidIntegerInput("Enter Seating Capacity: ");
                        if (seatingCapacity <= 0) {
                            cout << "Seating Capacity must be a positive integer. Please try again." << endl;
                            continue;
                        }
                        break;
                    }

                    // Create and add the new table
                    Table newTable(tableId, tableNumber, seatingCapacity);
                    tables.push_back(newTable);
                    cout << "Table " << tableNumber << " added successfully!" << endl;
                    break;
                }
                case 2: {
                    // View All Tables
                    if (tables.empty()) {
                        cout << "No tables available to display.\n";
                    } else {
                        cout << "\nAvailable Tables:\n";
                        for (const auto& table : tables) {
                            table.display();
                        }
                    }
                    break;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

bool isValidName(const string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;
}

bool isValidPhone(const string& phone) {
   return all_of(phone.begin(), phone.end(), ::isdigit) && phone.length() >= 10;
}

char getYesNoInput(const string& prompt) {
   char choice;
   while (true) {
       cout << prompt;
       cin >> choice;
       choice = tolower(choice);
       if (choice == 'y' || choice == 'n') {
           return choice;
       } else {
           cout << "Invalid input. Please enter 'y' or 'n'." << endl;
       }
   }
}

string getValidPhoneInput(const string& prompt) {
   string phone;
   while (true) {
       cout << prompt;
       cin >> phone;
       if (isValidPhone(phone)) {
           return phone;
       } else {
           cout << "Invalid phone number. Must be numeric and at least 10 digits." << endl;
       }
   }
}


bool isValidPassword(const string& password) {
   bool hasLetter = false;
   bool hasDigit = false;

   for (char c : password) {
       if (isalpha(c)) {
           hasLetter = true;
       } else if (isdigit(c)) {
           hasDigit = true;
       }
       if (hasLetter && hasDigit) {
           return true;
       }
   }
   return false;
}

string getValidPasswordInput(const string& prompt) {
   string password;
   while (true) {
       cout << prompt;
       cin >> password;
       if (isValidPassword(password)) {
           return password;
       } else {
            cout << "Invalid password. Password must contain at least one letter and one digit." << endl;
       }
   }
}

bool isValidString(const string& input) {
   if (input == "-1") return true;
   if (input.empty()) return false;
   for (char c : input) {
       if (!isalpha(c)) return false;
   }
   return true;
}

string getValidStringInput(const string& prompt) {
   string input;
   while (true) {
       cout << prompt;
       cin >> input;
       if (input == "-1") {
           return input;
       }
       if (isValidString(input)) {
           return input;
       } else {
           cout << "Invalid input. Please enter a valid string (letters only)." << endl;
       }
   }
}

bool confirmExit() {
   char choice;
   cout << "Are you sure you want to exit? (y/n): ";
   cin >> choice;
   return (choice == 'y' || choice == 'Y');
}

bool isValidAlphanumericString(const string& input) {
   if (input.empty()) return false;
   for (char c : input) {
       if (!isalnum(c)) return false;
   }
   return true;
}


string getValidAlphanumericStringInput(const string& prompt) {
   string input;
   while (true) {
       cout << prompt;
       cin >> input;
       if (isValidAlphanumericString(input)) {
           return input;
       } else {
           cout << "Invalid input. Please enter a valid alphanumeric string." << endl;
       }
   }
}

int main() {
  ReservationSystem* system = ReservationSystem::getInstance();
  system->showWelcomeMessage();

  vector<shared_ptr<RegisteredUsers>> customers; // Use shared_ptr for memory management
  vector<Staff> staffMembers;
  vector<Table> tables; // Declare a vector to hold Table objects

  while (true) {
      cout << "\nSystem Menu:" << endl;
      cout << "1. Login as Staff" << endl;
      cout << "2. Login as Customer" << endl;
      cout << "3. Exit" << endl;

      int choice = getValidIntegerInput("Please select an option (1 - 3): ");

      if (choice == 1) {
          string password;
          cout << "Enter Staff Password: ";
          cin >> password;

          if (password == "123") {
              Staff staff("1", "Admin", "admin@example.com", "1234567890", password, "Manager");
              while (true) {
                  cout << "\nStaff Menu:" << endl;
                  cout << "1. Manage Users" << endl;
                  cout << "2. Manage Tables" << endl;
                  cout << "3. Manage Reservations" << endl;
                  cout << "4. View Reports" << endl;
                  cout << "5. Logout" << endl;

                  int staffChoice = getValidIntegerInput("Please select an option (1-5): ");

                  switch (staffChoice) {
                      case 1:
                          staff.manageUsers(customers);
                          break;
                      case 2:
                          staff.manageTables(tables);
                          break;
                      case 3:
                          staff.manageReservations(customers, tables);
                          break;
                      case 4:
                          cout << "No Reports Available." << endl;
                          break;
                      case 5:
                          cout << "Logging out..." << endl;
                          goto backToMainMenu;
                      default:
                          cout << "Invalid choice." << endl;
                          break;
                  }
              }
          } else {
              cout << "Incorrect password." << endl;
          }
      } else if (choice == 2) {
          string email = getValidStringInput("Enter Email: ");
          auto it = find_if(customers.begin(), customers.end(), [&](const shared_ptr<RegisteredUsers>& user) {
              return user->getEmail() == email;
          });

          if (it != customers.end()) {
              string password;
              cout << "Enter Password: ";
              cin >> password;

              if (it->get()->getPassword() == password) {
                  RegisteredUsers& user = *it->get();
                  while (true) {
                      cout << "\nCustomer Menu:" << endl;
                      cout << "1. Create Profile" << endl;
                      cout << "2. Update Profile" << endl;
                      cout << "3. Make Reservation" << endl;
                      cout << "4. View Reservation History" << endl;
                      cout << "5. Cancel Reservation" << endl;
                      cout << "6. Make Payment" << endl;
                      cout << "7. Logout" << endl;

                      int customerChoice = getValidIntegerInput("Please select an option (1-7): ");

                      switch (customerChoice) {
                          case 1:
                              user.createProfile();
                              break;
                          case 2: {
                              user.updateProfile();
                              break;
                          }
                          case 3: {
                              user.makeReservation(nullptr, tables);
                              break;
                          }
                          case 4:
                              user.viewReservationHistory();
                              break;
                          case 5: {
                              user.cancelReservation();
                              break;
                          }
                          case 6: {
                              if (user.getReservationCount() > 0) { // Check if there are any reservations
                              float amount;
                              PaymentStrategy* paymentStrategy = nullptr; // Initialize payment strategy
                              user.makePayment(paymentStrategy, amount); // Call the updated method
                           } else {
                               cout << "No reservations found. Cannot make payment." << endl;
                           }
                           break;
                          }
                          case 7:
                              cout << "Logging out..." << endl;
                              goto backToMainMenu;
                          default:
                              cout << "Invalid choice." << endl;
                              break;
                      }
                  }
              } else {
                  cout << "Incorrect password." << endl;
              }
          } else {
              if (getYesNoInput("No account found. Would you like to create an account? (y/n): ") == 'y') {
                  string name = getValidStringInput("Enter Name: ");
                  string phone = getValidPhoneInput("Enter Phone #: ");
                  string newPassword = getValidPasswordInput("Enter Password: ");
                  customers.emplace_back(make_shared<RegisteredUsers>(to_string(customers.size() + 1), name, email, phone, newPassword));
                  cout << "Account created successfully!" << endl;

                  auto newUser_It = find_if(customers.begin(), customers.end(), [&](const shared_ptr<RegisteredUsers>& user) {
                      return user->getEmail() == email;
                  });

                  if (newUser_It != customers.end()) {
                      RegisteredUsers& user = *newUser_It->get();
                      while (true) {
                          cout << "\nCustomer Menu:" << endl;
                          cout << "1. Create Profile" << endl;
                          cout << "2. Update Profile" << endl;
                          cout << "3. Make Reservation" << endl;
                          cout << "4. View Reservation History" << endl;
                          cout << "5. Cancel Reservation" << endl;
                          cout << "6. Make Payment" << endl;
                          cout << "7. Logout" << endl;

                          int customerChoice = getValidIntegerInput("Please select an option (1 - 7): ");

                          switch (customerChoice) {
                              case 1:
                                  user.createProfile();
                                  break;
                              case 2: {
                                  user.updateProfile();
                              break;
                              }
                              case 3: {
                                  user.makeReservation(nullptr, tables);
                                  break;
                              }
                              case 4:
                                  user.viewReservationHistory();
                                  break;
                              case 5: {
                                  user.cancelReservation();
                                  break;
                              }
                              case 6: {
                                  if (user.getReservationCount() > 0) { // Check if there are any reservations
                                  float amount;
                                  PaymentStrategy* paymentStrategy = nullptr; // Initialize payment strategy
                                  user.makePayment(paymentStrategy, amount); // Call the updated method
                               } else {
                                   cout << "No reservations found. Cannot make payment." << endl;
                               }
                               break;
                              }
                              case 7:
                                  cout << "Logging out..." << endl;
                                  goto backToMainMenu;
                              default:
                                  cout << "Invalid choice." << endl;
                                  break;
                          }
                      }
                  }
              }
          }
      } else if (choice == 3) {
          if (confirmExit()) {
              cout << "Exiting the system..." << endl;
              break;
          }
      } else {
          cout << "Invalid choice. Please try again." << endl;
      }

      backToMainMenu:;
  }

  return 0;
}