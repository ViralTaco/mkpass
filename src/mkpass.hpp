#ifndef PRO_ANTH_MKPASS_HPP
#define PRO_ANTH_MKPASS_HPP
#include <string_view>

namespace mkpass {
using std::string_view_literals::operator ""sv;

static constexpr auto kVersion = "mkpass 1.4.2"sv;
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
  --help, ?      Prints this help message.
  --license      Prints the license.
  --version      Prints the version.

Examples:
  mkpass         Prints a 32 characters long password with symbols.
  mkpass on 32   Prints a 32 characters long password with symbols.
  mkpass off 1   Prints one alpha-numeric character.
  mkpass ?       Prints everything you just read.
  )"sv;
} // namespace mkpass
#endif
