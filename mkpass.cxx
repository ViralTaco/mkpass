#include <string_view>

namespace mkpass {
 using std::string_view_literals::operator ""sv;

 static constexpr auto kVersion = "mkpass 1.7.1"sv;
 static constexpr auto kLicense = R"(
Copyright (c) 2022 viraltaco_

MIT License
  Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 )"sv;

 static constexpr auto kUsage = R"(
mkpass generates 'random' passwords.
usage:
mkpass [OPT] symbols length

symbols         (off|on) if on use symbols. Default: on
length          (0 to 2^63) length/size in bytes. Default: 32

OPT (one of):
  --help         Prints this help message.
  --license      Prints the license.
  --version      Prints the version.

Examples:
  mkpass         Prints a 32 characters long password with symbols.
  mkpass on 32   Prints a 32 characters long password with symbols.
  mkpass off 1   Prints one alpha-numeric character.
  mkpass --help  Prints everything you just read.
 )"sv;
} // namespace mkpass

#include <cstdlib> // std::{ strtoul, exit }
#include <iostream>// std::{ cout, clog, cerr,... }
#include <random>  // std::{ random_device, default_random_engine,... }

int main(int argc, char** argv) {
  using uchar = unsigned char;
  using namespace mkpass;
  using namespace std;
  
  cout.sync_with_stdio(false); // One thread. Nothing to sync.

  static constexpr auto kAlpha =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\""sv;
  uchar lastidx = kAlpha.size() - ('\0' != kAlpha.back());
  auto len = 32u;
  
  if (argc > 1) {
    switch (string_view kArg(argv[1]); kArg[0]) {
    case 'o':
      if (kArg == "off") {
        lastidx -= "!\\#$%&'( )*+,-./:;<=>?@[]^_{|}~\""sv.size();
      }
      if (argv[2]) { len = strtoul(argv[2], nullptr, 10); }
      break;
    case '-':
      cout << kVersion;
      if      (kArg == "--license") { cout << kLicense; }
      else if (kArg != "--version") { cout << kUsage; }
      [[fallthrough]];
    default:
      cout.put('\n');
      return EXIT_SUCCESS;
    }
  }
  
  random_device r;
  seed_seq seed{ r(), r(), r(), };
  static auto t = mt19937_64(seed);
  
  uniform_int_distribution<uchar> d(0u, lastidx);
  generate_n(ostream_iterator<uchar>(cout), len, [&] { return kAlpha[d(t)]; });
}
