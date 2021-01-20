/*
 * Copyright 2020, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "km_compat_type_conversion.h"

#define TEST_ENUM_CONVERSION(type, variant)                                                        \
    ASSERT_EQ(KMV1::type::variant, convert(V4_0::type::variant));                                  \
    ASSERT_EQ(V4_0::type::variant, convert(KMV1::type::variant))

TEST(KmCompatTypeConversionTest, testEnumCoversion) {
    TEST_ENUM_CONVERSION(KeyPurpose, ENCRYPT);
    TEST_ENUM_CONVERSION(KeyPurpose, DECRYPT);
    TEST_ENUM_CONVERSION(KeyPurpose, SIGN);
    TEST_ENUM_CONVERSION(KeyPurpose, VERIFY);
    TEST_ENUM_CONVERSION(KeyPurpose, WRAP_KEY);
    TEST_ENUM_CONVERSION(Algorithm, RSA);
    TEST_ENUM_CONVERSION(Algorithm, EC);
    TEST_ENUM_CONVERSION(Algorithm, AES);
    TEST_ENUM_CONVERSION(Algorithm, TRIPLE_DES);
    TEST_ENUM_CONVERSION(Algorithm, HMAC);
    TEST_ENUM_CONVERSION(Digest, NONE);
    TEST_ENUM_CONVERSION(Digest, MD5);
    TEST_ENUM_CONVERSION(Digest, SHA1);
    TEST_ENUM_CONVERSION(Digest, SHA_2_224);
    TEST_ENUM_CONVERSION(Digest, SHA_2_256);
    TEST_ENUM_CONVERSION(Digest, SHA_2_384);
    TEST_ENUM_CONVERSION(Digest, SHA_2_512);
    TEST_ENUM_CONVERSION(EcCurve, P_224);
    TEST_ENUM_CONVERSION(EcCurve, P_256);
    TEST_ENUM_CONVERSION(EcCurve, P_384);
    TEST_ENUM_CONVERSION(EcCurve, P_521);
    TEST_ENUM_CONVERSION(BlockMode, ECB);
    TEST_ENUM_CONVERSION(BlockMode, CBC);
    TEST_ENUM_CONVERSION(BlockMode, CTR);
    TEST_ENUM_CONVERSION(BlockMode, GCM);
    TEST_ENUM_CONVERSION(PaddingMode, NONE);
    TEST_ENUM_CONVERSION(PaddingMode, RSA_OAEP);
    TEST_ENUM_CONVERSION(PaddingMode, RSA_PSS);
    TEST_ENUM_CONVERSION(PaddingMode, RSA_PKCS1_1_5_ENCRYPT);
    TEST_ENUM_CONVERSION(PaddingMode, RSA_PKCS1_1_5_SIGN);
    TEST_ENUM_CONVERSION(PaddingMode, PKCS7);
    TEST_ENUM_CONVERSION(HardwareAuthenticatorType, PASSWORD);
    TEST_ENUM_CONVERSION(HardwareAuthenticatorType, FINGERPRINT);
    TEST_ENUM_CONVERSION(SecurityLevel, SOFTWARE);
    TEST_ENUM_CONVERSION(SecurityLevel, TRUSTED_ENVIRONMENT);
    TEST_ENUM_CONVERSION(SecurityLevel, STRONGBOX);
    TEST_ENUM_CONVERSION(KeyOrigin, GENERATED);
    TEST_ENUM_CONVERSION(KeyOrigin, DERIVED);
    TEST_ENUM_CONVERSION(KeyOrigin, IMPORTED);
    TEST_ENUM_CONVERSION(KeyOrigin, GENERATED);
    TEST_ENUM_CONVERSION(KeyOrigin, SECURELY_IMPORTED);

    // RESERVED and UNKNOWN correspond but changed their names.
    ASSERT_EQ(KMV1::KeyOrigin::RESERVED, convert(V4_0::KeyOrigin::UNKNOWN));
    ASSERT_EQ(V4_0::KeyOrigin::UNKNOWN, convert(KMV1::KeyOrigin::RESERVED));
}

#define TEST_KEY_PARAMETER_CONVERSION_V4_0(tag)                                                    \
    do {                                                                                           \
        auto kmv1_param = KMV1::makeKeyParameter(                                                  \
            KMV1::tag, KMV1::TypedTag2ValueType<decltype(KMV1::tag)>::type{});                     \
        auto legacy_param = V4_0::makeKeyParameter(                                                \
            V4_0::tag, V4_0::TypedTag2ValueType<decltype(V4_0::tag)>::type{});                     \
        ASSERT_EQ(legacy_param, convertKeyParameterToLegacy(kmv1_param));                          \
        ASSERT_EQ(kmv1_param, convertKeyParameterFromLegacy(legacy_param));                        \
    } while (false)

#define TEST_KEY_PARAMETER_CONVERSION_V4_1(tag)                                                    \
    do {                                                                                           \
        auto kmv1_param = KMV1::makeKeyParameter(                                                  \
            KMV1::tag, KMV1::TypedTag2ValueType<decltype(KMV1::tag)>::type{});                     \
        auto legacy_param = V4_0::makeKeyParameter(                                                \
            V4_1::tag, V4_0::TypedTag2ValueType<decltype(V4_1::tag)>::type{});                     \
        ASSERT_EQ(legacy_param, convertKeyParameterToLegacy(kmv1_param));                          \
        ASSERT_EQ(kmv1_param, convertKeyParameterFromLegacy(legacy_param));                        \
    } while (false)

TEST(KmCompatTypeConversionTest, testKeyParameterConversion) {
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ACTIVE_DATETIME);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ALGORITHM);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ALLOW_WHILE_ON_BODY);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_APPLICATION_DATA);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_APPLICATION_ID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ASSOCIATED_DATA);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_APPLICATION_ID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_CHALLENGE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_BRAND);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_DEVICE);
    //    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_IMEI);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_MANUFACTURER);
    //    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_MEID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_PRODUCT);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_MODEL);
    //    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ATTESTATION_ID_SERIAL);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_AUTH_TIMEOUT);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_BLOCK_MODE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_BOOTLOADER_ONLY);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_BOOT_PATCHLEVEL);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_CALLER_NONCE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_CONFIRMATION_TOKEN);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_CREATION_DATETIME);
    TEST_KEY_PARAMETER_CONVERSION_V4_1(TAG_DEVICE_UNIQUE_ATTESTATION);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_DIGEST);
    TEST_KEY_PARAMETER_CONVERSION_V4_1(TAG_EARLY_BOOT_ONLY);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_EC_CURVE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_HARDWARE_TYPE);
    TEST_KEY_PARAMETER_CONVERSION_V4_1(TAG_IDENTITY_CREDENTIAL_KEY);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_INCLUDE_UNIQUE_ID);
    //    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_INVALID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_KEY_SIZE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_MAC_LENGTH);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_MAX_USES_PER_BOOT);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_MIN_MAC_LENGTH);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_MIN_SECONDS_BETWEEN_OPS);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_NONCE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_NO_AUTH_REQUIRED);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ORIGIN);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ORIGINATION_EXPIRE_DATETIME);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_OS_PATCHLEVEL);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_OS_VERSION);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_PADDING);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_PURPOSE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_RESET_SINCE_ID_ROTATION);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ROLLBACK_RESISTANCE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_ROOT_OF_TRUST);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_RSA_PUBLIC_EXPONENT);
    TEST_KEY_PARAMETER_CONVERSION_V4_1(TAG_STORAGE_KEY);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_TRUSTED_CONFIRMATION_REQUIRED);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_TRUSTED_USER_PRESENCE_REQUIRED);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_UNIQUE_ID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_UNLOCKED_DEVICE_REQUIRED);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_USAGE_EXPIRE_DATETIME);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_USER_AUTH_TYPE);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_USER_ID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_USER_SECURE_ID);
    TEST_KEY_PARAMETER_CONVERSION_V4_0(TAG_VENDOR_PATCHLEVEL);
}