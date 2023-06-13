const pipe=require('child_process');
const fs=require('fs');

let game=pipe.execFile(`${__dirname}/exe/test.exe`);

let canOutput=false;

game.stdout.on('data',(data)=>{
    if(canOutput){
        console.log(`stdout:${data.toString()}`);
        fs.writeFile(`${__dirname}/exe/stdout.txt`,data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,''),()=>{});
    }
    canOutput=false;
})

console.log(`game loaded!`);

let interval=setInterval(()=>{
    fs.readFile(`${__dirname}/exe/stdin.txt`,'utf-8',(err,data)=>{
        if(err) return;
        fs.unlink(`${__dirname}/exe/stdin.txt`,()=>{});
        canOutput=true;
        data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,'').split(' ').forEach((command)=>{
            console.log(`stdin:${command}`);
            if(command=='kill'){
                game.stdin.write("\x03");
                clearInterval(interval);
                process.exit();
            }
            game.stdin.write(command);
            game.stdin.write('\n');
        })
    })
},100);