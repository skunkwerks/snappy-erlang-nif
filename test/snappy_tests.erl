%% Copyright 2011,  Filipe David Manana  <fdmanana@apache.org>
%% Web:  http://github.com/fdmanana/snappy-erlang-nif
%%
%% Licensed under the Apache License, Version 2.0 (the "License"); you may not
%% use this file except in compliance with the License. You may obtain a copy of
%% the License at
%%
%%  http://www.apache.org/licenses/LICENSE-2.0
%%
%% Unless required by applicable law or agreed to in writing, software
%% distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
%% WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
%% License for the specific language governing permissions and limitations under
%% the License.

-module(snappy_tests).
-include_lib("eunit/include/eunit.hrl").


compress_test_() ->
    {timeout, 60, [fun run_compress_test/0]}.

uncompress_test_() ->
    {timeout, 60, [fun run_uncompress_test/0]}.


run_compress_test() ->
    Data = iolist_to_binary(
        lists:duplicate(11, <<"words that go unspoken, deeds that go undone">>)),
    Result = snappy:compress(Data),
    ?assertMatch({ok, _}, Result),
    {ok, Compressed} = Result,

    ?assertEqual(true, byte_size(Compressed) < byte_size(Data)),

    ?assertEqual(true, snappy:is_valid_compressed_buffer(Compressed)),
    ?assertEqual(false, snappy:is_valid_compressed_buffer(Data)),
    ?assertEqual(false, snappy:is_valid_compressed_buffer(<<"foobar123">>)),

    ?assertEqual({ok, byte_size(Data)}, snappy:get_uncompressed_length(Compressed)),
    ok.


run_uncompress_test() ->
    Data = iolist_to_binary(
        lists:duplicate(11, <<"words that go unspoken, deeds that go undone">>)),
    Result = snappy:compress(Data),
    ?assertMatch({ok, _}, Result),
    {ok, Compressed} = Result,

    ?assertEqual({ok, Data}, snappy:decompress(Compressed)),
    ok.
