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

#include "g2048_core/grid.h"

namespace wstux {
namespace g2048 {

grid::grid(const uint8_t rows_count, const uint8_t cols_count)
    : m_rows_count(rows_count)
    , m_cols_count(cols_count)
    , m_max_value(0)
    , m_grid(m_rows_count, row_type(m_cols_count, 0))
{}

grid::value_type grid::max_value() const
{
    return (value_type)std::pow(2, m_max_value);
}

bool grid::move(const MoveType /*m*/)
{
    bool was_action = false;
    return was_action;
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

