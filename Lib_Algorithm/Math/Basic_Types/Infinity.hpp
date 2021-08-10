#ifndef DATASTRUCTURE_INFINITY_HPP
#define DATASTRUCTURE_INFINITY_HPP


template<class cls>
concept fo_type = requires(cls const &c) {c+c;c-c;c+=c;c-=c;};

template<class cls>
concept so_type = requires(cls const &c) {c*c;c/c;c%c;c*=c;c/=c;c%=c;};


struct Infinity {
    template<class cls>
    constexpr bool operator>
    (cls const &) const
    {return true;}

    template<class cls>
    constexpr bool operator<
    (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator>=
    (cls const &)
    const {return true;}

    template<class cls>
    constexpr bool operator<=
    (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator==
    (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator!=
    (cls const &) const
    {return true;}

    constexpr bool operator>
    (Infinity const &) const
    {return false;}

    constexpr bool operator<
    (Infinity const &) const
    {return false;}

    constexpr bool operator>=
    (Infinity const &) const
    {return true;}

    constexpr bool operator<=
    (Infinity const &) const
    {return true;}

    constexpr bool operator==
    (Infinity const &) const
    {return true;}

    constexpr bool operator!=
    (Infinity const &) const
    {return false;}

    template<fo_type cls>
    Infinity operator+
    (cls const &) const
    {return Infinity{};}

    template<fo_type cls>
    Infinity operator-
    (cls const &) const
    {return Infinity{};}

    template<fo_type cls>
    Infinity &operator+=
    (cls const &)
    {return *this;}

    template<fo_type cls>
    Infinity &operator-=
    (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity operator*
    (cls const &) const
    {return Infinity{};}

    template<so_type cls>
    Infinity operator/
    (cls const &) const
    {return Infinity{};}

    template<so_type cls>
    Infinity &operator*=
    (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity &operator/=
    (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity operator%
    (cls const &) const
    = delete;

    template<so_type cls>
    Infinity &operator%=
    (cls const &)
    = delete;

    Infinity operator+
    (Infinity const &) const
    {return Infinity{};}

    Infinity operator-
    (Infinity const &) const
    = delete;

    Infinity &operator+=
    (Infinity const &)
    {return *this;}

    Infinity &operator-=
    (Infinity const &)
    = delete;

    Infinity operator*
    (Infinity const &) const
    {return Infinity{};}

    Infinity operator/
    (Infinity const &) const
    = delete;

    Infinity operator%
    (Infinity const &) const
    = delete;

    Infinity &operator*=
    (Infinity const &)
    {return *this;}

    Infinity &operator/=
    (Infinity const &)
    = delete;

    Infinity &operator%=
    (Infinity const &)
    = delete;

    Infinity operator++(int) const
    {return Infinity{};}

    Infinity operator--(int) const
    {return Infinity{};}

    Infinity &operator++()
    {return *this;}

    Infinity &operator--()
    {return  *this;}

    template<so_type cls>
    cls dev(cls const &c)
    {return cls{};}

    template<so_type cls>
    cls &dev_r(cls &c)
    {c = cls{};return c;}
};

#endif //DATASTRUCTURE_INFINITY_HPP
