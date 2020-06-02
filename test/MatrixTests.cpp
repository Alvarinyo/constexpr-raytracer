#include <catch2/catch.hpp>

#include "../src/Matrix.hpp"
#include "../src/Tuple.hpp"

SCENARIO("Constructing and inspecting a 4x4 matrix") {
  GIVEN("The following 4x4 matrix M") {
    constexpr Matrix<4> M = {1.f, 2.f,  3.f,  4.f,  5.5f,  6.5f,  7.5f,  8.5f,
                             9.f, 10.f, 11.f, 12.f, 13.5f, 14.5f, 15.5f, 16.5f};
    THEN("We can access its elements through operator[]") {
      STATIC_REQUIRE(M.at(0, 0) == 1.f);
      STATIC_REQUIRE(M.at(0, 3) == 4.f);
      STATIC_REQUIRE(M.at(1, 0) == 5.5f);
      STATIC_REQUIRE(M.at(1, 2) == 7.5f);
      STATIC_REQUIRE(M.at(2, 2) == 11.f);
      STATIC_REQUIRE(M.at(3, 0) == 13.5f);
      STATIC_REQUIRE(M.at(3, 2) == 15.5f);
    }
  }
}

SCENARIO("A 2x2 Matrix ought to be representable") {
  GIVEN("The following 2x2 matrix M") {
    constexpr Matrix<2> M = {-3.f, 5.f, 1.f, -2.f};
    THEN("We can access through operator[]") {
      STATIC_REQUIRE(M.at(0, 0) == -3.f);
      STATIC_REQUIRE(M.at(0, 1) == 5.f);
      STATIC_REQUIRE(M.at(1, 0) == 1.f);
      STATIC_REQUIRE(M.at(1, 1) == -2.f);
    }
  }
}

SCENARIO("A 3x3 Matrix ought to be representable") {
  GIVEN("The following matrix m") {
    constexpr Matrix<3> M = {-3.f, 5.f, 0.f, 1.f, -2.f, -7.f, 0.f, 1.f, 1.f};
    THEN("We can access through operator[]") {
      STATIC_REQUIRE(M.at(0, 0) == -3.f);
      STATIC_REQUIRE(M.at(1, 1) == -2.f);
      STATIC_REQUIRE(M.at(2, 2) == 1.f);
    }
  }
}

SCENARIO("Matrix equality with identical matrices") {
  GIVEN("The following matrices A and B") {
    constexpr Matrix<4> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                             9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f};
    constexpr Matrix<4> B = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                             9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f};
    THEN("A = B") { STATIC_REQUIRE(A == B); }
  }
}

SCENARIO("Matrix equality with different matrices") {
  GIVEN("The following matrices A and B") {
    constexpr Matrix<4> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                             9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f};
    constexpr Matrix<4> B = {2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f,
                             8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f};
    THEN("A != B") { STATIC_REQUIRE(A != B); }
  }
}

SCENARIO("Multiplying square matrices") {
  GIVEN("The following matrices A and B") {
    constexpr Matrix<4> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                             9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f};
    constexpr Matrix<4> B = {-2.f, 1.f, 2.f, 3.f, 3.f, 2.f, 1.f, -1.f,
                             4.f,  3.f, 6.f, 5.f, 1.f, 2.f, 7.f, 8.f};
    THEN("A * B returns as expected") {
      STATIC_REQUIRE(A * B == Matrix<4>{20.f, 22.f, 50.f, 48.f, 44.f, 54.f,
                                        114.f, 108.f, 40.f, 58.f, 110.f, 102.f,
                                        16.f, 26.f, 46.f, 42.f});
    }
  }
}

SCENARIO("Multiplying matrices of compatible dimensions") {
  GIVEN("The following matrices A and B") {
    constexpr Matrix<2, 3> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    constexpr Matrix<3, 2> B = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    THEN("A * B returns as expected")
    AND_THEN("B * A returns as expected") {
      STATIC_REQUIRE(A * B == Matrix<2, 2>(22.f, 28.f, 49.f, 64.f));
      STATIC_REQUIRE(B * A == Matrix<3, 3>(9.f, 12.f, 15.f, 19.f, 26.f, 33.f,
                                           29.f, 40.f, 51.f));
    }
  }
}

SCENARIO("A matrix multiplied by a tuple") {
  GIVEN("The following matrix A")
  AND_GIVEN("The following tuple b") {
    constexpr Matrix<4> A = {1.f, 2.f, 3.f, 4.f, 2.f, 4.f, 4.f, 2.f,
                             8.f, 6.f, 4.f, 1.f, 0.f, 0.f, 0.f, 1.f};
    constexpr Tuple b(1.f, 2.f, 3.f, 1.f);
    THEN("A * b = Tuple(18.f, 24.f, 33.f, 1.f)") {
      STATIC_REQUIRE(A * b == Tuple(18.f, 24.f, 33.f, 1.f));
    }
  }
}

SCENARIO("Multipying a matrix by the identity matrix") {
  GIVEN("The following matrix A") {
    constexpr Matrix<4> A = {0.f, 1.f, 2.f, 4.f,  1.f, 2.f, 4.f,  8.f,
                             2.f, 4.f, 8.f, 16.f, 4.f, 8.f, 16.f, 32.f};
    THEN("A * identity_matrix = A") {
      STATIC_REQUIRE(A * MatrixUtils::identity<4>() == A);
    }
  }
}

SCENARIO("Transposing a square matrix") {
  GIVEN("The following matrix A") {
    constexpr Matrix<4> A = {0.f, 9.f, 3.f, 0.f, 9.f, 8.f, 0.f, 8.f,
                             1.f, 8.f, 5.f, 3.f, 0.f, 0.f, 5.f, 8.f};
    THEN("transpose(A) is the following matrix:") {
      STATIC_REQUIRE(MatrixUtils::transpose(A) ==
                     Matrix<4>{0.f, 9.f, 1.f, 0.f, 9.f, 8.f, 8.f, 0.f, 3.f, 0.f,
                               5.f, 5.f, 0.f, 8.f, 3.f, 8.f});
    }
  }
}

SCENARIO("Transposing a matrix") {
  GIVEN("The following matrix A") {
    constexpr Matrix<3, 2> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    THEN("transpose(A) is the following matrix:") {
      STATIC_REQUIRE(MatrixUtils::transpose(A) ==
                     Matrix<2, 3>{1.f, 3.f, 5.f, 2.f, 4.f, 6.f});
    }
  }
}

SCENARIO("Transposing the identity matrix") {
  GIVEN("A <- transpose(A)") {
    constexpr Matrix<4> A = MatrixUtils::transpose(MatrixUtils::identity<4>());
    THEN("transpose(A) is the following matrix:") {
      STATIC_REQUIRE(A == MatrixUtils::identity<4>());
    }
  }
}

SCENARIO("Calculating the determinant of a 2x2 matrix") {
  GIVEN("The following 2x2 matrix A") {
    constexpr Matrix<2> A = {1.f, 5.f, -3.f, 2.f};
    THEN("determinant(A) = 17") {
      STATIC_REQUIRE(MatrixUtils::determinant(A) == 17.f);
    }
  }
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix") {
  GIVEN("The following 3x3 matrix A") {
    constexpr Matrix<3> A = {1.f, 5.f, 0.f, -3.f, 2.f, 7.f, 0.f, 6.f, -3.f};
    THEN("submatrix(A, 0, 2) is the following 2x2 matrix") {
      STATIC_REQUIRE(MatrixUtils::submatrix(A, 0, 2) ==
                     Matrix<2>{-3.f, 2.f, 0.f, 6.f});
    }
  }
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix") {
  GIVEN("The following 4x4 matrix A") {
    constexpr Matrix<4> A = {-6.f, 1.f, 1.f, 6.f, -8.f, 5.f, 8.f,  6.f,
                             -1.f, 0.f, 8.f, 2.f, -7.f, 1.f, -1.f, 1.f};
    THEN("submatrix(A, 2, 1) is the following 3x3 matrix") {
      STATIC_REQUIRE(
          MatrixUtils::submatrix(A, 2, 1) ==
          Matrix<3>{-6.f, 1.f, 6.f, -8.f, 8.f, 6.f, -7.f, -1.f, 1.f});
    }
  }
}

SCENARIO("Calculating the minor of a 3x3 matrix") {
  GIVEN("The following 3x3 matrix A")
  AND_GIVEN("B <- submatrix(A, 1, 0)") {
    constexpr Matrix<3> A = {3.f, 5.f, 0.f, 2.f, -1.f, -7.f, 6.f, -1.f, 5.f};
    constexpr Matrix<2> B = MatrixUtils::submatrix(A, 1, 0);
    THEN("determinant(B) = 25") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(B), 25.f));
    }
    AND_THEN("minor(A, 1, 0) = 25") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::minor(A, 1, 0), 25.f));
    }
  }
}

SCENARIO("Calculating the cofactor of a 3x3 matrix") {
  GIVEN("The following 3x3 matrix A") {
    constexpr Matrix<3> A = {3.f, 5.f, 0.f, 2.f, -1.f, -7.f, 6.f, -1.f, 5.f};
    THEN("minor(A, 0, 0) = -12") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::minor(A, 0, 0), -12.f));
    }
    AND_THEN("cofactor(A, 0, 0) = -12") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 0), -12.f));
    }
    AND_THEN("minor(A, 1, 0) = 25") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::minor(A, 1, 0), 25.f));
    }
    AND_THEN("cofactor(A, 1, 0) = -25") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 1, 0), -25.f));
    }
  }
}

SCENARIO("Calculating the determinant of a 3x3 matrix") {
  GIVEN("The following 3x3 matrix A") {
    constexpr Matrix<3> A = {1.f, 2.f, 6.f, -5.f, 8.f, -4.f, 2.f, 6.f, 4.f};
    THEN("cofactor(A, 0, 0) = 56") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 0), 56.f));
    }
    AND_THEN("cofactor(A, 0, 1) = 12") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 1), 12.f));
    }
    AND_THEN("minor(A, 0, 2) = -46") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 2), -46.f));
    }
    AND_THEN("determinant(A) = -196") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(A), -196.f));
    }
  }
}

SCENARIO("Calculating the determinant of a 4x4 matrix") {
  GIVEN("The following 4x4 matrix A") {
    constexpr Matrix<4> A = {-2.f, -8.f, 3.f,  5.f, -3.f, 1.f, 7.f, 3.f,
                             1.f,  2.f,  -9.f, 6.f, -6.f, 7.f, 7.f, -9.f};
    THEN("cofactor(A, 0, 0) = 56") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 0), 690.f));
    }
    AND_THEN("cofactor(A, 0, 1) = 12") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 1), 447.f));
    }
    AND_THEN("minor(A, 0, 2) = -46") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 2), 210.f));
    }
    AND_THEN("minor(A, 0, 3) = 51") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 0, 3), 51.f));
    }
    AND_THEN("determinant(A) = -4071") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(A), -4071.f));
    }
  }
}

SCENARIO("Testing an invertible matrix for invertibility") {
  GIVEN("The following 4x4 matrix A") {
    constexpr Matrix<4> A = {6.f, 4.f,  4.f, 4.f,  5.f, 5.f, 7.f, 6.f,
                             4.f, -9.f, 3.f, -7.f, 9.f, 1.f, 7.f, -6.f};
    THEN("determinat(A) = -2120") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(A), -2120.f));
    }
    AND_THEN("A is invertible") {
      STATIC_REQUIRE(MatrixUtils::is_invertible(A));
    }
  }
}

SCENARIO("Testing an noninvertible matrix for invertibility") {
  GIVEN("The following 4x4 matrix A") {
    constexpr Matrix<4> A = {-4.f, 2.f,  -2.f, -3.f, 9.f, 6.f, 2.f, 6.f,
                             0.f,  -5.f, 1.f,  -5.f, 0.f, 0.f, 0.f, 0.f};
    THEN("determinat(A) = 0") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(A), 0.f));
    }
    AND_THEN("A is not invertible") {
      STATIC_REQUIRE(!MatrixUtils::is_invertible(A));
    }
  }
}

SCENARIO("Calculating the inverse of a matrix") {
  GIVEN("The following 4x4 matrix A")
  AND_GIVEN("B <- inverse(A)") {
    constexpr Matrix<4> A = {-5.f, 2.f, 6.f,  -8.f, 1.f, -5.f, 1.f, 8.f,
                             7.f,  7.f, -6.f, -7.f, 1.f, -3.f, 7.f, 4.f};
    constexpr auto B = MatrixUtils::inverse(A);
    THEN("determinat(A) = 532") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::determinant(A), 532.f));
    }
    AND_THEN("cofactor(A, 2, 3) = -160") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 2, 3), -160.f));
    }
    AND_THEN("B.at(3, 2) = -160/532") {
      STATIC_REQUIRE(aprox_equal(B.at(3, 2), -160.f / 532.f));
    }
    AND_THEN("cofactor(A, 3, 2) = -105") {
      STATIC_REQUIRE(aprox_equal(MatrixUtils::cofactor(A, 3, 2), 105.f));
    }
    AND_THEN("B.at(2, 3) = -160/532") {
      STATIC_REQUIRE(aprox_equal(B.at(2, 3), 105.f / 532.f));
    }
    AND_THEN("B is the following matrix") {
      STATIC_REQUIRE(B == Matrix<4>{0.21805f, 0.45113f, 0.24060f, -0.04511f,
                                    -0.80827f, -1.45677f, -0.44361f, 0.52068f,
                                    -0.07895f, -0.22368f, -0.05263f, 0.19737f,
                                    -0.52256f, -0.81391f, -0.30075f, 0.30639f});
    }
  }
}

SCENARIO("Calculating the inverse of another matrix") {
  GIVEN("The following 4x4 matrix A")
  AND_GIVEN("B <- inverse(A)") {
    constexpr Matrix<4> A = {8.f,  -5.f, 9.f, 2.f, 7.f,  5.f, 6.f,  1.f,
                             -6.f, 0.f,  9.f, 6.f, -3.f, 0.f, -9.f, -4.f};
    constexpr auto B = MatrixUtils::inverse(A);
    THEN("B is the following matrix") {
      STATIC_REQUIRE(B == Matrix<4>{-0.15385f, -0.15385f, -0.28205f, -0.53846f,
                                    -0.07692f, 0.12308f, 0.02564f, 0.03077f,
                                    0.35897f, 0.35897f, 0.43590f, 0.92308f,
                                    -0.69231f, -0.69231f, -0.76923f,
                                    -1.92308f});
    }
  }
}

SCENARIO("Calculating the inverse of a third matrix") {
  GIVEN("The following 4x4 matrix A")
  AND_GIVEN("B <- inverse(A)") {
    constexpr Matrix<4> A = {9.f,  3.f, 0.f, 9.f, -5.f, -2.f, -6.f, -3.f,
                             -4.f, 9.f, 6.f, 4.f, -7.f, 6.f,  6.f,  2.f};
    constexpr auto B = MatrixUtils::inverse(A);
    THEN("B is the following matrix") {
      STATIC_REQUIRE(B == Matrix<4>{-0.04074f, -0.07778f, 0.14444f, -0.22222f,
                                    -0.07778f, 0.03333f, 0.36667f, -0.33333f,
                                    -0.02901f, -0.14630f, -0.10926f, 0.12963f,
                                    0.17778f, 0.06667f, -0.26667f, 0.33333f});
    }
  }
}

SCENARIO("Multiplying a product by its inverse") {
  GIVEN("The following 4x4 matrix A")
  AND_GIVEN("The following 4x4 matrix B")
  AND_GIVEN("C <- A*B") {
    constexpr Matrix<4> A = {3.f,  -9.f, 7.f, 3.f, 3.f,  -8.f, 2.f,  -9.f,
                             -4.f, 4.f,  4.f, 1.f, -6.f, 5.f,  -1.f, 1.f};
    constexpr Matrix<4> B = {8.f, 2.f, 2.f, 2.f, 3.f, -1.f, 7.f, 0.f,
                             7.f, 0.f, 5.f, 4.f, 6.f, -2.f, 0.f, 5.f};
    constexpr auto C = A * B;
    THEN("C * inverse(B) = A") {
      STATIC_REQUIRE(C * MatrixUtils::inverse(B) == A);
    }
  }
}