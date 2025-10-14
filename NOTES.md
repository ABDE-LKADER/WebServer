400 Bad Request = For Any Problem In The Request;
-----------------------------------------------------------------------
405 Method Not Allowed = Location Has Only GET And The Method Is POST;
-----------------------------------------------------------------------
414 Request-URI Too Long = line/target too big;
-----------------------------------------------------------------------
501 Not Implemented — unsupported method;
-----------------------------------------------------------------------
505 HTTP Version Not Supported — wrong HTTP version;
-----------------------------------------------------------------------


## HTTP/1.0:
    - Reserved (as delimiters only): ; / ? : @ = &
    - Percent-encodings: % HEX HEX
    - Unsafe / disallowed in URLs (must be percent-encoded): space, #, <, >, ", {, }, |, \, ^, ~, [, ], `, plus all control characters (0x00–0x1F and 0x7F) and non-ASCII.

+ Normalize dot-segments: Reject Traversal.
+ Reject NULL Injection.