#ifndef DATASTRUCTURE_UTILITY_HPP
#define DATASTRUCTURE_UTILITY_HPP

namespace ax {
    template<typename Tp>
    inline Tp remove_reference(Tp && value)
    {
        return Tp{value};
    }

    template<typename Tp>
    inline Tp remove_reference(Tp const& value)
    {
        return Tp{value};
    }

    template<typename Tp>
    inline Tp remove_reference(Tp & value)
    {
        return Tp{value};
    }

    template<typename Tp>
    inline Tp remove_reference(Tp value)
    {
        return Tp{value};
    }

    template <class T>
    decltype(auto) move(T&& t) noexcept
    {
        return static_cast<decltype(remove_reference(t))>(t);
    }

    template<typename tp>
    tp max(tp const &x, tp const &y)
    {
        return x>y?x:y;
    }

    template<typename tp>
    tp min(tp const &x, tp const &y)
    {
        return x<y?x:y;
    }
}

#endif //DATASTRUCTURE_UTILITY_HPP
