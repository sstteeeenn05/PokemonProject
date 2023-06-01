const Express=require('express')
const App=Express();
const SocketServer=require('ws').Server;
const Pipe=require('child_process');

App.use(Express.static(__dirname+"\\www",{index:"index.html"}));
const PORT=1212;
const server=App.listen(PORT);

const wss=new SocketServer({server});