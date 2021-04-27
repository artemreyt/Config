#include "Config.hpp"
#include <fstream>
#include <mutex>

namespace artemreyt
{
    // Constructors
    Config::Config(const std::string &filename) {
        std::ifstream config_file(filename);
        config_file >> _json_map;
    }

    Config::Config(const Config &other): _json_map(other._json_map) {}

    // at() methods
    Config::const_reference
    Config::at(const Config::key_type &key) const {
        std::lock_guard<std::mutex> guard(_mutex);
        return _json_map.at(key);
    }

    Config::reference
    Config::at(const Config::key_type &key) {
        std::lock_guard<std::mutex> guard(_mutex);
        return _json_map.at(key);
    }

    // operator[]
    Config::const_reference
    Config::operator[](const key_type &key) const {
        std::lock_guard<std::mutex> guard(_mutex);
        return _json_map[key];
    }

    Config::reference
    Config::operator[](const key_type &key) {
        std::lock_guard<std::mutex> guard(_mutex);
        return _json_map[key];
    }

    Config::const_iterator
    Config::begin() const {
        return _json_map.begin();
    }

    Config::const_iterator
    Config::end() const {
        return _json_map.end();
    }
}
