all: snappy eunit

snappy:
	./support/build-google-snappy.sh
	./rebar compile

eunit:
	./rebar eunit

check: eunit

clean:
	./support/clean-google-snappy.sh
	./rebar clean
	rm -fr priv ebin

