/// copyright 2019-2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include "mkpass.hpp"  // <string_view>, mkpass::{ kVersion,... }

#include <cstdlib>     // std::{ strtoul, exit }
#include <random>      // std::{ random_device, default_random_engine,... }
#include <iostream>    // std::{ cout, clog, cerr,... }

int main(int argc, char** argv) {
  std::cout.sync_with_stdio(false); // One thread. Nothing to sync.

  bool symbols = true;
  if (argc >= 3) {
    using mkpass::kVersion, mkpass::kLicense, mkpass::kUsage;
    auto kArg1 = std::string_view(argv[1]);

    switch (kArg1[0]) {
    case 'o':
      symbols = (kArg1[1] == 'n');
      break;
    case '-':
      if ("--help" != kArg1) {
        if ("--version" == kArg1) {
          std::cout << kVersion << std::endl;
          return EXIT_SUCCESS;
        } else if ("--license" == kArg1) {
          std::cout << kVersion << kLicense << std::endl;
          return EXIT_SUCCESS;
        } else {
          std::cerr << kUsage;
          return EXIT_FAILURE;
        }
      } else { // argv[1] == "--help"
        [[fallthrough]];
      }
    case '?':
      std::cout << kUsage << std::endl;
      return EXIT_SUCCESS;
    default:
      std::cerr << "https://youtu.be/tJjs4w_-lV4\n";
      return EXIT_FAILURE;
    }
  }

  static constexpr unsigned char alphabet[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    "0123456789!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\""
  };

  // sizeof range_no_symbols_ignore_nul == 62u == 26 + 26 + 10;
  const auto kRangeSize = static_cast<unsigned char>((symbols) ? sizeof alphabet : 62u);
  std::random_device r;
  std::seed_seq seed{r(), r(), r()};
  static auto mt64 = std::mt19937(seed);

  static auto dist = std::uniform_int_distribution<unsigned char>(0u, kRangeSize);
  static const auto gen = [&] { return alphabet[dist(mt64)]; };

  auto len = (argc >= 2) ? std::strtoul(argv[argc - 1], nullptr, 10) : 32UL;
  std::generate_n(std::ostream_iterator<unsigned char>(std::cout), len, gen);
  std::cout.flush();
}
