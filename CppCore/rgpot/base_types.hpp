#pragma once
// MIT License
// Copyright 2023--present Rohit Goswami <HaoZeke>
// clang-format off
#include <cxxabi.h>
// clang-format on

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

#ifdef NOT_PURE_LIB
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#endif

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using Eigen::Dynamic;
using Eigen::Matrix;
using Eigen::RowMajor;
using std::literals::string_literals::operator""s;

namespace rgpot {
using AtomMatrix =
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using AtomVector =
    Eigen::Matrix<double, Eigen::Dynamic, 1>; // Same as a normal VectorXd
                                              // The potentials
} // namespace rgpot
