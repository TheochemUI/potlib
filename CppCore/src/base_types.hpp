#pragma once

#include <algorithm>
#include <any>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <memory>
#include <numeric>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <cxxabi.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

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
