# C++ Class for holding and manupulation with Config from JSON file

Raw implementation of class `Config`.

Using self-written `Logger` class.

Not for production usage. Needed time to improve such things like
move semanthic, raise perfomance for interthread usage and so on.

## Build
```
    $ git submodule update --init --recursive
    $ cmake ./
    $ make
```


## Usage:
```C++
#include "Config.hpp"
#include "Logger.hpp"
...
    Logger::FileLogger logger("file.log", Logger::t_level::DEBUG);
    artemreyt::Config config("config.json", logger);

    // read
    int int_value = config["int_param_key"];
    std::string string_value = config.at("string_param_key");

    // add new element or overwrite existing
    config.insert_or_assign("pi", 3.14);

    // remove
    config.erase("key_name_to_erase");

    // contains
    config.contains("key_to_check");

    // iterate by values (now only)
    for (auto &elem: config) {
        std::cout << elem << std::endl;
    }
```