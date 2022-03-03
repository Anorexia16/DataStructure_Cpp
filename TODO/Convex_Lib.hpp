#ifndef DATASTRUCTURE_CONVEX_LIB_HPP
#define DATASTRUCTURE_CONVEX_LIB_HPP

static const double pi = 3.1415926;

# include <iostream>
# include <random>
# include <cmath>

class CL_Dot
{
public:
    explicit CL_Dot(double x = 0, double y = 0) : x{x}, y{y} {};

    static inline double distance(CL_Dot const &, CL_Dot const &);

    static inline double theta(CL_Dot const &, CL_Dot const &);

    static inline CL_Dot vector(CL_Dot const &, CL_Dot const &);

    static inline bool Obtuse(CL_Dot const &, CL_Dot const &, CL_Dot const &);

    double x;
    double y;

    friend std::ostream &operator<<(std::ostream &out, CL_Dot const &p)
    {
        char *temp = nullptr;
        sprintf(temp, "(%d, %d) ", p.x, p.y);
        out << temp;
        return out;
    }
};

double CL_Dot::distance(CL_Dot const &p1, CL_Dot const &p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

CL_Dot CL_Dot::vector(const CL_Dot &o, const CL_Dot &t)
{
    return CL_Dot(t.x - o.x, t.y - o.y);
}

double CL_Dot::theta(CL_Dot const &p1, CL_Dot const &p2)
{
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

bool CL_Dot::Obtuse(CL_Dot const &p1, CL_Dot const &p2, CL_Dot const &p3)
{
    double theta1 = theta(p2, p1);
    double theta2 = theta(p2, p3);
    theta1 = theta1 > pi ? theta1 - pi : theta1 + pi;
    return theta1 < theta2;
}

class Triangle : public CL_Dot {
public:
    Triangle(CL_Dot const &, CL_Dot const &, CL_Dot const &, bool const & = true);

    static CL_Dot take();

    CL_Dot p1;
    CL_Dot p2;
    CL_Dot p3;

private:
    [[nodiscard]] inline bool Construct_Check() const;
};

Triangle::Triangle(CL_Dot const &point1, CL_Dot const &point2, CL_Dot const &point3, const bool &access)
        : p1{point1}, p2{point2}, p3{point3}, CL_Dot() { if (!access) if (this->Construct_Check()) throw; }

bool Triangle::Construct_Check() const
{
    double a = CL_Dot::distance(p1, p2);
    double b = CL_Dot::distance(p2, p3);
    double c = CL_Dot::distance(p3, p1);
    return (a + b > c && a + c > b && b + c > a);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-mod_five"

CL_Dot Triangle::take()
{
    constexpr std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, 2);
    switch (u(e))
    {
        case 0:
            return p1;
        case 1:
            return p2;
        case 2:
            return p3;
    }
}

#pragma clang diagnostic pop

class Convex_Conversion
{
public:
    explicit Convex_Conversion(CL_Dot const & = CL_Dot{0, 0}, std::istream & = std::cin);

    static bool Is_Line();

    friend std::ostream &operator<<(std::ostream &out, Convex_Conversion const &op)
    {
        for (auto &&iter: op.Sets) out << iter;
        out << std::endl;
        return out;
    }

private:
    std::vector<CL_Dot> operator()();

    static inline bool Triangle_Check(CL_Dot const &, CL_Dot const &, CL_Dot const &);

    std::vector<CL_Dot> Sets;

    CL_Dot Original_Dot;
};

Convex_Conversion::Convex_Conversion(CL_Dot const &dot, std::istream &in)
        : Original_Dot{dot}, Sets{std::vector<Dot>{}}
{
    double temp1 = 0.0, temp2 = 0.0;
    do {
        in >> temp1;
        in >> temp2;
        Sets.emplace_back(CL_Dot(temp1, temp2));
    } while (in.good());

    (*this)();
}

bool Convex_Conversion::Triangle_Check(CL_Dot const &p1, CL_Dot const &p2, CL_Dot const &p3)
{
    double a = CL_Dot::distance(p1, p2);
    double b = CL_Dot::distance(p2, p3);
    double c = CL_Dot::distance(p3, p1);
    return (a + b > c && a + c > b && b + c > a);
}

bool Convex_Conversion::Is_Line()
{
    if (Sets.size() <= 2) return true;
    if (Sets.size() == 3) return Triangle_Check(Sets[0], Sets[1], Sets[2]);
    for (size_t iter1 = 0; iter1 != Sets.size() - 2; iter1++)
    {
        for (size_t iter2 = 0; iter2 != Sets.size() - 1; iter2++)
        {
            for (size_t iter3 = 0; iter3 != Sets.size(); iter3++)
            {
                if (!Triangle_Check(Sets[iter1], Sets[iter2], Sets[iter3])) return false;
            }
        }
    }
    return true;
}

std::vector<CL_Dot> Convex_Conversion::operator()()
{
    if (this->Sets.size() <= 2) throw;
    if (this->Sets.size() == 3)
        return this->Sets;
    decltype(auto) Container = this->Sets;
    bool Done_Flag = true;

    for (auto iter = 0; iter != Container.size(); iter++)
    {
        if (!CL_Dot::Obtuse(Container[iter], Container[(iter + 1) % Container.size()],
                            Container[(iter + 2) % Container.size()]))
        {
            Container.erase(std::begin(Container) + (iter + 1) % Container.size());
            Done_Flag = false;
        }
    }
    return Container;
}

#endif //DATASTRUCTURE_CONVEX_LIB_HPP