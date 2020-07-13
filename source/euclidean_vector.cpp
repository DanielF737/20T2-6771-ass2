// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <cstddef>
#include <fmt/format.h>
#include <gsl/gsl-lite.hpp>
#include <iostream>

namespace comp6771 {
	// Implement solution here
	euclidean_vector::euclidean_vector() { // default constructor
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(1);
		dimension_ = 1;
		magnitude_[0] = 0.0;
	}

	euclidean_vector::euclidean_vector(int dim) { // dimension specified
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < gsl_lite::narrow_cast<size_t>(dim); i++) {
			magnitude()[i] = 0.0;
		}
	}

	euclidean_vector::euclidean_vector(int dim, double val) { // default value and dimension
		                                                       // specified
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < gsl_lite::narrow_cast<size_t>(dim); i++) {
			magnitude_[i] = val;
		}
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
	                                   std::vector<double>::const_iterator end) { // Given iterator
		                                                                           // only
		auto c = 0;
		for (auto i = start; i < end; i++) {
			c++;
		}

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(c));
		dimension_ = c;
		auto x = size_t(0);
		for (auto i = start; i < end; i++) {
			magnitude_[x] = *i;
			x++;
		}
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> vals) { // Given initializer
		                                                                      // list only
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(vals.size()));
		dimension_ = gsl_lite::narrow_cast<int>(vals.size());
		auto i = size_t(0);
		for (double x : vals) {
			magnitude_[i] = x;
			i++;
		}
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& src) { // Copy constructor
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = src.magnitude();
		dimension_ = src.dimensions();
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& src) noexcept { // Move constructor
		magnitude_ = src.magnitude();
		dimension_ = src.dimensions();

		src.set_dimension(0);
		src.set_magnitude(nullptr, 0);
	}

	// copy assignment
	auto euclidean_vector::operator=(euclidean_vector const& src) -> euclidean_vector& {
		if (this == &src) { // self assignment protection
			return *this;
		}

		magnitude_ = src.magnitude();
		dimension_ = src.dimensions();

		return *this;
	}

	// move
	auto euclidean_vector::operator=(euclidean_vector&& src) noexcept -> euclidean_vector& {
		if (this == &src) { // self move protection
			return *this;
		}

		magnitude_ = src.magnitude();
		dimension_ = src.dimensions();

		src.set_dimension(0);
		src.set_magnitude(nullptr, 0);

		return *this;
	}

	// subscript
	auto euclidean_vector::operator[](int i) -> double& {
		assert(i >= 0 and i < dimensions()); // Ensure the index is within bounds
		return magnitude_[gsl_lite::narrow_cast<size_t>(i)];
	}

	// const subscript
	auto euclidean_vector::operator[](int i) const -> double {
		assert(i >= 0 and i < dimensions()); // Ensure the index is within bounds
		return magnitude()[gsl_lite::narrow_cast<size_t>(i)];
	}

	// unary plus
	auto euclidean_vector::operator+() -> euclidean_vector {
		auto new_ev = euclidean_vector(this->dimensions());
		for (auto i = 0; i < this->dimensions(); i++) {
			new_ev[i] = this->magnitude()[gsl_lite::narrow_cast<size_t>(i)];
		}
		return new_ev;
	}

	// negation
	auto euclidean_vector::operator-() -> euclidean_vector {
		auto new_ev = euclidean_vector(this->dimensions());
		for (auto i = 0; i < this->dimensions(); i++) {
			new_ev[i] = -this->magnitude()[gsl_lite::narrow_cast<size_t>(i)];
		}
		return new_ev;
	}

	// compound addition
	auto euclidean_vector::operator+=(euclidean_vector const& src) -> euclidean_vector& {
		if (this->dimension_ != src.dimensions()) {
			throw euclidean_vector_error(fmt::format("Dimensions of LHS({}) and RHS({}) do not "
			                                         "match",
			                                         this->dimensions(),
			                                         src.dimensions()));
		}
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] + src[i];
		}
		return *this;
	}

	// compound subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& src) -> euclidean_vector& {
		if (this->dimension_ != src.dimensions()) {
			throw euclidean_vector_error(fmt::format("Dimensions of LHS({}) and RHS({}) do not "
			                                         "match",
			                                         this->dimensions(),
			                                         src.dimensions()));
		}
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] - src[i];
		}
		return *this;
	}

	// compound multiplication
	auto euclidean_vector::operator*=(double n) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] * n;
		}
		return *this;
	}

	// compound division
	auto euclidean_vector::operator/=(double n) -> euclidean_vector& {
		if (n == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}

		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude_[gsl_lite::narrow_cast<size_t>(i)] / n;
		}
		return *this;
	}

	// Vector cast
	euclidean_vector::operator std::vector<double>() {
		auto retval = std::vector<double>();
		for (auto i = 0; i < dimensions(); i++) {
			retval.push_back(magnitude()[gsl_lite::narrow_cast<size_t>(i)]);
		}
		return retval;
	}

	// List cast
	euclidean_vector::operator std::list<double>() {
		auto retval = std::list<double>();
		for (auto i = 0; i < dimensions(); i++) {
			retval.push_back(magnitude()[gsl_lite::narrow_cast<size_t>(i)]);
		}
		return retval;
	}

	// const at function
	auto euclidean_vector::at(int i) const -> double {
		if (i < 0 or i >= this->dimensions()) {
			throw euclidean_vector_error(
			   fmt::format("Index {} is not valid for this euclidean_vector object", i));
		}

		return magnitude()[gsl_lite::narrow_cast<size_t>(i)];
	}

	// at function
	auto euclidean_vector::at(int i) -> double& {
		if (i < 0 or i >= this->dimensions()) {
			throw euclidean_vector_error(
			   fmt::format("Index {} is not valid for this euclidean_vector object", i));
		}

		return magnitude_[gsl_lite::narrow_cast<size_t>(i)];
	}

	// dimension getter
	auto euclidean_vector::dimensions() const -> int {
		return dimension_;
	}

	// equality operator
	auto operator==(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool {
		if (vec1.dimensions() != vec2.dimensions()) {
			return false;
		}
		for (auto i = 0; i < vec1.dimensions(); i++) {
			if (vec1[i] != vec2[i]) {
				return false;
			}
		}
		return true;
	}

	// not equals operator
	auto operator!=(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool {
		if (vec1.dimensions() != vec2.dimensions()) {
			return true;
		}
		for (auto i = 0; i < vec1.dimensions(); i++) {
			if (vec1[i] != vec2[i]) {
				return true;
			}
		}
		return false;
	}

	// vector addition
	auto operator+(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {
		auto retval = comp6771::euclidean_vector(vec1.dimensions());
		if (vec1.dimension_ != vec2.dimensions()) {
			throw euclidean_vector_error(fmt::format("Dimensions of LHS({}) and RHS({}) do not "
			                                         "match",
			                                         vec1.dimensions(),
			                                         vec2.dimensions()));
		}
		for (auto i = 0; i < vec1.dimensions(); i++) {
			retval[i] = vec1[i] + vec2[i];
		}

		return retval;
	}

	// vector subtraction
	auto operator-(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {
		auto retval = comp6771::euclidean_vector(vec1.dimensions());
		if (vec1.dimension_ != vec2.dimensions()) {
			throw euclidean_vector_error(fmt::format("Dimensions of LHS({}) and RHS({}) do not "
			                                         "match",
			                                         vec1.dimensions(),
			                                         vec2.dimensions()));
		}
		for (auto i = 0; i < vec1.dimensions(); i++) {
			retval[i] = vec1[i] - vec2[i];
		}

		return retval;
	}

	// Multiplication by a scalar
	auto operator*(euclidean_vector const& vec, double n) -> euclidean_vector {
		auto retval = comp6771::euclidean_vector(vec.dimensions());
		for (auto i = 0; i < vec.dimensions(); i++) {
			retval[i] = vec[i] * n;
		}

		return retval;
	}

	// Division by a scalar
	auto operator/(euclidean_vector const& vec, double n) -> euclidean_vector {
		auto retval = comp6771::euclidean_vector(vec.dimensions());
		if (n == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		for (auto i = 0; i < vec.dimensions(); i++) {
			retval[i] = vec[i] / n;
		}

		return retval;
	}

	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	auto euclidean_vector::magnitude() const -> std::unique_ptr<double[]> {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto mag = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dimensions()));
		for (auto i = 0; i < dimensions(); i++) {
			mag[gsl_lite::narrow_cast<size_t>(i)] = magnitude_[gsl_lite::narrow_cast<size_t>(i)];
		}

		return mag;
	}

	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	auto euclidean_vector::set_magnitude(std::unique_ptr<double[]> mag, int dim) -> void {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dim));

		for (auto i = 0; i < dimensions(); i++) {
			magnitude_[gsl_lite::narrow_cast<size_t>(i)] = mag[gsl_lite::narrow_cast<size_t>(i)];
		}
	}

	auto euclidean_vector::set_dimension(int dim) -> void {
		dimension_ = dim;
	}

	// Outputting to an iostream
	auto operator<<(std::ostream& os, euclidean_vector const& vec) -> std::ostream& {
		os << "[";
		for (auto i = 0; i < vec.dimensions(); i++) {
			if (i != 0) { // Insert spaces in the correct places
				os << " ";
			}
			os << vec[i];
		}
		os << "]";
		return os;
	}

	// Calculate the euclidean norm of a euclidean vector
	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a norm");
		}
		auto retval = double(0);
		for (auto i = 0; i < v.dimensions(); i++) {
			retval += v[i] * v[i];
		}
		return sqrt(retval);
	}

	// Returns the unit vector of v
	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		auto retval = comp6771::euclidean_vector(v.dimensions());
		auto euc_norm = euclidean_norm(v);
		if (euc_norm == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		for (auto i = 0; i < v.dimensions(); i++) {
			retval[i] = v[i] / euc_norm;
		}

		return retval;
	}

	// Computes the dot product of 2 vectors x and y
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error(fmt::format("Dimensions of LHS({}) and RHS({}) do not match",
			                                         x.dimensions(),
			                                         y.dimensions()));
		}
		auto retval = double(0);
		for (auto i = 0; i < x.dimensions(); i++) {
			retval += x[i] * y[i];
		}

		return retval;
	}

} // namespace comp6771
