#ifndef DATASTRUCTURE_ORTHOGONAL_LIST_ALIGNED_HPP
#define DATASTRUCTURE_ORTHOGONAL_LIST_ALIGNED_HPP

#include <cstdlib>

template<typename Tp>
struct Orthogonal_Node {
    Orthogonal_Node *right {nullptr};
    Orthogonal_Node *down {nullptr};
    ssize_t row{};
    ssize_t col{};
    Tp var;
};

template<typename Tp>
struct Orthogonal_List_Aligned {
    Orthogonal_Node<Tp> *CHead {nullptr};
    Orthogonal_Node<Tp> *RHead {nullptr};
    size_t columns{};
    size_t rows{};
};

template<typename Tp, size_t rows, size_t columns>
Orthogonal_List_Aligned<Tp> make_OTL(Tp (&array)[rows][columns]) {
    Orthogonal_List_Aligned<Tp> _matrix {nullptr, nullptr, rows, columns};
    Tp const _empty {};

    _matrix.CHead = new Orthogonal_Node<Tp> {nullptr, nullptr, -1, 0, _empty};
    Orthogonal_Node<Tp> *_cIter = _matrix.CHead;
    for (ssize_t ci=1; ci != columns; ++ci, _cIter=_cIter->right)
        _cIter->right = new Orthogonal_Node<Tp>{_cIter->right, nullptr, -1, ci, _empty};

    _matrix.RHead = new Orthogonal_Node<Tp> {nullptr, nullptr, 0, -1, _empty};
    Orthogonal_Node<Tp> *_rIter = _matrix.RHead;
    for (ssize_t ri=1; ri != rows; ++ri, _rIter=_rIter->down)
        _rIter->down = new Orthogonal_Node<Tp>{nullptr, _rIter->down, ri, -1, _empty};

    Orthogonal_Node<Tp> *_rIdx = _matrix.RHead;
    for (ssize_t ri=0;ri!=rows;++ri, _rIdx=_rIdx->down) {
        _cIter = _rIdx;
        for (ssize_t ci=0;ci!=columns;++ci) {
            if (array[ri][ci]!=_empty) {
                _cIter->right = new Orthogonal_Node<Tp> {nullptr, nullptr, ri, ci, array[ri][ci]};
                _cIter = _cIter->right;
                _rIter = _matrix.CHead;
                for (size_t bi=0;bi!=ci; ++bi, _rIter=_rIter->right);
                for (;_rIter->down!= nullptr; _rIter=_rIter->down);
                _rIter->down = _cIter;
            }
        }
    }

    return _matrix;
}

#endif //DATASTRUCTURE_ORTHOGONAL_LIST_ALIGNED_HPP
