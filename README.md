# SecretStapler
AES-128/CBC/PKCS7 encryption.

## Full build pipeline
Linux (Ninja)
```bash
./build_ninja.sh
```
Windows (Ninja)
```cmd
build_ninja.cmd
```
Windows (Visual Studio 15 2017 Win64)
```cmd
build_v141_x64.cmd
```

## Init submodules
```
git submodule update --init --recursive
```

### Dependencies
[`botan`](https://github.com/randombit/botan) - Crypto and TLS for Modern C++ (manual build required).

[`cxxopts`](https://github.com/jarro2783/cxxopts) - Lightweight C++ command line option parser.
