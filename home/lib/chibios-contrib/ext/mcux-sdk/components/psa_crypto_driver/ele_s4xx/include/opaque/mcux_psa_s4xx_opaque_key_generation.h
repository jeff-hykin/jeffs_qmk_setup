/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MCUX_PSA_S4XX_OPAQUE_KEY_GENERATION_H
#define MCUX_PSA_S4XX_OPAQUE_KEY_GENERATION_H

/** \file mcux_psa_opaque_s4xx_key_generation.h
 *
 * This file contains the declaration of the entry points associated to the
 * key generation (i.e. random generation and extraction of public keys) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

#include "psa/crypto.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Generate a random key
 *
 * \param[in]  attributes        Attributes of the key to use
 * \param[out] key_buffer        Buffer to hold the generated key
 * \param[in]  key_buffer_size   Size in bytes of the key_buffer buffer
 * \param[out] key_buffer_length Size in bytes of the generated key
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_opaque_generate_key(const psa_key_attributes_t *attributes,
                                          uint8_t *key_buffer, size_t key_buffer_size,
                                          size_t *key_buffer_length);

/*!
 * \brief Destroy a random key
 *
 * \param[in]  attributes        Attributes of the key to destroy
 * \param[out] key_buffer        Buffer for the key
 * \param[in]  key_buffer_size   Size in bytes of the key_buffer buffer

 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_opaque_destroy_key(const psa_key_attributes_t *attributes,
                                         uint8_t *key_buffer, size_t key_buffer_size);

/*!
 * \brief Export the public key from a private key.
 *
 * \param[in]  attributes      Attributes of the key to use
 * \param[in]  key_buffer      Buffer to hold the generated key
 * \param[in]  key_buffer_size Size in bytes of the key_buffer buffer
 * \param[out] data            Buffer to hold the extracted public key
 * \param[in]  data_size       Size in bytes of the data buffer
 * \param[out] data_length     Size in bytes of the extracted public key
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_opaque_export_public_key(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size, uint8_t *data,
                                               size_t data_size, size_t *data_length);

/*!
 * \brief Return the buffer size required by driver for storing key.
 *
 * \param[in]  key_type        Type of key
 * \param[in]  key_buffer_size Size in bits of the key to be stored
 *
 * \retval  size_t on success. 0 on
 *          failure
 */
size_t ele_s4xx_opaque_size_function(psa_key_type_t key_type, size_t key_bits);
#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_S4XX_OPAQUE_KEY_GENERATION_H */
