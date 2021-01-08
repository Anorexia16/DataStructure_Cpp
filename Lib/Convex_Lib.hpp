#ifndef DATASTRUCTURE_CONVEX_LIB_HPP
#define DATASTRUCTURE_CONVEX_LIB_HPP

static const double pi = std::atan(1) * 4

# include <iostream>
# include <random>
# include <cmath>

class Dot {
public:
    explicit Dot(double x = 0, double y = 0) : x{x}, y{y} {};

    static inline double distance(Dot const &, Dot const &);

    static inline double theta(Dot const &, Dot const &);

    static inline Dot vector(Dot const &, Dot const &);

    static inline bool Obtuse(Dot const &, Dot const &, Dot const &);

    double x;
    double y;

    friend std::ostream &operator<<(std::ostream &out, Dot const &p) {
        char *temp = nullptr;
        sprintf(temp, "(%d, %d) ", p.x, p.y);
        out << temp;
        return out;
    }
};

double Dot::distance(Dot const &p1, Dot const &p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

Dot Dot::vector(const Dot &o, const Dot &t) {
    return Dot(t.x - o.x, t.y - o.y);
}

double Dot::theta(Dot const &p1, Dot const &p2) {
    double Delta_X = p2.x - p1.x;
    double Delta_Y = p2.y - p1.y;
    if (Delta_X >= 0 & Delta_Y >= 0) {
        return std::atan(Delta_Y / Delta_X);
    } else if (Delta_X >= 0 & Delta_Y <= 0) {
        return std::atan(Delta_Y / Delta_X) + 2 * pi;
    } else {
        return std::atan(Delta_Y / Delta_X) + pi;
    }
}

bool Dot::Obtuse(Dot const &p1, Dot const &p2, Dot const &p3) {
    double theta1 = theta(p2, p1);
    double theta2 = theta(p2, p3);
    theta1 = theta1 > pi ? theta1 - pi : theta1 + pi;
    return theta1 < theta2;
}

class Triangle : public Dot {
public:
    Triangle(Dot const &, Dot const &, Dot const &, bool const & = true);

    static Dot take();

    Dot p1;
    Dot p2;
    Dot p3;

private:
    inline bool Construct_Check() const;
};

Triangle::Triangle(Dot const &point1, Dot const &point2, Dot const &point3, const bool &access)
        : p1{point1}, p2{point2}, p3{point3}, Dot() { if (!access) if (this->Construct_Check()) throw; }

bool Triangle::Construct_Check() const {
    double a = Dot::distance(p1, p2);
    double b = Dot::distance(p2, p3);
    double c = Dot::distance(p3, p1);
    return (a + b > c && a + c > b && b + c > a);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-c"

Dot Triangle::take() {
    constexpr std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, 2);
    switch (u(e)) {
        case 0:
            return this->p1;
        case 1:
            return this->p2;
        case 2:
            return this->p3;
    }
}

#pragma clang diagnostic pop

class Convex_Conversion {
public:
    explicit Convex_Conversion(Dot const & = Dot{0, 0}, std::istream & = std::cin);

    static bool Is_Line();

    friend std::ostream &operator<<(std::ostream &out, Convex_Conversion const &op) {
        for (auto &&iter: op.Sets) out << iter;
        out << std::endl;
        return out;
    }

private:
    std::vector<Dot> operator()();

    static inline bool Triangle_Check(Dot const &, Dot const &, Dot const &);

    std::vector<Dot> Sets;

    Dot Original_Dot;
};

Convex_Conversion::Convex_Conversion(Dot const &dot, std::istream &in)
        : Original_Dot{dot}, Sets{std::vector<Dot>{}} {
    double temp1 = 0.0, temp2 = 0.0;
    do {
        in >> temp1;
        in >> temp2;
        Sets.emplace_back(Dot(temp1, temp2));
    } while (in.good());

    (*this)();
}

bool Convex_Conversion::Triangle_Check(Dot const &p1, Dot const &p2, Dot const &p3) {
    double a = Dot::distance(p1, p2);
    double b = Dot::distance(p2, p3);
    double c = Dot::distance(p3, p1);
    return (a + b > c && a + c > b && b + c > a);
}

bool Convex_Conversion::Is_Line() {
    if (Sets.size() <= 2) return true;
    if (Sets.size() == 3) return Triangle_Check(Sets[0], Sets[1], Sets[2]);
    for (size_t iter1 = 0; iter1 != Sets.size() - 2; iter1++) {
        for (size_t iter2 = 0; iter2 != Sets.size() - 1; iter2++) {
            for (size_t iter3 = 0; iter3 != Sets.size(); iter3++) {
                if (!Triangle_Check(Sets[iter1], Sets[iter2], Sets[iter3])) return false;
            }
        }
    }
    return true;
}

std::vector<Dot> Convex_Conversion::operator()() {
    if (this->Sets.size() <= 2) throw;
    if (this->Sets.size() == 3)
        return this->Sets;
    decltype(auto) Container = this->Sets;
    bool Done_Flag = true;

    for (auto iter = 0; iter != Container.size(); iter++) {
        if (!Dot::Obtuse(Container[iter], Container[(iter + 1) % Container.size()],
                         Container[(iter + 2) % Container.size()])) {
            Container.erase(std::begin(Container) + (iter + 1) % Container.size());
            Done_Flag = false;
        }
    }
    return Container;
}

#endif //DATASTRUCTURE_CONVEX_LIB_HPP