// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <cstddef>
#include <gsl-lite/gsl-lite.hpp>
#include <gsl/gsl-lite.hpp>

namespace comp6771 {

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

	// Implement solution here
	euclidean_vector::euclidean_vector() { // default constructor
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude() = std::make_unique<double[]>(1);
		dimension_ = 1;
		magnitude()[0] = 0.0;
	}

	euclidean_vector::euclidean_vector(int dim) { // dimension specified
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude() = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < gsl_lite::narrow_cast<size_t>(dim); i++) {
			magnitude()[i] = 0.0;
		}
	}

	euclidean_vector::euclidean_vector(int dim, double val) { // default value and dimension
		                                                       // specified
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude() = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < gsl_lite::narrow_cast<size_t>(dim); i++) {
			magnitude()[i] = val;
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
		magnitude() = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(c));
		dimension_ = c;
		auto x = size_t(0);
		for (auto i = start; i < end; i++) {
			magnitude()[x] = *i;
			x++;
		}
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> vals) { // Given initializer
		                                                                      // list only
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude() = std::make_unique<double[]>(gsl_lite::narrow_cast<size_t>(vals.size()));
		dimension_ = gsl_lite::narrow_cast<int>(vals.size());
		auto i = size_t(0);
		for (double x : vals) {
			magnitude()[i] = x;
			i++;
		}
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& old) { // Copy constructor
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude() = old.magnitude();
		dimension_ = old.dimensions();
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& old) noexcept { // Move constructor
		magnitude() = old.magnitude();
		dimension_ = old.dimensions();

		old.set_dimension(0);
		old.set_magnitude(nullptr, 0);
	}

	// copy assignment
	auto euclidean_vector::operator=(euclidean_vector const& src) -> euclidean_vector& {
		if (this == &src) { // self assignment protection
			return *this;
		}

		magnitude() = src.magnitude();
		dimension_ = src.dimensions();

		return *this;
	}

	// move
	auto euclidean_vector::operator=(euclidean_vector&& src) noexcept -> euclidean_vector& {
		if (this == &src) { // self move protection
			return *this;
		}

		magnitude() = src.magnitude();
		dimension_ = src.dimensions();

		src.set_dimension(0);
		src.set_magnitude(nullptr, 0);

		return *this;
	}

	// subscript
	auto euclidean_vector::operator[](int i) -> double& {
		assert(i >= 0 and index < dimensions()); // Ensure the index is within bounds
		return magnitude()[gsl_lite::narrow_cast<size_t>(i)];
	}

	// const subscript
	auto euclidean_vector::operator[](int i) const -> double {
		assert(i >= 0 and index < dimensions()); // Ensure the index is within bounds
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
		for (auto i = 0; i < this->dimensions(); i++) {
			this[i] = -this[i];
		}
		return *this;
	}

	// compound addition
	auto euclidean_vector::operator+=(euclidean_vector const& src) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] + src[i];
		}
		return *this;
	}

	// compound subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& src) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] - src[i];
		}
		return *this;
	}

	// compound multiplication
	auto euclidean_vector::operator*=(double n) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] * n;
		}
		return *this;
	}

	// compound division
	auto euclidean_vector::operator/=(double n) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] =
			   this->magnitude()[gsl_lite::narrow_cast<size_t>(i)] / n;
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
		return magnitude()[gsl_lite::narrow_cast<size_t>(i)];
	}

	// at function
	auto euclidean_vector::at(int i) -> double& {
		return magnitude()[gsl_lite::narrow_cast<size_t>(i)];
	}

	// dimension getter
	auto euclidean_vector::dimensions() const -> int {
		return dimension_;
	}

	// equality operator
	auto operator==(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool {
		for (auto i = 0; i < vec1.dimensions(); i++) {
			if (vec1[i] != vec2[i]) {
				return false;
			}
		}
		return true;
	}

	// not equals operator
	auto operator!=(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool {
		for (auto i = 0; i < vec1.dimensions(); i++) {
			if (vec1[i] != vec2[i]) {
				return true;
			}
		}
		return false;
	}

	// vector addition
	auto operator+(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {}

	// vector subtraction
	auto operator-(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {}

	// Multiplication by a scalar
	auto operator*(euclidean_vector const& vec, double n) -> euclidean_vector {}

	// Division by a scalar
	auto operator/(euclidean_vector const& vec, double n) -> euclidean_vector {}

	// Outputting to an iostream
	auto operator<<(std::ostream& strm, euclidean_vector const& vec) -> std::ostream& {}

} // namespace comp6771
