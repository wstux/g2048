/*
 * games
 * Copyright (C) 2023  Chistyakov Alexander
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "g2048_core/grid.h"

namespace {

std::string to_string(const wstux::g2048::grid& grid)
{
    std::stringstream ss;
    for (size_t r = 0; r < grid.rows_count(); ++r) {
        for (size_t c = 0; c < grid.columns_count(); ++c) {
            const std::string val_str = std::to_string(grid.value(r, c));
            ss << " ";
            for (size_t i = val_str.size(); i < 5; ++i) { ss << " "; }
            ss << val_str;
            ss << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}

} // <anonymous> namespace

int main()
{
    wstux::g2048::grid grid(4, 4);
    const std::unordered_map<std::string, wstux::g2048::MoveType> cmds = {
        {"d",      wstux::g2048::MoveType::DOWN},
        {"down",   wstux::g2048::MoveType::DOWN},
        {"\x1B[B", wstux::g2048::MoveType::DOWN},
        {"l",      wstux::g2048::MoveType::LEFT},
        {"left",   wstux::g2048::MoveType::LEFT},
        {"\x1B[D", wstux::g2048::MoveType::LEFT},
        {"r",      wstux::g2048::MoveType::RIGHT},
        {"right",  wstux::g2048::MoveType::RIGHT},
        {"\x1B[C", wstux::g2048::MoveType::RIGHT},
        {"u",      wstux::g2048::MoveType::UP},
        {"up",     wstux::g2048::MoveType::UP},
        {"\x1B[A", wstux::g2048::MoveType::UP}
    };

    bool is_stop = false;
    while (! is_stop) {
        std::cout << "===========================================" << std::endl;
        std::cout << "Score: " << grid.score() << std::endl;
        std::cout << std::endl;
        std::cout << to_string(grid) << std::endl;
        std::cout << "===========================================" << std::endl;

        if (grid.max_value() == 2048) {
            std::cout << "Congratulations! You won!" << std::endl;
            is_stop = true;
            continue;
        }
        if (grid.is_finished()) {
            std::cout << "You lose" << std::endl;
            is_stop = true;
            continue;
        }

        bool was_action = false;
        do {
            std::cout << "Command: ";
            std::string cmd;
            std::cin >> cmd;
            if ((cmd == "quit") || (cmd == "q")) {
                is_stop = true;
                continue;
            }
            if (cmds.find(cmd) == cmds.cend()) {
                std::cout << "Invalid command" << std::endl;
                continue;
            }

            const wstux::g2048::MoveType m = cmds.at(cmd);
            was_action = grid.move(m);
            if (was_action && ! grid.is_finished()) {
                grid.add_new_value();
            }
        } while (! was_action);
    }

    return 0;
}

