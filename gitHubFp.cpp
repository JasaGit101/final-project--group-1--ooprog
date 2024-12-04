#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <cctype>
#include <limits>

using namespace std;

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
        cout << "Table ID: " << tableId << ", Number: " << tableNumber
             << ", Capacity: " << seatingCapacity << ", Status: " << status << endl;
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

// Abstract class for Payment Strategy
class PaymentStrategy {
public:
    virtual void processPayment(float amount) = 0; // Pure virtual function
};

// Concrete class for Credit Card Payment
class CreditCardPayment : public PaymentStrategy {
public:
    void processPayment(float amount) override {
        cout << "Processing credit card payment of $" << fixed << setprecision(2) << amount << endl;
    }
};

// Concrete class for PayPal Payment
class PayPalPayment : public PaymentStrategy {
public:
    void processPayment(float amount) override {
        cout << "Processing PayPal payment of $" << fixed << setprecision(2) << amount << endl;
    }
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2023) {
            throw invalid_argument("Invalid date provided.");
        }
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
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            throw invalid_argument("Invalid time provided.");
        }
    }

    void display() const {
        cout << hour << ":" << (minute < 10 ? "0" : "") << minute;
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
        cout << "Reservation " << reservationId << " has been canceled." << endl;
    }

    void viewReservation() const {
        cout << "Reservation ID: " << reservationId << ", Guests: " << numberOfGuests << ", Status: " << status << endl;
        cout << "Date: "; date.display(); cout << ", Time: "; time.display(); cout << endl;
    }

    string getStatus() const {
        return status;
    }
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

public:
    RegisteredUsers(string userId, string name, string email, string phone, string password)
        : User(userId, name, email, phone, password) {}

   void makeReservation(shared_ptr<Reservation> reservation, vector<Table>& tables) {
    // Show available tables
    cout << "\nAvailable Tables:\n";
    for (const auto& table : tables) {
        if (table.getStatus() == "Available") {
            table.display();
        }
    }

    // Let user choose a table
    string tableId;
    cout << "\nEnter the Table ID to reserve: ";
    cin >> tableId;

    bool tableFound = false;
    for (auto& table : tables) {
        if (table.getId() == tableId && table.getStatus() == "Available") {
            table.updateTableStatus("Reserved");
            tableFound = true;
            break;
        }
    }

    if (tableFound) {
        reservationHistory.push_back(reservation);
        reservation->createReservation();
        cout << "Reservation made successfully for Table ID: " << tableId << endl;
    } else {
        cout << "Invalid Table ID or Table is already reserved.\n";
    }
}

    void cancelReservation(int index) {
        if (index >= 0 && index < reservationHistory.size()) {
            reservationHistory[index]->cancelReservation();
            reservationHistory.erase(reservationHistory.begin() + index);
            cout << "Reservation canceled for " << getName() << endl; // Use getter
        } else {
            cout << "Invalid reservation index." << endl;
        }
    }

    void viewReservationHistory() const {
        cout << "Reservation history for " << getName() << ":" << endl; // Use getter
        for (const auto& reservation : reservationHistory) {
            reservation->viewReservation();
        }
    }

    void makePayment(PaymentStrategy* paymentStrategy, float amount) {
        paymentStrategy->processPayment(amount);
        cout << "Payment made by " << getName() << endl; // Use getter
    }
};

class Staff : public User {
private:
    string role;

public:
    Staff(string userId, string name, string email, string phone, string password, string role)
        : User(userId, name, email, phone, password), role(role) {}

    void manageUsers() {
        cout << "Managing users as " << role << endl;
    }

    void manageReservations() {
        cout << "Managing reservations as " << role << endl;
    }

    void manageTables(vector<Table>& tables) {
        cout << "Managing tables as " << role << endl;

        string tableId;
        int tableNumber, seatingCapacity;
        cout << "Enter Table ID: ";
        cin >> tableId;
        cout << "Enter Table Number: ";
        cin >> tableNumber;
        cout << "Enter Seating Capacity: ";
        cin >> seatingCapacity;

        Table newTable(tableId, tableNumber, seatingCapacity);
        tables.push_back(newTable);
        cout << "Table " << tableNumber << " added successfully!" << endl;
    }
};

class Payment {
private:
    string paymentId;
    float amount;
    string paymentStatus;
    shared_ptr<Reservation> reservation; // Use shared_ptr for memory management
    RegisteredUsers* customer;

public:
    Payment(string paymentId, float amount, string paymentStatus, shared_ptr<Reservation> reservation, RegisteredUsers* customer)
        : paymentId(paymentId), amount(amount), paymentStatus(paymentStatus), reservation(reservation), customer(customer) {}

    void processPayment() {
        paymentStatus = "Processed";
        cout << "Payment of " << fixed << setprecision(2) << amount << " processed for " << customer->getName() << endl; // Use getter
    }

    void viewPaymentHistory() const {
        cout << "Payment history for " << customer->getName() << ": " << paymentId << " - " << fixed << setprecision(2) << amount << " - " << paymentStatus << endl; // Use getter
    }
};

bool isValidPhone(const string& phone) {
    return all_of(phone.begin(), phone.end(), ::isdigit) && phone.length() >= 10;
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
        if (isValidString(input)) {
            return input;
        } else {
            cout << "Invalid input. Please enter a valid string (letters only)." << endl;
        }
    }
}

bool confirmExit();
char getYesNoInput(const string& prompt);

char getYesNoInput(const string& prompt) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'y' || choice == 'n') {
            return choice;
        } else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
        }
    }
}

bool confirmExit() {
    return getYesNoInput("Are you sure you want to exit? (y/n): ") == 'y';
}

bool isValidIntegerInput(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    return !input.empty();
}

int getValidIntegerInput(const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
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

            if (password == "staffpassword") {
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
                        case 1: staff.manageUsers(); break;
                        case 2: staff.manageTables(tables); break;
                        case 3: staff.manageReservations(); break;
                        case 4: cout << "Viewing reports..." << endl; break;
                        case 5: cout << "Logging out..." << endl; return 0;
                        default: cout << "Invalid choice." << endl; break;
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
                            case 1: user.createProfile(); 
                                break;
                            case 2: {
                                string newName = getValidStringInput("Enter new Name: ");
                                string newEmail = getValidStringInput("Enter new Email: ");
                                string newPhone = getValidPhoneInput(" Enter new Phone: ");
                                user.updateProfile(newName, newEmail, newPhone);
                                break;
                            }
                            case 3: {
                                string reservationId = getValidStringInput("Enter Reservation ID: ");
                                int day, month, year, hour, minute, numberOfGuests;
                                cout << "Enter Date (day month year): ";
                                cin >> day >> month >> year;
                                cout << "Enter Time (hour minute): ";
                                cin >> hour >> minute;
                                numberOfGuests = getValidIntegerInput("Enter Number of Guests: ");

                                try {
                                    Date date(day, month, year);
                                    Time time(hour, minute);
                                    auto newReservation = make_shared<Reservation>(reservationId, date, time, numberOfGuests, "Confirmed", &user, nullptr);
                                    user.makeReservation(newReservation, tables);
                                } catch (const invalid_argument& e) {
                                    cout << e.what() << endl;
                                }
                                break;
                            }
                            case 4: 
                                user.viewReservationHistory(); 
                                break;
                            case 5: {
                                int index = getValidIntegerInput("Enter reservation index to cancel: ");
                                user.cancelReservation(index);
                                break;
                            }
                            case 6: {
                                float amount;
                                cout << "Enter payment amount: ";
                                cin >> amount;
                                PaymentStrategy* paymentStrategy = new CreditCardPayment();
                                user.makePayment(paymentStrategy, amount);
                                delete paymentStrategy;
                                break;
                            }
                            case 7: 
                                cout << "Logging out..." << endl; 
                                return 0;
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
                    string phone = getValidPhoneInput("Enter Phone: ");
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
                                case 1: user.createProfile(); 
                                    break;
                                case 2: {
                                    string newName = getValidStringInput("Enter new Name: ");
                                    string newEmail = getValidStringInput("Enter new Email: ");
                                    string newPhone = getValidPhoneInput("Enter new Phone: ");
                                    user.updateProfile(newName, newEmail, newPhone);
                                    break;
                                }
                                case 3: {
                                    string reservationId = getValidStringInput("Enter Reservation ID: ");
                                    int day, month, year, hour, minute, numberOfGuests;
                                    cout << "Enter Date (day month year): ";
                                    cin >> day >> month >> year;
                                    cout << "Enter Time (hour minute): ";
                                    cin >> hour >> minute;
                                    numberOfGuests = getValidIntegerInput("Enter Number of Guests: ");

                                    try {
                                        Date date(day, month, year);
                                        Time time(hour, minute);
                                        auto newReservation = make_shared<Reservation>(reservationId, date, time, numberOfGuests, "Confirmed", &user, nullptr);
                                        user.makeReservation(newReservation, tables);
                                    } catch (const invalid_argument& e) {
                                        cout << e.what() << endl;
                                    }
                                    break;
                                }
                                case 4: 
                                    user.viewReservationHistory(); 
                                    break;
                                case 5: {
                                    int index = getValidIntegerInput("Enter reservation index to cancel: ");
                                    user.cancelReservation(index);
                                    break;
                                }
                                case 6: {
                                    float amount;
                                    cout << "Enter payment amount: ";
                                    cin >> amount;
                                    PaymentStrategy* paymentStrategy = new CreditCardPayment();
                                    user.makePayment(paymentStrategy, amount);
                                    delete paymentStrategy;
                                    break;
                                }
                                case 7: 
                                    cout << "Logging out..." << endl; 
                                    return 0;
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
    }

    return 0;
}