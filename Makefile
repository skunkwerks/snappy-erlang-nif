all: snappy eunit

snappy:
	./rebar compile

eunit:
	./rebar eunit

check: eunit

clean:
	./rebar clean
	rm -fr priv ebin

