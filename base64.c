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

#include "base64.h"

uint8_t *EncodeBase64(const uint8_t *string) {
    uint8_t *output;
    if (!(output = malloc(1 + (((strlen(string) + 2) / 3) << 2)))) {
        return (uint8_t *)0;
    }

    size_t index = 0;
    uint16_t storage = 0;
    while (*string) {
        storage |= *string++;
        output[index++] = encodeMap[(storage >> 2) & 0x3F];
        storage <<= 8;

        storage |= *string++;
        output[index++] = encodeMap[(storage >> 4) & 0x3F];

        if (storage <<= 8) {
            storage |= *string++;
            output[index++] = encodeMap[(storage >> 6) & 0x3F];
        } else {
            break;
        }

        if (storage <<= 8) {
            output[index++] = encodeMap[(storage >> 8) & 0x3F];
        } else {
            break;
        }
    }

    if (index & 1) {
        output[index] = '=';
        output[index + 1] = '\0';
    } else if (index & 2) {
        output[index] = '=';
        output[index + 1] = '=';
        output[index + 2] = '\0';
    }

    return output;
}

uint8_t *DecodeBase64(const uint8_t *string) {
    uint8_t *output;
    size_t length = strlen(string);
    if (!(output = malloc(1 + (length >> 2) * 3 - (string[length - 1] == '=')
            - (string[length - 2] == '=')))) {
        return (uint8_t *)0;
    }

    size_t index = 0;
    uint32_t storage = 0;
    while (string[4]) {
        storage |= DecodeChar(*string++) << 18;
        storage |= DecodeChar(*string++) << 12;
        storage |= DecodeChar(*string++) << 6;
        storage |= DecodeChar(*string++);

        output[index++] = storage >> 16;
        output[index++] = (uint8_t)(storage >> 8);
        output[index++] = (uint8_t)storage;

        storage = 0;
    }

    storage |= DecodeChar(*string++) << 18;
    storage |= DecodeChar(*string++) << 12;
    output[index++] = storage >> 16;

    if (*string == '=') {
        output[index] = '\0';
        return output;
    }
    storage |= DecodeChar(*string++) << 6;
    output[index++] = (uint8_t)(storage >> 8);

    if (*string == '=') {
        output[index] = '\0';
        return output;
    }
    storage |= DecodeChar(*string);
    output[index++] = (uint8_t)storage;

    output[index] = '\0';
    return output;
}

uint8_t VerifyBase64(const uint8_t *string) {
    size_t index = 0;
    uint8_t temp = *string;
    while (temp) {
        if (!(
            (temp >= 'A' && temp <= 'Z') ||
            (temp >= 'a' && temp <= 'z') ||
            (temp >= '0' && temp <= '9') ||
            (temp == '-') ||
            (temp == '_')
        )) {
            if (temp == '=' &&
                (string[index + 1] == '\0' || // Only check further if not end
                (string[index + 1] == '=' && string[index + 2] == '\0'))
            ) {
                return 1;
            }
            return 0;
        }
        temp = string[++index];
    }
    return 1;
}
