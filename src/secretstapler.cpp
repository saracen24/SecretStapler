#include "secretstapler.hpp"

#include <botan/auto_rng.h>
#include <botan/cipher_mode.h>
#include <botan/hex.h>

#include <fstream>

using namespace std;

namespace ss {

static const string_view kAlgorithm = "AES-128/CBC/PKCS7";

filesystem::path generate(const filesystem::path &file) {
  if (filesystem::is_directory(file) ||
      !filesystem::exists(filesystem::absolute(file).parent_path()))
    return filesystem::path();

  unique_ptr<Botan::Cipher_Mode> cipher =
      Botan::Cipher_Mode::create(kAlgorithm.data(), Botan::ENCRYPTION);

  Botan::AutoSeeded_RNG rng;
  Botan::secure_vector<uint8_t> key =
      rng.random_vec(cipher->default_nonce_length());
  Botan::secure_vector<uint8_t> iv =
      rng.random_vec(cipher->default_nonce_length());

  filesystem::path result = filesystem::absolute(file);
  ofstream output(result, ios::app);
  output << "{\"key\":\"" << Botan::hex_encode(key) << "\",\"iv\":\""
         << Botan::hex_encode(iv) << "\"}" << endl;
  output.close();

  return result;
}

filesystem::path xcrypt(const filesystem::path &file, string_view key,
                        string_view iv, string_view direction) {
  if (!filesystem::exists(file) || filesystem::is_directory(file))
    return filesystem::path();

  ifstream input(file, ios::binary);
  if (!input.is_open()) return filesystem::path();
  Botan::secure_vector<uint8_t> buffer(
      {(istreambuf_iterator<char>(input)), istreambuf_iterator<char>()});
  input.close();

  Botan::Cipher_Dir cdir;
  filesystem::path result;
  if (direction == "encrypt") {
    cdir = Botan::ENCRYPTION;
    result = filesystem::absolute(file.string().append(".enc"));
  } else /*if (direction == "decrypt")*/ {
    cdir = Botan::DECRYPTION;
    result = filesystem::absolute(file.string().append(".dec"));
  }

  unique_ptr<Botan::Cipher_Mode> cipher =
      Botan::Cipher_Mode::create(kAlgorithm.data(), cdir);

  cipher->set_key(Botan::hex_decode_locked(key.data()));
  cipher->start(Botan::hex_decode_locked(iv.data()));
  cipher->finish(buffer);

  ofstream output(result, ios::binary | ios::trunc);
  output.write(reinterpret_cast<const char *>(buffer.data()),
               static_cast<streamsize>(buffer.size()));
  output.close();

  return result;
}

}  // namespace ss
