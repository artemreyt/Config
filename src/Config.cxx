#include "Config.hpp"
#include "Logger.hpp"
#include <fstream>
#include <mutex>

namespace artemreyt
{
    // Constructors
    Config::Config(const std::string &filename,  Logger::BaseLogger &logger): _logger(logger) {
        std::ifstream config_file(filename);
        config_file >> _json_map;
    }

    Config::Config(const Config &other, Logger::BaseLogger &logger): 
            _json_map(other._json_map), _logger(logger) {}

    // at() methods
    Config::const_reference
    Config::at(const Config::key_type &key) const {
        std::lock_guard<std::mutex> guard(_mutex);



        try {
            Config::const_reference retv = _json_map.at(key);
            _logger.info(std::string("Access by const reference to value of field `").append(key) + '`');
            return retv;
        } catch (nlohmann::detail::out_of_range &ex) {
            _logger.warn(std::string("Access to field `").append(key).append("` failed: ").append(ex.what()));
            throw;
        }
    }

    Config::reference
    Config::at(const Config::key_type &key) {
        std::lock_guard<std::mutex> guard(_mutex);

        try {
            Config::reference retv = _json_map.at(key);
            _logger.info(std::string("Access by non-const reference to value of field `").append(key) + '`');
            return retv;
        } catch (nlohmann::detail::out_of_range &ex) {
            _logger.warn(std::string("Access to field `").append(key).append("` failed: ").append(ex.what()));
            throw;
        }
    }

    // operator[]
    Config::const_reference
    Config::operator[](const key_type &key) const {
        std::lock_guard<std::mutex> guard(_mutex);

         try {
            Config::const_reference retv = _json_map[key];
            _logger.info(std::string("Access by const reference to value of field `").append(key) + '`');
            return retv;
        } catch (nlohmann::detail::out_of_range &ex) {
            _logger.warn(std::string("Access to field `").append(key).append("` failed: ").append(ex.what()));
            throw;
        }
        return _json_map[key];
    }

    Config::reference
    Config::operator[](const key_type &key) {
        std::lock_guard<std::mutex> guard(_mutex);

         try {
            Config::reference retv = _json_map[key];
            _logger.info(std::string("Access by non-const reference to value of field `").append(key) + '`');
            return retv;
        } catch (nlohmann::detail::out_of_range &ex) {
            _logger.warn(std::string("Access to field `").append(key).append("` failed: ").append(ex.what()));
            throw;
        }
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
