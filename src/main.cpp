/// copyright 2019-2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include "mkpass.hpp"  // <string_view>, mkpass::{ kVersion,... }

#include <cstdlib>     // std::{ strtoul, exit }
#include <random>      // std::{ random_device, default_random_engine,... }
#include <iostream>    // std::{ cout, clog, cerr,... }

int main(int argc, char** argv) {
  std::cout.sync_with_stdio(false); // One thread. Nothing to sync.
  
  auto passlen = 32UL;
  auto symbols = true;
  if (argc >= 2) {
    const auto kArg1 = std::string_view(argv[1]);

    switch (kArg1[0]) {
    case 'o':
      symbols = (kArg1[1] == 'n');
      if (argc > 2) passlen = std::strtoul(argv[2], nullptr, 10);
      break;
    case '-':
      if ("--help" != kArg1) {
        if ("--version" == kArg1)
          std::cout << mkpass::kVersion;
        else if ("--license" == kArg1)
          std::cout << mkpass::kVersion << mkpass::kLicense;
        else
          goto fail_;
        
        return EXIT_SUCCESS;
      }
      [[fallthrough]];
    case '?':
      std::cout << mkpass::kUsage;
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
  auto dist = std::uniform_int_distribution<uchar>(0u, kLen);

  auto rice = std::random_device();
  auto seed = std::seed_seq{ rice(), rice(), rice() };
  auto mt32 = std::mt19937(seed);
  const auto gen = [&] { return kAlphabet[dist(mt32)]; };

  std::generate_n(std::ostream_iterator<uchar>(std::cout), passlen, gen);
  std::cout.flush();
}
