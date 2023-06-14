//
// Created by rares on 5/13/2023.
//

#include <bits/stdc++.h>

using namespace std;

class Policy {
protected:
    bool isChecked;
public:
    virtual void check(const string &_password) = 0;

    bool getCheck() const {
        return isChecked;
    }
};

class LengthPolicy : public Policy {
private:
    uint16_t minLength;
    uint16_t maxLength;
public:
    LengthPolicy(uint16_t _minLength) : minLength(_minLength), maxLength(255) {}

    LengthPolicy(uint16_t _minLength, uint16_t _maxLength) : minLength(_minLength), maxLength(_maxLength) {}

    void check(const string &_password) override {
        ;
        if (_password.length() >= minLength && _password.length() <= maxLength) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

class ClassPolicy : public Policy {
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t _minClassCount) : minClassCount(_minClassCount) {}

    void check(const string &_password) override {
        uint16_t classCount = 0;
        bool hasDigit = false;
        bool hasLower = false;
        bool hasUpper = false;
        bool hasSpecial = false;
        for (char c: _password) {
            if (isdigit(c)) {
                hasDigit = true;
            } else if (islower(c)) {
                hasLower = true;
            } else if (isupper(c)) {
                hasUpper = true;
            } else if (!isalnum(c)) {
                hasSpecial = true;
            }
        }
        if (hasDigit) {
            classCount++;
        }
        if (hasLower) {
            classCount++;
        }
        if (hasUpper) {
            classCount++;
        }
        if (hasSpecial) {
            classCount++;
        }
        if (classCount >= minClassCount) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

class IncludePolicy : public Policy {
private:
    char characterType;
public:
    IncludePolicy(char _characterType) : characterType(_characterType) {}


    bool isType(char c) {
        if (isdigit(characterType)) {
            return isdigit(c);
        } else if (islower(characterType)) {
            return islower(c);
        } else if (isupper(characterType)) {
            return isupper(c);
        } else {
            return !isalnum(c);
        }
    }

    void check(const string &_password) override {
        for (char c: _password) {
            if (isType(c)) {
                isChecked = true;
                return;
            }
        }
        isChecked = false;
    };
};

class NotIncludePolicy : public Policy {
private:
    char characterType;
public:
    NotIncludePolicy(char _characterType) : characterType(_characterType) {}

    bool isType(char c) {
        if (isdigit(characterType)) {
            return isdigit(c);
        } else if (islower(characterType)) {
            return islower(c);
        } else if (isupper(characterType)) {
            return isupper(c);
        } else {
            return !isalnum(c);
        }
    }

    void check(const string &_password) override {
        for (char c: _password) {
            if (isType(c)) {
                isChecked = false;
                return;
            }
        }
        isChecked = true;
    }
};

class RepetitionPolicy : public Policy {
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t _maxCount) : maxCount(_maxCount) {}

    void check(const string &_password) override {
        uint16_t count = 0;
        uint16_t currentCount = 1;
        for (int i = 0; i < _password.length() - 1; i++) {
            if (_password[i] == _password[i + 1]) {
                currentCount++;
            } else {
                if (currentCount > count) {
                    count = currentCount;
                }
                currentCount = 1;
            }
        }
        if (currentCount > count) {
            count = currentCount;
        }

        if (count <= maxCount) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

class ConsecutivePolicy : public Policy {
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t _maxCount) : maxCount(_maxCount) {}

    void check(const string &_password) override {
        uint16_t count = 0;
        uint16_t currentCount = 1;
        for (int i = 0; i < _password.length() - 1; i++) {
            if (_password[i] + 1 == _password[i + 1]) {
                currentCount++;
            } else {
                if (currentCount > count) {
                    count = currentCount;
                }
                currentCount = 1;
            }
        }
        if (currentCount > count) {
            count = currentCount;
        }

        if (count <= maxCount) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }
};

string checkPassword(string _password, vector<Policy *> _policies) {
    for (auto policy: _policies) {
        policy->check(_password);
        if (!policy->getCheck()) {
//            cout << typeid(*policy).name() << endl;
            return "NOK";
        }
    }
    return "OK";
}

int main() {
    int n_policies;
    cin >> n_policies;

    vector<Policy *> policies;
    for (int i = 1; i <= n_policies; i++) {
        string policy_type;
        cin >> policy_type;
        if (policy_type == "length") {
            uint16_t min_length, max_length;
            cin >> min_length;
            if (isdigit(cin.ignore().peek())) {
                cin >> max_length;
            } else {
                max_length = 255;
            }
            policies.push_back(new LengthPolicy(min_length, max_length));
        } else if (policy_type == "class") {
            uint16_t min_class_count;
            cin >> min_class_count;
            policies.push_back(new ClassPolicy(min_class_count));
        } else if (policy_type == "include") {
            char character_type;
            cin >> character_type;
            policies.push_back(new IncludePolicy(character_type));
        } else if (policy_type == "ninclude") {
            char character_type;
            cin >> character_type;
            policies.push_back(new NotIncludePolicy(character_type));
        } else if (policy_type == "repetition") {
            uint16_t max_count;
            cin >> max_count;
            policies.push_back(new RepetitionPolicy(max_count));
        } else if (policy_type == "consecutive") {
            uint16_t max_count;
            cin >> max_count;
            policies.push_back(new ConsecutivePolicy(max_count));
        }
    }

    string password;
    while (cin >> password) {
        cout << checkPassword(password, policies) << endl;
    }
    return 0;
}
