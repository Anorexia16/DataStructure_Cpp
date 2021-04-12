#ifndef DATASTRUCTURE_LONGEST_PROCESSING_TIME_HPP
#define DATASTRUCTURE_LONGEST_PROCESSING_TIME_HPP

#include <map>
#include <vector>
#include "../../Structure/Assistance/Storage_Unit.hpp"
#include "../../Structure/Dendroid/Leftist_Tree.hpp"

using Machine_Info = Pair_Unit<double, size_t>;

std::vector<std::vector<size_t>> solve_lpt(std::vector<double> const &time_chart, size_t const &machine_num)
{
    Leftist_Tree<Machine_Info> _machine_time = make_LT<Machine_Info>(true);
    Machine_Info machine_instance;
    for (size_t machine = 0; machine != machine_num; ++machine)
    {
        machine_instance = Machine_Info {0, machine};
        _machine_time.insert(machine_instance);
    }
    std::vector<Pair_Unit<double, size_t>> _task_info {};

    _task_info.reserve(time_chart.size());
    for (size_t i = 0; i < time_chart.size(); ++i) _task_info.emplace_back(Pair_Unit<double, size_t> {time_chart[i], i});
    Leftist_Tree<Pair_Unit<double, size_t>> _longest_task = make_LT<Pair_Unit<double, size_t>>(_task_info, false);
    std::vector<std::vector<size_t>> res {};

    for (size_t _index = 0; _index != machine_num; ++_index) res.template emplace_back(std::vector<size_t>{});

    for(size_t _index = 0; _index!=time_chart.size() ; ++_index)
    {
        res[_machine_time.top().Value].emplace_back(_longest_task.top().Value);
        _machine_time.insert(Machine_Info {_machine_time.top().Key + _longest_task.top().Key, _machine_time.top().Value});
        _machine_time.pop();
        _longest_task.pop();
    }
    return res;
}

#endif //DATASTRUCTURE_LONGEST_PROCESSING_TIME_HPP
