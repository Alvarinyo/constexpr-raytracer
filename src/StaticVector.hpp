#ifndef CONSTEXPR_RAYTRACER_VECTOR_HPP
#define CONSTEXPR_RAYTRACER_VECTOR_HPP

#include <array>
#include <cassert>

template <typename T, size_t Size>
class StaticVector : protected std::array<T, Size> {
  using storage_type = std::array<T, Size>;

 public:
  using iterator = typename storage_type::iterator;
  using const_iterator = typename storage_type::const_iterator;
  using value_type = T;
  using size_type = size_t;
  using difference_type = typename storage_type::difference_type;
  using reference = typename storage_type::reference;
  using const_reference = typename storage_type::const_reference;

  static constexpr size_type max_size = Size;

  template <typename Iter>
  requires(!std::is_same_v<Iter, value_type>) constexpr StaticVector(
      Iter first, const Iter& last) noexcept {
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  template <typename... Args>
  requires(std::is_same_v<Args, value_type>&&...) constexpr StaticVector(
      Args&&... args)
      : storage_type{std::forward<Args>(args)...}, size_{sizeof...(Args)} {
        
      }

  constexpr StaticVector(size_type size, const value_type& value)
      : size_{size} {
    assert(size <= max_size);
    std::fill_n(std::begin(*this), size, value);
  }

  [[nodiscard]] constexpr auto begin() const noexcept {
    return storage_type::begin();
  }

  [[nodiscard]] constexpr auto begin() noexcept {
    return storage_type::begin();
  }

  [[nodiscard]] constexpr auto end() const noexcept {
    return std::next(begin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr auto end() noexcept {
    return std::next(begin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept {
    return storage_type::cbegin();
  }

  [[nodiscard]] constexpr auto cend() const noexcept {
    return std::next(cbegin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr const value_type& operator[](
      const size_type pos) const noexcept {
    assert(pos <= size_);
    return data()[pos];
  }

  [[nodiscard]] constexpr value_type& operator[](const size_type pos) noexcept {
    assert(pos <= size_);
    return data()[pos];
  }

  constexpr void push_back(value_type value) noexcept {
    assert(size_ < max_size);
    data()[size_++] = std::move(value);
  }

  constexpr void pop_back() noexcept {
    assert(!empty());
    --size_;
  }

  [[nodiscard]] constexpr const value_type& back() const noexcept {
    assert(!empty());
    return data()[size_ - 1];
  }

  [[nodiscard]] constexpr value_type& back() noexcept {
    assert(!empty());
    return data()[size_ - 1];
  }

  [[nodiscard]] constexpr size_type capacity() const noexcept {
    return max_size;
  }

  [[nodiscard]] constexpr size_type size() const noexcept { return size_; }

  [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }

  [[nodiscard]] constexpr const value_type* data() const noexcept {
    return storage_type::data();
  }

  [[nodiscard]] constexpr value_type* data() noexcept {
    return storage_type::data();
  }

 private:
  size_type size_{0};
};

#endif