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

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "g2048_core/grid.h"

namespace wstux {
namespace g2048 {
namespace {

template<typename T>
std::pair<T, T> gen_random_pos(const size_t row_count, const size_t col_count)
{
    static bool is_once = true;
    if (is_once) {
        is_once = false;
        std::srand(std::time(nullptr));
    }

    std::pair<T, T> pos;
    pos.first = std::rand() % row_count;
    pos.second = std::rand() % col_count;
    return pos;
}

template<typename T>
T gen_random_value()
{
    static bool is_once = true;
    if (is_once) {
        is_once = false;
        std::srand(std::time(nullptr));
    }
    const double r = static_cast<double>(std::rand()) / RAND_MAX + 0.5;
    return static_cast<T>(r) + 1;
}

} // <anonymous> namespace

///////////////////////////////////////////////////////////////////////////////
/// struct grid::position

struct grid::position
{
    using value_type = grid::value_type;

    value_type row;
    value_type col;

    bool is_valid_col() const { return (col != std::numeric_limits<value_type>::max()); }
    bool is_valid_row() const { return (row != std::numeric_limits<value_type>::max()); }

    void set_col_if_invalid(const value_type c);
    void set_row_if_invalid(const value_type r);

    static value_type invalid_value() { return std::numeric_limits<value_type>::max(); }
};

void grid::position::set_col_if_invalid(const value_type c)
{
    if (! is_valid_col()) {
        col = c;
    }
}

void grid::position::set_row_if_invalid(const value_type r)
{
    if (! is_valid_row()) {
        row = r;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// class grid

grid::grid(const uint8_t rows_count, const uint8_t cols_count)
    : m_rows_count(rows_count)
    , m_cols_count(cols_count)
    , m_max_value(0)
    , m_grid(m_rows_count, row_type(m_cols_count, 0))
{
    init();
}

void grid::add_new_value()
{
    std::pair<size_t, size_t> pos = {0, 0};
    do {
        pos = gen_random_pos<size_t>(m_rows_count, m_cols_count);
    } while (m_grid[pos.first][pos.second] != 0);
    set_value(pos.first, pos.second, gen_random_value<value_type>());
}

void grid::init()
{
    for (size_t i = 0; i < 2; ++i) {
        add_new_value();
    }
}

void grid::match(const position_type& cur_pos, const position_type& match_pos,
                 const position_type& free_pos)
{
    const value_type val = m_grid[cur_pos.row][cur_pos.col] + 1;
    set_value(cur_pos, 0);
    set_value(match_pos, 0);
    set_value(free_pos, val);
}

grid::value_type grid::max_value() const
{
    return (value_type)std::pow(2, m_max_value);
}

bool grid::move(const MoveType m)
{
    bool was_action = false;
    switch (m) {
    case MoveType::DOWN:
        was_action = move_down();
        break;
    case MoveType::LEFT:
        break;
    case MoveType::RIGHT:
        break;
    case MoveType::UP:
        break;
    }
    return was_action;
}

bool grid::move_down()
{
    bool was_action = false;
    for (size_t col = 0; col < m_cols_count; ++col) {
        position_type free_pos = {position_type::invalid_value(), col};
        for (size_t j = 0; j < m_rows_count; ++j) {
            const size_t row = m_rows_count - j - 1;
            if (m_grid[row][col] == 0) {
                free_pos.set_row_if_invalid(row);
                continue;
            }

            position_type match_pos = {0, 0};
            bool has_match = false;
            for (size_t k = row - 1; k != (size_t)-1; --k) {
                if (m_grid[k][col] != 0) {
                    if (m_grid[k][col] == m_grid[row][col]) {
                        has_match = true;
                        match_pos = {k, col};
                    }
                    break;
                }
            }

            if (has_match) {
                free_pos.set_row_if_invalid(row);
                match({row, col}, match_pos, free_pos);
                --free_pos.row;
                was_action = true;
            } else if (free_pos.is_valid_row()) {
                move_to_end({row, col}, free_pos);
                --free_pos.row;
                was_action = true;
            }
        }
    }
    return was_action;
}

void grid::move_to_end(const position_type& cur_pos, const position_type& free_pos)
{
    set_value(free_pos, m_grid[cur_pos.row][cur_pos.col]);
    set_value(cur_pos, 0);
}

void grid::set_value(const size_t r, const size_t c, const value_type v)
{
    m_grid[r][c] = v;
    m_max_value = std::max(m_max_value, v);
}

void grid::set_value(const position_type& p, const value_type v)
{
    set_value(p.row, p.col, v);
}

grid::value_type grid::value(const size_t r, const size_t c) const
{
    if (m_grid[r][c] == 0) {
        return 0;
    }
    return (value_type)std::pow(2, m_grid[r][c]);
}

} // namespace g2048
} // namespace wstux

