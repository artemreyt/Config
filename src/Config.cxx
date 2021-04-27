#include "Config.hpp"
#include "Logger.hpp"
#include <fstream>
#include <mutex>

namespace artemreyt
{
    Config::Config(const std::string &filename,  Logger::BaseLogger &logger): _logger(logger) {
        std::ifstream config_file(filename);
        config_file >> _json_map;
    }

    Config::Config(const Config &other, Logger::BaseLogger &logger): 
            _json_map(other._json_map), _logger(logger) {}

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

    void
    Config::insert_or_assign(const Config::key_type &key, const Config::value_type &value) {
        std::lock_guard<std::mutex> guard(_mutex);
        if (_json_map.contains(key)) {
            value_type old_value = _json_map[key];
            _json_map[key] = value;
            _logger.info(std::string("Change value for field `").append(key).append("` from ")
                        .append(old_value.dump()).append(" to ").append(value.dump()));
        } else {
            _json_map.emplace(key, value);
            _logger.info(std::string("Insert new pair.").append(key).append(": ").append(value.dump()));
        }
    }

    bool
    Config::erase(const key_type& key) {
        std::lock_guard<std::mutex> guard(_mutex);
        
        bool retv =  _json_map.erase(key);
        if (retv)
            _logger.info(std::string("Field `").append(key).append("` erased"));
        else
            _logger.warn(std::string("Fail to erase field `").append(key).append("`"));
            return retv;
        
    }
    
    bool
    Config::contains(const key_type &key) {
        std::lock_guard<std::mutex> guard(_mutex);
        _logger.debug(std::string("Checking contains field`").append(key).append("`"));
        return _json_map.contains(key);
    }

    Config::const_iterator
    Config::begin() const {
        std::lock_guard<std::mutex> guard(_mutex);

        _logger.debug("Access to begin() by const reference");
        return _json_map.begin();
    }

    Config::const_iterator
    Config::end() const {
        std::lock_guard<std::mutex> guard(_mutex);
        _logger.debug("access to end() by const reference");
        return _json_map.end();
    }
}
