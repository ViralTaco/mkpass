/// copyright 2019-2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include <cstdlib> // std::{ strtoul, exit }
#include <iostream>// std::{ cout, clog, cerr,... }
#include <random>  // std::{ random_device, default_random_engine,... }

#include "mkpass.hpp"// <string_view>, mkpass::{ kVersion,... }

int main(int argc, char** argv) {
  std::cout.sync_with_stdio(false);// One thread. Nothing to sync.
  using uchar = unsigned char;
  static constexpr uchar kAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz0123456789"
                                       "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\"";
  static constexpr auto kSymCount = sizeof "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\"";
  uchar lastidx = sizeof kAlphabet - sizeof '\0';
  auto passlen = 32u;
  if (argc > 1) {
    switch (const std::string_view kArg1(argv[1]); kArg1[0]) {
    case 'o':
      if (kArg1 == "off") { lastidx = lastidx - kSymCount; }
      if (argv[2]) { passlen = std::strtoul(argv[2], nullptr, 10); }
      break;
    case '-':
      std::cout << mkpass::kVersion;
      if (kArg1 == "--license") {
        std::cout << mkpass::kLicense;
      } else if (kArg1 != "--version") {
        std::cout << mkpass::kUsage;
      }
      [[fallthrough]];
    default: std::cout.put('\n'); return EXIT_SUCCESS;
    }
  }
  static std::uniform_int_distribution<uchar> dist(0u, lastidx);

  std::random_device r;
  std::seed_seq seed{
    r(),
    r(),
    r(),
  };
  static auto twister = std::mt19937_64(seed);

  std::generate_n(std::ostream_iterator<uchar>(std::cout), passlen,
                  [&] { return kAlphabet[dist(twister)]; });
  std::cout.put('\n');
}
