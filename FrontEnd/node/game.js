const pipe=require('child_process');
const fs=require('fs');

console.log(__dirname);

let process=pipe.execFile(`${__dirname}/exe/test.exe`);

process.stdout.on('data',(data)=>{
    console.log(data);
    fs.writeFile(`${__dirname}/exe/stdout.txt`,data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,''),()=>{});
})

console.log(`game loaded!`);

setInterval(()=>{
    fs.readFile(`${__dirname}/exe/stdin.txt`,'utf-8',(err,data)=>{
        if(err) return;
        console.log(`stdin:${data.toString()}`)
        data.toString().replaceAll(/[\u0000-\u001F\u007F-\u009F]/g,'').split(' ').forEach((command)=>{
            process.stdin.write(command);
            process.stdin.write('\n');
            console.log(`stdin!${command}`);
        })
        fs.unlink(`${__dirname}/exe/stdin.txt`,()=>{});
    })
},100);