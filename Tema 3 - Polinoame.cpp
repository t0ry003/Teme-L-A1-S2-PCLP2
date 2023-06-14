#include <bits/stdc++.h>

using namespace std;

class Polynomial {
protected:
    vector<double> mCoeffs;
    uint32_t mDegree;
public:
    Polynomial(const vector<double> &_coef) {
        mCoeffs = _coef;
        mDegree = _coef.size() - 1;
    }

    Polynomial(uint32_t grad) {
        mDegree = grad;
        for (int i = 0; i < grad + 1; i++) {
            mCoeffs.push_back(0);
        }

    }

    Polynomial derivate() const {
        Polynomial p = *this;
        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        p.mCoeffs.erase(p.mCoeffs.begin());

        for (int i = 0; i < p.mCoeffs.size(); i++) {
            p.mCoeffs[i] *= (i + 1);
        }

        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        p.mDegree--;

        return p;
    }

    double calculate(double value) const {
        Polynomial p = *this;

        double x = 0;

        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        for (int i = 0; i < p.mCoeffs.size(); i++) {
            x += p.mCoeffs[i] * pow(value, i);
        }

        return x;
    }

    complex<double> calculate(const complex<double> &value) const {
        Polynomial p = *this;

        complex<double> x = 0;

        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        for (int i = 0; i < p.mCoeffs.size(); i++) {
            x += p.mCoeffs[i] * pow(value, i);
        }

        return x;
    }

    uint32_t getDegree() const {
        return mDegree;
    }

    double &operator[](uint32_t index) {
        return mCoeffs[index];
    }

    double operator[](uint32_t index) const {
        return mCoeffs[index];
    }

    Polynomial operator+(const Polynomial &rhs) const {
        Polynomial p1 = *this;
        Polynomial p2 = rhs;

        Polynomial p(max(mDegree, rhs.mDegree));

        reverse(p1.mCoeffs.begin(), p1.mCoeffs.end());
        reverse(p2.mCoeffs.begin(), p2.mCoeffs.end());

        for (int i = 0; i < p1.mCoeffs.size(); i++) {
            p[i] += p1[i];
        }

        for (int i = 0; i < p2.mCoeffs.size(); i++) {
            p[i] += p2[i];
        }

        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        return p;
    }

    Polynomial operator*(const Polynomial &rhs) const {
        Polynomial p1 = *this;
        Polynomial p2 = rhs;

        Polynomial p(mDegree + rhs.mDegree);

        reverse(p1.mCoeffs.begin(), p1.mCoeffs.end());
        reverse(p2.mCoeffs.begin(), p2.mCoeffs.end());

        for (int i = 0; i < p1.mCoeffs.size(); i++) {
            for (int j = 0; j < p2.mCoeffs.size(); j++) {
                p[i + j] += p1[i] * p2[j];
            }
        }

        reverse(p.mCoeffs.begin(), p.mCoeffs.end());

        return p;
    }

    Polynomial &operator*=(const double constant) {
        for (auto &x: mCoeffs)
            x *= constant;

        return *this;
    }

    Polynomial &operator/=(const double constant) {
        for (auto &x: mCoeffs)
            x /= constant;

        return *this;
    }

    virtual vector<std::complex<double>> roots() const {
        cout << "Implementation for method roots for polynomials with degree = " << mDegree << " is not available."
             << endl;

        vector<complex<double>> v;

        return v;
    }
};

class ZeroDegreePolynomial : public Polynomial {
public:
    ZeroDegreePolynomial(const vector<double> &_coef) : Polynomial(_coef) {
        if (_coef.size() != 1) {
            cout << "Error: Invalid number of coefficients for a zero degree polynomial." << endl;
            exit(1);
        }
    }

    ZeroDegreePolynomial(uint32_t grad) : Polynomial(grad) {
        if (grad != 0) {
            cout << "Error: Invalid number of coefficients for a zero degree polynomial." << endl;
            exit(1);
        }
    }

    vector<std::complex<double>> roots() const override {
        vector<complex<double>> v;

        if (mCoeffs[0] == 0) {
            cout << "Polynomials with degree 0 doesn't have roots." << endl;
            return vector<complex<double>>();
        }

        return v;
    }
};

class FirstDegreePolynomial : public Polynomial {
public:
    FirstDegreePolynomial(const vector<double> &_coef) : Polynomial(_coef) {
        if (_coef.size() != 2) {
            cout << "Error: Invalid number of coefficients for a first degree polynomial." << endl;
            exit(1);
        }
    }

    FirstDegreePolynomial(uint32_t grad) : Polynomial(grad) {}

    vector<std::complex<double>> roots() const override {
        vector<complex<double>> v;

        if (mCoeffs[1] == 0) {
            cout << "Polynomials with degree 1 doesn't have roots." << endl;
            return vector<complex<double>>();
        }

        v.push_back(-mCoeffs[0] / mCoeffs[1]);

        return v;
    }
};

class SecondDegreePolynomial : public Polynomial {
public:
    SecondDegreePolynomial(const vector<double> &_coef) : Polynomial(_coef) {}

    SecondDegreePolynomial(uint32_t grad) : Polynomial(grad) {}

    vector<std::complex<double>> roots() const override {
        vector<complex<double>> v;

        if (mCoeffs[2] == 0) {
            cout << "Polynomials with degree 2 doesn't have roots." << endl;
            return vector<complex<double>>();
        }

        double delta = mCoeffs[1] * mCoeffs[1] - 4 * mCoeffs[2] * mCoeffs[0];

        if (delta == 0) {
            v.push_back(-mCoeffs[1] / (2 * mCoeffs[2]));
        } else if (delta > 0) {
            v.push_back((-mCoeffs[1] + sqrt(delta)) / (2 * mCoeffs[2]));
            v.push_back((-mCoeffs[1] - sqrt(delta)) / (2 * mCoeffs[2]));
        } else {
            v.push_back(complex<double>(-mCoeffs[1] / (2 * mCoeffs[2]), sqrt(-delta) / (2 * mCoeffs[2])));
            v.push_back(complex<double>(-mCoeffs[1] / (2 * mCoeffs[2]), -sqrt(-delta) / (2 * mCoeffs[2])));
        }

        return v;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
