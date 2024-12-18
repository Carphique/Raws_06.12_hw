#include <iostream>
#include <string>

using namespace std;

class MyString {
    char* arr;
    int Capacity;
public:
    MyString() { // конструктор за замовчуванням
        this->arr = new char[1];
        this->arr[0] = '\0';
        this->Capacity = 1;
    }

    MyString(const char* arr) { // конструктор з параметрами
        int amount = 0;
        while (arr[amount] != '\0') {
            amount++;
        }
        this->Capacity = amount + 1;
        this->arr = new char[this->Capacity];
        for (int i = 0; i < this->Capacity; i++) {
            this->arr[i] = arr[i];
        }
    }

    MyString(const MyString& other) { // конструктор копіювання
        this->Capacity = other.Capacity;
        this->arr = new char[this->Capacity];
        for (int i = 0; i < this->Capacity; i++) {
            this->arr[i] = other.arr[i];
        }
    }

    MyString& operator=(const MyString& other) { // оператор присвоювання
        if (this == &other) return *this;
        delete[] this->arr;
        this->Capacity = other.Capacity;
        this->arr = new char[this->Capacity];
        for (int i = 0; i < this->Capacity; i++) {
            this->arr[i] = other.arr[i];
        }
        return *this;
    }

    char& operator[](int index) { // оператор індексації
        if (index < 0 || index >= size()) throw out_of_range("Index out of bounds");
        return this->arr[index];
    }

    friend ostream& operator<<(ostream& os, const MyString& str) { // оператор виводу в консоль
        os << str.arr;
        return os;
    }

    void append(char symbol) { // додати елемент в кінець рядку
        int amount = size();
        char* tempArr = new char[amount + 2];
        for (int i = 0; i < amount; i++) {
            tempArr[i] = this->arr[i];
        }
        tempArr[amount] = symbol;
        tempArr[amount + 1] = '\0';
        delete[] this->arr;
        this->arr = tempArr;
        this->Capacity = amount + 2;
    }

    void push_back(char symbol) { // додати символ на початок
        int amount = size();
        char* tempArr = new char[amount + 2];
        tempArr[0] = symbol;
        for (int i = 0; i < amount; i++) {
            tempArr[i + 1] = this->arr[i];
        }
        tempArr[amount + 1] = '\0';
        delete[] this->arr;
        this->arr = tempArr;
        this->Capacity = amount + 2;
    }

    void pop_back() { // видалити останній символ
        int amount = size();
        if (amount == 0) return;
        char* tempArr = new char[amount];
        for (int i = 0; i < amount - 1; i++) {
            tempArr[i] = this->arr[i];
        }
        tempArr[amount - 1] = '\0';
        delete[] this->arr;
        this->arr = tempArr;
        this->Capacity = amount;
    }

    int size() const { // отримати кількість символів
        int amount = 0;
        while (this->arr[amount] != '\0') {
            amount++;
        }
        return amount;
    }

    int capacity() const { // отримати об'єм елементів
        return this->Capacity;
    }

    int length() const { // кількість символів
        return size();
    }

    void clear() { // Очистити рядок
        delete[] this->arr;
        this->arr = new char[1];
        this->arr[0] = '\0';
        this->Capacity = 1;
    }

    MyString copy() const { // копіювати рядок
        return MyString(*this);
    }

    int find(const char* substring) { // знайти підрядок
        int subLength = 0;
        while (substring[subLength] != '\0') {
            subLength++;
        }

        for (int i = 0; i <= size() - subLength; i++) {
            int j = 0;
            while (j < subLength && this->arr[i + j] == substring[j]) {
                j++;
            }
            if (j == subLength) return i;
        }
        return -1; // підрядок не знайдено (((
    }

    void insert(int index, const char* substring) { // вставити підрядок за індексом
        if (index < 0 || index > size()) throw out_of_range("Index out of bounds");
        int subLength = 0;
        while (substring[subLength] != '\0') {
            subLength++;
        }

        int newSize = size() + subLength;
        char* tempArr = new char[newSize + 1];

        for (int i = 0; i < index; i++) {
            tempArr[i] = this->arr[i];
        }
        for (int i = 0; i < subLength; i++) {
            tempArr[index + i] = substring[i];
        }
        for (int i = index; i < size(); i++) {
            tempArr[subLength + i] = this->arr[i];
        }

        tempArr[newSize] = '\0';
        delete[] this->arr;
        this->arr = tempArr;
        this->Capacity = newSize + 1;
    }

    ~MyString() { // деструктор
        delete[] this->arr;
    }
};

int main() {
    MyString str = "Boryslav";
    cout << str << endl;
    str.append('s');
    cout << str << endl;
    str.push_back('L');
    cout << str << endl;
    str.pop_back();
    cout << str << endl;
    cout << str.size() << endl;
    cout << str.capacity() << endl;

    MyString str2 = str.copy();
    cout << str2 << endl;

    cout << str.find("ry") << endl;

    str.insert(3, "xzChtoVstavit");
    cout << str << endl;

    str.clear();
    cout << str << endl;
}
