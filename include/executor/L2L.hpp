#pragma once
/** @file L2L.hpp
 * @brief Dispatch methods for the L2L stage
 *
 */

#include "KernelTraits.hpp"
#include <type_traits>

struct L2L
{
  /** If no other L2L dispatcher matches */
  template <typename Expansion, typename... Args>
  inline static void eval(const Expansion&, Args...) {
    std::cerr << "Expansion does not have a correct L2L!\n";
    std::cerr << ExpansionTraits<Expansion>() << std::endl;
    exit(1);
  }

  template <typename Expansion>
  inline static
  typename std::enable_if<ExpansionTraits<Expansion>::has_L2L>::type
  eval(const Expansion& K,
       const typename Expansion::local_type& source,
       typename Expansion::local_type& target,
       const typename Expansion::point_type& translation) {
    K.L2L(source, target, translation);
  }

 public:

  template <typename Context>
  inline static void eval(Context& c,
                          const typename Context::target_box_type& source,
                          const typename Context::target_box_type& target)
  {
#ifdef DEBUG
    std::cout << "L2L:\n  " << source << "\n  " << target << std::endl;
#endif

    L2L::eval(c.expansion(),
              c.local(source),
              c.local(target),
              target.center() - source.center());
  }
};

