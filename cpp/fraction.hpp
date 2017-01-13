#ifndef FRACTION_HOLT59_HPP
#define FRACTION_HOLT59_HPP

#include <type_traits>
#include <cstdlib>
#include <numeric>

namespace holt59 {
  
#if __cplusplus <= 201402L
  	template<class M, class N>
	  constexpr std::common_type_t<M, N> gcd(M m, N n) {
     	return n == 0 ? m : gcd(n, m % n); 
    }
#else
	  using std::gcd;
#endif
  
  	template <typename T>
  	struct fraction {
      	using value_type = T;
      	
      	constexpr static fraction zero() { return fraction(); }
      
      	constexpr fraction(value_type const& num = 0, value_type const& den = 1) :
      		  num_(num), den_(den) { 
        	  normalize_();    
        }
      	
      	fraction(fraction const&) = default;
      	fraction(fraction &&) = default;
      
      	fraction& operator=(fraction const&) = default;
      	fraction& operator=(fraction &&) = default;
        fraction& operator=(value_type const& t) {
          	return operator=(fraction(t));
        }
      
      	constexpr fraction operator+() const { return *this; }
      	constexpr fraction operator-() const { return fraction(-num_, den_); }
      
      	fraction& operator+=(fraction const& rhs) {
         	  return normalize_(num() * rhs.den() + den() * rhs.num(), den() * rhs.den());
        }
      	fraction& operator+=(value_type const& rhs) {
         	  return operator+=(fraction(rhs)); 
        }
      
      	fraction& operator-=(fraction const& rhs) {
         	  return normalize_(num() * rhs.den() - den() * rhs.num(), den() * rhs.den());
        }
      	fraction& operator-=(value_type const& rhs) {
         	  return operator-=(fraction(rhs)); 
        }
      
      	fraction& operator*=(fraction const& rhs) {
         	  return normalize_(num() * rhs.num(), den() * rhs.den());
        }
      	fraction& operator*=(value_type const& rhs) {
         	  return operator*=(fraction(rhs)); 
        }
      	
      	fraction& operator/=(fraction const& rhs) {
         	  return normalize_(num() * rhs.den(), den() * rhs.num());
        }
      	fraction& operator/=(value_type const& rhs) {
         	  return operator/=(fraction(rhs)); 
        }
      
      	constexpr bool operator!() const { return num_ != 0; }
      
      	explicit operator bool() const { return num_ == 0; }
      
      	constexpr const value_type& num() const { return num_; }
      	constexpr const value_type& den() const { return den_; }
      
      	constexpr bool is_integral() const { return den_ == 1; }
      	constexpr bool is_legal() const { return den_ != 0; }
      
    private:
      	value_type num_, den_;
      
      	constexpr fraction& normalize_() {
         	  auto g = gcd(std::abs(num_), std::abs(den_));
          	auto m = den_ < 0 ? -1 : 1;
          	num_ = num_ / g * m;
          	den_ = den_ / g * m;
          	return *this;
        }
      
      	constexpr fraction& normalize_(value_type const& num, value_type const& den) {
          	num_ = num;
          	den_ = den;
          	return normalize_();
        }
    };
  
  	template <typename T>
  	bool operator==(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() == rhs.num() && lhs.den() == rhs.den();
    }
  	template <typename T>
  	bool operator!=(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() != rhs.num() || lhs.den() != rhs.den();
    }
  	template <typename T>
  	bool operator<(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() * rhs.den() < rhs.num() * lhs.den();
    }
  	template <typename T>
  	bool operator<=(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() * rhs.den() <= rhs.num() * lhs.den();
    }
  	template <typename T>
  	bool operator>(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() * rhs.den() > rhs.num() * lhs.den();
    }
  	template <typename T>
  	bool operator>=(fraction<T> const& lhs, fraction<T> const& rhs) {
      	return lhs.num() * rhs.den() >= rhs.num() * lhs.den();
    }
  
  	template <typename T, typename U>
  	fraction<T> operator+(fraction<T> lhs, U const& rhs) {
     	  return lhs += rhs; 
    }
  
  	template <typename T, typename U>
  	fraction<T> operator-(fraction<T> lhs, U const& rhs) {
     	  return lhs -= rhs; 
    }
  
  	template <typename T, typename U>
  	fraction<T> operator*(fraction<T> lhs, U const& rhs) {
     	  return lhs *= rhs; 
    }
  
  	template <typename T, typename U>
  	fraction<T> operator/(fraction<T> lhs, U const& rhs) {
     	  return lhs /= rhs; 
    }
  
  	template <typename U, typename T>
  	T to_real(fraction<U> const& f) {
     	  return static_cast<T>(f.num()) / f.den(); 
    }
 
}

#ifdef TEST_HOLT59_FRACTION
int main() {
 	  using namespace holt59;
  	constexpr fraction<int> f1(15, 63);
  	static_assert(f1.num() == 5 && f1.den() == 21, "");
  	fraction<int> f2(1, 2);
  	f2 = -f1;
  	auto f3 = f1 + f2;
}
#endif

#endif
