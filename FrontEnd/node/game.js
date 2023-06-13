const pipe=require('child_process');
const fs=require('fs');

let process=pipe.execFile(`${__dirname}/exe/test.exe`);

let canOutput=false;

process.stdout.on('data',(data)=>{
    if(canOutput){
        console.log(`stdout:${data.toString()}`);
        fs.writeFile(`${__dirname}/exe/stdout.txt`,data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,''),()=>{});
    }
    canOutput=false;
})

console.log(`game loaded!`);

setInterval(()=>{
    fs.readFile(`${__dirname}/exe/stdin.txt`,'utf-8',(err,data)=>{
        if(err) return;
        canOutput=true;
        data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,'').split(' ').forEach((command)=>{
            process.stdin.write(command);
            process.stdin.write('\n');
            console.log(`stdin:${command}`);
        })
        fs.unlink(`${__dirname}/exe/stdin.txt`,()=>{});
    })
},100);