#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector();
		explicit euclidean_vector(int dim);
		euclidean_vector(int dim, double val);
		euclidean_vector(std::vector<double>::const_iterator start,
		                 std::vector<double>::const_iterator end);
		euclidean_vector(std::initializer_list<double> vals);
		euclidean_vector(euclidean_vector const& src);
		euclidean_vector(euclidean_vector&& src) noexcept;

		// Destructor
		~euclidean_vector() = default;

		// Operations
		auto operator=(euclidean_vector const& src) -> euclidean_vector&;
		auto operator=(euclidean_vector&& src) noexcept -> euclidean_vector&;
		auto operator[](int i) -> double&;
		auto operator[](int i) const -> double;
		auto operator+() -> euclidean_vector;
		auto operator-() -> euclidean_vector;
		auto operator+=(euclidean_vector const& src) -> euclidean_vector&;
		auto operator-=(euclidean_vector const& src) -> euclidean_vector&;
		auto operator*=(double n) -> euclidean_vector&;
		auto operator/=(double n) -> euclidean_vector&;
		explicit operator std::vector<double>();
		explicit operator std::list<double>();

		// Member Functions
		[[nodiscard]] auto at(int i) const -> double;
		auto at(int i) -> double&;
		[[nodiscard]] auto dimensions() const -> int;

		// Friend Functions
		friend auto operator==(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool;
		friend auto operator!=(euclidean_vector const& vec1, euclidean_vector const& vec2) -> bool;
		friend auto operator+(euclidean_vector const& vec1, euclidean_vector const& vec2)
		   -> euclidean_vector;
		friend auto operator-(euclidean_vector const& vec1, euclidean_vector const& vec2)
		   -> euclidean_vector;
		friend auto operator*(euclidean_vector const& vec, double n) -> euclidean_vector;
		friend auto operator/(euclidean_vector const& vec, double n) -> euclidean_vector;
		friend auto operator<<(std::ostream& os, euclidean_vector const& vec) -> std::ostream&;

	private:
		// Attributes
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;

		// some fun little functions to make my life easier
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		[[nodiscard]] auto magnitude() const -> std::unique_ptr<double[]>;

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto set_magnitude(std::unique_ptr<double[]> mag, int dim) -> void;
		auto set_dimension(int dim) -> void;
	};

	// Utility Functions
	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
