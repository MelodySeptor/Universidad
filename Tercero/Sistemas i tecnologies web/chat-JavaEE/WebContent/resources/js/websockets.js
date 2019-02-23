var ws;

function initiateChatSession() {
	console.log("In initiateChatSession");
	if ("WebSocket" in window) {
		//Defining the serverEnd point of the websocket connection. 
		//var chatEndpoint = "ws://localhost:8080/Chat-1718/chat/";
		//var chatEndpoint = "http://localhost:8080/Chat-stw-c4_v4/xatUser.xhtml";
		var chatEndpointWS = "ws://localhost:8080/Chat-stw-c4_v4/chat/" + document.getElementById("channelId").value;
		//document.getElementById("channelId");
		//window.location = chatEndpointWS // + "?id=" + document.getElementById("channelId").value;
		// Opening a web socket	connection	
		ws = new WebSocket(chatEndpointWS);
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

function onMessage(evt){
	console.log("In onMessage");
	var msg = evt.data;	
	document.getElementById("outText").value = msg;
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
	var msg = document.getElementById('inText').value
	ws.send(msg)
	console.log("Message sended: " + msg)
}

function fakeClick() {
	setInterval(function run() {document.getElementById("hidd").click(); setTimeOut(run, 100)}, 2000);
	
}

fakeClick();
window.onload = function(){
	console.log("onload");
	initiateChatSession();};

