var ws;

function initiateChatSession() {
	console.log("In initiateChatSession");
	if ("WebSocket" in window) {
		//Defining the serverEnd point of the websocket connection. 
		//var chatEndpoint = "ws://localhost:8080/Chat-1718/chat/";
		var chatEndpoint = "http://localhost:8080/chat-stw-c4/xatUser.xhtml";
		//document.getElementById("channelId");
		window.location = chatEndpoint + "?id=" + document.getElementById("xatForm:channelId").value;
		// Opening a web socket	connection	
		ws = new WebSocket(chatEndpoint);
		ws.onopen = function(evt) {onOpen(evt);};
		ws.onmessage = function(evt) {onMessage(evt);}; 
		ws.close = function(evt) { onClose(evt);};
		ws.onerror = function(evt) { onError(evt);};
	} else {
		// The browser doesn't support WebSocket
		alert("WebSocket NOT supported!");
	}
}
 
function onOpen(evt){
	console.log("On Open");
}

function onClose(evt){	
}

//Variacion con js nuestro para saber si recibe bien
function onMessage(evt){
	console.log("In onMessage");
	var msg = evt.data;	
	//Variacion aqui
	document,getElementById('xatForm:xatArea:outText').value=msg
}

/**
 * This function is called on a connection error.
 * @param evt the event that contains the error.
 */
function onError(evt){
	ws.close();
}

function sendChatMessage() {
  //TODO: set msg variable to the string to be sent via websockets
  //ws.send(msg);
	var msg = document.getElementById('xatForm:xatArea:inText').value
	ws.send(msg)
	console.log("Message sended: " + msg)
}

window.onload = function(){
	console.log("onload");
	initiateChatSession();};
