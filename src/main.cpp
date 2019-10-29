#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>

#include "secretstapler.hpp"

using namespace std;

void usage(string_view appname) {
  cerr << "Usage:" << endl;
  cerr << appname
       << " <--mode=generate|encrypt|decrypt> "
          "--file=\"/path/to/file.ext\" [--key=\"KEY\"] [--iv=\"IV\"]"
       << endl;
}

cxxopts::ParseResult parseCli(int argc, char* argv[]) {
  try {
    string appname = filesystem::path(argv[0]).filename().string();
    cxxopts::Options cli(appname, string(PROJECT_DESCRIPTION));
    cli.allow_unrecognised_options();

    cxxopts::OptionAdder add = cli.add_options();
    add("h,help", "Print this message.");
    add("m,mode", "Cipher mode <generate|encrypt|decrypt>.",
        cxxopts::value<string>()->default_value("generate"));
    add("f,file", "File.", cxxopts::value<filesystem::path>());
    add("key", "Cipher key.", cxxopts::value<string>());
    add("iv", "Initialization vector.", cxxopts::value<string>());

    cxxopts::ParseResult result = cli.parse(argc, argv);
    if (result.count("help")) {
      clog << cli.help() << endl;
      exit(EXIT_SUCCESS);
    }

    // Check arguments.
    bool isNeedUsageMessage = false;
    string mode = result["mode"].as<string>();
    if (mode != "generate" && mode != "encrypt" && mode != "decrypt")
      isNeedUsageMessage = true;

    if (!result.count("file")) isNeedUsageMessage = true;

    if (mode == "encrypt" || mode == "decrypt") {
      if (!result.count("key") || !result.count("iv"))
        isNeedUsageMessage = true;
    }

    // Show usage.
    if (isNeedUsageMessage) {
      usage(appname);
      exit(EXIT_FAILURE);
    }

    // Check file.
    filesystem::path file = result["file"].as<filesystem::path>();
    if (mode != "generate") {
      if (!filesystem::exists(file) || filesystem::is_directory(file)) {
        cerr << "[ERROR] File not found: " << file << endl;
        exit(EXIT_FAILURE);
      }
    }

    return result;
  } catch (const cxxopts::OptionException& e) {
    cerr << "[ERROR] Options parsing failed: " << e.what() << endl;
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char* argv[]) {
  auto cli = parseCli(argc, argv);

  string mode = cli["mode"].as<string>();
  filesystem::path file = cli["file"].as<filesystem::path>();
  filesystem::path result;

  cout << "[" << mode << "]" << endl;

  if (mode == "generate") {
    result = ss::generate(file);
  } else if (mode == "encrypt") {
    string key = cli["key"].as<string>();
    string iv = cli["iv"].as<string>();

    result = ss::xencrypt(file, key, iv);
  } else if (mode == "decrypt") {
    string key = cli["key"].as<string>();
    string iv = cli["iv"].as<string>();

    result = ss::xdecrypt(file, key, iv);
  }

  cout << "Output file: " << result.string() << endl;

  return EXIT_SUCCESS;
}
