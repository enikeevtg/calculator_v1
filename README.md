# console calculator

It is the first step to smart_calc project with UI.

Dijkstra's algorithm was used for converting infix expression to Reverse Polish notation.

Stack and Queue structures were used in project.

Usage:

+ executable file building:

      $ make build

+ launch:

      $ make calc

  or

      $ ./calculator

Calculator supports basic math operations (+-*/%^) and math functions:

+ cos
+ sin
+ tan
+ acos
+ asin
+ atan
+ sqrt
+ ln
+ log

Examples:

    $ make calc
    sqrt(4)
    2
    
    $ make calc
    sin(3.1415)
    0.000093
    
    $ make calc
    (1 + 2) * 3 / sin1 + cos(2.1 / 14) % 8 + sqrt(2)
    12.109770

    $ make calc
    habracadabra
    error: UNDEFINED_TOKEN
