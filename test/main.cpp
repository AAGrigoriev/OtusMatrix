#include <gtest/gtest.h>
#include <matrix.hpp>

TEST(matrix, default_value)
{
  OtusMatrix::Matrix<int, 0> matrix;

  for (std::size_t i = 0; i < 5; i++)
  {
    for (std::size_t j = 0; j < 5; j++)
    {
      ASSERT_EQ(matrix[i][j],0);
    }
  }
  ASSERT_EQ(0, matrix.size());
}

TEST(matrix, add_delete)
{
  OtusMatrix::Matrix<int, -1> matrix;

  std::size_t size_matrix = 5;

  for (std::size_t i = 0; i < size_matrix; i++)
  {
    for (std::size_t j = 0; j < size_matrix; j++)
    {
      matrix[i][j] = i * size_matrix + j;
    }
  }

  for (std::size_t i = 0; i < size_matrix; i++)
  {
    for (std::size_t j = 0; j < size_matrix; j++)
    {
      ASSERT_EQ(matrix[i][j], i * size_matrix + j);
    }
  }

  ASSERT_EQ(size_matrix * size_matrix, matrix.size());

  for (std::size_t i = 0; i < size_matrix; i++)
  {
    for (std::size_t j = 0; j < size_matrix; j++)
    {
      matrix[i][j] = -1;
    }
  }

  ASSERT_EQ(0, matrix.size());
}

TEST(matrix, multiple_assignment)
{
  OtusMatrix::Matrix<int, 0> matrix;

  ((matrix[0][0] = 314) = 214) = 317;

  ASSERT_EQ(matrix[0][0],317);

}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}