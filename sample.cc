#include <cassert>
#include <iostream>
#include "warp.hpp"

int main() {

    // 1) Simple interpolation usage:
    //    - Use `$(symbol)` macro to create or update a symbol.
    //    - Use `$$(string)` macro to translate all symbols into a string.
    //    - `$symbols` are valid until they're destroyed (past end of scope).

    {
        $(WORLD) = "world";
        assert( $$("Hello $WORLD") == "Hello world" );
    }
    assert( $$("Hello $WORLD") == "Hello $WORLD" );

    // 2) Valid $symbols are replaced, everything else is quoted.

    $(PLAYER_1) = "Mark";
    $(PLAYER_2) = "Karl";

    assert( $$("$PLAYER_1 and $PLAYER_2 logged in") == "Mark and Karl logged in");
    assert( $$("$PLAYER_3 logged out") == "$PLAYER_3 logged out");

    // 3) You can reassign and update symbols as many times as needed.

    $(PLAYER_1) = "Mike";
    $(PLAYER_2) = "John";
    assert( $$("$PLAYER_1 and $PLAYER_2 logged in") == "Mike and John logged in");

    // 4) Composition and symbol chaining is supported through dynamic lookups.

    $(HEY) = "Hello stranger";
    $(GREETING) = "$HEY! How are you?";
    assert( $$("$GREETING") == "Hello stranger! How are you?" );

    // 5) However, recursive symbols are quoted to avoid recursive locks.

    $(LOOPBACK) = "$LOOPBACK is unsafe, and quoted";
    assert( $$("$LOOPBACK") == "$LOOPBACK" );

    // 6) Symbol hot-swapping is supported as well.

    $(HEY) = "Hey $PLAYER_1 and $PLAYER_2";
    assert( $$("$GREETING") == "Hey Mike and John! How are you?" );

    // 7) Symbols are stringgs, and can hold values of many different types.

    $(name) = "John Doe";   // strings
    $(flag) = true;         // booleans
    $(letter) = 'a';        // characters
    $(items) = 100;         // integers
    $(price) = 99.95f;      // floats
    $(pi) = 3.141592;       // doubles

    // 8) Cast symbols to other types by using these additional macros.

    assert( $bool(flag) == true );
    assert( $char(letter) == 'a' );
    assert( $int(items) * 2 == 200 );
    assert( $string(name) + $string(name) == "John DoeJohn Doe" );
    assert( $float(price) * $double(pi) > 300 );

    // 9) Casting to custom types is supported as well, by using $cast(type,symbol)

    typedef int my_custom_type;
    my_custom_type currency = $cast(my_custom_type, price);
    assert( currency == 99 );

    //

    std::cout << "All ok." << std::endl;
}
