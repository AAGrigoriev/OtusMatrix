
#include <unordered_map>
#include <tuple>

#include "hashFunction.hpp"

namespace OtusMatrix
{
    template <typename T, T def_v, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    class Matrix
    {
    private:
        class Container_Wrapper
        {
        public:
            using size_matrix = typename std::unordered_map<MyKey, T, MyHashFunction>::size_type;
            using iterator_matrix = typename std::unordered_map<MyKey, T, MyHashFunction>::iterator;

            Container_Wrapper() = default;
            ~Container_Wrapper() = default;

            /*!
                @brief 
            */
            T get(std::size_t row_index, std::size_t col_index)
            {
                auto search = u_map.find(MyKey(row_index, col_index));
                return search == u_map.end() ? def_v : search->second;
            }

            /*!
                @brief Function assign value to unordered_map 
            */
            void assign(std::size_t row_index, std::size_t col_index, T value)
            {
                if (value != def_v)
                {
                    u_map[MyKey(row_index, col_index)] = value;
                }
                else
                {
                    u_map.erase(MyKey(row_index, col_index));
                }
            }

            iterator_matrix begin()
            {
                return u_map.begin();
            }

            iterator_matrix end()
            {
                return u_map.end();
            }

            size_matrix size()
            {
                return u_map.size();
            }

        private:
            std::unordered_map<MyKey, T, MyHashFunction> u_map;
        };

        class ProxyCol
        {
        public:
            ProxyCol(std::size_t index_row, std::size_t index_col, Container_Wrapper &container) : index_row(index_row), index_col(index_col), container(container) {}

            ProxyCol &operator=(T value)
            {
                container.assign(index_row, index_col, value);
                return *this;
            }

            operator T()
            {
                return container.get(index_row, index_col);
            }

            bool operator==(T other)
            {
                return container.get(index_row, index_col) == other;
            }

            bool operator!=(T other)
            {
                return container.get(index_row, index_col) != other;
            }

            ~ProxyCol() = default;

            // ProxyCol(ProxyCol const &other) = delete;
            // ProxyCol(ProxyCol &&other) : container(other.container)
            // ProxyCol &operator=(ProxyCol const &other) = delete;
            // ProxyCol &operator=(ProxyCol &&other) = delete;

        private:
            std::size_t index_row;
            std::size_t index_col;
            Container_Wrapper &container;
        };

        class ProxyRow
        {
        public:
            ProxyRow(std::size_t index_row, Container_Wrapper &container) : index_row(index_row), container(container) {}

            ProxyCol operator[](std::size_t index_column)
            {
                return ProxyCol(index_row, index_column, container);
            }

            ~ProxyRow() = default;
            //ProxyRow(ProxyRow const &other) = delete;
            //ProxyRow(ProxyRow &&other) = delete;
            //ProxyRow(ProxyRow &&other)  = delete;
            //ProxyRow &operator=(ProxyRow const &other) = delete;
            //ProxyRow &operator=(ProxyRow &&other) = delete;

        private:
            std::size_t index_row;
            Container_Wrapper &container;
        };

        class Iterator
        {
        public:
            using value_type = std::tuple<std::size_t, std::size_t, T>;
            using difference_type = size_t;
            using reference = value_type &;
            using pointer = value_type *;
            using iterator_category = std::forward_iterator_tag;

            Iterator(typename Container_Wrapper::iterator_matrix iter) : iter(iter) {}

            value_type operator*()
            {
                return std::make_tuple(iter->first.first, iter->first.last, iter->second);
            }

            Iterator &operator++()
            {
                ++iter;
                return *this;
            }

            bool operator==(Iterator const &other)
            {
                return (iter == other.iter);
            }

            bool operator!=(Iterator const &other)
            {
                return !(*this == other);
            }

        private:
            typename Container_Wrapper::iterator_matrix iter;
        };

    public:
        Matrix() = default;
        ~Matrix() = default;

        ProxyRow operator[](std::size_t index_row)
        {
            return ProxyRow(index_row, container);
        }

        typename Container_Wrapper::size_matrix size()
        {
            return container.size();
        }

        Iterator begin()
        {
            return Iterator(container.begin());
        }

        Iterator end()
        {
            return Iterator(container.end());
        }

    private:
        Container_Wrapper container;
    };

} // namespace OtusMatrix