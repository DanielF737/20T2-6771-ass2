// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <cstddef>

namespace comp6771 {

	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	auto euclidean_vector::magnitude() const -> std::unique_ptr<double[]> {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto mag = std::make_unique<double[]>(static_cast<size_t>(dimension()));
		for (auto i = 0; i < dimension(); i++) {
			mag[static_cast<size_t>(i)] = magnitude_[static_cast<size_t>(i)];
		}

		return mag;
	}

	auto euclidean_vector::dimension() const -> int {
		return dimension_;
	}

	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	auto euclidean_vector::set_magnitude(std::unique_ptr<double[]> mag, int dim) -> void {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dim));

		for (auto i = 0; i < dimension(); i++) {
			magnitude_[static_cast<size_t>(i)] = mag[static_cast<size_t>(i)];
		}
	}

	auto euclidean_vector::set_dimension(int dim) -> void {
		dimension_ = dim;
	}

	// Implement solution here
	euclidean_vector::euclidean_vector() {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(1);
		dimension_ = 1;
		magnitude_[0] = 0.0;
	}

	euclidean_vector::euclidean_vector(int dim) {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < static_cast<size_t>(dim); i++) {
			magnitude_[i] = 0.0;
		}
	}

	euclidean_vector::euclidean_vector(int dim, double val) {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		dimension_ = dim;
		for (auto i = size_t(0); i < static_cast<size_t>(dim); i++) {
			magnitude_[i] = val;
		}
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
	                                   std::vector<double>::const_iterator end) {
		auto c = 0;
		for (auto i = start; i < end; i++) {
			c++;
		}

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(c));
		dimension_ = c;
		auto x = size_t(0);
		for (auto i = start; i < end; i++) {
			magnitude_[x] = *i;
			x++;
		}
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> vals) {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(vals.size()));
		dimension_ = static_cast<int>(vals.size());
		auto i = size_t(0);
		for (double x : vals) {
			magnitude_[i] = x;
			i++;
		}
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& old) {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = old.magnitude();
		dimension_ = old.dimension();
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& old) noexcept {
		magnitude_ = old.magnitude();
		dimension_ = old.dimension();

		old.set_dimension(0);
		old.set_magnitude(nullptr, 0)
	}

} // namespace comp6771
