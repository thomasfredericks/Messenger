// CHANGE THE FOLLOWING TO THE VALUE IN YOUR ARDUINO IDE!!!!!!!!!!!!!
var ARDUINO_PORT = 'COM4'; 
//var ARDUINO_PORT = '/dev/tty.usbmodem1421';

var SERVER_PORT = 8080;

// https://github.com/voodootikigod/node-serialport
var SerialPort = require( 'serialport' );

// https://github.com/Worlize/WebSocket-Node
var WebSocketServer = require( 'websocket' ).server;

// HTTP server that ships with Node.js
var Http = require( 'http' );

var serial;


// List ports and connect to port if it exists
SerialPort.list( function( err, ports ) {
	console.log("ARDUINO > Available ports: ");
    var found = false;
    
	ports.forEach( function(port) {
		console.log( port.comName + " - " + port.manufacturer );
        if ( port.comName == ARDUINO_PORT ) found = true;
    } );
    
    if ( found == false ) {
        console.log("ARDUINO > Could not find port "+ARDUINO_PORT);
        process.exit(1);
    }
    
    startArduino();
    
} );

var arduinoInCount = 0;
var arduinoInLast = "";

function startArduino() {
     // Connect to Arduino
    // Look for newline delimiter
    console.log("ARDUINO > Connecting to port: "+ARDUINO_PORT);
    serial = new SerialPort.SerialPort( ARDUINO_PORT, {parser: SerialPort.parsers.readline( '\n' ) 	} );
    
    // Serial data captured from Arduino
// Note that this happens at a sub-second rate
// You may want to adjust to fit your needs
serial.on( 'data', function( data ) {
    arduinoInCount++;
	arduinoInLast = data;
	// Send to all connected clients
	for( var c = 0; c < clients.length; c++ )
	{
		clients[c].sendUTF( data );
	}
} );
    
    logReceivedFromSerial();
    
}


function logReceivedFromSerial()
{
   if ( arduinoInCount  > 0 ) {
       console.log("ARDUINO > Sent "+arduinoInCount+" massage(s) in the last second.");
       console.log("ARDUINO > Last massage was: "+arduinoInLast);
       arduinoInCount = 0;
   }
   setTimeout(logReceivedFromSerial, 1000);
}


// Web Sockets start life as HTTP requests
var server = Http.createServer( function( request, response ) {
    // Process HTTP request
	// Just Web Sockets here so nothing to see here
	// Move along!
} );
server.listen( SERVER_PORT , function() {;} );
console.log("SERVER > Listening on port "+SERVER_PORT);

// Create Web Socket server
var socket = new WebSocketServer( {
    httpServer: server,
    fragmentOutgoingMessages: false
} );

var clients = [];

// Handle Web Socket requests from browser


var clientInCount = 0;
var clientInLast = "";

function logReceivedFromClient()
{
   if ( clientInCount  > 0 ) {
       console.log("CLIENTS > Sent "+clientInCount+" massage(s) in the last second.");
       console.log("CLIENTS > Last massage was: "+clientInLast);
       clientInCount = 0;
   }
   setTimeout(logReceivedFromClient, 1000);
}
logReceivedFromClient();

// Handle Web Socket requests from browser
socket.on( 'request', function( request ) {
    var connection = request.accept( null, request.origin );

	// Keep track of the clients
	clients.push( connection );
	console.log( 'SERVER > New Web Socket connection' );

	// Handle incoming client messages
	// Send messages to the Arduino	
	connection.on( 'message', function( message ) {
        clientInCount++;
        clientInLast = message.utf8Data;
		serial.write( message.utf8Data );
	} );

	// Close the connection
	// Update client list
    connection.on( 'close', function( connection ) {
		var index = clients.indexOf( connection );
        
		// Remove client from list
		if( index !== -1 ) 
		{
            clients.splice( index, 1 );
        }		
	} );
} );
