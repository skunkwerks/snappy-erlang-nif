# snappy-erlang-nif

This is an Erlang NIF for Google's snappy fast compressor and decompressor.

Google snappy's official repository and bug tracking system is at:

* http://code.google.com/p/snappy/

Its source is included in this project.

# changelog

- tag `1.1.2` as tests pass against OTP-24
- tag `otp-24` compatibility
- switch build chain to [rebar3] and [enc] requiring OTP20 or newer
- tag `snappy-1.1.8`, also first version compatible with OTP23 (thanks @skaes)
- tag `snappy-1.1.3`
- add a changelog

[rebar3]: https://rebar3.org/
[enc]: https://github.com/davisp/erlang-native-compiler

# site

https://github.com/skunkwerks/snappy-erlang-nif

# credits

Software is built by a few people and maintained by many. Thank-you for
all your patches!


- Arne Ehrlich <Arne.Ehrlich@groknet.de>
- Bryan Chan <bryanpkc@gmail.com>
- Dave Cottlehuber <dch@skunkwerks.at>
- Filipe David Manana <fdmanana@apache.org>
- Joshua Scott <joshua.scott@gmail.com>
- Kelly McLaughlin <kelly@basho.com>
- Louis-Philippe Gauthier <lpgauth@gmail.com>
- Mikhail Uvarov <arcusfelis@gmail.com>
- Peter Membrey <peter@membrey.hk>
- Piotr Nosek <piotr.nosek@erlang-solutions.com>
- benoitc <bchesneau@gmail.com>
- @dch314
- glejeune <gregoire.lejeune@free.fr>
- Stefan Kaes <stkaes@gmail.com>

# performance tests

Snappy is much faster than zlib's deflate compression, specially for reasonably large amounts of
data. Here follow a few basic tests.

<pre>
Erlang R14B02 (erts-5.8.3) [source] [smp:2:2] [rq:2] [async-threads:0] [hipe] [kernel-poll:false]

Eshell V5.8.3  (abort with ^G)
1&gt; code:add_path("ebin").
true
2&gt; {ok, J} = file:read_file("../seatoncouch/doc_11k.json").
{ok,&lt;&lt;"{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUOl4APLS7GB9Nw"...&gt;&gt;}
3&gt;
3&gt; timer:tc(snappy, compress, [J]).
{4365,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
4&gt; timer:tc(snappy, compress, [J]).
{115,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
5&gt; timer:tc(snappy, compress, [J]).
{113,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
6&gt; timer:tc(snappy, compress, [J]).
{112,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
7&gt; timer:tc(snappy, compress, [J]).
{113,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
8&gt; timer:tc(snappy, compress, [J]).
{111,
 {ok,&lt;&lt;"úZðÔ{\n\"data3\":\"ColreUHAtn8iYvHIHw2ohiAuaXNGNX9WhlwANGDBYKYs6YEvHXgFXRkWuYoFyfLVqtjZNPedtukWRDXFz7VUO"...&gt;&gt;}}
9&gt;
9&gt; timer:tc(zlib, zip, [J]).
{1025,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
10&gt; timer:tc(zlib, zip, [J]).
{753,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
11&gt; timer:tc(zlib, zip, [J]).
{974,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
12&gt; timer:tc(zlib, zip, [J]).
{753,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
13&gt; timer:tc(zlib, zip, [J]).
{960,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
14&gt; timer:tc(zlib, zip, [J]).
{769,
 &lt;&lt;237,88,217,142,226,88,18,125,175,175,104,241,108,89,
   119,95,234,13,39,24,179,153,37,49,182,25,181,...&gt;&gt;}
15&gt;
15&gt; byte_size(element(2, snappy:compress(J))).
2846
16&gt; byte_size(zlib:zip(J)).
1858
17&gt;
17&gt; crypto:start().
ok
18&gt; Large = base64:encode(crypto:rand_bytes(100 * 1024)).
&lt;&lt;"72GMvPLuWJLJeYSlNm9oNkYkbjTeSBDgTrqamQ/zgj7hcUge1co6LvldJyitKPZkMPQGnrN98EyqSyWto3k7ShNgiNc05Gt4zdXSbTVSDzeID661DnJX"...&gt;&gt;
19&gt;
19&gt; timer:tc(snappy, compress, [Large]).
{365,
 {ok,&lt;&lt;216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...&gt;&gt;}}
20&gt; timer:tc(snappy, compress, [Large]).
{541,
 {ok,&lt;&lt;216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...&gt;&gt;}}
21&gt; timer:tc(snappy, compress, [Large]).
{455,
 {ok,&lt;&lt;216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...&gt;&gt;}}
22&gt; timer:tc(snappy, compress, [Large]).
{479,
 {ok,&lt;&lt;216,170,8,244,255,127,55,50,71,77,118,80,76,117,
       87,74,76,74,101,89,83,108,78,109,57,...&gt;&gt;}}
23&gt;
23&gt; timer:tc(zlib, zip, [Large]).
{14666,
 &lt;&lt;20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...&gt;&gt;}
24&gt; timer:tc(zlib, zip, [Large]).
{19716,
 &lt;&lt;20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...&gt;&gt;}
25&gt; timer:tc(zlib, zip, [Large]).
{14561,
 &lt;&lt;20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...&gt;&gt;}
26&gt; timer:tc(zlib, zip, [Large]).
{21683,
 &lt;&lt;20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...&gt;&gt;}
27&gt; timer:tc(zlib, zip, [Large]).
{11575,
 &lt;&lt;20,155,181,118,195,64,20,5,63,72,133,152,74,49,147,197,
   234,196,204,236,175,143,115,210,164,112,188,...&gt;&gt;}
28&gt;
28&gt; byte_size(element(2, snappy:compress(Large))).
136554
29&gt; byte_size(zlib:zip(Large)).
103440
30&gt;
</pre>
