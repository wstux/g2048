/*
 * g2048
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

#ifndef _G2048_G2048_CORE_GRID_H_
#define _G2048_G2048_CORE_GRID_H_

#include <cstdint>
#include <vector>

namespace wstux {
namespace g2048 {

enum class MoveType
{
    DOWN,
    LEFT,
    RIGHT,
    UP
};

class grid final
{
public:
    using value_type = size_t;
    using row_type   = std::vector<value_type>;
    using grid_type  = std::vector<row_type>;

    grid(const uint8_t rows_count, const uint8_t cols_count);

    void add_new_value();

    size_t columns_count() const { return m_cols_count; }

    value_type max_value() const;

    bool move(const MoveType m);

    size_t rows_count() const { return m_rows_count; }

    value_type value(const size_t r, const size_t c) const;

private:
    void init();

    void set_value(const size_t r, const size_t c, const value_type v);

private:
    const size_t m_rows_count;
    const size_t m_cols_count;

    value_type m_max_value;
    grid_type m_grid;
};

} // namespace g2048
} // namespace wstux

#endif /* _G2048_G2048_CORE_GRID_H_ */

