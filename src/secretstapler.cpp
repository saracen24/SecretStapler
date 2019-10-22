#include "secretstapler.hpp"

#include <botan/auto_rng.h>
#include <botan/cipher_mode.h>
#include <botan/hex.h>

#include <fstream>

using namespace std;

namespace ss {

static const string_view kAlgorithm = "AES-128/CBC/PKCS7";

void generate(Botan::secure_vector<uint8_t> &key,
              Botan::secure_vector<uint8_t> &iv) {
  unique_ptr<Botan::Cipher_Mode> cipher =
      Botan::Cipher_Mode::create(kAlgorithm.data(), Botan::ENCRYPTION);

  Botan::AutoSeeded_RNG rng;
  key = rng.random_vec(cipher->default_nonce_length());
  iv = rng.random_vec(cipher->default_nonce_length());
}

void xcrypt(Botan::secure_vector<uint8_t> &barray,
            const Botan::secure_vector<uint8_t> &key,
            const Botan::secure_vector<uint8_t> &iv,
            Botan::Cipher_Dir direction) {
  unique_ptr<Botan::Cipher_Mode> cipher =
      Botan::Cipher_Mode::create(kAlgorithm.data(), direction);

  cipher->set_key(key);
  cipher->start(iv);
  cipher->finish(barray);
}

filesystem::path xgenerate(const filesystem::path &file) {
  if (filesystem::is_directory(file) ||
      !filesystem::exists(filesystem::absolute(file).parent_path()))
    return filesystem::path();

  Botan::secure_vector<uint8_t> key;
  Botan::secure_vector<uint8_t> iv;
  generate(key, iv);

  ofstream output(filesystem::absolute(file), ios::app);
  output << "{\"key\":\"" << Botan::hex_encode(key) << "\",\"iv\":\""
         << Botan::hex_encode(iv) << "\"}" << endl;
  output.close();

  return filesystem::absolute(file);
}

filesystem::path xencrypt(const filesystem::path &file, string_view key,
                          string_view iv) {
  if (!filesystem::exists(file) || filesystem::is_directory(file))
    return filesystem::path();

  ifstream input(file, ios::binary);
  if (!input.is_open()) return filesystem::path();
  Botan::secure_vector<uint8_t> barray(
      {(istreambuf_iterator<char>(input)), istreambuf_iterator<char>()});
  input.close();

  xcrypt(barray, Botan::hex_decode_locked(key.data()),
         Botan::hex_decode_locked(iv.data()), Botan::ENCRYPTION);

  filesystem::path result = filesystem::absolute(file.string().append(".enc"));
  ofstream output(result, ios::binary | ios::trunc);
  output << Botan::hex_encode(barray);
  output.close();

  return result;
}

filesystem::path xdecrypt(const filesystem::path &file, string_view key,
                          string_view iv) {
  if (!filesystem::exists(file) || filesystem::is_directory(file))
    return filesystem::path();

  ifstream input(file, ios::binary);
  if (!input.is_open()) return filesystem::path();
  Botan::secure_vector<uint8_t> barray = Botan::hex_decode_locked(
      {(istreambuf_iterator<char>(input)), istreambuf_iterator<char>()});
  input.close();

  xcrypt(barray, Botan::hex_decode_locked(key.data()),
         Botan::hex_decode_locked(iv.data()), Botan::DECRYPTION);

  filesystem::path result = filesystem::absolute(file.string().append(".dec"));
  ofstream output(result, ios::binary | ios::trunc);
  output << string(barray.begin(), barray.end());
  output.close();

  return result;
}

}  // namespace ss
