#!/usr/bin/env node

'use strict';

// Library
const express = require('express');
const http = require('http');
const url = require('url');
const WebSocket = require('ws');
const fs = require('fs');

// Create the web server
const app = express();
const server = http.createServer(app);


/***** Webpage **********************************************/

app.use(express.static(__dirname));

app.get('/', function (req, res) {
  res.sendFile('./index.html');
});

app.listen(8080, function () {
  console.log('Webpage on 8080');
});


/***** WebSocket *******************************************/

const wss = new WebSocket.Server({'server':server, 'clientTracking':true});

wss.on('connection', function connection (ws) {
  ws.on('message', function incoming (message) {
    console.log('Received: %s', message);
    ws.send('ACK')
  });

  console.log('New Connection')
  ws.send('Welcome');
});

server.listen(8181, function listening () {
  console.log('WebSocket on %d', server.address().port);
});


/***** UART Stream *****************************************/

const uart = fs.createReadStream('/dev/ttyACM0')

// const log = fs.createWriteStream('logs.txt')
// uart.pipe(log)

uart.setEncoding('utf8');

uart.on('readable', function () {
  var data = uart.read();
  // console.log(data);
  for (let cli of wss.clients) {
    cli.send(data);
  }
});
