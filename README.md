Messenger
=================

Simple ASCII messages for Wiring and Arduino

Messenger is a "toolkit" that facilitates the parsing of ASCII messages. Messenger buffers characters until it receives a new line character ('\n',10,NL). It then considers the message complete and available. The message is split into many elements as defined by a separator. The default separator is the space character (' '," ",32,SPACE), but can be any character other than null, new line or carriage return.

Please note that the default end of message character was a carriage return ('\r',13,CR). Since Arduino 1.6 this has changed to the new line character ('\n',10,NL). 

The full documentation is in the "Documentation" folder.
