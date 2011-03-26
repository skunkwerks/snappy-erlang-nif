# snappy-erlang-nif

This is an Erlang NIF for Google's snappy fast compressor and decompressor.

Google snappy's official repository and bug tracking system is at:

* http://code.google.com/p/snappy/

Its source is included in this project.


# site

https://github.com/fdmanana/snappy-erlang-nif


# performance tests

Snappy is much faster than zlib's deflate compression, specially for reasonably large amounts of
data. Here are a few basic tests.

Erlang R14B02 (erts-5.8.3) [source] [smp:2:2] [rq:2] [async-threads:0] [hipe] [kernel-poll:false]

Eshell V5.8.3  (abort with ^G)
1> code:add_path("ebin").
true
2> {ok, J} = file:read_file("../seatoncouch/doc_11k.json").
{ok,<<"{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUOl4APLS7GB9Nw"...>>}
3>
3> timer:tc(snappy, compress, [J]).
{4365,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
4> timer:tc(snappy, compress, [J]).
{115,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
5> timer:tc(snappy, compress, [J]).
{113,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
6> timer:tc(snappy, compress, [J]).
{112,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
7> timer:tc(snappy, compress, [J]).
{113,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
8> timer:tc(snappy, compress, [J]).
{111,
 {ok,<<"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...>>}}
9>
9> timer:tc(zlib, zip, [J]).
{1025,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
10> timer:tc(zlib, zip, [J]).
{753,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
11> timer:tc(zlib, zip, [J]).
{974,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
12> timer:tc(zlib, zip, [J]).
{753,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
13> timer:tc(zlib, zip, [J]).
{960,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
14> timer:tc(zlib, zip, [J]).
{769,
 <<237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...>>}
15>
15> byte_size(element(2, snappy:compress(J))).
2846
16> byte_size(zlib:zip(J)).
1858
17>
17> crypto:start().
ok
18> Large = base64:encode(crypto:rand_bytes(100 * 1024)).
<<"72GMvPLuWJLJeYSlNm9oNkYkbjTeSBDgTrqamQ/zgj7hcUge1co6LvldJyitKPZkMPQGnrN98EyqSyWto3k7ShNgiNc05Gt4zdXSbTVSDzeID661DnJX"...>>
19>
19> timer:tc(snappy, compress, [Large]).
{365,
 {ok,<<216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...>>}}
20> timer:tc(snappy, compress, [Large]).
{541,
 {ok,<<216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...>>}}
21> timer:tc(snappy, compress, [Large]).
{455,
 {ok,<<216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...>>}}
22> timer:tc(snappy, compress, [Large]).
{479,
 {ok,<<216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...>>}}
23>
23> timer:tc(zlib, zip, [Large]).
{14666,
 <<20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...>>}
24> timer:tc(zlib, zip, [Large]).
{19716,
 <<20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...>>}
25> timer:tc(zlib, zip, [Large]).
{14561,
 <<20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...>>}
26> timer:tc(zlib, zip, [Large]).
{21683,
 <<20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...>>}
27> timer:tc(zlib, zip, [Large]).
{11575,
 <<20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...>>}
28>
28> byte_size(element(2, snappy:compress(Large))).
136554
29> byte_size(zlib:zip(Large)).
103440
30>
