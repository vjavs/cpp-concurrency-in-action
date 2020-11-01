/*
  Listing 3.13
  Protecting a data structure with std::shared_mutex
*/

#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

class dns_entry {};

class dns_cache {
  std::map<std::string, dns_entry> entries;
  mutable std::shared_mutex entry_mutex;

public:
  dns_entry find_entry(std::string const &domain) const {
    std::shared_lock lk{entry_mutex}; // protects for shared, read-only access
    return entries.contains(domain) ? entries.at(domain) : dns_entry{};
  }

  void update_or_add_entry(std::string const &domain,
                           dns_entry const &dns_details) {
    std::scoped_lock lk{entry_mutex}; // provides exclusive access for writing
    entries[domain] = dns_details;
  }
};
