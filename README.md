Messenger
=================

Simple ASCII messages for Wiring and Arduino

See the included documentation.

Messenger is a "toolkit" that facilitates the parsing of ASCII messages. Messenger buffers characters until it receives a carriage return (CR). It then considers the message complete and available. The message is split into many elements as defined by a separator. The default separator is the space character, but can be any character other than NULL, LF or CR.