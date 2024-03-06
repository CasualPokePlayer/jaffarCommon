#pragma once

/**
 * @file concurrent.hpp
 * @brief Containers designed for fast parallel, mutual exclusive access
 */

#include <mutex>
#include <deque>
#include <phmap/parallel_hashmap/phmap.h>
#include <atomic_queue/include/atomic_queue/atomic_queue.h>
#include <oneapi/tbb/concurrent_map.h>

namespace jaffarCommon
{

namespace concurrent
{

template <class T> using atomicQueue_t = atomic_queue::AtomicQueueB<T>;
template <class V> using HashSet_t = phmap::parallel_flat_hash_set<V, phmap::priv::hash_default_hash<V>, phmap::priv::hash_default_eq<V>, std::allocator<V>, 4, std::mutex>;
template <class K, class V> using HashMap_t = phmap::parallel_flat_hash_map<K, V, phmap::priv::hash_default_hash<K>, phmap::priv::hash_default_eq<K>, std::allocator<std::pair<const K, V>>, 4, std::mutex>;
template <class K, class V, class C = std::greater<K>> using concurrentMultimap_t = oneapi::tbb::concurrent_multimap<K,V,C>;

template <class T> class Deque
{
 public: 

 Deque() = default;
 ~Deque() = default;

 __INLINE__ auto& getInternalStorage() { return _internalDeque; }

 __INLINE__ void push_back_no_lock(T element)
 {
   _internalDeque.push_back(element);
 }

 __INLINE__ void push_back(T element)
 {
   _mutex.lock();
   _internalDeque.push_back(element);
   _mutex.unlock();
 }

  __INLINE__ void push_front_no_lock(T element)
 {
   _internalDeque.push_front(element);
 }


 __INLINE__ void push_front(T element)
 {
   _mutex.lock();
   _internalDeque.push_front(element);
   _mutex.unlock();
 }

 __INLINE__ T front() const
 {
   return _internalDeque.front();
 }
 
 __INLINE__ T back() const
 {
   return _internalDeque.back();
 }

 __INLINE__ void pop_front()
 {
   _mutex.lock();
   _internalDeque.pop_front();
   _mutex.unlock();
 }

 __INLINE__ void pop_back()
 {
   _mutex.lock();
   _internalDeque.pop_back();
   _mutex.unlock();
 }

 __INLINE__ bool pop_back_get(T& element)
 {
   _mutex.lock();

   if (_internalDeque.empty())
   {
    _mutex.unlock();
     return false;
   }

   element = _internalDeque.back();
   _internalDeque.pop_back();
   
   _mutex.unlock();
   return true;
 }

 __INLINE__ bool pop_front_get(T& element)
 {
   _mutex.lock();

   if (_internalDeque.empty())
   {
    _mutex.unlock();
     return false;
   }

   element = _internalDeque.front();
   _internalDeque.pop_front();
   
   _mutex.unlock();
   return true;
 }

 __INLINE__ size_t wasSize() const
 {
   return _internalDeque.size();
 }

 private:

 std::mutex _mutex;
 std::deque<T> _internalDeque;
};

} // namespace concurrent

} // namespace jaffarCommon
