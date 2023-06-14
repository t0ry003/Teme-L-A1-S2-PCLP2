//
// Created by rares on 6/11/2023.
//

#include <bits/stdc++.h>

using namespace std;

class NumberFormatException : public std::exception {
private:
    string message_;
public:
    explicit NumberFormatException(const string &value) : message_("Value " + value + " is not a valid number.") {}

    const char *what() const noexcept override {
        return message_.c_str();
    }
};

class Number {
public:
    static int64_t stoi(const string &str) {
        size_t i = 0;
        bool positive = true;

        while (i < str.length() && str[i] == ' ') {
            i++;
        }

        if (i < str.length() || (str[i] == '+' || str[i] == '-')) {
            if (str[i] == '-')
                positive = 0;
            if (!isdigit(str[i]))
                i++;
        } else {
            throw NumberFormatException(str);
        }

        long long result = 0;
        bool digitFound = false;

        if (isdigit(str[i])) {
            digitFound = true;
        } else {
            throw NumberFormatException(str);
        }

        int putere = 0;
        bool firstdigitdiffzero = false;
        while (i < str.length() && isdigit(str[i])) {
            if (str[i] - '0' != 0)
                firstdigitdiffzero = true;
            result = result * 10 + (str[i] - '0');
            if (firstdigitdiffzero)
                putere++;
            i++;
        }

        if (!positive) {
            result = -result;
        }

        int64_t resultcopy = result;

//        max is 18; 19 is overflow
        if (!positive && putere >= 19) {
            result = (int64_t) pow(2, 63) * (-1);
        } else if (positive && putere >= 19) {
            result = (int64_t) pow(2, 63) - 1;
        }

        if (resultcopy == 9223372036854775806)
            result = 9223372036854775806;
        else if (resultcopy == -9223372036854775807)
            result = -9223372036854775807;

        return result;
    }
};

class FileException : public exception {
private:
    string message_;
public:
    explicit FileException(const string &filename) : message_("Cannot open file " + filename + ".") {}

    const char *what() const noexcept override {
        return message_.c_str();
    }
};


class OpenFileException : public FileException {
public:
    explicit OpenFileException(const string &filename) : FileException(filename) {}
};


class InputFile : public ifstream {
public:
    InputFile() {}

    explicit InputFile(const string &filename) : ifstream(filename) {
        open(filename);
    }

    void open(const string &filename) {
        ifstream::open(filename);
        if (!is_open()) {
            throw OpenFileException(filename);
        }
    }

    ~InputFile() override {
        if (is_open())
            close();
    }
};

int main() {
    string filename;
    while (cin >> filename) {
        try {
            InputFile file(filename);
            ifstream fisier(filename);
            string line;
            while (getline(fisier, line)) {
                try {
                    cout << Number::stoi(line.c_str()) << '\n';
                } catch (NumberFormatException &ex) {
                    cout << ex.what() << '\n';
                }
            }
        } catch (OpenFileException &ex) {
            cout << ex.what() << '\n';
        }
    }
    return 0;
}
