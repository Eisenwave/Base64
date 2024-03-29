// Copyright (c) 2021, FearlessDoggo21
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. All advertising materials mentioning features or use of this software must
//    display the following acknowledgement:
//      This product includes the Base64 Utilities Library or a modified version,
//      originally developed by FearlessDoggo21.

// 4. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY FearlessDoggo21 "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL FearlessDoggo21 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <stdio.h>
#include "base64.h"

int main(int argc, char *argv[]) {
    char *string = "NXBUwl^MYZVJi47a1*n22@iTCD-%Z3rM&YJoLU&9Ss6Y_T5*sW?ufI27iKN"
    "4Lst%@sA2N7&IX9dXl-D&^-A-B$7=i9dDNdg7ygcK#KBFT?A9T&h|k#=l=3699Rp1pPhJO+fx="
    "fdD^b0s%$i?EPBq$mqX9n3xr*OEMk3*!dbHu=Uy5nc3O9U3h4rCW&lk$EkZ!@XD6*d0Bj#==qb"
    "CnW*g=E0r^ItOIizy0SdMe32xh9xupKZsRwx7hj-YG!Wpc$d^";

    char *encode = EncodeBase64(string);
    printf("Encoded:\n%s\n", encode);

    char verify = VerifyBase64(encode);
    printf("Verified:\n%s\n", verify ? "True" : "False");

    char *decode = DecodeBase64(encode);
    printf("Decoded:\n%s\n", decode);
    printf("Original:\n%s\n", string);
    printf("Correct:\n%s\n", strcmp(string, decode) ? "No" : "Yes");
}
