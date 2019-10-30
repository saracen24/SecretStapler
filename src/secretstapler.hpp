#pragma once

#include <filesystem>
#include <string_view>

namespace ss {

/*!
 * \brief Generate cipher key and initialization vector.
 * \param[in] file Path to output file.
 * \return Output file.
 */
std::filesystem::path generate(const std::filesystem::path& file);
/*!
 * \brief Encrypt or decrypt file.
 * \param[in] file Path to input file.
 * \param key Cipher key.
 * \param iv Initialization vector.
 * \param direction Encryption or decryption direction.
 * \return Output file.
 */
std::filesystem::path xcrypt(const std::filesystem::path& file,
                             std::string_view key, std::string_view iv,
                             std::string_view direction);

}  // namespace ss
