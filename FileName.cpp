#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <conio.h>
#include <windows.h>

using namespace std;

// Функция для корректного вывода русских символов в Windows
void setRussianLocale() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// Пространство имен для утилит
namespace Utils {
    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
            return tolower(c);
            });
        return result;
    }

    string encryptPassword(const string& password) {
        string encrypted = password;
        for (char& c : encrypted) {
            c = c + 1;
        }
        return encrypted;
    }

    string decryptPassword(const string& encrypted) {
        string decrypted = encrypted;
        for (char& c : decrypted) {
            c = c - 1;
        }
        return decrypted;
    }

    string getHiddenPassword() {
        string password;
        char ch;
        while (true) {
            ch = _getch();
            if (ch == 13 || ch == 10) {
                cout << endl;
                break;
            }
            else if (ch == 8) {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        return password;
    }

    // Функция для разделения строки
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

// Класс клиента
class Client {
private:
    string clientId;
    string firstName;
    string lastName;
    string passportNumber;
    string phoneNumber;
    string address;

public:
    Client(const string& id, const string& fname, const string& lname,
        const string& passport, const string& phone, const string& addr)
        : clientId(id), firstName(fname), lastName(lname),
        passportNumber(passport), phoneNumber(phone), address(addr) {}

    Client(const vector<string>& data) {
        if (data.size() >= 6) {
            clientId = data[0];
            firstName = data[1];
            lastName = data[2];
            passportNumber = data[3];
            phoneNumber = data[4];
            address = data[5];
        }
    }

    string getClientId() const { return clientId; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getPassportNumber() const { return passportNumber; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }

    void setFirstName(const string& fname) { firstName = fname; }
    void setLastName(const string& lname) { lastName = lname; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setAddress(const string& addr) { address = addr; }

    // Метод для сохранения в строку
    string toString() const {
        return clientId + "|" + firstName + "|" + lastName + "|" +
            passportNumber + "|" + phoneNumber + "|" + address;
    }

    friend ostream& operator<<(ostream& os, const Client& client);
};

ostream& operator<<(ostream& os, const Client& client) {
    os << "ID клиента: " << client.clientId << endl;
    os << "Имя: " << client.firstName << endl;
    os << "Фамилия: " << client.lastName << endl;
    os << "Паспорт: " << client.passportNumber << endl;
    os << "Телефон: " << client.phoneNumber << endl;
    os << "Адрес: " << client.address << endl;
    return os;
}

// Класс страхового полиса
class InsurancePolicy {
private:
    string policyId;
    string policyType;
    string description;
    double price;
    int duration;
    int popularity;
    string clientId;
    string startDate;
    string endDate;
    bool isActive;

public:
    InsurancePolicy(const string& id, const string& type, const string& desc,
        double pr, int dur, const string& clientId = "")
        : policyId(id), policyType(type), description(desc), price(pr),
        duration(dur), popularity(0), clientId(clientId), isActive(false) {}

    InsurancePolicy(const vector<string>& data) {
        if (data.size() >= 9) {
            policyId = data[0];
            policyType = data[1];
            description = data[2];
            price = stod(data[3]);
            duration = stoi(data[4]);
            popularity = stoi(data[5]);
            clientId = data[6];
            startDate = data[7];
            endDate = data[8];
            isActive = (data[9] == "1");
        }
    }

    string getPolicyId() const { return policyId; }
    string getPolicyType() const { return policyType; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    int getDuration() const { return duration; }
    int getPopularity() const { return popularity; }
    string getClientId() const { return clientId; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    bool getIsActive() const { return isActive; }

    void setPolicyType(const string& type) { policyType = type; }
    void setDescription(const string& desc) { description = desc; }
    void setPrice(double pr) { price = pr; }
    void setDuration(int dur) { duration = dur; }
    void incrementPopularity() { popularity++; }
    void setClientId(const string& id) { clientId = id; }
    void activatePolicy(const string& start, const string& end) {
        startDate = start;
        endDate = end;
        isActive = true;
    }
    void deactivatePolicy() { isActive = false; }

    // Метод для сохранения в строку
    string toString() const {
        return policyId + "|" + policyType + "|" + description + "|" +
            to_string(price) + "|" + to_string(duration) + "|" +
            to_string(popularity) + "|" + clientId + "|" +
            startDate + "|" + endDate + "|" + (isActive ? "1" : "0");
    }

    friend ostream& operator<<(ostream& os, const InsurancePolicy& policy);
};

ostream& operator<<(ostream& os, const InsurancePolicy& policy) {
    os << "ID полиса: " << policy.policyId << endl;
    os << "Тип: " << policy.policyType << endl;
    os << "Описание: " << policy.description << endl;
    os << "Цена: " << policy.price << " руб./мес." << endl;
    os << "Длительность: " << policy.duration << " мес." << endl;
    os << "Популярность: " << policy.popularity << " просмотров" << endl;
    if (!policy.clientId.empty()) {
        os << "ID клиента: " << policy.clientId << endl;
        os << "Статус: " << (policy.isActive ? "Активен" : "Неактивен") << endl;
        if (policy.isActive) {
            os << "Начало: " << policy.startDate << endl;
            os << "Окончание: " << policy.endDate << endl;
        }
    }
    return os;
}

// Абстрактный базовый класс для пользователей
class User {
protected:
    string username;
    string encryptedPassword;
    string role;

public:
    User(const string& uname, const string& pwd, const string& r)
        : username(uname), encryptedPassword(Utils::encryptPassword(pwd)), role(r) {}

    User(const vector<string>& data) {
        if (data.size() >= 3) {
            username = data[0];
            encryptedPassword = data[1];
            role = data[2];
        }
    }

    virtual ~User() = default;

    virtual void displayMenu() = 0;
    virtual bool hasPermission(const string& action) = 0;

    string getUsername() const { return username; }
    string getRole() const { return role; }
    string getEncryptedPassword() const { return encryptedPassword; }

    bool checkPassword(const string& pwd) const {
        return Utils::encryptPassword(pwd) == encryptedPassword;
    }

    static int userCount;
    static void displayUserCount() {
        cout << "Всего пользователей в системе: " << userCount << endl;
    }

    // Метод для сохранения в строку
    string toString() const {
        return username + "|" + encryptedPassword + "|" + role;
    }

    friend ostream& operator<<(ostream& os, const User& user);
};

int User::userCount = 0;

ostream& operator<<(ostream& os, const User& user) {
    os << "Имя пользователя: " << user.username << ", Роль: " << user.role;
    return os;
}

// Класс администратора
class Admin : public User {
private:
    static int adminCount;

public:
    Admin(const string& uname, const string& pwd)
        : User(uname, pwd, "admin") {
        adminCount++;
        userCount++;
    }

    Admin(const vector<string>& data) : User(data) {
        adminCount++;
        userCount++;
    }

    ~Admin() {
        adminCount--;
        userCount--;
    }

    void displayMenu() override {
        cout << "\n=== ПАНЕЛЬ АДМИНИСТРАТОРА ===" << endl;
        cout << "1. Управление полисами" << endl;
        cout << "2. Управление клиентами" << endl;
        cout << "3. Оформление полисов" << endl;
        cout << "4. Управление учетными записями" << endl;
        cout << "5. Просмотр статистики" << endl;
        cout << "6. Сохранить данные" << endl;
        cout << "7. Загрузить данные" << endl;
        cout << "8. Выход" << endl;
    }

    bool hasPermission(const string& action) override {
        return true;
    }

    static int getAdminCount() {
        return adminCount;
    }
};

int Admin::adminCount = 0;

// Класс обычного пользователя
class RegularUser : public User {
private:
    static int regularUserCount;

public:
    RegularUser(const string& uname, const string& pwd)
        : User(uname, pwd, "user") {
        regularUserCount++;
        userCount++;
    }

    RegularUser(const vector<string>& data) : User(data) {
        regularUserCount++;
        userCount++;
    }

    ~RegularUser() {
        regularUserCount--;
        userCount--;
    }

    void displayMenu() override {
        cout << "\n=== ПАНЕЛЬ ПОЛЬЗОВАТЕЛЯ ===" << endl;
        cout << "1. Просмотр полисов" << endl;
        cout << "2. Поиск полисов" << endl;
        cout << "3. Сортировка полисов" << endl;
        cout << "4. Выход" << endl;
    }

    bool hasPermission(const string& action) override {
        return action != "manage_data" && action != "manage_accounts";
    }

    static int getRegularUserCount() {
        return regularUserCount;
    }
};

int RegularUser::regularUserCount = 0;

// Шаблонный класс для управления данными с файловым хранилищем
template<typename T>
class DataManager {
private:
    vector<shared_ptr<T>> items;
    string filename;

public:
    DataManager(const string& file = "") : filename(file) {}

    void setFilename(const string& file) {
        filename = file;
    }

    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void removeItem(const string& id) {
        auto it = remove_if(items.begin(), items.end(),
            [&id](const shared_ptr<T>& item) {
                if constexpr (is_same_v<T, InsurancePolicy>) {
                    return item->getPolicyId() == id;
                }
                else if constexpr (is_same_v<T, Client>) {
                    return item->getClientId() == id;
                }
                return false;
            });

        if (it != items.end()) {
            items.erase(it, items.end());
            cout << "Элемент удален успешно." << endl;
        }
        else {
            cout << "Элемент не найден." << endl;
        }
    }

    shared_ptr<T> findItem(const string& id) {
        for (const auto& item : items) {
            if constexpr (is_same_v<T, InsurancePolicy>) {
                if (item->getPolicyId() == id) return item;
            }
            else if constexpr (is_same_v<T, Client>) {
                if (item->getClientId() == id) return item;
            }
        }
        return nullptr;
    }

    vector<shared_ptr<T>> getAllItems() const {
        return items;
    }

    void displayAll() const {
        if (items.empty()) {
            cout << "Нет элементов для отображения." << endl;
            return;
        }

        for (const auto& item : items) {
            cout << *item << endl;
        }
    }

    vector<shared_ptr<T>> searchItems(const string& keyword) {
        vector<shared_ptr<T>> results;

        if (keyword.empty()) {
            return results;
        }

        string searchTerm = Utils::toLower(keyword);

        for (const auto& item : items) {
            bool found = false;

            if constexpr (is_same_v<T, InsurancePolicy>) {
                vector<string> fields = {
                    Utils::toLower(item->getPolicyType()),
                    Utils::toLower(item->getDescription()),
                    Utils::toLower(item->getPolicyId())
                };

                for (const auto& field : fields) {
                    if (field.find(searchTerm) != string::npos) {
                        found = true;
                        break;
                    }
                }

            }
            else if constexpr (is_same_v<T, Client>) {
                vector<string> fields = {
                    Utils::toLower(item->getFirstName()),
                    Utils::toLower(item->getLastName()),
                    Utils::toLower(item->getPassportNumber()),
                    Utils::toLower(item->getPhoneNumber()),
                    Utils::toLower(item->getAddress()),
                    Utils::toLower(item->getClientId())
                };

                for (const auto& field : fields) {
                    if (field.find(searchTerm) != string::npos) {
                        found = true;
                        break;
                    }
                }
            }

            if (found) {
                results.push_back(item);
            }
        }

        return results;
    }

    // Сохранение данных в файл
    bool saveToFile() {
        if (filename.empty()) {
            cout << "Имя файла не установлено." << endl;
            return false;
        }

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла для записи: " << filename << endl;
            return false;
        }

        for (const auto& item : items) {
            if constexpr (is_same_v<T, InsurancePolicy>) {
                file << item->toString() << endl;
            }
            else if constexpr (is_same_v<T, Client>) {
                file << item->toString() << endl;
            }
        }

        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
        return true;
    }

    // Загрузка данных из файла
    bool loadFromFile() {
        if (filename.empty()) {
            cout << "Имя файла не установлено." << endl;
            return false;
        }

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Файл не найден: " << filename << ". Будет создан новый." << endl;
            return false;
        }

        items.clear();
        string line;
        int loadedCount = 0;

        while (getline(file, line)) {
            if (!line.empty()) {
                vector<string> data = Utils::split(line, '|');
                if constexpr (is_same_v<T, InsurancePolicy>) {
                    if (data.size() >= 10) {
                        auto item = make_shared<InsurancePolicy>(data);
                        items.push_back(item);
                        loadedCount++;
                    }
                }
                else if constexpr (is_same_v<T, Client>) {
                    if (data.size() >= 6) {
                        auto item = make_shared<Client>(data);
                        items.push_back(item);
                        loadedCount++;
                    }
                }
            }
        }

        file.close();
        cout << "Загружено " << loadedCount << " записей из файла: " << filename << endl;
        return true;
    }
};

// Менеджер пользователей с файловым хранилищем
class UserManager {
private:
    map<string, shared_ptr<User>> users;
    string filename;

public:
    UserManager(const string& file = "") : filename(file) {}

    void addUser(shared_ptr<User> user) {
        users[user->getUsername()] = user;
    }

    shared_ptr<User> findUser(const string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second;
        }
        return nullptr;
    }

    void removeUser(const string& username) {
        users.erase(username);
    }

    map<string, shared_ptr<User>> getAllUsers() const {
        return users;
    }

    void displayAll() const {
        if (users.empty()) {
            cout << "Нет пользователей." << endl;
            return;
        }

        for (const auto& pair : users) {
            cout << *pair.second << endl;
        }
    }

    // Сохранение пользователей в файл
    bool saveToFile() {
        if (filename.empty()) {
            cout << "Имя файла не установлено." << endl;
            return false;
        }

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла для записи: " << filename << endl;
            return false;
        }

        for (const auto& pair : users) {
            file << pair.second->toString() << endl;
        }

        file.close();
        cout << "Данные пользователей сохранены в файл: " << filename << endl;
        return true;
    }

    // Загрузка пользователей из файла
    bool loadFromFile() {
        if (filename.empty()) {
            cout << "Имя файла не установлено." << endl;
            return false;
        }

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Файл пользователей не найден: " << filename << ". Будет создан новый." << endl;
            return false;
        }

        users.clear();
        string line;
        int loadedCount = 0;

        while (getline(file, line)) {
            if (!line.empty()) {
                vector<string> data = Utils::split(line, '|');
                if (data.size() >= 3) {
                    shared_ptr<User> user;
                    if (data[2] == "admin") {
                        user = make_shared<Admin>(data);
                    }
                    else {
                        user = make_shared<RegularUser>(data);
                    }
                    users[data[0]] = user;
                    loadedCount++;
                }
            }
        }

        file.close();
        cout << "Загружено " << loadedCount << " пользователей из файла: " << filename << endl;
        return true;
    }
};

// Класс для управления системой
class InsuranceSystem {
private:
    UserManager userManager;
    DataManager<InsurancePolicy> policyManager;
    DataManager<Client> clientManager;
    shared_ptr<User> currentUser;

    void initializeData() {
        // Установка имен файлов
        userManager = UserManager("users.txt");
        policyManager.setFilename("policies.txt");
        clientManager.setFilename("clients.txt");

        // Попытка загрузки данных из файлов
        if (!userManager.loadFromFile()) {
            // Создание данных по умолчанию, если файлы не найдены
            userManager.addUser(make_shared<Admin>("admin", "admin123"));
            userManager.addUser(make_shared<RegularUser>("user", "user123"));
            userManager.saveToFile();
        }

        if (!policyManager.loadFromFile()) {
            // Создание полисов по умолчанию
            auto policy1 = make_shared<InsurancePolicy>("POL001", "Автострахование",
                "Полное страхование автомобиля от ущерба и угонов", 2500.0, 12);
            auto policy2 = make_shared<InsurancePolicy>("POL002", "Медицинское страхование",
                "Комплексное медицинское обслуживание", 1800.0, 6);
            auto policy3 = make_shared<InsurancePolicy>("POL003", "Страхование недвижимости",
                "Защита вашего дома от пожаров, потопов и других рисков", 3200.0, 12);

            policyManager.addItem(policy1);
            policyManager.addItem(policy2);
            policyManager.addItem(policy3);
            policyManager.saveToFile();
        }

        if (!clientManager.loadFromFile()) {
            // Создание клиентов по умолчанию
            auto client1 = make_shared<Client>("CL001", "Иван", "Иванов", "1234567890", "+79161234567", "Москва, ул. Ленина, 1");
            auto client2 = make_shared<Client>("CL002", "Мария", "Петрова", "0987654321", "+79167654321", "Санкт-Петербург, Невский пр., 10");

            clientManager.addItem(client1);
            clientManager.addItem(client2);
            clientManager.saveToFile();
        }
    }

public:
    InsuranceSystem() {
        initializeData();
    }

    bool login(const string& username, const string& password) {
        auto user = userManager.findUser(username);
        if (user && user->checkPassword(password)) {
            currentUser = user;
            cout << "Успешный вход! Добро пожаловать, " << username << "!" << endl;
            return true;
        }
        cout << "Неверное имя пользователя или пароль." << endl;
        return false;
    }

    bool registerUser(const string& username, const string& password, const string& role = "user") {
        if (userManager.findUser(username)) {
            cout << "Пользователь с таким именем уже существует." << endl;
            return false;
        }

        shared_ptr<User> newUser;
        if (role == "admin") {
            newUser = make_shared<Admin>(username, password);
        }
        else {
            newUser = make_shared<RegularUser>(username, password);
        }

        userManager.addUser(newUser);
        userManager.saveToFile(); // Сохраняем изменения
        cout << "Пользователь " << username << " успешно зарегистрирован." << endl;
        return true;
    }

    void run() {
        while (true) {
            if (!currentUser) {
                showMainMenu();
            }
            else {
                if (currentUser->getRole() == "admin") {
                    showAdminMenu();
                }
                else {
                    showUserMenu();
                }
            }
        }
    }

private:
    void showMainMenu() {
        cout << "\n=== СТРАХОВАЯ КОМПАНИЯ ===" << endl;
        cout << "1. Вход" << endl;
        cout << "2. Регистрация" << endl;
        cout << "3. Выход из программы" << endl;
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Имя пользователя: ";
            getline(cin, username);
            cout << "Пароль: ";
            password = Utils::getHiddenPassword();
            login(username, password);
            break;
        }
        case 2: {
            string username, password;
            cout << "Имя пользователя: ";
            getline(cin, username);
            cout << "Пароль: ";
            password = Utils::getHiddenPassword();
            registerUser(username, password);
            break;
        }
        case 3:
            saveAllData();
            cout << "До свидания!" << endl;
            exit(0);
        default:
            cout << "Неверный выбор." << endl;
        }
    }

    void showAdminMenu() {
        while (currentUser) {
            currentUser->displayMenu();
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                managePolicies();
                break;
            case 2:
                manageClients();
                break;
            case 3:
                issuePolicy();
                break;
            case 4:
                manageAccounts();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                saveAllData();
                break;
            case 7:
                loadAllData();
                break;
            case 8:
                logout();
                return;
            default:
                cout << "Неверный выбор." << endl;
            }
        }
    }

    void showUserMenu() {
        while (currentUser) {
            currentUser->displayMenu();
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                viewPolicies();
                break;
            case 2:
                searchPolicies();
                break;
            case 3:
                sortPolicies();
                break;
            case 4:
                logout();
                return;
            default:
                cout << "Неверный выбор." << endl;
            }
        }
    }

    void saveAllData() {
        userManager.saveToFile();
        policyManager.saveToFile();
        clientManager.saveToFile();
        cout << "Все данные сохранены в файлы." << endl;
    }

    void loadAllData() {
        userManager.loadFromFile();
        policyManager.loadFromFile();
        clientManager.loadFromFile();
        cout << "Все данные загружены из файлов." << endl;
    }

    // Остальные методы остаются без изменений...
    void managePolicies() {
        while (true) {
            cout << "\n=== УПРАВЛЕНИЕ ПОЛИСАМИ ===" << endl;
            cout << "1. Просмотр всех полисов" << endl;
            cout << "2. Добавить полис" << endl;
            cout << "3. Редактировать полис" << endl;
            cout << "4. Удалить полис" << endl;
            cout << "5. Поиск полисов" << endl;
            cout << "6. Назад" << endl;
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                policyManager.displayAll();
                break;
            case 2:
                addPolicy();
                break;
            case 3:
                editPolicy();
                break;
            case 4:
                deletePolicy();
                break;
            case 5:
                searchPolicies();
                break;
            case 6:
                return;
            default:
                cout << "Неверный выбор." << endl;
            }
        }
    }

    void manageClients() {
        while (true) {
            cout << "\n=== УПРАВЛЕНИЕ КЛИЕНТАМИ ===" << endl;
            cout << "1. Просмотр всех клиентов" << endl;
            cout << "2. Добавить клиента" << endl;
            cout << "3. Редактировать клиента" << endl;
            cout << "4. Удалить клиента" << endl;
            cout << "5. Поиск клиента" << endl;
            cout << "6. Назад" << endl;
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                clientManager.displayAll();
                break;
            case 2:
                addClient();
                break;
            case 3:
                editClient();
                break;
            case 4:
                deleteClient();
                break;
            case 5:
                searchClients();
                break;
            case 6:
                return;
            default:
                cout << "Неверный выбор." << endl;
            }
        }
    }

    void addPolicy() {
        string id, type, desc;
        double price;
        int duration;

        cout << "ID полиса: ";
        getline(cin, id);
        cout << "Тип полиса: ";
        getline(cin, type);
        cout << "Описание: ";
        getline(cin, desc);
        cout << "Цена: ";
        cin >> price;
        cout << "Длительность (мес.): ";
        cin >> duration;
        cin.ignore();

        auto policy = make_shared<InsurancePolicy>(id, type, desc, price, duration);
        policyManager.addItem(policy);
        policyManager.saveToFile(); // Сохраняем изменения
        cout << "Полис успешно добавлен." << endl;
    }

    void addClient() {
        string id, fname, lname, passport, phone, addr;

        cout << "ID клиента: ";
        getline(cin, id);
        cout << "Имя: ";
        getline(cin, fname);
        cout << "Фамилия: ";
        getline(cin, lname);
        cout << "Паспорт: ";
        getline(cin, passport);
        cout << "Телефон: ";
        getline(cin, phone);
        cout << "Адрес: ";
        getline(cin, addr);

        auto client = make_shared<Client>(id, fname, lname, passport, phone, addr);
        clientManager.addItem(client);
        clientManager.saveToFile(); // Сохраняем изменения
        cout << "Клиент успешно добавлен." << endl;
    }

    void issuePolicy() {
        cout << "\n=== ОФОРМЛЕНИЕ ПОЛИСА ===" << endl;

        cout << "Доступные полисы:" << endl;
        policyManager.displayAll();

        cout << "\nЗарегистрированные клиенты:" << endl;
        clientManager.displayAll();

        string policyId, clientId;
        cout << "Введите ID полиса для оформления: ";
        getline(cin, policyId);
        cout << "Введите ID клиента: ";
        getline(cin, clientId);

        auto policy = policyManager.findItem(policyId);
        auto client = clientManager.findItem(clientId);

        if (!policy) {
            cout << "Полис не найден." << endl;
            return;
        }
        if (!client) {
            cout << "Клиент не найден." << endl;
            return;
        }

        policy->setClientId(clientId);
        policy->activatePolicy("2024-01-01", "2024-12-31");
        policyManager.saveToFile(); // Сохраняем изменения

        cout << "Полис успешно оформлен на клиента " << client->getFirstName()
            << " " << client->getLastName() << "!" << endl;
        cout << "Стоимость: " << policy->getPrice() * policy->getDuration() << " руб." << endl;
    }

    void searchClients() {
        while (true) {
            cout << "\n=== ПОИСК КЛИЕНТОВ ===" << endl;
            string keyword;
            cout << "Введите ключевое слово для поиска (или 'назад' для возврата): ";
            getline(cin, keyword);

            if (keyword == "назад") return;

            auto results = clientManager.searchItems(keyword);
            if (results.empty()) {
                cout << "Ничего не найдено по запросу: '" << keyword << "'" << endl;
            }
            else {
                cout << "Найдено " << results.size() << " клиентов:" << endl;
                for (const auto& client : results) {
                    cout << *client << endl;
                }
            }

            cout << "1. Новый поиск" << endl;
            cout << "2. Назад" << endl;
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 2) return;
        }
    }

    void searchPolicies() {
        while (true) {
            cout << "\n=== ПОИСК ПОЛИСОВ ===" << endl;
            string keyword;
            cout << "Введите ключевое слово для поиска (или 'назад' для возврата): ";
            getline(cin, keyword);

            if (keyword == "назад") return;

            auto results = policyManager.searchItems(keyword);
            if (results.empty()) {
                cout << "Ничего не найдено по запросу: '" << keyword << "'" << endl;
                cout << "Попробуйте: авто, медицин, недвижимость, путешествие или ID полиса (POL001)" << endl;
            }
            else {
                cout << "Найдено " << results.size() << " полисов:" << endl;
                for (const auto& policy : results) {
                    cout << *policy << endl;
                    policy->incrementPopularity();
                }
            }

            cout << "1. Новый поиск" << endl;
            cout << "2. Назад" << endl;
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 2) return;
        }
    }

    void editClient() {
        string id;
        cout << "Введите ID клиента для редактирования: ";
        getline(cin, id);

        auto client = clientManager.findItem(id);
        if (!client) {
            cout << "Клиент не найден." << endl;
            return;
        }

        cout << "Текущие данные:" << endl;
        cout << *client << endl;

        string fname, lname, phone, addr;
        cout << "Новое имя: ";
        getline(cin, fname);
        cout << "Новая фамилия: ";
        getline(cin, lname);
        cout << "Новый телефон: ";
        getline(cin, phone);
        cout << "Новый адрес: ";
        getline(cin, addr);

        client->setFirstName(fname);
        client->setLastName(lname);
        client->setPhoneNumber(phone);
        client->setAddress(addr);
        clientManager.saveToFile(); // Сохраняем изменения

        cout << "Данные клиента обновлены." << endl;
    }

    void deleteClient() {
        string id;
        cout << "Введите ID клиента для удаления: ";
        getline(cin, id);
        clientManager.removeItem(id);
        clientManager.saveToFile(); // Сохраняем изменения
    }

    void editPolicy() {
        string id;
        cout << "Введите ID полиса для редактирования: ";
        getline(cin, id);

        auto policy = policyManager.findItem(id);
        if (!policy) {
            cout << "Полис не найден." << endl;
            return;
        }

        cout << "Текущие данные:" << endl;
        cout << *policy << endl;

        string type, desc;
        double price;
        int duration;

        cout << "Новый тип полиса: ";
        getline(cin, type);
        cout << "Новое описание: ";
        getline(cin, desc);
        cout << "Новая цена: ";
        cin >> price;
        cout << "Новая длительность (мес.): ";
        cin >> duration;
        cin.ignore();

        policy->setPolicyType(type);
        policy->setDescription(desc);
        policy->setPrice(price);
        policy->setDuration(duration);
        policyManager.saveToFile(); // Сохраняем изменения

        cout << "Полис успешно обновлен." << endl;
    }

    void deletePolicy() {
        string id;
        cout << "Введите ID полиса для удаления: ";
        getline(cin, id);
        policyManager.removeItem(id);
        policyManager.saveToFile(); // Сохраняем изменения
    }

    void viewPolicies() {
        cout << "\n=== ДОСТУПНЫЕ ПОЛИСЫ ===" << endl;
        policyManager.displayAll();
    }

    void sortPolicies() {
        cout << "\n=== СОРТИРОВКА ПОЛИСОВ ПО ПОПУЛЯРНОСТИ ===" << endl;
        auto policies = policyManager.getAllItems();
        sort(policies.begin(), policies.end(),
            [](shared_ptr<InsurancePolicy> a, shared_ptr<InsurancePolicy> b) {
                return a->getPopularity() > b->getPopularity();
            });

        for (const auto& policy : policies) {
            cout << *policy << endl;
        }
    }

    void manageAccounts() {
        while (true) {
            cout << "\n=== УПРАВЛЕНИЕ УЧЕТНЫМИ ЗАПИСЯМИ ===" << endl;
            cout << "1. Просмотр всех пользователей" << endl;
            cout << "2. Добавить пользователя" << endl;
            cout << "3. Удалить пользователя" << endl;
            cout << "4. Назад" << endl;
            cout << "Выберите опцию: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                userManager.displayAll();
                User::displayUserCount();
                break;
            case 2: {
                string username, password, role;
                cout << "Имя пользователя: ";
                getline(cin, username);
                cout << "Пароль: ";
                password = Utils::getHiddenPassword();
                cout << "Роль (admin/user): ";
                getline(cin, role);
                registerUser(username, password, role);
                break;
            }
            case 3: {
                string username;
                cout << "Введите имя пользователя для удаления: ";
                getline(cin, username);
                if (username == "admin") {
                    cout << "Нельзя удалить администратора по умолчанию." << endl;
                }
                else {
                    userManager.removeUser(username);
                    userManager.saveToFile();
                    cout << "Пользователь удален." << endl;
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "Неверный выбор." << endl;
            }
        }
    }

    void showStatistics() {
        cout << "\n=== СТАТИСТИКА ===" << endl;
        cout << "Всего пользователей: " << User::userCount << endl;
        cout << "Администраторов: " << Admin::getAdminCount() << endl;
        cout << "Обычных пользователей: " << RegularUser::getRegularUserCount() << endl;

        auto policies = policyManager.getAllItems();
        auto clients = clientManager.getAllItems();

        cout << "Всего полисов: " << policies.size() << endl;
        cout << "Всего клиентов: " << clients.size() << endl;

        int activePolicies = 0;
        for (const auto& policy : policies) {
            if (policy->getIsActive()) activePolicies++;
        }
        cout << "Активных полисов: " << activePolicies << endl;

        if (!policies.empty()) {
            auto mostPopular = *max_element(policies.begin(), policies.end(),
                [](shared_ptr<InsurancePolicy> a, shared_ptr<InsurancePolicy> b) {
                    return a->getPopularity() < b->getPopularity();
                });
            cout << "Самый популярный полис: " << mostPopular->getPolicyType()
                << " (" << mostPopular->getPopularity() << " просмотров)" << endl;
        }
    }

    void logout() {
        saveAllData();
        currentUser = nullptr;
        cout << "Выход выполнен успешно. Данные сохранены." << endl;
    }
};

int main() {
    setRussianLocale();

    try {
        InsuranceSystem system;
        system.run();
    }
    catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}