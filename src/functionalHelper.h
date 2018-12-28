#include <algorithm>
#include <numeric>
#include <iostream>
#include <tuple>

namespace ELI {

  template <template <typename...> class CONTAINER, typename TYPE, 
           typename... TS, typename OPERATION>
    constexpr auto map(const CONTAINER<TYPE, TS...> &col, const OPERATION &op){
      CONTAINER<decltype(op((*col.begin())))> ret;
      std::transform(col.begin(), col.end(), std::back_inserter(ret), op);
      return ret;
    }
  
  template <template <typename...> class CONTAINER, typename TYPE, 
           typename... TS, typename OPERATION>
    constexpr auto filter(const CONTAINER<TYPE, TS...> &col, const OPERATION &predicate){
      CONTAINER<TYPE> ret;
      std::copy_if(col.begin(), col.end(), std::back_inserter(ret),predicate);
      return ret;
    }

  template <template <typename...> class CONTAINER, typename TYPE,
           typename ACC_TYPE, typename... TS,  typename OPERATION>
    constexpr auto reduce(const CONTAINER<TYPE, TS...> &col, const OPERATION &reducer, ACC_TYPE acc){
      return std::accumulate(col.begin(), col.end(), acc, reducer);  
    }

  // based on solution by Nathan Reed reedbeta.com
  template <typename T, typename TIter = decltype(std::begin(std::declval<T>())), 
           typename = decltype(std::end(std::declval<T>()))>
    constexpr auto enumerate(T && iterable) {
      struct iterator{
        size_t i;
        TIter iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () { ++i; ++iter; }
        auto operator * () const { return std::tie(i, *iter); }
      };
      struct iterable_wrapper {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable) }; }
        auto end() { return iterator{ 0, std::end(iterable) }; }
      };
      return iterable_wrapper{ std::forward<T>(iterable) };
    }
}


