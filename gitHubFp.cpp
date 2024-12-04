#include <iostream>
#include <string>
#include <vector>


using namespace std;

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

        // Virtual destructor for polymorphism
        virtual ~User() {}

        virtual void createProfile() {
            try {
                cout << "Creating profile...\n";

                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Email: ";
                getline(cin, email);

                if (email.find('@') == string::npos) {
                    throw invalid_argument("Invalid email format.");
            }
            cout << "Enter Phone Number: ";
            getline(cin, phone);

            cout << "Enter Password: ";
            getline(cin, password);

            cout << "Profile created successfully.\n";
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "n";
            }
        }

        virtual void updateProfile() {
            cout << "Updating profile...\n";
            cout << "Enter New Name (current : " << name << "): ";
            string newName;
            cin.ignore();
            getline(cin, newName);

            if(!newName.empty()) name = newName;

            cout << "Profile updated successfully!\n";
        }

        virtual void deleteProfile() {
            cout << "Deleting profile...\n";
            name = email = phone = password = "Deleted";
            cout << "Profile deleted successfully!\n";

        }
        // Getter for User ID (Encapsulation)
        string getUserId() const { return userId; }
};

class RegisteredUsers : public User {
    private:
        vector<Reservation*> reservationHistory;
        string name;
        string email;

    public:
        RegisteredUsers(string userId, string name, string email, string phone, string password)
            : User(userId, name, email, phone, password) {}

        string getName() const { return name; }
        string getEmail() const { return email; }

        void makeReservation() {
            cout << "Making reservation...\n";

            string reservationId;
            int day, month, year, hour, minute, numberOfGuests;

            cout << "Enter Reservation ID: ";
            cin >> reservationId;

            cout << "Enter Reservation Date (dd / mm / yyyy): ";
            cin >> day >> month >> year;

            cout << "Enter Reservation Time (hour/minute): ";
            cin >> hour >> minute;

            cout << "Enter Number of Guests: ";
            cin >> numberOfGuests;

            Date reservationDate(day, month, year);
            Time reservationTime(hour, minute);

            // For now, we'll pass null placeholders for customer and table
            Reservation* newReservation = new Reservation(reservationId, reservationDate, reservationTime, numberOfGuests, "Pending", this, nullptr);

            reservationHistory.push_back(newReservation);

            cout << "Reservation created successfully!\n";
        }

        void updateReservation() {
            cout << "Updating a reservation...\n";

            string reservationId;
            cout << "Enter Reservation ID to update: ";
            cin >> reservationId;

            for(auto res : reservationHistory) {
                if(res->getReservationId() == reservationId) {
                    int newGuests;
                    cout << "Enter updated number of guests: ";
                    cin >> newGuests;
                    res->setNumberOfGuest(newGuests);
                    cout << "Reservation updated successfully!\n";
                    return;
                }
            }

            cout << "Reservation not found!\n";
        }

        void cancelReservation() {
            cout << "Canceling a reservation...\n";

            string reservationId;
            cout << "Enter Reservation ID to cancel: ";
            cin >> reservationId;

            for(auto it = reservationHistory.begin(); it != reservationHistory.end(); ++it) {
                if((*it)->getReservationId() == reservationId) {
                    delete *it;
                    reservationHistory.erase(it);
                    cout << "Reservation canceled successfully!\n";
                    return;
                }
            }

           cout << "Reservation not found!\n";
        }

        void viewReservationHistory() {
            if(reservationHistory.empty()) {
                cout << "No reservations found!\n";
                return;
            }

            cout << "Reservation History:\n";
            for(const auto& res : reservationHistory) {
                res->display();
            }
        }

        void makePayment() {
            cout << "Processing payment...\n";

            string paymentId;
            float amount;

            cout << "Enter Payment ID: ";
            cin >> paymentId;

            cout << "Enter Amount: ";
            cin >> amount;

            Payment* payment = new Payment(paymentId, amount, "Completed", nullptr, this);

            cout << "Payment of " << amount << "processed successfully!\n";
        }

        void viewPaymentDetails() {
            cout << "Viewing payment details...\n";

            // Assuming payment details would be linked to reservation/payment history
            cout << "Feature not fully implemented yet.\n";
        }
};

class Staff : public User {
    private:
        string role;

    public:
        Staff(string userId, string name, string email, string phone, string password, string role)
            : User(userId, name, email, phone, password), role(role) {}

        void manageUsers(vector<RegisteredUsers>& registeredUsers) {
            cout << "Managing users...\n";
            string userId;
            cout << "Enter User ID to view or delete: ";
            cin >> userId;

            for(auto& user : registeredUsers) {
                if(user.getUserId() == userId) {
                    cout << "User found: " << user.getName() << endl;

                    char choice;
                    cout << "Do you want to delete this user? (y/n): ";
                    cin >> choice;

                    if(choice == 'y' || choice == 'Y') {
                        registeredUsers.erase(remove(registeredUsers.begin(), registeredUsers.end(), user), registeredUsers.end());
                        cout << "User deleted successfully!\n";
                    }
                    return;
                }
            }
            cout << "User not found.\n";
        }

        void manageReservations(vector<Reservation*>& reservationHistory) {
            cout << "Managing reservations...\n";
            string reservationId;
            cout << "Enter Reservation ID manage: ";
            cin >> reservationId;
        
            for(auto& reservation : reservationHistory) {
                if(reservation->getReservationId() == reservationId) {
                    cout << "Reservation found: ";
                    reservation->display();

                    char choice;
                    cout << "Do you want to cancel this reservation? (y/n): ";
                    cin >> choice;

                    if(choice == 'y' || choice == 'Y') {
                        delete reservation;
                        reservationHistory.erase(remove(reservationHistory.begin(), reservationHistory.end(), reservation), reservationHistory.end());
                        cout << "Reservation cancelled successfully!\n";
                    }
                    return;
                }
            }
            cout << "Reservation not found.\n";
        }

        void manageTables(vector<Table>& tables) {
            cout << "Managing tables...\n";
            int choice;
            cout << "1. Add Table\n2. Update Table status\n3. Delete Table\nEnter choice: ";
            cin >> choice;

            if(choice == 1) {
                string tableId;
                int tableNumber, seatingCapacity;
                string status;

                cout << "Enter Table ID: ";
                cin >> tableId;

                cout << "Enter Table Number: ";
                cin >> tableNumber;

                cout << "Enter Seating Capacity: ";
                cin >> seatingCapacity;

                cout << "Enter Table Status (Available/ Reserved): ";
                cin >> status;

                Table::addTable(tables, tableId, tableNumber, seatingCapacity, status);
            } else if(choice == 2) {
                string tableId, newStatus;
                cout << "Enter Table ID to update: ";
                cin >> tableId;

                cout << "Enter new Table Status (Available/ Reserved): ";
                cin >> newStatus;

                for(auto& table : tables) {
                    if(table.getTableId() == tableId) {
                        table.updateTableStatus(newStatus);
                        cout << "Table status updated successfully!\n";
                        return;
                }
            }
            cout << "Table not found.\n";
        } else if(choice == 3) {
            string tableId;
            cout << "Enter Table ID to delete: ";
            cin >> tableId;
            Table::deleteTable(tables, tableId);
        } else {
            cout << "Invalid choice.\n";
        }
    }

        void processPayment(vector<Payment*>& paymentHistory) {
            cout << "Processing payment...\n";
            string paymentId;
            float amount;

            cout << "Enter Payment ID: ";
            cin >> paymentId;

            cout << "Enter Amount: ";
            cin >> amount;

            Payment* payment = new Payment(paymentId, amount, "Completed", nullptr, nullptr);
            paymentHistory.push_back(payment);

            cout << "Payment processed successfully.\n";
        }

        void confirmPayment(vector<Payment*>& paymentHistory) {
            cout << "Confirming payment...\n";
            string paymentId;

            cout << "Enter Payment ID to confirm: ";
            cin >> paymentId;

            for(auto& payment : paymentHistory) {
                if(payment->getPaymentId() == paymentId) {
                    payment->updateStatus("Confirmed");
                    cout << "Payment confirmed!\n";
                    return;
                }
            }

            cout << "Payment not found.\n";
        }

        void viewReports() {
            cout << "Viewing reports...\n";
            cout << "Report: Reservation and Payment Summary\n";
            cout << "Total Reservations: 50\n" << endl;
            cout << "Total Payments Processed: 45\n";
            cout << "Pending Reservations: 5\n";
            cout << "Report generated successfully.\n";
        }
};

class Date {        // to apply date: Date in Reservation
    private:
        int day;
        int month;
        int year;

    public:
        Date(int day, int month, int year)
            : day(day), month(month), year(year) {}

        void display() {
            cout << day << "/" << month << "/" << year << endl;
        }
};

class Time {        // to apply time: Time in Reservation
    private:
        int hour;
        int minute;

    public:
        Time(int hour, int minute)
            : hour(hour), minute(minute) {}

        void display() {
            cout << hour << ":" << minute << endl;
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

        void setNumberOfGuest(int guests) {
            numberOfGuests = guests;
        }

        void display() {
            cout << "Reservation Details: \n";
            cout << "Number of guests: " << numberOfGuests << endl;
        }

        void createReservation() {
            cout << "Creating reservation...\n";
            cout << "Reservation ID: " << reservationId << endl;
            cout << "Date: "; date.display();
            cout << "Time: "; time.display();
            cout << "Number of Guests: " << numberOfGuests << endl;
            cout << "Reservation Status: " << status << endl;

            status = "Confirmed";
            cout << "Reservation created successfully! Status: " << status << endl;
        }

        void updateReservation() {
            cout << "Updating reservation...\n";

            cout << "Enter new number of guests: ";
            cin >> numberOfGuests;

            cout << "Enter new reservation status (e.g., 'Confirmed', 'Pending', 'Cancelled'): ";
            cin >> status;

            cout << "Reservation updated successfully!";
        }

        void cancelReservation() {
            cout << "Canceling reservation...\n";
            status = "Cancelled";
            cout << "Reservation canceled successfully!\n";
        }

        string getReservationId() const { return reservationId; }
        Date getDate() const { return date; }
        Time getTime() const { return time; }
        int getNumberOfGuests() const { return numberOfGuests; }
        string getStatus() const { return status; }
        RegisteredUsers* getCustomer() const { return customer; }
        Table* getTable() const { return table; }

        void setStatus(const string& newStatus) { status = newStatus; }
};

class Table {
    private:
        string tableId;
        int tableNumber;
        int seatingCapacity;
        string status;

    public:
        Table(string tableId, int tableNumber, int seatingCapacity, string status)
            : tableId(tableId), tableNumber(tableNumber), seatingCapacity(seatingCapacity), status(status) {}

        string getTableId() const { return tableId; }
        int getTableNumber() const { return tableNumber; }
        int getSeatingCapacity() const { return seatingCapacity; }
        string getStatus() const { return status; }

        void setStatus(const string& newStatus) { status = newStatus; }

        // Add a new table (static for demo purposes)
        static void addTable(vector<Table>& tables, string tableId, int tableNumber, int seatingCapacity, string status) {
            Table newTable(tableId, tableNumber, seatingCapacity, status);
            tables.push_back(newTable);
            cout << "Table added successfully!\n";
        }

        // Update table status
        void updateTableStatus(const string& newStatus) {
            status = newStatus;
            cout << "Table status updated to " << status << "!\n";
        }

        // Delete a table (static for demo purposes)
        static void deleteTable(vector<Table>& tables, const string& tableId) {
        for (vector<Table>::iterator it = tables.begin(); it != tables.end(); ++it) {
            if (it->getTableId() == tableId) {
                tables.erase(it);
                cout << "Table with ID " << tableId << " deleted successfully!\n";
                return;
            }
        }
        cout << "Table with ID " << tableId << " not found.\n";
    }

    // Display table details
    void display() const {
        cout << "Table ID: " << tableId
             << ", Table Number: " << tableNumber
             << ", Seating Capacity: " << seatingCapacity
             << ", Status: " << status << endl;
    }
};

class Payment {
    private:
        string paymentId;
        float amount;
        string paymentStatus;
        Reservation* reservation;
        RegisteredUsers* customer;
        string status;

    public:
        Payment(string paymentId, float amount, string paymentStatus, Reservation* reservation, RegisteredUsers* customer)
            : paymentId(paymentId), amount(amount), paymentStatus(paymentStatus), reservation(reservation), customer(customer) {}

        void updateStatus(const string & newStatus) { status = newStatus; }

        void processPayment() {
            cout << "Processing payment...\n";
            cout << "Payment ID: " << paymentId << endl;
            cout << "Amount: " << amount << endl;

            paymentStatus = "Completed";
            cout << "Payment processed successfully! Status: " << paymentStatus << endl;
        }

        void updatePaymentStatus() {
            if(paymentStatus == "Pending"){
                paymentStatus = "Completed";
                cout << "Payment status updated to Completed.\n";
            } else {
                cout << "Payment is already completed.\n";
            }
        }

        void viewPaymentHistory() const {
            cout << "Payment History:\n";
            cout << "Payment ID: " << paymentId << endl;
            cout << "Amount: " << amount << endl;
            cout << "Payment Status: " << paymentStatus << endl;

            if(reservation != nullptr) {
                cout << "Reservation ID: " << reservation->getReservationId() << endl;
            } else {
                cout << "No associated reservation.\n";
            }

            if(customer != nullptr) {
                cout << "Customer: " << customer->getName() << endl;
            } else {
                cout << "No associated customer.\n";
            }
        }

        string getPaymentId() const { return paymentId; }
        float getAmount() const { return amount; }
        string getPaymentStatus() const { return paymentStatus; }
        Reservation* getReservation() const { return reservation; }
        RegisteredUsers* getCustomer() const { return customer; }

        void setPaymentStatus(const string& status) { paymentStatus = status; }
};

vector<RegisteredUsers> customers;
vector<Staff> staffMembers;
vector<Reservation*> reservations;
vector<Table> tables;
vector<Payment*> payments;

// Global admin password for demonstration
const string STAFF_PASSWORD = "admin123";

void mainMenu();
void staffMenu(Staff&);
void customerMenu(RegisteredUsers&);

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;

    while(true) {
        cout << "\n=== System Menu ===\n";
        cout << "1. Login as Staff\n";
        cout << "2. Login as Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1) {
            string password;
            cout << "Enter Staff Password: ";
            cin >> password;

            if(password == STAFF_PASSWORD) {
                cout << "Access granted. Welcome, Staff!\n";
                Staff dummyStaff("S001", "Admin", "admin@system.com", "1234567890", "admin123", "Admin");
                staffMenu(dummyStaff);
            } else {
                cout << "Invalid password. Access denied.\n";
            }
        } else if(choice == 2) {
            string email;
            cout << "Enter your email to log in (or type 'register' to create a new account): ";
            cin >> email;


            if(email == "register") {
                string userId, name, phone, password;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Phone Number: ";
                getline(cin,phone);

                cout << "Enter Password: ";
                getline(cin, password);

                userId = "C" + to_string(customers.size() + 1);
                RegisteredUsers newCustomer(userId, name, email, phone, password);
                customers.push_back(newCustomer);
                cout << "Account created successfully! Your User ID is " << userId << ".\n";

                customerMenu(newCustomer);
            } else {
                bool found = false;
                for(auto& customer : customers) {
                    if(customer.getUserId() == email || customer.getEmail() == email) {
                        cout << "Welcome back, " << customer.getName() << "!\n";
                        customerMenu(customer);
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    cout << "Account not found. Please register.\n";
                }
            }
        } else if (choice == 3) {
            cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void staffMenu(Staff& staff) {
    int choice;
    while (true) {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Manage Users\n";
        cout << "2. Manage Reservations\n";
        cout << "3. Manage Tables\n";
        cout << "4. Process Payments\n";
        cout << "5. View Reports\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            staff.manageUsers(customers);
            break;
        case 2:
            staff.manageReservations(reservations);
            break;
        case 3:
            staff.manageTables(tables);
            break;
        case 4:
            staff.processPayment(payments);
            break;
        case 5:
            staff.viewReports();
            break;
        case 6:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void customerMenu(RegisteredUsers& customer) {
    int choice;
    while (true) {
        cout << "\n=== Customer Menu ===\n";
        cout << "1. Customize Profile\n";
        cout << "2. Manage Reservations\n";
        cout << "3. Manage Payments\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            customer.updateProfile();
            break;
        case 2:
            int resChoice;
            cout << "\n1. Create Reservation\n2. Update Reservation\n3. Cancel Reservation\n4. View Reservation History\nEnter choice: ";
            cin >> resChoice;
            if (resChoice == 1) customer.makeReservation();
            else if (resChoice == 2) customer.updateReservation();
            else if (resChoice == 3) customer.cancelReservation();
            else if (resChoice == 4) customer.viewReservationHistory();
            else cout << "Invalid choice.\n";
            break;
        case 3:
            int payChoice;
            cout << "\n1. Make Payment\n2. View Payment Details\nEnter choice: ";
            cin >> payChoice;
            if (payChoice == 1) customer.makePayment();
            else if (payChoice == 2) customer.viewPaymentDetails();
            else cout << "Invalid choice.\n";
            break;
        case 4:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
