/// copyright 2019-2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include <cstdlib> // std::{ strtoul, exit }
#include <iostream>// std::{ cout, clog, cerr,... }
#include <random>  // std::{ random_device, default_random_engine,... }

#include "mkpass.hpp"// <string_view>, mkpass::{ kVersion,... }

int main(int argc, char** argv) {
  std::cout.sync_with_stdio(false); // One thread. Nothing to sync.
  using uchar = unsigned char;
  static constexpr uchar kAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz0123456789"
                                       "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\"";
  uchar symbols = sizeof "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\"" - 1;
  auto passlen = 32ul;
  if (argc >= 2) {
    switch (const std::string_view kArg1(argv[1]); kArg1[0]) {
    case 'o':
      symbols = symbols * (kArg1[1] == 'n');
      if (argv[2]) // argv[argc] is always nullptr
        passlen = std::strtoul(argv[2], nullptr, 10);
      break;
    case '-':
      if ("--version" == kArg1)
        std::cout << mkpass::kVersion;
      else if ("--license" == kArg1)
        std::cout << mkpass::kVersion << mkpass::kLicense;
      else
        std::cout << mkpass::kUsage;
      [[fallthrough]];
    default:
      std::cout.put('\n').flush();
      return EXIT_SUCCESS;
    }
  }
  // sizeof kAlphabet - symbols (32) - NUL (1) = 10 + 2(26) = 62
  static std::uniform_int_distribution<uchar> dist(0u, symbols + 61u);

  std::random_device r;
  std::seed_seq seed{r(), r(), r()};
  static auto twister = std::mt19937_64(seed);

  std::generate_n(std::ostream_iterator<uchar>(std::cout), passlen,
                  [&] { return kAlphabet[dist(twister)]; });
  std::cout.put('\n').flush();
}
