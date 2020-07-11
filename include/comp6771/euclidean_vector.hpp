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
		// some fun little functions to make my life easier
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		[[nodiscard]] auto magnitude() const -> std::unique_ptr<double[]>;
		[[nodiscard]] auto dimension() const -> int;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto set_magnitude(std::unique_ptr<double[]> mag, int dim) -> void;
		auto set_dimension(int dim) -> void;

		// Constructors
		euclidean_vector();
		explicit euclidean_vector(int dim);
		euclidean_vector(int dim, double val);
		euclidean_vector(std::vector<double>::const_iterator start,
		                 std::vector<double>::const_iterator end);
		euclidean_vector(std::initializer_list<double> vals);
		euclidean_vector(euclidean_vector const& old);
		euclidean_vector(euclidean_vector&& old) noexcept;

		// Destructor
		~euclidean_vector() = default;

		// Operations
		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		auto operator[](int) -> double;
		auto operator[](int) const -> double;
		auto operator+() -> euclidean_vector;
		auto operator-() -> euclidean_vector;
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		explicit operator std::vector<double>();
		explicit operator std::list<double>();

		// Member Functions
		[[nodiscard]] auto at(int) const -> double;
		auto at(int) -> double&;
		auto dimensions() -> int;

		// Friend Functions
		friend auto operator==(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;

		// Utility Functions

	private:
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;
	};
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
