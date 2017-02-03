var connection = new WebSocket('ws://127.0.0.1:21234', ['soap', 'xmpp']);
//var connection = new WebSocket('ws://html5rocks.websocket.org/echo', ['soap', 'xmpp']);
/*connection.onopen = function () {
	connection.send("0:0");
  // Send the message 'Ping' to the server
};*/

// Log errors
connection.onerror = function (error) {
  console.log('WebSocket Error ' + error);
};

// Log messages from the server
connection.onmessage = function (e) {
  console.log('Server Score: ' + e.data);
  var array = e.data.split(":");
  document.getElementById("ButtonPress").value = array[0];
  document.getElementById("ButtonPress2").value = array[1];
};


function sendIt(inc)
{
	connection.send(inc);
}

function done()
{
	connection.send("DONE");
}
