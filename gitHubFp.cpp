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

        void createProfile() {

        }

        void updateProfile() {

        }

        void deleteProfile() {

        }
};

class RegisteredUsers : public User {
    private:
        vector<Reservation*> reservationHistory;

    public:
        RegisteredUsers(string userId, string name, string email, string phone, string password)
            : User(userId, name, email, phone, password) {}

        void makeReservation() {

        }

        void updateReservation() {

        }

        void cancelReservation() {

        }

        void viewReservationHistory() {

        }

        void makePayment() {

        }

        void viewPaymentDetails() {

        }
};

class Staff : public User {
    private:
        string role;

    public:
        Staff(string userId, string name, string email, string phone, string password, string role)
            : User(userId, name, email, phone, password), role(role) {}

        void manageUsers() {

        }

        void manageReservations() {
        
        }

        void manageTables() {

        }

        void processPayment() {

        }

        void confirmPayment() {

        }

        void viewReports() {

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

        void createReservation() {

        }

        void updateReservation() {

        }

        void cancelReservation() {
        
        }
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

        void addTable() {

        }

        void updateTableStatus() {

        }

        void deleteTable() {

        }
};

class Payment {
    private:
        string paymentId;
        float amount;
        string paymentStatus;
        Reservation* reservation;
        RegisteredUsers* customer;

    public:
        Payment(string paymentId, float amount, string paymentStatus, Reservation* reservation, RegisteredUsers* customer)
            : paymentId(paymentId), amount(amount), paymentStatus(paymentStatus), reservation(reservation), customer(customer) {}

        void processPayment() {

        }

        void updatePaymentStatus() {
        
        }

        void viewPaymentHistory() {

        }
};

int main() {
    
}