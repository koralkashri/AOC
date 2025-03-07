#ifndef ADVENTOFCODE2021_MATRIX_HPP
#define ADVENTOFCODE2021_MATRIX_HPP

#include <cstdint>
#include <string_view>
#include "point.hpp"

namespace aoc_tools {

    template<typename T>
    class matrix {
    public:
        void set_width_and_height(size_t new_width, size_t new_height, T default_value = T()) {
            width = new_width;
            data.resize(new_width * new_height, default_value);
        }

        void insert_line(const std::vector<T> &str) {
            set_width_if_not_set(str.size());
            data.insert(data.end(), str.begin(), str.end());
        }

        void insert_line_front(const std::vector<T> &str) {
            set_width_if_not_set(str.size());
            data.insert(data.begin(), str.begin(), str.end());
        }

        void insert_padding_lines(T padding) {
            insert_line(std::vector<T>(width, padding));
            insert_line_front(std::vector<T>(width, padding));
        }

        [[nodiscard]] T operator[](size_t x, size_t y) const {
            return data[y * width + x];
        }

        [[nodiscard]] T &operator[](size_t x, size_t y) {
            return data[y * width + x];
        }


        [[nodiscard]] T operator[](point_xd<2> location) const {
            return data[location[1] * width + location[0]];
        }

        [[nodiscard]] T &operator[](point_xd<2> location) {
            return data[location[1] * width + location[0]];
        }

        [[nodiscard]] size_t size_x() const {
            return width;
        }

        [[nodiscard]] size_t size_y() const {
            return data.size() / width;
        }

        template <typename Conversion = T>
        void print(T space_char = -1) {
            for (size_t y = 0; y < size_y(); ++y) {
                for (size_t x = 0; x < size_x(); ++x) {
                    char c = (*this)[x, y];
                    if (c == space_char)
                        std::cout << " ";
                    else std::cout << (Conversion)c;
                }
                std::cout << "\n";
            }
        }

        template<typename FuncT>
        void for_each(FuncT&& func) const {
            for (size_t y = 0; y < size_y(); ++y) {
                for (size_t x = 0; x < size_x(); ++x) {
                    auto c = (*this)[x, y];
                    func(c, x, y);
                }
            }
        }

        template<typename FuncT>
        void for_each(FuncT&& func) {
            for (size_t y = 0; y < size_y(); ++y) {
                for (size_t x = 0; x < size_x(); ++x) {
                    auto c = (*this)[x, y];
                    func(c, x, y);
                }
            }
        }

        bool is_border_location(point_xd<2> location) const {
            return location[0] == size_x() - 1 || location[1] == size_y() - 1 || location[0] == 0 || location[1] == 0;
        }

        const auto& get_data() const {
            return data;
        }

    protected:
        std::vector<T> data;
        size_t width = 0;

        void set_width_if_not_set(size_t new_width) {
            if (!width) width = new_width;
        }
    };

    template<>
    class matrix<char> : public matrix<uint8_t> {
    public:
        using matrix<uint8_t>::insert_line;
        using matrix<uint8_t>::insert_line_front;

        void insert_line(std::string_view str) {
            set_width_if_not_set(str.size());
            data.insert(data.end(), str.begin(), str.end());
        }

        void insert_line_front(std::string_view str) {
            set_width_if_not_set(str.size());
            data.insert(data.begin(), str.begin(), str.end());
        }
    };
}

#endif
