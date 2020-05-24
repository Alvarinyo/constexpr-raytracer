#ifndef CONSTEXPR_RAYTRACER_VECTOR_HPP
#define CONSTEXPR_RAYTRACER_VECTOR_HPP

#include <array>
#include <cassert>

template <typename T, size_t Size>
class StaticVector {
  using Storage = std::array<T, Size>;

 public:
  using iterator = typename Storage::iterator;
  using const_iterator = typename Storage::const_iterator;
  using value_type = T;
  using size_type = size_t;
  using difference_type = typename Storage::difference_type;
  using reference = typename Storage::reference;
  using const_reference = typename Storage::const_reference;

  constexpr static size_type max_size = Size;

  constexpr StaticVector(size_type size) : data_{}, size_{size} {}

  template <typename Iter>
  constexpr StaticVector(Iter first, const Iter& last) noexcept {
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  constexpr StaticVector(std::initializer_list<T> list) noexcept
      : StaticVector(list.begin(), list.end()) {}

  constexpr StaticVector() = default;

  [[nodiscard]] constexpr auto begin() const noexcept { return data_.begin(); }

  [[nodiscard]] constexpr auto begin() noexcept { return data_.begin(); }

  [[nodiscard]] constexpr auto end() const noexcept {
    return std::next(data_.begin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr auto end() noexcept {
    return std::next(data_.begin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept {
    return data_.cbegin();
  }

  [[nodiscard]] constexpr auto cend() const noexcept {
    return std::next(data_.cbegin(), static_cast<difference_type>(size_));
  }

  [[nodiscard]] constexpr const value_type& operator[](
      const size_type pos) const noexcept {
    assert(pos <= size_);
    return data_[pos];
  }

  [[nodiscard]] constexpr value_type& operator[](const size_type pos) noexcept {
    assert(pos <= size_);
    return data_[pos];
  }

  constexpr void push_back(value_type value) noexcept {
    assert(size_ < max_size);
    data_[size_++] = std::move(value);
  }

  constexpr void pop_back() noexcept {
    assert(!empty());
    --size_;
  }

  [[nodiscard]] constexpr const value_type& back() const noexcept {
    assert(!empty());
    return data_[size_ - 1];
  }

  [[nodiscard]] constexpr value_type& back() noexcept {
    assert(!empty());
    return data_[size_ - 1];
  }

  [[nodiscard]] constexpr size_type capacity() const noexcept {
    return max_size;
  }

  [[nodiscard]] constexpr size_type size() const noexcept { return size_; }

  [[nodiscard]] constexpr value_type* data() const noexcept {
    return data_.data();
  }

  [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }

 private:
  Storage data_{};
  size_type size_{0};
};

#endif