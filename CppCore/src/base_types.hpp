#pragma once

#include <algorithm>
#include <any>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <cxxabi.h>

#ifdef NOT_PURE_LIB
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#endif

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace Eigen;
using namespace std::string_literals; // For ""s

namespace rgpot {
using AtomMatrix =
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using AtomVector =
    Eigen::Matrix<double, Eigen::Dynamic, 1>; // Same as a normal VectorXd
                                              // The potentials
} // namespace rgpot
