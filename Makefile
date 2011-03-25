all: google-snappy snappy

snappy:
	mkdir -p ebin
	./rebar compile

google-snappy:
	./support/build-google-snappy.sh

test: snappy
	./rebar eunit

clean:
	./rebar clean
	./support/clean-google-snappy.sh
	rm -fr priv ebin

