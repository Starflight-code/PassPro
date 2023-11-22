#include <openssl/crypto.h>
#include <string>

namespace data {
  template <class T>
  class allocator : public std::allocator<T> {
public:
    template <class U>
    struct rebind {
      typedef allocator<U> other;
    };
    allocator() throw() {}
    allocator(const allocator&) throw() {}
    template <class U>
    allocator(const allocator<U>&) throw() {}

    void cleanse(void* ptr, size_t len) {
      // memset_func(ptr, 0, len);
      OPENSSL_cleanse(ptr, len);
    }
  };

  typedef std::basic_string<char, std::char_traits<char>, allocator<char>> string;
}