#include "Config.hpp"
#include <string>
#include <filesystem>
#include <iostream>
#include "Logger.hpp"

namespace fs = std::filesystem;
const char *config_filename = "config.json";

static void print_object(const typename artemreyt::Config::json_map_t &object, std::string indent="") {
    for (const auto &param_value: object) {
        if (param_value.is_object())
            print_object(param_value, indent + "  ");
        else
            std::cout << indent << param_value << std::endl;
    }
}

static void print_config(const artemreyt::Config &config) {
    
    for (const auto &param_value: config) {
        if (param_value.is_object())
            print_object(param_value, "  ");
        else
            std::cout << param_value << std::endl;
    }
}

static void test_read_at(const artemreyt::Config &config) {
    if (config.at("write_hello_message")) {
        int times_to_write = config.at("times_to_write");
        for (int i = 0; i < times_to_write; ++i) {
            std::string hello_message = config.at("hello_message");
            std::cout << i + 1 << ". config.at: " << hello_message << std::endl;
        }
    }
}

static void test_read_barckets_operator(const artemreyt::Config &config) {
    if (config["write_hello_message"]) {
        int times_to_write = config["times_to_write"];
        for (int i = 0; i < times_to_write; ++i) {
            std::string hello_message = config["hello_message"];
            std::cout << i + 1 << ". config[]: " << hello_message << std::endl;
        }
    }
}


int main(int argc, char **argv) {
    const std::string json_config_relative_path = 
            fs::path(argv[0]).parent_path().append(config_filename).string();

    Logger::FileLogger logger("easy_example.log");
    artemreyt::Config config(json_config_relative_path, logger);

    std::cout << "------- PRINT CONFIG TEST -------\n";
    print_config(config);
    std::cout << "------- PRINT CONFIG TEST -------\n";

    std::cout << "-------- READ `at()` TEST -------\n";
    test_read_at(config);
    std::cout << "-------- READ `at()` TEST -------\n";

    std::cout << "--------- READ `[]` TEST --------\n";
    test_read_barckets_operator(config);
    std::cout << "--------- READ `[]` TEST --------\n";

    std::cout << "------- WRITE `at()` TEST -------\n";
    std::cout << "switching `hello_message` to `hello from config` and `times_to_write` to 2\n";

    Logger::FileLogger copy_logger("copy_easy_example.log");
    artemreyt::Config copy_config(config, copy_logger);
    copy_config.at("hello_message") = "hello from copy config";
    copy_config["times_to_write"] = 2;
    test_read_at(copy_config);
    std::cout << "------- WRITE `at()` TEST -------\n";

    // Access to non-exist
    try {
        copy_config.at("sdkdk") = 4;
    } catch (...) {}



    return 0;
}