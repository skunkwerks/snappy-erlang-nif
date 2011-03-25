/**
 * Copyright 2011,  Filipe David Manana  <fdmanana@apache.org>
 * Web:  http://github.com/fdmanana/snappy-erlang-nif
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 **/

#include <iostream>
#include <cstring>

#include "erl_nif_compat.h"
#include "google-snappy/snappy.h"


extern "C" {

#ifdef OTP_R13B03
    ERL_NIF_TERM snappy_compress(ErlNifEnv* env, ERL_NIF_TERM binary) {
#else
    ERL_NIF_TERM snappy_compress(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ERL_NIF_TERM binary = argv[0];
#endif
        ErlNifBinary input;
        ErlNifBinary retBin;
        std::string output;

        if (!enif_inspect_binary(env, binary, &input)) {
            return enif_make_badarg(env);
        }

        snappy::Compress(reinterpret_cast<const char *>(input.data),
                         input.size, &output);

        if (!enif_alloc_binary_compat(env, output.length(), &retBin)) {
            return enif_make_tuple(env, 2,
                                   enif_make_atom(env, "error"),
                                   enif_make_atom(env, "insufficient_memory"));
        }

        memcpy(retBin.data, output.data(), output.length());

        return enif_make_tuple(env, 2,
                               enif_make_atom(env, "ok"),
                               enif_make_binary(env, &retBin));
    }


#ifdef OTP_R13B03
    ERL_NIF_TERM snappy_decompress(ErlNifEnv* env, ERL_NIF_TERM binary) {
#else
    ERL_NIF_TERM snappy_decompress(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ERL_NIF_TERM binary = argv[0];
#endif
        ErlNifBinary input;

        if (!enif_inspect_binary(env, binary, &input)) {
            return enif_make_badarg(env);
        }

        ErlNifBinary retBin;
        std::string output;

        snappy::Uncompress(reinterpret_cast<const char *>(input.data),
                           input.size, &output);

        if (!enif_alloc_binary_compat(env, output.length(), &retBin)) {
            return enif_make_tuple(env, 2,
                                   enif_make_atom(env, "error"),
                                   enif_make_atom(env, "insufficient_memory"));
        }

        memcpy(retBin.data, output.data(), output.length());

        return enif_make_tuple(env, 2,
                               enif_make_atom(env, "ok"),
                               enif_make_binary(env, &retBin));
    }


#ifdef OTP_R13B03
    ERL_NIF_TERM snappy_get_uncompressed_length(ErlNifEnv* env, ERL_NIF_TERM binary) {
#else
    ERL_NIF_TERM snappy_get_uncompressed_length(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ERL_NIF_TERM binary = argv[0];
#endif
        ErlNifBinary input;

        if (!enif_inspect_binary(env, binary, &input)) {
            return enif_make_badarg(env);
        }

        size_t len = -1;
        bool isCompressed = snappy::GetUncompressedLength(
            reinterpret_cast<const char *>(input.data), input.size, &len);

        if (isCompressed) {
            return enif_make_tuple(env, 2,
                                   enif_make_atom(env, "ok"),
                                   enif_make_ulong(env, len));
        } else {
            return enif_make_tuple(env, 2,
                                   enif_make_atom(env, "error"),
                                   enif_make_atom(env, "not_compressed_data"));
        }
    }


#ifdef OTP_R13B03
    ERL_NIF_TERM snappy_is_valid_compressed_buffer(ErlNifEnv* env, ERL_NIF_TERM binary) {
#else
    ERL_NIF_TERM snappy_is_valid_compressed_buffer(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ERL_NIF_TERM binary = argv[0];
#endif
        ErlNifBinary input;

        if (!enif_inspect_binary(env, binary, &input)) {
            return enif_make_badarg(env);
        }

        bool valid = snappy::IsValidCompressedBuffer(
            reinterpret_cast<const char *>(input.data), input.size);

        if (valid) {
            return enif_make_atom(env, "true");
        } else {
            return enif_make_atom(env, "false");
        }
    }



    int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM info) {
        return 0;
    }


    int on_reload(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM info) {
        return 0;
    }

    int on_upgrade(ErlNifEnv* env, void** priv_data, void** old_data, ERL_NIF_TERM info) {
        return 0;
    }


}


static ErlNifFunc nif_functions[] = {
    {"compress", 1, snappy_compress},
    {"decompress", 1, snappy_decompress},
    {"get_uncompressed_length", 1, snappy_get_uncompressed_length},
    {"is_valid_compressed_buffer", 1, snappy_is_valid_compressed_buffer}
};

ERL_NIF_INIT(snappy, nif_functions, &on_load, &on_reload, &on_upgrade, NULL);
