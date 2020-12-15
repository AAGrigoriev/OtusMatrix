
#include <unordered_map>
#include "hashFunction.hpp"

namespace OtusMatrix
{
    template <typename T, T def_v, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    class Matrix
    {
        using size_matrix = typename std::unordered_map<MyKey, T, MyHashFunction>::size_type;
        using iterator_matrix = typename std::unordered_map<MyKey, T, MyHashFunction>::iterator;

    private:
        class Container_Wrapper
        {
        public:
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

            size_matrix getSize()
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
                return container.get(index_row,index_col) != other;
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
            ProxyRow(std::size_t index_row, Container_Wrapper &container) : index_row(index_row), container(container){}

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

    public:
        Matrix() = default;
        ~Matrix() = default;

        ProxyRow operator[](std::size_t index_row)
        {
            return ProxyRow(index_row, container);
        }

        size_matrix getSize()
        {
            return container.getSize();
        }

    private:
        Container_Wrapper container;
    };

} // namespace OtusMatrix