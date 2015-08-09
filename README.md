# Warp :recycle: <a href="https://travis-ci.org/r-lyeh/warp"><img src="https://api.travis-ci.org/r-lyeh/warp.svg?branch=master" align="right" /></a>
- Warp is a handy string interpolator (C++11).
- Warp is cross-platform, lightweight and header-only.
- Warp is zlib/libpng licensed.

## Quick tutorial

- Simple interpolation usage:
  - Use `$(symbol)` macro to create or update a symbol.
  - Use `$$(string)` macro to translate all symbols into a string.
  - `$symbols` are valid until they're destroyed (past end of scope).
```c++
{
    $(WORLD) = "world";
    assert( $$("Hello $WORLD") == "Hello world" );
}
assert( $$("Hello $WORLD") == "Hello $WORLD" );
```

- Valid $symbols are replaced, everything else is quoted.
```c++
$(PLAYER_1) = "Mark";
$(PLAYER_2) = "Karl";

assert( $$("$PLAYER_1 and $PLAYER_2 logged in") == "Mark and Karl logged in");
assert( $$("$PLAYER_3 logged out") == "$PLAYER_3 logged out");
```

- You can reassign and update symbols as many times as needed.
```c++
$(PLAYER_1) = "Mike";
$(PLAYER_2) = "John";
assert( $$("$PLAYER_1 and $PLAYER_2 logged in") == "Mike and John logged in");
```

- Composition and symbol chaining is supported through dynamic lookups.
```c++
$(HEY) = "Hello stranger";
$(GREETING) = "$HEY! How are you?";
assert( $$("$GREETING") == "Hello stranger! How are you?" );
```

- However, recursive symbols are quoted to avoid recursive locks.
```c++
$(LOOPBACK) = "$LOOPBACK is unsafe, hence quoted";
assert( $$("$LOOPBACK") == "$LOOPBACK" );
```

- Symbol hot-swapping is supported as well.
```c++
$(HEY) = "Hey $PLAYER_1 and $PLAYER_2";
assert( $$("$GREETING") == "Hey Mike and John! How are you?" );
```

- Symbols are stringgs, and can hold values of many different types.
```c++
$(name) = "John Doe";   // strings
$(flag) = true;         // booleans
$(letter) = 'a';        // characters
$(items) = 100;         // integers
$(price) = 99.95f;      // floats
$(pi) = 3.141592;       // doubles
```

- Cast symbols to other types by using these additional macros.
```c++
assert( $bool(flag) == true );
assert( $char(letter) == 'a' );
assert( $int(items) * 2 == 200 );
assert( $string(name) + $string(name) == "John DoeJohn Doe" );
assert( $float(price) * $double(pi) > 300 );
```

- Casting to custom types is supported as well, by using $cast(type,symbol)
```c++
typedef int my_custom_type;
my_custom_type currency = $cast(my_custom_type, price);
assert( currency == 99 );
```

## Changelog
- v0.0.0 (2015/08/09)
  - Initial version
