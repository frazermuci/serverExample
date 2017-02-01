var connection = new WebSocket('ws://127.0.0.1:21234', ['soap', 'xmpp']);
//var connection = new WebSocket('ws://html5rocks.websocket.org/echo', ['soap', 'xmpp']);
connection.onopen = function () {
	connection.send("0");
  // Send the message 'Ping' to the server
};

// Log errors
connection.onerror = function (error) {
  console.log('WebSocket Error ' + error);
};

// Log messages from the server
connection.onmessage = function (e) {
  console.log('Server Score: ' + e.data);
  document.getElementById("ButtonPress").value = e.data;
};


function sendIt()
{
	connection.send(document.getElementById("ButtonPress").value)
}

function done()
{
	connection.send("DONE");
}
