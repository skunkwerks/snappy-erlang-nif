all: snappy eunit

snappy:
	./rebar3 compile

eunit:
	./rebar3 eunit

check: eunit

clean:
	./rebar3 clean
	rm -fr priv ebin

