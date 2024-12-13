#include <iostream>
#include <cstring>
#include <cctype>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <limits>


class InvalidInput : std::exception {
    private:
    char* __message;

    public:
    InvalidInput(const char* message) {
        __message = new char[strlen(message) + 1];
    }
    ~InvalidInput() {
        delete[] __message;
    }

    const char* what() const noexcept override {
        return __message;
    }
};


class Order {
private:
    char* _client_name;
    char* _driver_name;
    int _duration;
    char* _pick_up_point;
    char* _arrival_point;
    float _cost;
    char* _status;

public:

    Order():_duration(0), _pick_up_point(nullptr),
      _arrival_point(nullptr), _cost(0), _status(nullptr) , _client_name(nullptr), _driver_name(nullptr){}

    Order(char* status, char* pick_up_point, char* arrival_point, char* driver, char* client) : _cost(0){

        _pick_up_point = new char[strlen(pick_up_point) + 1];
        strcpy(_pick_up_point, pick_up_point);

        _arrival_point = new char[strlen(arrival_point) + 1];
        strcpy(_arrival_point, arrival_point);

        _status = new char[strlen(status) + 1];
        strcpy(_status, status);

        _client_name = new char[strlen(client) + 1];
        strcpy(_client_name, client);

        _driver_name = new char[strlen(driver) + 1];
        strcpy(_driver_name, driver);

        srand(time(NULL));
        _duration = (rand() % 60) + 5;

    }
    ~Order() {
        delete[] _pick_up_point;
        delete[] _arrival_point;
        delete[] _status;
        delete[] _client_name;
        delete[] _driver_name;
    }

    void set_cost(float rating) {
        _cost = (rating == 0.0) ? 7.5 : ((_duration + 2*rating)/2);
    }

    void setStatus(char* status) {
        delete[] _status;
        _status = new char[strlen(status) + 1];
        strcpy(_status, status);
        std::cout<<"Status changed: "<<_status<<std::endl;
    }
    void setPickUpPoint(char* pick_up_point) {
        delete[] _pick_up_point;
        _pick_up_point = new char[strlen(pick_up_point) + 1];
        strcpy(_pick_up_point, pick_up_point);
    }
    void setArrivalPoint(char* arrival_point) {
        delete[] _arrival_point;
        _arrival_point = new char[strlen(arrival_point) + 1];
        strcpy(_arrival_point, arrival_point);
    }

    void setDriverName(char* driver) {
        delete[] _driver_name;
        _driver_name = new char[strlen(driver) + 1];
        strcpy(_driver_name, driver);
    }

    void setClientName(char* client_name) {
        delete[] _client_name;
        _client_name = new char[strlen(client_name) + 1];
        strcpy(_client_name, client_name);
    }


    char* getStatus() {
        return _status;
    }
    char* getPickUpPoint() {
        return _pick_up_point;
    }
    char* getArrivalPoint() {
        return _arrival_point;
    }

    int getDuration() {
        return _duration;
    }

    float getCost() {
        return _cost;
    }

    char* getClientName() {
        return _client_name;
    }

    char* getDriverName() {
        return _driver_name;
    }


    void saveToFile(std::ofstream& out) const {
        size_t length;

        // Save client name
        length = strlen(_client_name);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_client_name, length);

        // Save driver name
        length = strlen(_driver_name);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_driver_name, length);

        // Save duration and cost
        out.write(reinterpret_cast<const char*>(&_duration), sizeof(_duration));
        out.write(reinterpret_cast<const char*>(&_cost), sizeof(_cost));

        // Save pickup point
        length = strlen(_pick_up_point);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_pick_up_point, length);

        // Save arrival point
        length = strlen(_arrival_point);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_arrival_point, length);

        // Save status
        length = strlen(_status);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_status, length);
    }

    void loadFromFile(std::ifstream& in) {
        size_t length;

        // Load client name
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _client_name = new char[length + 1];
        in.read(_client_name, length);
        _client_name[length] = '\0';

        // Load driver name
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _driver_name = new char[length + 1];
        in.read(_driver_name, length);
        _driver_name[length] = '\0';

        // Load duration and cost
        in.read(reinterpret_cast<char*>(&_duration), sizeof(_duration));
        in.read(reinterpret_cast<char*>(&_cost), sizeof(_cost));

        // Load pickup point
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _pick_up_point = new char[length + 1];
        in.read(_pick_up_point, length);
        _pick_up_point[length] = '\0';

        // Load arrival point
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _arrival_point = new char[length + 1];
        in.read(_arrival_point, length);
        _arrival_point[length] = '\0';

        // Load status
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _status = new char[length + 1];
        in.read(_status, length);
        _status[length] = '\0';
    }
};


int displayOrderDetails(Order* order) {
    if(strcmp(order->getStatus(),"In Process") == 0) {
        return 1;
    }
    else return 0;
}
bool isPhoneNumberValid(const char* phone_number) {
    for (int i = 0; phone_number[i] != '\0'; ++i) {
        if (!std::isdigit(phone_number[i])) {
            return false;
        }
    }
    return true;
}

class Car {
private:
    char* _car_brand;
    char* _car_model;
    char* _plates;
    int _year;
    int _mileage;
    char* _status;

public:
    Car(const char* car_brand, const char* car_model,const char* plates, int year, int mileage)
        : _year(year), _mileage(mileage) {
        _car_brand = new char[strlen(car_brand) + 1];
        strcpy(_car_brand, car_brand);

        _car_model = new char[strlen(car_model) + 1];
        strcpy(_car_model, car_model);

        _plates = new char[strlen(plates) + 1];
        strcpy(_plates, plates);

        _status = new char[10];
        if(_year > 2020 && _mileage < 100000) {
            strcpy(_status,"Perfect");
        }
        else if(_year < 2020 && _mileage < 100000) {
            strcpy(_status,"Good");
        }
        else if(_year < 2000 && _mileage > 200000) {
            strcpy(_status,"Bad");
        }
        else {
            strcpy(_status,"Undetermined");
        }
    }

    Car():_car_brand(nullptr),_car_model(nullptr),_year(0),_mileage(0),_status(nullptr){};

    ~Car() {
        delete[] _car_brand;
        delete[] _car_model;
        delete [] _plates;
        delete[] _status;
    }

    void setCarBrand(const char* car_brand) {
        delete[] _car_brand;
        _car_brand = new char[strlen(car_brand) + 1];
        strcpy(_car_brand, car_brand);
    }

    void setCarModel(const char* car_model) {
        delete[] _car_model;
        _car_model = new char[strlen(car_model) + 1];
        strcpy(_car_model, car_model);
    }

    void setPlates(const char* plates) {
        delete[] _plates;
        _plates = new char[strlen(plates) + 1];
        strcpy(_plates, plates);
    }

    void setYear(int year) {
        _year = year;
    }

    void setMileage(int mileage) {
        _mileage = mileage;
    }

    void setStatus(const char* status) {
        delete[] _status;
        _status = new char[strlen(status) + 1];
        strcpy(_status, status);
    }

    char* getCarBrand() const {
        return _car_brand;
    }

    char* getCarModel() const {
        return _car_model;
    }

    char* getPlates() const {
        return _plates;
    }

    int getYear() const {
        return _year;
    }

    int getMileage() const {
        return _mileage;
    }

    char* getStatus() const {
        return _status;
    }

        void saveToFile(std::ofstream& out) const {
        size_t length;

        // Save car brand
        length = strlen(_car_brand);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_car_brand, length);

        // Save car model
        length = strlen(_car_model);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_car_model, length);

        // Save plates
        length = strlen(_plates);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_plates, length);

        // Save year and mileage
        out.write(reinterpret_cast<const char*>(&_year), sizeof(_year));
        out.write(reinterpret_cast<const char*>(&_mileage), sizeof(_mileage));

        // Save status
        length = strlen(_status);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_status, length);
    }

    void loadFromFile(std::ifstream& in) {
        size_t length;

        // Load car brand
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _car_brand = new char[length + 1];
        in.read(_car_brand, length);
        _car_brand[length] = '\0';

        // Load car model
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _car_model = new char[length + 1];
        in.read(_car_model, length);
        _car_model[length] = '\0';

        // Load plates
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _plates = new char[length + 1];
        in.read(_plates, length);
        _plates[length] = '\0';

        // Load year and mileage
        in.read(reinterpret_cast<char*>(&_year), sizeof(_year));
        in.read(reinterpret_cast<char*>(&_mileage), sizeof(_mileage));

        // Load status
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _status = new char[length + 1];
        in.read(_status, length);
        _status[length] = '\0';
    }
};

class Person {
protected:
    char* _name;
    char* _surname;
    int _age;
    char* _phone_number;

public:
    Person(const char* name, const char* surname, int age, const char* phone_number)
        : _age(age) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);

        _surname = new char[strlen(surname) + 1];
        strcpy(_surname, surname);

        _phone_number = new char[strlen(phone_number) + 1];
        strcpy(_phone_number, phone_number);
    }

    virtual ~Person() {
        delete[] _surname;
        delete[] _phone_number;
        delete[] _name;
    }

    virtual void setName(const char* name) {
        delete[] _name;
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    }

    virtual void setSurname(const char* surname) {
        delete[] _surname;
        _surname = new char[strlen(surname) + 1];
        strcpy(_surname, surname);
    }

    virtual void setAge(int age) {
        _age = age;
    }

    virtual void setPhoneNumber(const char* phone_number) {
        delete[] _phone_number;
        _phone_number = new char[strlen(phone_number) + 1];
        strcpy(_phone_number, phone_number);
    }

    virtual char* getName() const {
        return _name;
    }

    virtual char* getSurname() const {
        return _surname;
    }

    virtual int getAge() const {
        return _age;
    }

    virtual char* getPhoneNumber() const {
        return _phone_number;
    }
};

class Driver : public Person {
private:
    Car* _car;
    float _rating;
    char* _license;
    char* _login;
    char* _password;

    Order** _orders;
    int _order_max;
    int _orders_completed;

private:
    void generate_random_string(char* str, int length) {
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int charset_size = sizeof(charset) - 1;

        for (int i = 0; i < length; ++i) {
            str[i] = charset[rand() % charset_size];
        }
        str[length] = '\0';
    }

public:
    Driver() : Person("", "", 0, ""), _car(nullptr), _rating(0.0), _license(nullptr), _orders_completed(0), _login(nullptr), _password(nullptr), _orders(nullptr), _order_max(0) {}

    Driver(Car& car, char* name, char* surname, int age, char* phone_number, char* license)
        : Person(name, surname, age, phone_number), _car(&car), _rating(0.0), _orders_completed(0), _order_max(100) {

        _license = new char[strlen(license) + 1];
        strcpy(_license, license);

        _orders = new Order*[_order_max];

        _login = new char[strlen(name) + strlen(surname) + 1];
        strcpy(_login, name);
        strcat(_login, surname);

        int password_length = 10;
        _password = new char[password_length + 1];
        generate_random_string(_password, password_length);
    }

    ~Driver() override {
        delete[] _license;
        delete[] _login;
        delete[] _password;
        delete[] _orders;
    }

    void addOrder(Order** order) {
        if (_orders_completed == _order_max) {
            _order_max *= 2;
            Order** new_orders = new Order*[_order_max];
            for (int i = 0; i < _orders_completed; ++i) {
                new_orders[i] = _orders[i];
            }
            delete[] _orders;
            _orders = new_orders;
        }
        _orders[_orders_completed++] = *order;
    }

    void removeOrder(int index) {
        if (index < 0 || index >= _orders_completed) {
            return;
        }

        for (int i = index; i < _orders_completed - 1; ++i) {
            _orders[i] = _orders[i + 1];
        }
        --_orders_completed;
    }

    void setLicense(char* license) {
        delete[] _license;
        _license = new char[strlen(license) + 1];
        strcpy(_license, license);
    }

    void setRating(float rating) {
        _rating = rating;
    }

    void setOrdersCompleted(int orders) {
        _orders_completed = orders;
    }


    void setLogin(char* login) {
        delete[] _login;
        _login = new char[strlen(login) + 1];
        strcpy(_login, login);
    }

    void setPassword(char* password) {
        delete[] _password;
        _password = new char[strlen(password) + 1];
        strcpy(_password, password);
    }

    Order** getOrders() {
        return _orders;
    }


    Order* getOrder(int index) const {
        if (index >= 0 && index < _orders_completed) {
            return _orders[index];
        }
        return nullptr;
    }


    Car& get_car() {
        return *_car;
    }

    char* getLicense() {
        return _license;
    }

    float getRating() {
        return _rating;
    }

    int getOrdersCompleted() {
        return _orders_completed;
    }

    char* getLogin() {
        return _login;
    }
    char* getPassword() {
        return _password;
    }

        // Save method for Driver class
    void saveToFile(std::ofstream& out) const {
        size_t length;

        // Save name
        length = strlen(_name);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_name, length);

        // Save surname
        length = strlen(_surname);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_surname, length);

        // Save age
        out.write(reinterpret_cast<const char*>(&_age), sizeof(_age));

        // Save phone number
        length = strlen(_phone_number);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_phone_number, length);

        // Save license
        length = strlen(_license);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_license, length);

        // Save login
        length = strlen(_login);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_login, length);

        // Save password
        length = strlen(_password);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_password, length);

        // Save car
        _car->saveToFile(out);  // Assuming Car class has a saveToFile method

        // Save orders
        out.write(reinterpret_cast<const char*>(&_orders_completed), sizeof(_orders_completed));
        for (int i = 0; i < _orders_completed; ++i) {
            _orders[i]->saveToFile(out);  // Assuming Order class has a saveToFile method
        }
    }

    // Load method for Driver class
    void loadFromFile(std::ifstream& in) {
        size_t length;

        // Load name
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _name = new char[length + 1];
        in.read(_name, length);
        _name[length] = '\0';

        // Load surname
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _surname = new char[length + 1];
        in.read(_surname, length);
        _surname[length] = '\0';

        // Load age
        in.read(reinterpret_cast<char*>(&_age), sizeof(_age));

        // Load phone number
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _phone_number = new char[length + 1];
        in.read(_phone_number, length);
        _phone_number[length] = '\0';

        // Load license
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _license = new char[length + 1];
        in.read(_license, length);
        _license[length] = '\0';

        // Load login
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _login = new char[length + 1];
        in.read(_login, length);
        _login[length] = '\0';

        // Load password
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _password = new char[length + 1];
        in.read(_password, length);
        _password[length] = '\0';

        // Load car
        _car = new Car();
        _car->loadFromFile(in);  // Assuming Car class has a loadFromFile method

        // Load orders
        in.read(reinterpret_cast<char*>(&_orders_completed), sizeof(_orders_completed));
        _orders = new Order*[_orders_completed];
        for (int i = 0; i < _orders_completed; ++i) {
            _orders[i] = new Order();
            _orders[i]->loadFromFile(in);  // Assuming Order class has a loadFromFile method
        }
    }

};

class Client : public Person {
private:
    char* _login;
    char* _password;

    Order** _orders;
    int _orders_completed;
    int _orders_max;

private:
    void generate_random_string(char* str, int length) {
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int charset_size = sizeof(charset) - 1;

        for (int i = 0; i < length; ++i) {
            str[i] = charset[rand() % charset_size];
        }
        str[length] = '\0';
    }

public:
    Client() : Person("", "", 0, ""), _login(nullptr), _password(nullptr), _orders(nullptr), _orders_completed(0), _orders_max(0) {}

    Client(const char* name, const char* surname, int age, const char* phone_number)
        : Person(name, surname, age, phone_number), _orders_completed(0), _orders_max(10) {

        _orders = new Order*[_orders_max];

        _login = new char[strlen(name) + strlen(surname) + 1];
        strcpy(_login, name);
        strcat(_login, surname);
        _login[strlen(name) + strlen(surname)] = '\0';

        int password_length = 10;
        _password = new char[password_length + 1];
        generate_random_string(_password, password_length);
    }

    ~Client() override {
        delete[] _login;
        delete[] _password;
        delete[] _orders;
    }

    void addOrder(Order* order) {
        if (_orders_completed == _orders_max) {
            _orders_max *= 2;
            Order** new_orders = new Order*[_orders_max];
            for (int i = 0; i < _orders_completed; ++i) {
                new_orders[i] = _orders[i];
            }
            delete[] _orders;
            _orders = new_orders;
        }
        _orders[_orders_completed++] = order;
    }

    void removeOrder(int index) {
        if (index < 0 || index >= _orders_completed) {
            return;
        }

        for (int i = index; i < _orders_completed - 1; ++i) {
            _orders[i] = _orders[i + 1];
        }
        --_orders_completed;
    }

    Order** getOrders() {
        return _orders;
    }

    void setLogin(char* login) {
        delete[] _login;
        _login = new char[strlen(login) + 1];
        strcpy(_login, login);
    }

    void setPassword(char* password) {
        delete[] _password;
        _password = new char[strlen(password) + 1];
        strcpy(_password, password);
    }


    int getOrdersMax() const {
        return _orders_max;
    }

    int getOrderCount() const {
        return _orders_completed;
    }

    char* getLogin() {
        return _login;
    }

    char* getPassword() {
        return _password;
    }


     void saveToFile(std::ofstream& out) const {
        size_t length;

        // Save name
        length = strlen(_name);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_name, length);

        // Save surname
        length = strlen(_surname);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_surname, length);

        // Save age
        out.write(reinterpret_cast<const char*>(&_age), sizeof(_age));

        // Save phone number
        length = strlen(_phone_number);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_phone_number, length);

        // Save login
        length = strlen(_login);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_login, length);

        // Save password
        length = strlen(_password);
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(_password, length);

        // Save orders
        out.write(reinterpret_cast<const char*>(&_orders_completed), sizeof(_orders_completed));
        for (int i = 0; i < _orders_completed; ++i) {
            _orders[i]->saveToFile(out);
        }
    }

    void loadFromFile(std::ifstream& in) {
        size_t length;

        // Load name
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _name = new char[length + 1];
        in.read(_name, length);
        _name[length] = '\0';

        // Load surname
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _surname = new char[length + 1];
        in.read(_surname, length);
        _surname[length] = '\0';

        // Load age
        in.read(reinterpret_cast<char*>(&_age), sizeof(_age));

        // Load phone number
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _phone_number = new char[length + 1];
        in.read(_phone_number, length);
        _phone_number[length] = '\0';

        // Load login
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _login = new char[length + 1];
        in.read(_login, length);
        _login[length] = '\0';

        // Load password
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        _password = new char[length + 1];
        in.read(_password, length);
        _password[length] = '\0';

        // Load orders
        in.read(reinterpret_cast<char*>(&_orders_completed), sizeof(_orders_completed));
        _orders = new Order*[_orders_completed];
        for (int i = 0; i < _orders_completed; ++i) {
            _orders[i] = new Order();
            _orders[i]->loadFromFile(in);
        }
    }
};

class System {
private:
    Driver* _drivers;
    Client* _clients;

    int _num_drivers;
    int _num_clients;

public:

    System():_num_drivers(0), _num_clients(0){
        _drivers = new Driver[100];
        _clients = new Client[100];
    }

    ~System() {
        delete[] _drivers;
        delete[] _clients;
    }


    void add_driver(const Driver& driver) {
        _drivers[_num_drivers] = driver;
        ++_num_drivers;
    }


    void add_client(const Client& client) {
        _clients[_num_clients] = client;
        ++_num_clients;
    }



    Driver* get_drivers() const { return _drivers; }
    Client* get_clients() const { return _clients; }
    int get_number_of_drivers() const { return _num_drivers; }
    int get_number_of_clients() const { return _num_clients; }


    int remove_driver(const char* name, const char* surname) {
        for (int i = 0; i < _num_drivers; i++) {
            if (strcmp(name, _drivers[i].getName()) == 0 &&
                strcmp(surname, _drivers[i].getSurname()) == 0) {
                for (int j = i; j < _num_drivers - 1; j++) {
                    _drivers[j] = _drivers[j + 1];
                }
                _num_drivers--;
                return 1;
                }
        }
        return 0;
    }

    int remove_client(const char* name, const char* surname) {
        for (int i = 0; i < _num_clients; i++) {
            if (strcmp(name, _clients[i].getName()) == 0 &&
                strcmp(surname, _clients[i].getSurname()) == 0) {
                for (int j = i; j < _num_clients - 1; j++) {
                    _clients[j] = _clients[j + 1];
                }
                _num_clients--;
                return 1;
                }
        }
        return 0;
    }



    void signIn() {
        char* login = new char[100];
        char* password = new char[100];

        std::cout<<"=== Sing In ==="<<std::endl;
        while (true) {
            std::cout << "Enter username: ";
            std::cin.ignore();
            std::cin.getline(login, 100);

            std::cout << "Enter password: ";
            std::cin.getline(password, 100);

            if (strlen(login) == 0 || strlen(password) == 0) {
                std::cout<<"=== Again! ==="<<std::endl;
            } else {
                break;
            }
        }

        for (int i = 0; i < _num_drivers; i++) {
            if(strcmp(login, _drivers[i].getLogin()) == 0 && strcmp(password,_drivers[i].getPassword()) == 0) {
                std::cout<<"=== Welcome ==="<<std::endl;
                delete [] login;
                delete [] password;
                driver_menu(_drivers[i]);
                return;
            }
        }
        for (int i = 0; i < _num_clients; i++) {
            if(strcmp(login, _clients[i].getLogin()) == 0 && strcmp(password,_clients[i].getPassword()) == 0) {
                std::cout<<"=== Welcome ==="<<std::endl;
                delete [] login;
                delete [] password;
                client_menu(_clients[i]);
                return;
            }
        }


        std::cout<<"=== Not found ==="<<std::endl;
        delete [] login;
        delete [] password;
        return;

    }

    void register_driver() {
        char* brand = new char[50];
        char* model = new char[50];
        char* plates = new char[50];
        int year;
        int mileage;

        std::cout << "=== Register Driver ===" << std::endl;
        std::cout << "=== Enter Info About Your Vehicle ===" << std::endl;

        std::cin.ignore();

        while (true) {
            std::cout << "Brand: ";
            std::cin.getline(brand, 50);
            if (std::strlen(brand) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            std::cout << "Model: ";
            std::cin.getline(model, 50);
            if (std::strlen(model) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            std::cout << "Plates: ";
            std::cin.getline(plates, 50);
            if (std::strlen(plates) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            try {
                std::cout << "Year: ";
                std::cin >> year;
                std::cin.ignore();
                std::time_t now = std::time(nullptr);

                // Convert to local time
                std::tm* localTime = std::localtime(&now);

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput("Input is not a valid number.");
                }

                // Extract the current year
                int currentYear = 1900 + localTime->tm_year;
                if (year <= 1886 || year >= currentYear) {
                    std::cout << "=== Error ===" << std::endl;
                } else {
                    break;
                }
            } catch (InvalidInput& e) {
                std::cout << "=== Error ===" << std::endl;
            }
        }

        while (true) {
            try {
                std::cout << "Mileage: ";
                std::cin >> mileage;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput("Input is not a valid number.");
                }

                if (mileage < 0) {
                    throw InvalidInput("Mileage cannot be negative.");
                }

                break;
            } catch (InvalidInput& e) {
                std::cout << "=== Error ===" << std::endl;
            }
        }



        Car* car1 = new Car(brand, model, plates, year, mileage);

        delete[] brand;
        delete[] model;
        delete[] plates;

        char* name = new char[50];
        char* surname = new char[50];
        int age;
        char* phone_number = new char[50];
        char* license = new char[50];

        std::cout << "Car registered!" << std::endl;
        std::cout << "=== Enter Personal Info ===" << std::endl;
        std::cin.ignore();

        while (true) {
            std::cout << "Name: ";
            std::cin.getline(name, 50);
            if (std::strlen(name) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            std::cout << "Surname: ";
            std::cin.getline(surname, 50);
            if (std::strlen(surname) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }
        while (true) {
            try {
                std::cout << "Age: ";
                std::cin >> age;
                std::cin.ignore();
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput("Input is not a valid number.");
                }
                if (age <= 18 || age >= 99) {
                    std::cout << "=== Error ===" << std::endl;
                } else {
                    break;
                }
            } catch (InvalidInput& e) {
                std::cout << "=== Error ===" << std::endl;
            }
        }

        while (true) {
            std::cout << "Phone Number: ";
            std::cin.getline(phone_number, 50);
            if (strlen(phone_number) == 0 || strlen(phone_number) > 10 || strlen(phone_number) < 10) {
                std::cout << "=== Error ===" << std::endl;
            } else if (!isPhoneNumberValid(phone_number)) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            std::cout << "License: ";
            std::cin.getline(license, 50);
            if (std::strlen(license) == 0) {
                std::cout << "=== Error ===" << std::endl;
                std::cout << "License cannot be empty! Please try again." << std::endl;
            } else {
                break;
            }
        }


        Driver* driver1 = new Driver(*car1, name, surname, age, phone_number, license);
        std::cout << "Driver registered!" << std::endl;


        delete[] name;
        delete[] surname;
        delete[] phone_number;
        delete[] license;

        add_driver(*driver1);

        driver_menu(*driver1);
    }

    void register_client() {
        char* name = new char[50];
        char* surname = new char[50];
        int age;
        char* phone_number = new char[50];

        std::cout << "=== Register Client ===" << std::endl;
        std::cin.ignore();
        while (true) {
            std::cout << "Name: ";
            std::cin.getline(name, 50);
            if (std::strlen(name) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            std::cout << "Surname: ";
            std::cin.getline(surname, 50);
            if (std::strlen(surname) == 0) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        while (true) {
            try {
                std::cout << "Age: ";
                std::cin >> age;
                std::cin.ignore();
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput("Input is not a valid number.");
                }
                if (age <= 18 || age >= 99) {
                    std::cout << "=== Error ===" << std::endl;
                } else {
                    break;
                }
            } catch (InvalidInput& e) {
                std::cout << "=== Error ===" << std::endl;
                continue;
            }
        }

        while (true) {
            std::cout << "Phone Number: ";
            std::cin.getline(phone_number, 50);
            if (strlen(phone_number) == 0 || strlen(phone_number) > 10 || strlen(phone_number) < 10) {
                std::cout << "=== Error ===" << std::endl;
            } else if (!isPhoneNumberValid(phone_number)) {
                std::cout << "=== Error ===" << std::endl;
            } else {
                break;
            }
        }

        Client client(name, surname, age, phone_number);
        Client *client1 = new Client(name, surname, age, phone_number);

        std::cout << "Client registered!" << std::endl;

        delete[] name;
        delete[] surname;
        delete[] phone_number;

        add_client(*client1);

        client_menu(*client1);
    }

    void driver_menu(Driver& driver) {
        while(true) {
            int choice;
            std::cout<<"=== Driver Window ==="<<std::endl;
            std::cout<<"=== "<<driver.getName()<<" ==="<<std::endl;
            std::cout<<"1)Car info\n2)Personal info\n3)Statistics\n4)Exit\nChoice:";
            std::cin>>choice;

            if(choice == 1) {
                std::cout<<"=== Car info ==="<<std::endl;
                std::cout<<"Brand: "<<driver.get_car().getCarBrand()<<std::endl;
                std::cout<<"Model: "<<driver.get_car().getCarModel()<<std::endl;
                std::cout<<"Year: "<<driver.get_car().getYear()<<std::endl;
                std::cout<<"Mileage: "<<driver.get_car().getMileage()<<std::endl;
                std::cout<<"Plates: "<<driver.get_car().getPlates()<<std::endl;
                std::cout<<"Status: "<<driver.get_car().getStatus()<<std::endl;
            }
            else if(choice == 2) {
                std::cout<<"=== Personal info ==="<<std::endl;
                std::cout<<"Name: "<<driver.getName()<<std::endl;
                std::cout<<"Surname: "<<driver.getSurname()<<std::endl;
                std::cout<<"Age: "<<driver.getAge()<<std::endl;
                std::cout<<"Phone Number: (+994)"<<driver.getPhoneNumber()<<std::endl;
                std::cout<<"License: "<<driver.getLicense()<<std::endl;
                std::cout<<"Login: "<<driver.getLogin()<<std::endl;
                std::cout<<"Password: "<<driver.getPassword()<<std::endl;
            }
            else if(choice == 3) {
                std::cout<<"=== Statistics ==="<<std::endl;
                std::cout<<"Rating :"<<driver.getRating()<<std::endl;
                std::cout<<"Orders completed: "<<driver.getOrdersCompleted()<<std::endl;

                if(driver.getOrdersCompleted()>0) {
                    std::cout<<"=== Orders ==="<<std::endl;
                    int counter = 0;
                    for(int i = 0; i < driver.getOrdersCompleted(); i++) {
                        std::cout<<"=== Order "<<++counter<<" ==="<<std::endl;
                        std::cout<<"Status: "<<driver.getOrders()[i]->getStatus()<<std::endl;
                        std::cout<<"Client: "<<driver.getOrders()[i]->getClientName()<<std::endl;
                        std::cout<<"Pick up point: "<<driver.getOrders()[i]->getPickUpPoint()<<std::endl;
                        std::cout<<"Arrival point: "<<driver.getOrders()[i]->getArrivalPoint()<<std::endl;
                        std::cout<<"Duration: "<<driver.getOrders()[i]->getDuration()<<" min"<<std::endl;
                        std::cout<<"Cost: $"<<driver.getOrders()[i]->getCost()<<std::endl;
                        std::cout<<std::endl;
                        if(strcmp(driver.getOrders()[i]->getStatus(),"In Process") == 0) {
                            while(true) {
                                int choice;
                                std::cout<<"Do you want to end up the ride?(1(YES)|0(NO)): ";
                                std::cin>>choice;
                                if(choice == 1) {
                                    driver.getOrders()[i]->setStatus("Done");
                                    std::cout<<"=== The ride has been ended! ==="<<std::endl;
                                    break;
                                }
                                else if(choice == 0) {
                                    break;
                                }
                                else {
                                    std::cout<<"=== Again ==="<<std::endl;
                                }
                            }
                        }
                    }
                }
            }
            else if(choice == 4) {
                return;
            }
            else {
                std::cout<<"=== Failure! ==="<<std::endl;
            }
        }
    }

    void client_menu(Client& client) {
        while(true) {
            int choice_client;
            std::cout<<"=== Client Window ==="<<std::endl;
            std::cout<<"=== "<<client.getName()<<" ==="<<std::endl;
            std::cout<<"1)Personal info\n2)Statistics\n3)Make an order\n4)Exit\nChoice:";
            std::cin>>choice_client;
            if(choice_client == 1) {
                std::cout<<"=== Personal info ==="<<std::endl;
                std::cout<<"Name: "<<client.getName()<<std::endl;
                std::cout<<"Surname: "<<client.getSurname()<<std::endl;
                std::cout<<"Age: "<<client.getAge()<<std::endl;
                std::cout<<"Phone Number: +(994)"<<client.getPhoneNumber()<<std::endl;
                std::cout<<"Login: "<<client.getLogin()<<std::endl;
                std::cout<<"Password: "<<client.getPassword()<<std::endl;
            }
            else if(choice_client == 2) {
                std::cout<<"=== Statistics ==="<<std::endl;
                std::cout<<"Orders: "<<client.getOrderCount()<<std::endl;

                if(client.getOrderCount() > 0) {
                    int counter = 0;
                    std::cout<<"=== Orders ==="<<std::endl;
                    for(int i = 0; i < client.getOrderCount(); i++) {
                        std::cout<<"=== Order "<<++counter<<" ==="<<std::endl;
                        std::cout<<"Status: "<<client.getOrders()[i]->getStatus()<<std::endl;
                        std::cout<<"Driver: "<<client.getOrders()[i]->getDriverName()<<std::endl;
                        std::cout<<"Pick up point: "<<client.getOrders()[i]->getPickUpPoint()<<std::endl;
                        std::cout<<"Arrival point: "<<client.getOrders()[i]->getArrivalPoint()<<std::endl;
                        std::cout<<"Duration: "<<client.getOrders()[i]->getDuration()<<" min"<<std::endl;
                        std::cout<<"Cost: $"<<client.getOrders()[i]->getCost()<<std::endl;
                        std::cout<<std::endl;
                    }
                }

            }
            else if(choice_client == 3) {
                bool is_processes = 0;
                for(int i = 0; i < client.getOrderCount(); i++) {
                    if(strcmp("In Process",client.getOrders()[i]->getStatus()) == 0) {
                        std::cout<<"=== You must end the current ride to make an order ==="<<std::endl;
                        is_processes = 1;
                    }
                }
                if(is_processes == 1) {
                    continue;
                }
                int count = 0;
                if(_num_drivers > 0) {
                    std::cout<<"=== Make an order ==="<<std::endl;
                    std::cout<<"=== Drivers available ==="<<std::endl;
                    for(int i = 0; i < _num_drivers; i++) {
                        count++;
                        std::cout<<"=== Driver "<<count<<" ==="<<std::endl;
                        std::cout<<"Name: "<<_drivers[i].getName()<<std::endl;
                        std::cout<<"Car: "<<_drivers[i].get_car().getCarBrand()<<" "<<_drivers[i].get_car().getCarModel()<<std::endl;
                        std::cout<<"Plates: "<<_drivers[i].get_car().getPlates()<<std::endl;
                        std::cout<<"Rating: "<<_drivers[i].getRating()<<std::endl;
                        std::cout<<"Orders: "<<_drivers[i].getOrdersCompleted()<<std::endl;
                        std::cout<<std::endl;
                    }
                    int choice;
                    std::cout<<"Choice: ";
                    std::cin>>choice;

                    if(choice <= 0 || choice > _num_drivers) {
                        std::cout<<"=== Incorrect ==="<<std::endl;
                    }
                    else {
                        --choice;

                        //Check if driver is busy
                        int numOrders = _drivers[choice].getOrdersCompleted();


                        int result = 0;
                        if (numOrders != 0) {
                            for (int j = 0; j < numOrders; ++j) {
                                Order* order = _drivers[choice].getOrder(j);
                                result = displayOrderDetails(order);
                            }
                        }

                        if(result == 1) {
                            std::cout<<"=== The driver is busy ==="<<std::endl;
                            continue;
                        }

                        char* pick_up_point = new char[100];
                        char* arrival_point = new char[100];

                        std::cout<<"=== Order data ==="<<std::endl;

                        while (true) {
                            std::cout<<"Pick up point: ";
                            std::cin.ignore();
                            std::cin.getline(pick_up_point, 100);
                            if(strlen(pick_up_point) == 0) std::cout<<"Pick up point is empty"<<std::endl;
                            else break;
                        }


                        while (true) {
                            std::cout<<"Arrival point: ";
                            std::cin.getline(arrival_point, 100);
                            if(strlen(pick_up_point) == 0) std::cout<<"Is empty"<<std::endl;
                            else break;
                        }


                        Order* order = new Order("In Process",pick_up_point,arrival_point,_drivers[choice].getName(),client.getName());
                        order->set_cost(_drivers[choice].getRating());

                        client.addOrder(&*order);
                        _drivers[choice].addOrder(&order);


                        for(int i = 0; i < _num_clients; i++) {
                            if(strcmp(client.getPassword(), _clients[i].getPassword()) == 0) {
                                _clients[i] = client;
                            }
                        }

                        delete[] pick_up_point;
                        delete[] arrival_point;

                        std::cout<<"=== Success! Now wait for the driver! ==="<<std::endl;
                        _sleep((rand()%5)*1000);

                        std::cout<<"=== The ride has started! ==="<<std::endl;
                        std::cout<<"Status: "<<order->getStatus()<<std::endl;
                        std::cout<<"Driver: "<<order->getDriverName()<<std::endl;
                        std::cout<<"Pick up point: "<<order->getPickUpPoint()<<std::endl;
                        std::cout<<"Arrival point: "<<order->getArrivalPoint()<<std::endl;
                        std::cout<<"Duration: "<<order->getDuration()<<" min"<<std::endl;
                        std::cout<<"Cost: $"<<order->getCost()<<std::endl;
                        std::cout<<"============================="<<std::endl;

                        float rating;
                        while(true) {
                            std::cout<<"Rate the driver (0.0 - 5.0): ";
                            std::cin>>rating;

                            if(rating < 0.0 || rating > 5.0) {
                                std::cout<<"=== Incorrect ==="<<std::endl;
                            }
                            else {
                                _drivers[choice].setRating(rating);
                                break;
                            }
                        }
                        continue;
                    }
                }
                else {
                    std::cout<<"=== No drivers available! ==="<<std::endl;
                }
            }
            else if(choice_client == 4) {
                return;
            }
            else {
                std::cout<<"=== Failure! ==="<<std::endl;
            }
        }
    }

    void user_menu() {
        while (true) {
            int choice;
            std::cout<<"=== Smart Taxi ==="<<std::endl;
            std::cout<<"1)Authorize\n2)Register\n3)Exit\nChoice: ";
            std::cin>>choice;

            if(choice==1) {
                signIn();
            }
            else if(choice==2) {
                int choice;
                std::cout<<"=== Register ==="<<std::endl;
                std::cout<<"1)Driver\n2)Client\n3)Exit\nChoice: ";
                std::cin>>choice;

                if(choice == 1) {
                    register_driver();
                }
                else if(choice == 2) {
                    register_client();
                }
                else {
                    std::cout<<"=== Incorrect! ==="<<std::endl;
                    continue;
                }
            }
            else if(choice == 3) {
                return;
            }
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            std::cerr << "Error: Unable to open file for saving." << std::endl;
            return;
        }

        out.write(reinterpret_cast<const char*>(&_num_drivers), sizeof(_num_drivers));
        for (int i = 0; i < _num_drivers; ++i) {
            _drivers[i].saveToFile(out);
        }

        out.write(reinterpret_cast<const char*>(&_num_clients), sizeof(_num_clients));
        for (int i = 0; i < _num_clients; ++i) {
            _clients[i].saveToFile(out);
        }

        out.close();
    };

    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) {
            std::cerr << "Error: Unable to open file for loading." << std::endl;
            return;
        }

        in.read(reinterpret_cast<char*>(&_num_drivers), sizeof(_num_drivers));
        for (int i = 0; i < _num_drivers; ++i) {
            _drivers[i].loadFromFile(in);
        }

        in.read(reinterpret_cast<char*>(&_num_clients), sizeof(_num_clients));
        for (int i = 0; i < _num_clients; ++i) {
            _clients[i].loadFromFile(in);
        }

        in.close();
    }
};



int main() {
    srand(time(NULL));
    System system{};
    std::ofstream out("system.bin", std::ios::binary);

    system.loadFromFile("system.bin");
    system.user_menu();

    system.saveToFile("system.bin");

    return 0;
}