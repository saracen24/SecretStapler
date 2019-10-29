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
 * \brief Encrypt file.
 * \param[in] file Path to input file.
 * \param key Cipher key.
 * \param iv Initialization vector.
 * \return Output file.
 */
std::filesystem::path xencrypt(const std::filesystem::path& file,
                               std::string_view key, std::string_view iv);
/*!
 * \brief Decrypt file.
 * \param[in] file Path to input file.
 * \param key Cipher key.
 * \param iv Initialization vector.
 * \return Output file.
 */
std::filesystem::path xdecrypt(const std::filesystem::path& file,
                               std::string_view key, std::string_view iv);

}  // namespace ss
