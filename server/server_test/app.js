var net = require('net');
function ConnectServer() {
    var client = new net.Socket();
    client.connect(9595, "192.168.1.5", function () {
        console.log('connected to: 192.168.1.4');
        var buf = new Buffer(8);
        var str = "asdfsadfsadf";
        buf.writeInt32LE(str.length + 4);
        buf.writeInt32LE(str.length,4);
        client.write(buf);
        client.write(new Buffer(str));
        

    });
    client.on('data', function (data) {
        console.log(data.toString('utf8'));
        ConnectServer();
    });
    client.on('close', function () {
        console.log("client close");
    });
}
ConnectServer();
//setInterval(ConnectServer, 1);
