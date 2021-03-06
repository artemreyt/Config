#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "nlohmann/json.hpp"
#include "Logger.hpp"
#include <mutex>
#include <string>
#include <iostream>

namespace artemreyt {

class Config {
public:
    using json_map_t  = nlohmann::json;
    using value_type = json_map_t::value_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using key_type = json_map_t::object_t::key_type;
    using const_iterator = json_map_t::const_iterator;

private:
    json_map_t _json_map;
    mutable std::mutex _mutex;
    Logger::BaseLogger &_logger;

public:
    explicit Config(const std::string &filename, Logger::BaseLogger &logger);
    Config(const Config &other, Logger::BaseLogger &logger);

    const_reference at(const key_type &key) const ;
    const_reference operator[](const key_type &key) const;

    void insert_or_assign(const key_type &key, const value_type &value);
    bool erase(const key_type& key);
    bool contains(const key_type &key);

    const_iterator begin() const ;
    const_iterator end() const ;
};
};

#endif // CONFIG_HPP
