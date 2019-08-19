//
// Aspia Project
// Copyright (C) 2019 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "crypto/srp_constants.h"

namespace crypto {

//
// RFC 5054
// Appendix A. SRP Group Parameters
// N - big prime number (N = 2q + 1, where q prime also).
// g - generator of prime modulo N.
//

namespace {

const uint8_t kSrpGroup_1024[] =
{
    0xEE, 0xAF, 0x0A, 0xB9, 0xAD, 0xB3, 0x8D, 0xD6, 0x9C, 0x33, 0xF8, 0x0A, 0xFA, 0x8F, 0xC5, 0xE8,
    0x60, 0x72, 0x61, 0x87, 0x75, 0xFF, 0x3C, 0x0B, 0x9E, 0xA2, 0x31, 0x4C, 0x9C, 0x25, 0x65, 0x76,
    0xD6, 0x74, 0xDF, 0x74, 0x96, 0xEA, 0x81, 0xD3, 0x38, 0x3B, 0x48, 0x13, 0xD6, 0x92, 0xC6, 0xE0,
    0xE0, 0xD5, 0xD8, 0xE2, 0x50, 0xB9, 0x8B, 0xE4, 0x8E, 0x49, 0x5C, 0x1D, 0x60, 0x89, 0xDA, 0xD1,
    0x5D, 0xC7, 0xD7, 0xB4, 0x61, 0x54, 0xD6, 0xB6, 0xCE, 0x8E, 0xF4, 0xAD, 0x69, 0xB1, 0x5D, 0x49,
    0x82, 0x55, 0x9B, 0x29, 0x7B, 0xCF, 0x18, 0x85, 0xC5, 0x29, 0xF5, 0x66, 0x66, 0x0E, 0x57, 0xEC,
    0x68, 0xED, 0xBC, 0x3C, 0x05, 0x72, 0x6C, 0xC0, 0x2F, 0xD4, 0xCB, 0xF4, 0x97, 0x6E, 0xAA, 0x9A,
    0xFD, 0x51, 0x38, 0xFE, 0x83, 0x76, 0x43, 0x5B, 0x9F, 0xC6, 0x1D, 0x2F, 0xC0, 0xEB, 0x06, 0xE3
};

const uint8_t kSrpGroup_1536[] =
{
    0x9D, 0xEF, 0x3C, 0xAF, 0xB9, 0x39, 0x27, 0x7A, 0xB1, 0xF1, 0x2A, 0x86, 0x17, 0xA4, 0x7B, 0xBB,
    0xDB, 0xA5, 0x1D, 0xF4, 0x99, 0xAC, 0x4C, 0x80, 0xBE, 0xEE, 0xA9, 0x61, 0x4B, 0x19, 0xCC, 0x4D,
    0x5F, 0x4F, 0x5F, 0x55, 0x6E, 0x27, 0xCB, 0xDE, 0x51, 0xC6, 0xA9, 0x4B, 0xE4, 0x60, 0x7A, 0x29,
    0x15, 0x58, 0x90, 0x3B, 0xA0, 0xD0, 0xF8, 0x43, 0x80, 0xB6, 0x55, 0xBB, 0x9A, 0x22, 0xE8, 0xDC,
    0xDF, 0x02, 0x8A, 0x7C, 0xEC, 0x67, 0xF0, 0xD0, 0x81, 0x34, 0xB1, 0xC8, 0xB9, 0x79, 0x89, 0x14,
    0x9B, 0x60, 0x9E, 0x0B, 0xE3, 0xBA, 0xB6, 0x3D, 0x47, 0x54, 0x83, 0x81, 0xDB, 0xC5, 0xB1, 0xFC,
    0x76, 0x4E, 0x3F, 0x4B, 0x53, 0xDD, 0x9D, 0xA1, 0x15, 0x8B, 0xFD, 0x3E, 0x2B, 0x9C, 0x8C, 0xF5,
    0x6E, 0xDF, 0x01, 0x95, 0x39, 0x34, 0x96, 0x27, 0xDB, 0x2F, 0xD5, 0x3D, 0x24, 0xB7, 0xC4, 0x86,
    0x65, 0x77, 0x2E, 0x43, 0x7D, 0x6C, 0x7F, 0x8C, 0xE4, 0x42, 0x73, 0x4A, 0xF7, 0xCC, 0xB7, 0xAE,
    0x83, 0x7C, 0x26, 0x4A, 0xE3, 0xA9, 0xBE, 0xB8, 0x7F, 0x8A, 0x2F, 0xE9, 0xB8, 0xB5, 0x29, 0x2E,
    0x5A, 0x02, 0x1F, 0xFF, 0x5E, 0x91, 0x47, 0x9E, 0x8C, 0xE7, 0xA2, 0x8C, 0x24, 0x42, 0xC6, 0xF3,
    0x15, 0x18, 0x0F, 0x93, 0x49, 0x9A, 0x23, 0x4D, 0xCF, 0x76, 0xE3, 0xFE, 0xD1, 0x35, 0xF9, 0xBB
};

const uint8_t kSrpGroup_2048[] =
{
    0xAC, 0x6B, 0xDB, 0x41, 0x32, 0x4A, 0x9A, 0x9B, 0xF1, 0x66, 0xDE, 0x5E, 0x13, 0x89, 0x58, 0x2F,
    0xAF, 0x72, 0xB6, 0x65, 0x19, 0x87, 0xEE, 0x07, 0xFC, 0x31, 0x92, 0x94, 0x3D, 0xB5, 0x60, 0x50,
    0xA3, 0x73, 0x29, 0xCB, 0xB4, 0xA0, 0x99, 0xED, 0x81, 0x93, 0xE0, 0x75, 0x77, 0x67, 0xA1, 0x3D,
    0xD5, 0x23, 0x12, 0xAB, 0x4B, 0x03, 0x31, 0x0D, 0xCD, 0x7F, 0x48, 0xA9, 0xDA, 0x04, 0xFD, 0x50,
    0xE8, 0x08, 0x39, 0x69, 0xED, 0xB7, 0x67, 0xB0, 0xCF, 0x60, 0x95, 0x17, 0x9A, 0x16, 0x3A, 0xB3,
    0x66, 0x1A, 0x05, 0xFB, 0xD5, 0xFA, 0xAA, 0xE8, 0x29, 0x18, 0xA9, 0x96, 0x2F, 0x0B, 0x93, 0xB8,
    0x55, 0xF9, 0x79, 0x93, 0xEC, 0x97, 0x5E, 0xEA, 0xA8, 0x0D, 0x74, 0x0A, 0xDB, 0xF4, 0xFF, 0x74,
    0x73, 0x59, 0xD0, 0x41, 0xD5, 0xC3, 0x3E, 0xA7, 0x1D, 0x28, 0x1E, 0x44, 0x6B, 0x14, 0x77, 0x3B,
    0xCA, 0x97, 0xB4, 0x3A, 0x23, 0xFB, 0x80, 0x16, 0x76, 0xBD, 0x20, 0x7A, 0x43, 0x6C, 0x64, 0x81,
    0xF1, 0xD2, 0xB9, 0x07, 0x87, 0x17, 0x46, 0x1A, 0x5B, 0x9D, 0x32, 0xE6, 0x88, 0xF8, 0x77, 0x48,
    0x54, 0x45, 0x23, 0xB5, 0x24, 0xB0, 0xD5, 0x7D, 0x5E, 0xA7, 0x7A, 0x27, 0x75, 0xD2, 0xEC, 0xFA,
    0x03, 0x2C, 0xFB, 0xDB, 0xF5, 0x2F, 0xB3, 0x78, 0x61, 0x60, 0x27, 0x90, 0x04, 0xE5, 0x7A, 0xE6,
    0xAF, 0x87, 0x4E, 0x73, 0x03, 0xCE, 0x53, 0x29, 0x9C, 0xCC, 0x04, 0x1C, 0x7B, 0xC3, 0x08, 0xD8,
    0x2A, 0x56, 0x98, 0xF3, 0xA8, 0xD0, 0xC3, 0x82, 0x71, 0xAE, 0x35, 0xF8, 0xE9, 0xDB, 0xFB, 0xB6,
    0x94, 0xB5, 0xC8, 0x03, 0xD8, 0x9F, 0x7A, 0xE4, 0x35, 0xDE, 0x23, 0x6D, 0x52, 0x5F, 0x54, 0x75,
    0x9B, 0x65, 0xE3, 0x72, 0xFC, 0xD6, 0x8E, 0xF2, 0x0F, 0xA7, 0x11, 0x1F, 0x9E, 0x4A, 0xFF, 0x73
};

const uint8_t kSrpGroup_3072[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9, 0x0F, 0xDA, 0xA2, 0x21, 0x68, 0xC2, 0x34,
    0xC4, 0xC6, 0x62, 0x8B, 0x80, 0xDC, 0x1C, 0xD1, 0x29, 0x02, 0x4E, 0x08, 0x8A, 0x67, 0xCC, 0x74,
    0x02, 0x0B, 0xBE, 0xA6, 0x3B, 0x13, 0x9B, 0x22, 0x51, 0x4A, 0x08, 0x79, 0x8E, 0x34, 0x04, 0xDD,
    0xEF, 0x95, 0x19, 0xB3, 0xCD, 0x3A, 0x43, 0x1B, 0x30, 0x2B, 0x0A, 0x6D, 0xF2, 0x5F, 0x14, 0x37,
    0x4F, 0xE1, 0x35, 0x6D, 0x6D, 0x51, 0xC2, 0x45, 0xE4, 0x85, 0xB5, 0x76, 0x62, 0x5E, 0x7E, 0xC6,
    0xF4, 0x4C, 0x42, 0xE9, 0xA6, 0x37, 0xED, 0x6B, 0x0B, 0xFF, 0x5C, 0xB6, 0xF4, 0x06, 0xB7, 0xED,
    0xEE, 0x38, 0x6B, 0xFB, 0x5A, 0x89, 0x9F, 0xA5, 0xAE, 0x9F, 0x24, 0x11, 0x7C, 0x4B, 0x1F, 0xE6,
    0x49, 0x28, 0x66, 0x51, 0xEC, 0xE4, 0x5B, 0x3D, 0xC2, 0x00, 0x7C, 0xB8, 0xA1, 0x63, 0xBF, 0x05,
    0x98, 0xDA, 0x48, 0x36, 0x1C, 0x55, 0xD3, 0x9A, 0x69, 0x16, 0x3F, 0xA8, 0xFD, 0x24, 0xCF, 0x5F,
    0x83, 0x65, 0x5D, 0x23, 0xDC, 0xA3, 0xAD, 0x96, 0x1C, 0x62, 0xF3, 0x56, 0x20, 0x85, 0x52, 0xBB,
    0x9E, 0xD5, 0x29, 0x07, 0x70, 0x96, 0x96, 0x6D, 0x67, 0x0C, 0x35, 0x4E, 0x4A, 0xBC, 0x98, 0x04,
    0xF1, 0x74, 0x6C, 0x08, 0xCA, 0x18, 0x21, 0x7C, 0x32, 0x90, 0x5E, 0x46, 0x2E, 0x36, 0xCE, 0x3B,
    0xE3, 0x9E, 0x77, 0x2C, 0x18, 0x0E, 0x86, 0x03, 0x9B, 0x27, 0x83, 0xA2, 0xEC, 0x07, 0xA2, 0x8F,
    0xB5, 0xC5, 0x5D, 0xF0, 0x6F, 0x4C, 0x52, 0xC9, 0xDE, 0x2B, 0xCB, 0xF6, 0x95, 0x58, 0x17, 0x18,
    0x39, 0x95, 0x49, 0x7C, 0xEA, 0x95, 0x6A, 0xE5, 0x15, 0xD2, 0x26, 0x18, 0x98, 0xFA, 0x05, 0x10,
    0x15, 0x72, 0x8E, 0x5A, 0x8A, 0xAA, 0xC4, 0x2D, 0xAD, 0x33, 0x17, 0x0D, 0x04, 0x50, 0x7A, 0x33,
    0xA8, 0x55, 0x21, 0xAB, 0xDF, 0x1C, 0xBA, 0x64, 0xEC, 0xFB, 0x85, 0x04, 0x58, 0xDB, 0xEF, 0x0A,
    0x8A, 0xEA, 0x71, 0x57, 0x5D, 0x06, 0x0C, 0x7D, 0xB3, 0x97, 0x0F, 0x85, 0xA6, 0xE1, 0xE4, 0xC7,
    0xAB, 0xF5, 0xAE, 0x8C, 0xDB, 0x09, 0x33, 0xD7, 0x1E, 0x8C, 0x94, 0xE0, 0x4A, 0x25, 0x61, 0x9D,
    0xCE, 0xE3, 0xD2, 0x26, 0x1A, 0xD2, 0xEE, 0x6B, 0xF1, 0x2F, 0xFA, 0x06, 0xD9, 0x8A, 0x08, 0x64,
    0xD8, 0x76, 0x02, 0x73, 0x3E, 0xC8, 0x6A, 0x64, 0x52, 0x1F, 0x2B, 0x18, 0x17, 0x7B, 0x20, 0x0C,
    0xBB, 0xE1, 0x17, 0x57, 0x7A, 0x61, 0x5D, 0x6C, 0x77, 0x09, 0x88, 0xC0, 0xBA, 0xD9, 0x46, 0xE2,
    0x08, 0xE2, 0x4F, 0xA0, 0x74, 0xE5, 0xAB, 0x31, 0x43, 0xDB, 0x5B, 0xFC, 0xE0, 0xFD, 0x10, 0x8E,
    0x4B, 0x82, 0xD1, 0x20, 0xA9, 0x3A, 0xD2, 0xCA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const uint8_t kSrpGroup_4096[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9, 0x0F, 0xDA, 0xA2, 0x21, 0x68, 0xC2, 0x34,
    0xC4, 0xC6, 0x62, 0x8B, 0x80, 0xDC, 0x1C, 0xD1, 0x29, 0x02, 0x4E, 0x08, 0x8A, 0x67, 0xCC, 0x74,
    0x02, 0x0B, 0xBE, 0xA6, 0x3B, 0x13, 0x9B, 0x22, 0x51, 0x4A, 0x08, 0x79, 0x8E, 0x34, 0x04, 0xDD,
    0xEF, 0x95, 0x19, 0xB3, 0xCD, 0x3A, 0x43, 0x1B, 0x30, 0x2B, 0x0A, 0x6D, 0xF2, 0x5F, 0x14, 0x37,
    0x4F, 0xE1, 0x35, 0x6D, 0x6D, 0x51, 0xC2, 0x45, 0xE4, 0x85, 0xB5, 0x76, 0x62, 0x5E, 0x7E, 0xC6,
    0xF4, 0x4C, 0x42, 0xE9, 0xA6, 0x37, 0xED, 0x6B, 0x0B, 0xFF, 0x5C, 0xB6, 0xF4, 0x06, 0xB7, 0xED,
    0xEE, 0x38, 0x6B, 0xFB, 0x5A, 0x89, 0x9F, 0xA5, 0xAE, 0x9F, 0x24, 0x11, 0x7C, 0x4B, 0x1F, 0xE6,
    0x49, 0x28, 0x66, 0x51, 0xEC, 0xE4, 0x5B, 0x3D, 0xC2, 0x00, 0x7C, 0xB8, 0xA1, 0x63, 0xBF, 0x05,
    0x98, 0xDA, 0x48, 0x36, 0x1C, 0x55, 0xD3, 0x9A, 0x69, 0x16, 0x3F, 0xA8, 0xFD, 0x24, 0xCF, 0x5F,
    0x83, 0x65, 0x5D, 0x23, 0xDC, 0xA3, 0xAD, 0x96, 0x1C, 0x62, 0xF3, 0x56, 0x20, 0x85, 0x52, 0xBB,
    0x9E, 0xD5, 0x29, 0x07, 0x70, 0x96, 0x96, 0x6D, 0x67, 0x0C, 0x35, 0x4E, 0x4A, 0xBC, 0x98, 0x04,
    0xF1, 0x74, 0x6C, 0x08, 0xCA, 0x18, 0x21, 0x7C, 0x32, 0x90, 0x5E, 0x46, 0x2E, 0x36, 0xCE, 0x3B,
    0xE3, 0x9E, 0x77, 0x2C, 0x18, 0x0E, 0x86, 0x03, 0x9B, 0x27, 0x83, 0xA2, 0xEC, 0x07, 0xA2, 0x8F,
    0xB5, 0xC5, 0x5D, 0xF0, 0x6F, 0x4C, 0x52, 0xC9, 0xDE, 0x2B, 0xCB, 0xF6, 0x95, 0x58, 0x17, 0x18,
    0x39, 0x95, 0x49, 0x7C, 0xEA, 0x95, 0x6A, 0xE5, 0x15, 0xD2, 0x26, 0x18, 0x98, 0xFA, 0x05, 0x10,
    0x15, 0x72, 0x8E, 0x5A, 0x8A, 0xAA, 0xC4, 0x2D, 0xAD, 0x33, 0x17, 0x0D, 0x04, 0x50, 0x7A, 0x33,
    0xA8, 0x55, 0x21, 0xAB, 0xDF, 0x1C, 0xBA, 0x64, 0xEC, 0xFB, 0x85, 0x04, 0x58, 0xDB, 0xEF, 0x0A,
    0x8A, 0xEA, 0x71, 0x57, 0x5D, 0x06, 0x0C, 0x7D, 0xB3, 0x97, 0x0F, 0x85, 0xA6, 0xE1, 0xE4, 0xC7,
    0xAB, 0xF5, 0xAE, 0x8C, 0xDB, 0x09, 0x33, 0xD7, 0x1E, 0x8C, 0x94, 0xE0, 0x4A, 0x25, 0x61, 0x9D,
    0xCE, 0xE3, 0xD2, 0x26, 0x1A, 0xD2, 0xEE, 0x6B, 0xF1, 0x2F, 0xFA, 0x06, 0xD9, 0x8A, 0x08, 0x64,
    0xD8, 0x76, 0x02, 0x73, 0x3E, 0xC8, 0x6A, 0x64, 0x52, 0x1F, 0x2B, 0x18, 0x17, 0x7B, 0x20, 0x0C,
    0xBB, 0xE1, 0x17, 0x57, 0x7A, 0x61, 0x5D, 0x6C, 0x77, 0x09, 0x88, 0xC0, 0xBA, 0xD9, 0x46, 0xE2,
    0x08, 0xE2, 0x4F, 0xA0, 0x74, 0xE5, 0xAB, 0x31, 0x43, 0xDB, 0x5B, 0xFC, 0xE0, 0xFD, 0x10, 0x8E,
    0x4B, 0x82, 0xD1, 0x20, 0xA9, 0x21, 0x08, 0x01, 0x1A, 0x72, 0x3C, 0x12, 0xA7, 0x87, 0xE6, 0xD7,
    0x88, 0x71, 0x9A, 0x10, 0xBD, 0xBA, 0x5B, 0x26, 0x99, 0xC3, 0x27, 0x18, 0x6A, 0xF4, 0xE2, 0x3C,
    0x1A, 0x94, 0x68, 0x34, 0xB6, 0x15, 0x0B, 0xDA, 0x25, 0x83, 0xE9, 0xCA, 0x2A, 0xD4, 0x4C, 0xE8,
    0xDB, 0xBB, 0xC2, 0xDB, 0x04, 0xDE, 0x8E, 0xF9, 0x2E, 0x8E, 0xFC, 0x14, 0x1F, 0xBE, 0xCA, 0xA6,
    0x28, 0x7C, 0x59, 0x47, 0x4E, 0x6B, 0xC0, 0x5D, 0x99, 0xB2, 0x96, 0x4F, 0xA0, 0x90, 0xC3, 0xA2,
    0x23, 0x3B, 0xA1, 0x86, 0x51, 0x5B, 0xE7, 0xED, 0x1F, 0x61, 0x29, 0x70, 0xCE, 0xE2, 0xD7, 0xAF,
    0xB8, 0x1B, 0xDD, 0x76, 0x21, 0x70, 0x48, 0x1C, 0xD0, 0x06, 0x91, 0x27, 0xD5, 0xB0, 0x5A, 0xA9,
    0x93, 0xB4, 0xEA, 0x98, 0x8D, 0x8F, 0xDD, 0xC1, 0x86, 0xFF, 0xB7, 0xDC, 0x90, 0xA6, 0xC0, 0x8F,
    0x4D, 0xF4, 0x35, 0xC9, 0x34, 0x06, 0x31, 0x99, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const uint8_t kSrpGroup_6144[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9, 0x0F, 0xDA, 0xA2, 0x21, 0x68, 0xC2, 0x34,
    0xC4, 0xC6, 0x62, 0x8B, 0x80, 0xDC, 0x1C, 0xD1, 0x29, 0x02, 0x4E, 0x08, 0x8A, 0x67, 0xCC, 0x74,
    0x02, 0x0B, 0xBE, 0xA6, 0x3B, 0x13, 0x9B, 0x22, 0x51, 0x4A, 0x08, 0x79, 0x8E, 0x34, 0x04, 0xDD,
    0xEF, 0x95, 0x19, 0xB3, 0xCD, 0x3A, 0x43, 0x1B, 0x30, 0x2B, 0x0A, 0x6D, 0xF2, 0x5F, 0x14, 0x37,
    0x4F, 0xE1, 0x35, 0x6D, 0x6D, 0x51, 0xC2, 0x45, 0xE4, 0x85, 0xB5, 0x76, 0x62, 0x5E, 0x7E, 0xC6,
    0xF4, 0x4C, 0x42, 0xE9, 0xA6, 0x37, 0xED, 0x6B, 0x0B, 0xFF, 0x5C, 0xB6, 0xF4, 0x06, 0xB7, 0xED,
    0xEE, 0x38, 0x6B, 0xFB, 0x5A, 0x89, 0x9F, 0xA5, 0xAE, 0x9F, 0x24, 0x11, 0x7C, 0x4B, 0x1F, 0xE6,
    0x49, 0x28, 0x66, 0x51, 0xEC, 0xE4, 0x5B, 0x3D, 0xC2, 0x00, 0x7C, 0xB8, 0xA1, 0x63, 0xBF, 0x05,
    0x98, 0xDA, 0x48, 0x36, 0x1C, 0x55, 0xD3, 0x9A, 0x69, 0x16, 0x3F, 0xA8, 0xFD, 0x24, 0xCF, 0x5F,
    0x83, 0x65, 0x5D, 0x23, 0xDC, 0xA3, 0xAD, 0x96, 0x1C, 0x62, 0xF3, 0x56, 0x20, 0x85, 0x52, 0xBB,
    0x9E, 0xD5, 0x29, 0x07, 0x70, 0x96, 0x96, 0x6D, 0x67, 0x0C, 0x35, 0x4E, 0x4A, 0xBC, 0x98, 0x04,
    0xF1, 0x74, 0x6C, 0x08, 0xCA, 0x18, 0x21, 0x7C, 0x32, 0x90, 0x5E, 0x46, 0x2E, 0x36, 0xCE, 0x3B,
    0xE3, 0x9E, 0x77, 0x2C, 0x18, 0x0E, 0x86, 0x03, 0x9B, 0x27, 0x83, 0xA2, 0xEC, 0x07, 0xA2, 0x8F,
    0xB5, 0xC5, 0x5D, 0xF0, 0x6F, 0x4C, 0x52, 0xC9, 0xDE, 0x2B, 0xCB, 0xF6, 0x95, 0x58, 0x17, 0x18,
    0x39, 0x95, 0x49, 0x7C, 0xEA, 0x95, 0x6A, 0xE5, 0x15, 0xD2, 0x26, 0x18, 0x98, 0xFA, 0x05, 0x10,
    0x15, 0x72, 0x8E, 0x5A, 0x8A, 0xAA, 0xC4, 0x2D, 0xAD, 0x33, 0x17, 0x0D, 0x04, 0x50, 0x7A, 0x33,
    0xA8, 0x55, 0x21, 0xAB, 0xDF, 0x1C, 0xBA, 0x64, 0xEC, 0xFB, 0x85, 0x04, 0x58, 0xDB, 0xEF, 0x0A,
    0x8A, 0xEA, 0x71, 0x57, 0x5D, 0x06, 0x0C, 0x7D, 0xB3, 0x97, 0x0F, 0x85, 0xA6, 0xE1, 0xE4, 0xC7,
    0xAB, 0xF5, 0xAE, 0x8C, 0xDB, 0x09, 0x33, 0xD7, 0x1E, 0x8C, 0x94, 0xE0, 0x4A, 0x25, 0x61, 0x9D,
    0xCE, 0xE3, 0xD2, 0x26, 0x1A, 0xD2, 0xEE, 0x6B, 0xF1, 0x2F, 0xFA, 0x06, 0xD9, 0x8A, 0x08, 0x64,
    0xD8, 0x76, 0x02, 0x73, 0x3E, 0xC8, 0x6A, 0x64, 0x52, 0x1F, 0x2B, 0x18, 0x17, 0x7B, 0x20, 0x0C,
    0xBB, 0xE1, 0x17, 0x57, 0x7A, 0x61, 0x5D, 0x6C, 0x77, 0x09, 0x88, 0xC0, 0xBA, 0xD9, 0x46, 0xE2,
    0x08, 0xE2, 0x4F, 0xA0, 0x74, 0xE5, 0xAB, 0x31, 0x43, 0xDB, 0x5B, 0xFC, 0xE0, 0xFD, 0x10, 0x8E,
    0x4B, 0x82, 0xD1, 0x20, 0xA9, 0x21, 0x08, 0x01, 0x1A, 0x72, 0x3C, 0x12, 0xA7, 0x87, 0xE6, 0xD7,
    0x88, 0x71, 0x9A, 0x10, 0xBD, 0xBA, 0x5B, 0x26, 0x99, 0xC3, 0x27, 0x18, 0x6A, 0xF4, 0xE2, 0x3C,
    0x1A, 0x94, 0x68, 0x34, 0xB6, 0x15, 0x0B, 0xDA, 0x25, 0x83, 0xE9, 0xCA, 0x2A, 0xD4, 0x4C, 0xE8,
    0xDB, 0xBB, 0xC2, 0xDB, 0x04, 0xDE, 0x8E, 0xF9, 0x2E, 0x8E, 0xFC, 0x14, 0x1F, 0xBE, 0xCA, 0xA6,
    0x28, 0x7C, 0x59, 0x47, 0x4E, 0x6B, 0xC0, 0x5D, 0x99, 0xB2, 0x96, 0x4F, 0xA0, 0x90, 0xC3, 0xA2,
    0x23, 0x3B, 0xA1, 0x86, 0x51, 0x5B, 0xE7, 0xED, 0x1F, 0x61, 0x29, 0x70, 0xCE, 0xE2, 0xD7, 0xAF,
    0xB8, 0x1B, 0xDD, 0x76, 0x21, 0x70, 0x48, 0x1C, 0xD0, 0x06, 0x91, 0x27, 0xD5, 0xB0, 0x5A, 0xA9,
    0x93, 0xB4, 0xEA, 0x98, 0x8D, 0x8F, 0xDD, 0xC1, 0x86, 0xFF, 0xB7, 0xDC, 0x90, 0xA6, 0xC0, 0x8F,
    0x4D, 0xF4, 0x35, 0xC9, 0x34, 0x02, 0x84, 0x92, 0x36, 0xC3, 0xFA, 0xB4, 0xD2, 0x7C, 0x70, 0x26,
    0xC1, 0xD4, 0xDC, 0xB2, 0x60, 0x26, 0x46, 0xDE, 0xC9, 0x75, 0x1E, 0x76, 0x3D, 0xBA, 0x37, 0xBD,
    0xF8, 0xFF, 0x94, 0x06, 0xAD, 0x9E, 0x53, 0x0E, 0xE5, 0xDB, 0x38, 0x2F, 0x41, 0x30, 0x01, 0xAE,
    0xB0, 0x6A, 0x53, 0xED, 0x90, 0x27, 0xD8, 0x31, 0x17, 0x97, 0x27, 0xB0, 0x86, 0x5A, 0x89, 0x18,
    0xDA, 0x3E, 0xDB, 0xEB, 0xCF, 0x9B, 0x14, 0xED, 0x44, 0xCE, 0x6C, 0xBA, 0xCE, 0xD4, 0xBB, 0x1B,
    0xDB, 0x7F, 0x14, 0x47, 0xE6, 0xCC, 0x25, 0x4B, 0x33, 0x20, 0x51, 0x51, 0x2B, 0xD7, 0xAF, 0x42,
    0x6F, 0xB8, 0xF4, 0x01, 0x37, 0x8C, 0xD2, 0xBF, 0x59, 0x83, 0xCA, 0x01, 0xC6, 0x4B, 0x92, 0xEC,
    0xF0, 0x32, 0xEA, 0x15, 0xD1, 0x72, 0x1D, 0x03, 0xF4, 0x82, 0xD7, 0xCE, 0x6E, 0x74, 0xFE, 0xF6,
    0xD5, 0x5E, 0x70, 0x2F, 0x46, 0x98, 0x0C, 0x82, 0xB5, 0xA8, 0x40, 0x31, 0x90, 0x0B, 0x1C, 0x9E,
    0x59, 0xE7, 0xC9, 0x7F, 0xBE, 0xC7, 0xE8, 0xF3, 0x23, 0xA9, 0x7A, 0x7E, 0x36, 0xCC, 0x88, 0xBE,
    0x0F, 0x1D, 0x45, 0xB7, 0xFF, 0x58, 0x5A, 0xC5, 0x4B, 0xD4, 0x07, 0xB2, 0x2B, 0x41, 0x54, 0xAA,
    0xCC, 0x8F, 0x6D, 0x7E, 0xBF, 0x48, 0xE1, 0xD8, 0x14, 0xCC, 0x5E, 0xD2, 0x0F, 0x80, 0x37, 0xE0,
    0xA7, 0x97, 0x15, 0xEE, 0xF2, 0x9B, 0xE3, 0x28, 0x06, 0xA1, 0xD5, 0x8B, 0xB7, 0xC5, 0xDA, 0x76,
    0xF5, 0x50, 0xAA, 0x3D, 0x8A, 0x1F, 0xBF, 0xF0, 0xEB, 0x19, 0xCC, 0xB1, 0xA3, 0x13, 0xD5, 0x5C,
    0xDA, 0x56, 0xC9, 0xEC, 0x2E, 0xF2, 0x96, 0x32, 0x38, 0x7F, 0xE8, 0xD7, 0x6E, 0x3C, 0x04, 0x68,
    0x04, 0x3E, 0x8F, 0x66, 0x3F, 0x48, 0x60, 0xEE, 0x12, 0xBF, 0x2D, 0x5B, 0x0B, 0x74, 0x74, 0xD6,
    0xE6, 0x94, 0xF9, 0x1E, 0x6D, 0xCC, 0x40, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const uint8_t kSrpGroup_8192[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9, 0x0F, 0xDA, 0xA2, 0x21, 0x68, 0xC2, 0x34,
    0xC4, 0xC6, 0x62, 0x8B, 0x80, 0xDC, 0x1C, 0xD1, 0x29, 0x02, 0x4E, 0x08, 0x8A, 0x67, 0xCC, 0x74,
    0x02, 0x0B, 0xBE, 0xA6, 0x3B, 0x13, 0x9B, 0x22, 0x51, 0x4A, 0x08, 0x79, 0x8E, 0x34, 0x04, 0xDD,
    0xEF, 0x95, 0x19, 0xB3, 0xCD, 0x3A, 0x43, 0x1B, 0x30, 0x2B, 0x0A, 0x6D, 0xF2, 0x5F, 0x14, 0x37,
    0x4F, 0xE1, 0x35, 0x6D, 0x6D, 0x51, 0xC2, 0x45, 0xE4, 0x85, 0xB5, 0x76, 0x62, 0x5E, 0x7E, 0xC6,
    0xF4, 0x4C, 0x42, 0xE9, 0xA6, 0x37, 0xED, 0x6B, 0x0B, 0xFF, 0x5C, 0xB6, 0xF4, 0x06, 0xB7, 0xED,
    0xEE, 0x38, 0x6B, 0xFB, 0x5A, 0x89, 0x9F, 0xA5, 0xAE, 0x9F, 0x24, 0x11, 0x7C, 0x4B, 0x1F, 0xE6,
    0x49, 0x28, 0x66, 0x51, 0xEC, 0xE4, 0x5B, 0x3D, 0xC2, 0x00, 0x7C, 0xB8, 0xA1, 0x63, 0xBF, 0x05,
    0x98, 0xDA, 0x48, 0x36, 0x1C, 0x55, 0xD3, 0x9A, 0x69, 0x16, 0x3F, 0xA8, 0xFD, 0x24, 0xCF, 0x5F,
    0x83, 0x65, 0x5D, 0x23, 0xDC, 0xA3, 0xAD, 0x96, 0x1C, 0x62, 0xF3, 0x56, 0x20, 0x85, 0x52, 0xBB,
    0x9E, 0xD5, 0x29, 0x07, 0x70, 0x96, 0x96, 0x6D, 0x67, 0x0C, 0x35, 0x4E, 0x4A, 0xBC, 0x98, 0x04,
    0xF1, 0x74, 0x6C, 0x08, 0xCA, 0x18, 0x21, 0x7C, 0x32, 0x90, 0x5E, 0x46, 0x2E, 0x36, 0xCE, 0x3B,
    0xE3, 0x9E, 0x77, 0x2C, 0x18, 0x0E, 0x86, 0x03, 0x9B, 0x27, 0x83, 0xA2, 0xEC, 0x07, 0xA2, 0x8F,
    0xB5, 0xC5, 0x5D, 0xF0, 0x6F, 0x4C, 0x52, 0xC9, 0xDE, 0x2B, 0xCB, 0xF6, 0x95, 0x58, 0x17, 0x18,
    0x39, 0x95, 0x49, 0x7C, 0xEA, 0x95, 0x6A, 0xE5, 0x15, 0xD2, 0x26, 0x18, 0x98, 0xFA, 0x05, 0x10,
    0x15, 0x72, 0x8E, 0x5A, 0x8A, 0xAA, 0xC4, 0x2D, 0xAD, 0x33, 0x17, 0x0D, 0x04, 0x50, 0x7A, 0x33,
    0xA8, 0x55, 0x21, 0xAB, 0xDF, 0x1C, 0xBA, 0x64, 0xEC, 0xFB, 0x85, 0x04, 0x58, 0xDB, 0xEF, 0x0A,
    0x8A, 0xEA, 0x71, 0x57, 0x5D, 0x06, 0x0C, 0x7D, 0xB3, 0x97, 0x0F, 0x85, 0xA6, 0xE1, 0xE4, 0xC7,
    0xAB, 0xF5, 0xAE, 0x8C, 0xDB, 0x09, 0x33, 0xD7, 0x1E, 0x8C, 0x94, 0xE0, 0x4A, 0x25, 0x61, 0x9D,
    0xCE, 0xE3, 0xD2, 0x26, 0x1A, 0xD2, 0xEE, 0x6B, 0xF1, 0x2F, 0xFA, 0x06, 0xD9, 0x8A, 0x08, 0x64,
    0xD8, 0x76, 0x02, 0x73, 0x3E, 0xC8, 0x6A, 0x64, 0x52, 0x1F, 0x2B, 0x18, 0x17, 0x7B, 0x20, 0x0C,
    0xBB, 0xE1, 0x17, 0x57, 0x7A, 0x61, 0x5D, 0x6C, 0x77, 0x09, 0x88, 0xC0, 0xBA, 0xD9, 0x46, 0xE2,
    0x08, 0xE2, 0x4F, 0xA0, 0x74, 0xE5, 0xAB, 0x31, 0x43, 0xDB, 0x5B, 0xFC, 0xE0, 0xFD, 0x10, 0x8E,
    0x4B, 0x82, 0xD1, 0x20, 0xA9, 0x21, 0x08, 0x01, 0x1A, 0x72, 0x3C, 0x12, 0xA7, 0x87, 0xE6, 0xD7,
    0x88, 0x71, 0x9A, 0x10, 0xBD, 0xBA, 0x5B, 0x26, 0x99, 0xC3, 0x27, 0x18, 0x6A, 0xF4, 0xE2, 0x3C,
    0x1A, 0x94, 0x68, 0x34, 0xB6, 0x15, 0x0B, 0xDA, 0x25, 0x83, 0xE9, 0xCA, 0x2A, 0xD4, 0x4C, 0xE8,
    0xDB, 0xBB, 0xC2, 0xDB, 0x04, 0xDE, 0x8E, 0xF9, 0x2E, 0x8E, 0xFC, 0x14, 0x1F, 0xBE, 0xCA, 0xA6,
    0x28, 0x7C, 0x59, 0x47, 0x4E, 0x6B, 0xC0, 0x5D, 0x99, 0xB2, 0x96, 0x4F, 0xA0, 0x90, 0xC3, 0xA2,
    0x23, 0x3B, 0xA1, 0x86, 0x51, 0x5B, 0xE7, 0xED, 0x1F, 0x61, 0x29, 0x70, 0xCE, 0xE2, 0xD7, 0xAF,
    0xB8, 0x1B, 0xDD, 0x76, 0x21, 0x70, 0x48, 0x1C, 0xD0, 0x06, 0x91, 0x27, 0xD5, 0xB0, 0x5A, 0xA9,
    0x93, 0xB4, 0xEA, 0x98, 0x8D, 0x8F, 0xDD, 0xC1, 0x86, 0xFF, 0xB7, 0xDC, 0x90, 0xA6, 0xC0, 0x8F,
    0x4D, 0xF4, 0x35, 0xC9, 0x34, 0x02, 0x84, 0x92, 0x36, 0xC3, 0xFA, 0xB4, 0xD2, 0x7C, 0x70, 0x26,
    0xC1, 0xD4, 0xDC, 0xB2, 0x60, 0x26, 0x46, 0xDE, 0xC9, 0x75, 0x1E, 0x76, 0x3D, 0xBA, 0x37, 0xBD,
    0xF8, 0xFF, 0x94, 0x06, 0xAD, 0x9E, 0x53, 0x0E, 0xE5, 0xDB, 0x38, 0x2F, 0x41, 0x30, 0x01, 0xAE,
    0xB0, 0x6A, 0x53, 0xED, 0x90, 0x27, 0xD8, 0x31, 0x17, 0x97, 0x27, 0xB0, 0x86, 0x5A, 0x89, 0x18,
    0xDA, 0x3E, 0xDB, 0xEB, 0xCF, 0x9B, 0x14, 0xED, 0x44, 0xCE, 0x6C, 0xBA, 0xCE, 0xD4, 0xBB, 0x1B,
    0xDB, 0x7F, 0x14, 0x47, 0xE6, 0xCC, 0x25, 0x4B, 0x33, 0x20, 0x51, 0x51, 0x2B, 0xD7, 0xAF, 0x42,
    0x6F, 0xB8, 0xF4, 0x01, 0x37, 0x8C, 0xD2, 0xBF, 0x59, 0x83, 0xCA, 0x01, 0xC6, 0x4B, 0x92, 0xEC,
    0xF0, 0x32, 0xEA, 0x15, 0xD1, 0x72, 0x1D, 0x03, 0xF4, 0x82, 0xD7, 0xCE, 0x6E, 0x74, 0xFE, 0xF6,
    0xD5, 0x5E, 0x70, 0x2F, 0x46, 0x98, 0x0C, 0x82, 0xB5, 0xA8, 0x40, 0x31, 0x90, 0x0B, 0x1C, 0x9E,
    0x59, 0xE7, 0xC9, 0x7F, 0xBE, 0xC7, 0xE8, 0xF3, 0x23, 0xA9, 0x7A, 0x7E, 0x36, 0xCC, 0x88, 0xBE,
    0x0F, 0x1D, 0x45, 0xB7, 0xFF, 0x58, 0x5A, 0xC5, 0x4B, 0xD4, 0x07, 0xB2, 0x2B, 0x41, 0x54, 0xAA,
    0xCC, 0x8F, 0x6D, 0x7E, 0xBF, 0x48, 0xE1, 0xD8, 0x14, 0xCC, 0x5E, 0xD2, 0x0F, 0x80, 0x37, 0xE0,
    0xA7, 0x97, 0x15, 0xEE, 0xF2, 0x9B, 0xE3, 0x28, 0x06, 0xA1, 0xD5, 0x8B, 0xB7, 0xC5, 0xDA, 0x76,
    0xF5, 0x50, 0xAA, 0x3D, 0x8A, 0x1F, 0xBF, 0xF0, 0xEB, 0x19, 0xCC, 0xB1, 0xA3, 0x13, 0xD5, 0x5C,
    0xDA, 0x56, 0xC9, 0xEC, 0x2E, 0xF2, 0x96, 0x32, 0x38, 0x7F, 0xE8, 0xD7, 0x6E, 0x3C, 0x04, 0x68,
    0x04, 0x3E, 0x8F, 0x66, 0x3F, 0x48, 0x60, 0xEE, 0x12, 0xBF, 0x2D, 0x5B, 0x0B, 0x74, 0x74, 0xD6,
    0xE6, 0x94, 0xF9, 0x1E, 0x6D, 0xBE, 0x11, 0x59, 0x74, 0xA3, 0x92, 0x6F, 0x12, 0xFE, 0xE5, 0xE4,
    0x38, 0x77, 0x7C, 0xB6, 0xA9, 0x32, 0xDF, 0x8C, 0xD8, 0xBE, 0xC4, 0xD0, 0x73, 0xB9, 0x31, 0xBA,
    0x3B, 0xC8, 0x32, 0xB6, 0x8D, 0x9D, 0xD3, 0x00, 0x74, 0x1F, 0xA7, 0xBF, 0x8A, 0xFC, 0x47, 0xED,
    0x25, 0x76, 0xF6, 0x93, 0x6B, 0xA4, 0x24, 0x66, 0x3A, 0xAB, 0x63, 0x9C, 0x5A, 0xE4, 0xF5, 0x68,
    0x34, 0x23, 0xB4, 0x74, 0x2B, 0xF1, 0xC9, 0x78, 0x23, 0x8F, 0x16, 0xCB, 0xE3, 0x9D, 0x65, 0x2D,
    0xE3, 0xFD, 0xB8, 0xBE, 0xFC, 0x84, 0x8A, 0xD9, 0x22, 0x22, 0x2E, 0x04, 0xA4, 0x03, 0x7C, 0x07,
    0x13, 0xEB, 0x57, 0xA8, 0x1A, 0x23, 0xF0, 0xC7, 0x34, 0x73, 0xFC, 0x64, 0x6C, 0xEA, 0x30, 0x6B,
    0x4B, 0xCB, 0xC8, 0x86, 0x2F, 0x83, 0x85, 0xDD, 0xFA, 0x9D, 0x4B, 0x7F, 0xA2, 0xC0, 0x87, 0xE8,
    0x79, 0x68, 0x33, 0x03, 0xED, 0x5B, 0xDD, 0x3A, 0x06, 0x2B, 0x3C, 0xF5, 0xB3, 0xA2, 0x78, 0xA6,
    0x6D, 0x2A, 0x13, 0xF8, 0x3F, 0x44, 0xF8, 0x2D, 0xDF, 0x31, 0x0E, 0xE0, 0x74, 0xAB, 0x6A, 0x36,
    0x45, 0x97, 0xE8, 0x99, 0xA0, 0x25, 0x5D, 0xC1, 0x64, 0xF3, 0x1C, 0xC5, 0x08, 0x46, 0x85, 0x1D,
    0xF9, 0xAB, 0x48, 0x19, 0x5D, 0xED, 0x7E, 0xA1, 0xB1, 0xD5, 0x10, 0xBD, 0x7E, 0xE7, 0x4D, 0x73,
    0xFA, 0xF3, 0x6B, 0xC3, 0x1E, 0xCF, 0xA2, 0x68, 0x35, 0x90, 0x46, 0xF4, 0xEB, 0x87, 0x9F, 0x92,
    0x40, 0x09, 0x43, 0x8B, 0x48, 0x1C, 0x6C, 0xD7, 0x88, 0x9A, 0x00, 0x2E, 0xD5, 0xEE, 0x38, 0x2B,
    0xC9, 0x19, 0x0D, 0xA6, 0xFC, 0x02, 0x6E, 0x47, 0x95, 0x58, 0xE4, 0x47, 0x56, 0x77, 0xE9, 0xAA,
    0x9E, 0x30, 0x50, 0xE2, 0x76, 0x56, 0x94, 0xDF, 0xC8, 0x1F, 0x56, 0xE8, 0x80, 0xB9, 0x6E, 0x71,
    0x60, 0xC9, 0x80, 0xDD, 0x98, 0xED, 0xD3, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static_assert(sizeof(kSrpGroup_1024) == 1024 / 8);
static_assert(sizeof(kSrpGroup_1536) == 1536 / 8);
static_assert(sizeof(kSrpGroup_2048) == 2048 / 8);
static_assert(sizeof(kSrpGroup_3072) == 3072 / 8);
static_assert(sizeof(kSrpGroup_4096) == 4096 / 8);
static_assert(sizeof(kSrpGroup_6144) == 6144 / 8);
static_assert(sizeof(kSrpGroup_8192) == 8192 / 8);

const uint8_t kSrpGenerator_2[] = { 2 };
const uint8_t kSrpGenerator_5[] = { 5 };
const uint8_t kSrpGenerator_19[] = { 19 };

} // namespace

const SrpNgPair kSrpNgPair_1024 =
{
    { reinterpret_cast<const char*>(kSrpGroup_1024), sizeof(kSrpGroup_1024) },
    { reinterpret_cast<const char*>(kSrpGenerator_2), sizeof(kSrpGenerator_2) }
};

const SrpNgPair kSrpNgPair_1536 =
{
    { reinterpret_cast<const char*>(kSrpGroup_1536), sizeof(kSrpGroup_1536) },
    { reinterpret_cast<const char*>(kSrpGenerator_2), sizeof(kSrpGenerator_2) }
};

const SrpNgPair kSrpNgPair_2048 =
{
    { reinterpret_cast<const char*>(kSrpGroup_2048), sizeof(kSrpGroup_2048) },
    { reinterpret_cast<const char*>(kSrpGenerator_2), sizeof(kSrpGenerator_2) }
};

const SrpNgPair kSrpNgPair_3072 =
{
    { reinterpret_cast<const char*>(kSrpGroup_3072), sizeof(kSrpGroup_3072) },
    { reinterpret_cast<const char*>(kSrpGenerator_5), sizeof(kSrpGenerator_5) }
};

const SrpNgPair kSrpNgPair_4096 =
{
    { reinterpret_cast<const char*>(kSrpGroup_4096), sizeof(kSrpGroup_4096) },
    { reinterpret_cast<const char*>(kSrpGenerator_5), sizeof(kSrpGenerator_5) }
};

const SrpNgPair kSrpNgPair_6144 =
{
    { reinterpret_cast<const char*>(kSrpGroup_6144), sizeof(kSrpGroup_6144) },
    { reinterpret_cast<const char*>(kSrpGenerator_5), sizeof(kSrpGenerator_5) }
};

const SrpNgPair kSrpNgPair_8192 =
{
    { reinterpret_cast<const char*>(kSrpGroup_8192), sizeof(kSrpGroup_8192) },
    { reinterpret_cast<const char*>(kSrpGenerator_19), sizeof(kSrpGenerator_19) }
};

} // namespace crypto
