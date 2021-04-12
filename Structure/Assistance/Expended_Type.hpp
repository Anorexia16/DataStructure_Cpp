#ifndef DATASTRUCTURE_EXPENDED_TYPE_HPP
#define DATASTRUCTURE_EXPENDED_TYPE_HPP

template<class cls>
class Expended_Type
{
public:
    explicit Expended_Type(cls &&);

    Expended_Type(bool const &, bool const &);

    inline void set(cls &&);

    inline void set_null();

    inline void set_inf();

    [[nodiscard]] inline bool is_null() const;

    [[nodiscard]] inline bool is_inf() const;

    inline cls *operator->();

    inline cls &operator*();

    inline bool operator==(Expended_Type const &) const;

    inline bool operator!=(Expended_Type const &) const;

    inline bool operator>(Expended_Type const &) const;

    inline bool operator<(Expended_Type const &) const;

    inline bool operator>=(Expended_Type const &) const;

    inline bool operator<=(Expended_Type const &) const;

    inline bool operator==(cls const &) const;

    inline bool operator!=(cls const &) const;

    inline bool operator>(cls const &) const;

    inline bool operator<(cls const &) const;

    inline bool operator>=(cls const &) const;

    inline bool operator<=(cls const &) const;

protected:
    cls Value;
    bool Is_Null;
    bool Is_Inf;
};

template<class cls>
Expended_Type<cls>::Expended_Type(cls &&instance)
:Value{std::forward<cls>(instance)}, Is_Inf{false}, Is_Null{false} {}

template<class cls>
Expended_Type<cls>::Expended_Type(bool const &null, bool const &inf)
:Value{}, Is_Null{null}, Is_Inf{!null && inf} {}

template<class cls>
void Expended_Type<cls>::set(cls &&instance)
{
    this->Is_Inf = false;
    this->Is_Null = false;
    this->Value = std::forward<cls>(instance);
}

template<class cls>
void Expended_Type<cls>::set_null()
{
    this->Is_Inf = false;
    this->Is_Null = true;
}

template<class cls>
void Expended_Type<cls>::set_inf()
{
    this->Is_Null = false;
    this->Is_Inf = true;
}

template<class cls>
bool Expended_Type<cls>::is_null() const
{
    return this->Is_Null;
}

template<class cls>
bool Expended_Type<cls>::is_inf() const
{
    return this->Is_Inf;
}

template<class cls>
cls *Expended_Type<cls>::operator->()
{
    return &this->Value;
}

template<class cls>
cls &Expended_Type<cls>::operator*()
{
    return this->Value;
}

template<class cls>
bool Expended_Type<cls>::operator==(Expended_Type const &instance) const
{
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) return false;
    return this->Value == instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator!=(Expended_Type const &instance) const
{
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) return false;
    return this->Value != instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator>(Expended_Type const &instance) const
{
    if (this->Is_Inf && !instance.Is_Inf) return true;
    if (this->Is_Null || instance.Is_Null) throw;
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) throw;
    return this->Value > instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator<(Expended_Type const &instance) const
        {
    if (this->Is_Inf && !instance.Is_Inf) return true;
    if (this->Is_Null || instance.Is_Null) throw;
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) throw;
    return this->Value < instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator>=(Expended_Type const &instance) const
{
    if (this->Is_Inf && !instance.Is_Inf) return true;
    if (this->Is_Null || instance.Is_Null) throw;
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) throw;
    return this->Value >= instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator<=(Expended_Type const &instance) const
{
    if (this->Is_Inf && !instance.Is_Inf) return true;
    if (this->Is_Null || instance.Is_Null) throw;
    if (this->Is_Inf || instance.Is_Inf || this->Is_Null || instance.Is_Null) throw;
    return this->Value <= instance.Value;
}

template<class cls>
bool Expended_Type<cls>::operator==(const cls &instance) const
{
    if (this->Is_Inf) return false;
    if (this->Is_Null) throw;
    return this->Value == instance;
}

template<class cls>
bool Expended_Type<cls>::operator!=(const cls &instance) const
{
    if (this->Is_Inf) return false;
    if (this->Is_Null) throw;
    return this->Value != instance;
}

template<class cls>
bool Expended_Type<cls>::operator>(const cls &instance) const
{
    if (this->Is_Inf) return true;
    if (this->Is_Null) throw;
    return this->Value > instance;
}

template<class cls>
bool Expended_Type<cls>::operator<(const cls &instance) const
{
    if (this->Is_Inf) return false;
    if (this->Is_Null) throw;
    return this->Value < instance;
}

template<class cls>
bool Expended_Type<cls>::operator>=(const cls &instance) const
{
    if (this->Is_Inf) return true;
    if (this->Is_Null) throw;
    return this->Value >= instance;
}

template<class cls>
bool Expended_Type<cls>::operator<=(const cls &instance) const
{
    if (this->Is_Inf) return false;
    if (this->Is_Null) throw;
    return this->Value <= instance;
}

#endif //DATASTRUCTURE_EXPENDED_TYPE_HPP
