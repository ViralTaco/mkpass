/// copyright 2019-2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include <random>    // std::{ random_device, default_random_engine,... }
#include <cstdlib>   // std::{ strtoul, exit }
#include <iostream>  // std::{ cout, clog, cerr,... }

#include "mkpass.hpp"  // <string_view>, mkpass::{ kVersion,... }

int main(int argc, char** argv) {
  std::cout.sync_with_stdio(false); // One thread. Nothing to sync.
  
  auto passlen = 32ul;
  auto symbols = true;
  if (argc >= 2) {
    const auto kArg1 = std::string_view(argv[1]);

    switch (kArg1[0]) {
    case 'o':
      symbols = (kArg1[1] == 'n');
      if (argv[2]) // argv[argc] is always nullptr
        passlen = std::strtoul(argv[2], nullptr, 10);
      break;
    case '-':
      if ("--help" != kArg1) {
        if ("--version" == kArg1)
          std::cout << mkpass::kVersion << std::endl;
        else if ("--license" == kArg1)
          std::cout << mkpass::kVersion << mkpass::kLicense << std::endl;
        else
          goto fail_;
        
        return EXIT_SUCCESS;
      }
      [[fallthrough]];  // "--help" == kArg1
    case '?':
      std::cout << mkpass::kUsage << std::endl;
      return EXIT_SUCCESS;
fail_:
    default:
      std::cerr << mkpass::kUsage << "\nhttps://youtu.be/tJjs4w_-lV4\n";
      return EXIT_FAILURE;
    }
  }

  using uchar = unsigned char;
  static constexpr uchar kAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz0123456789!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\"";

  // length of kAlphabet (no symbols, no NUL) is 10 + 2(26) = 62
  const auto kLen = static_cast<uchar>((symbols) ? sizeof kAlphabet : 62u);
  static auto dist = std::uniform_int_distribution<uchar>(0u, kLen - 1);

  std::random_device rice;
  std::seed_seq seed{ rice(), rice(), rice() };
  static auto twister = std::mt19937_64(seed);
  static const auto gen = [&] { return kAlphabet[dist(twister)]; };

  std::generate_n(std::ostream_iterator<uchar>(std::cout), passlen, gen);
  std::cout << std::endl;
}
