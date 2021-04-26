#ifndef DATASTRUCTURE_DECK_HPP
#define DATASTRUCTURE_DECK_HPP

#include "../../../Structure/Linear/Chain_Unidirectional_Circle.hpp"
#include <utility>

using namespace std::rel_ops;
enum class Suit {
    Spades = 4, Hearts = 3, Diamonds = 2, Clubs = 1
};

class Card {
public:
    Card(int const &, int const &, Suit);

    Card &operator=(Card const &) noexcept = default;

    Card &operator=(Card &&) noexcept = default;

    Card(Card const &) noexcept = default;

    Card(Card &&) noexcept = default;

    bool operator==(Card const &) const;

    bool operator>(Card const &);

    explicit operator int() const;

    int group;

    int value;

    Suit suit;
};

Card::Card(int const &group, int const &value, Suit type)
        : group{group}, value{value}, suit{type} {}

bool Card::operator==(Card const &op) const {
    return ((void *) this == (void *) &op);
}

Card::operator int() const {
    return (int) this->suit + (this->value - 1) * 4;
}

bool Card::operator>(Card const &op) {
    if (this->group > op.group) return true;
    return ((int) (*this) > (int) op);
}

class Deck_Refresher {
public:
    Deck_Refresher(ChainUC <Card> &, int const &, bool const & = false);

    Deck_Refresher(Deck_Refresher const &) = delete;

    Deck_Refresher(Deck_Refresher &&) = delete;

private:
    ChainUC <Card> operator()(ChainUC <Card> &, int const &);

    bool reverse;
};

Deck_Refresher::Deck_Refresher(ChainUC <Card> &container, int const &groups, bool const &reverse)
        : reverse(reverse) { (*this)(container, groups); }

ChainUC <Card> Deck_Refresher::operator()(ChainUC <Card> &decks, int const &n)
{
    ChainUC <Card> Container(52 * n);
    // TODO
    return Container;
}


#endif //DATASTRUCTURE_DECK_HPP
